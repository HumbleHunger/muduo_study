// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "muduo/base/Thread.h"
#include "muduo/base/CurrentThread.h"
#include "muduo/base/Exception.h"
#include "muduo/base/Logging.h"

#include <type_traits>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace muduo
{
namespace detail
{

pid_t gettid()
{
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

void afterFork()
{
  muduo::CurrentThread::t_cachedTid = 0;
  muduo::CurrentThread::t_threadName = "main";
  CurrentThread::tid();
  // no need to call pthread_atfork(NULL, NULL, &afterFork);
}

class ThreadNameInitializer
{
 public:
  ThreadNameInitializer()
  {
    muduo::CurrentThread::t_threadName = "main";
    CurrentThread::tid();
    pthread_atfork(NULL, NULL, &afterFork);
  }
};

ThreadNameInitializer init;
//线程信息类
struct ThreadData
{
  typedef muduo::Thread::ThreadFunc ThreadFunc;
  //线程回调函数
  ThreadFunc func_;
  //线程名
  string name_;
  //指向线程真实ID
  pid_t* tid_;
  //线程任务数
  CountDownLatch* latch_;

  ThreadData(ThreadFunc func,
             const string& name,
             pid_t* tid,
             CountDownLatch* latch)
    : func_(std::move(func)),
      name_(name),
      tid_(tid),
      latch_(latch)
  { }

  void runInThread()
  {
    //获取初始化tid
    *tid_ = muduo::CurrentThread::tid();
    //重置 不再修改tid
    tid_ = NULL;
    //阀门计数减一 条件变量变为真 通知主线程继续执行
    latch_->countDown();
    latch_ = NULL;
    //设置线程局部数据：线程名
    muduo::CurrentThread::t_threadName = name_.empty() ? "muduoThread" : name_.c_str();
    //在内核中设置当前线程名字
    ::prctl(PR_SET_NAME, muduo::CurrentThread::t_threadName);
    try
    {
      //调用回调函数
      func_();
      //调用完成将线程局部数据的线程名改为finished
      muduo::CurrentThread::t_threadName = "finished";
    }
    catch (const Exception& ex)
    {
      muduo::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
      abort();
    }
    catch (const std::exception& ex)
    {
      muduo::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      abort();
    }
    catch (...)
    {
      muduo::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
      throw; // rethrow
    }
  }
};
//线程入口函数
void* startThread(void* obj)
{
  //通过ThreadData：：runInThread 来调用注册的回调函数（任务函数）
  ThreadData* data = static_cast<ThreadData*>(obj);
  //执行
  data->runInThread();
  delete data;
  return NULL;
}

}  // namespace detail

void CurrentThread::cacheTid()
{
  if (t_cachedTid == 0)
  {
    t_cachedTid = detail::gettid();
    t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
  }
}

bool CurrentThread::isMainThread()
{
  return tid() == ::getpid();
}

void CurrentThread::sleepUsec(int64_t usec)
{
  struct timespec ts = { 0, 0 };
  ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
  ts.tv_nsec = static_cast<long>(usec % Timestamp::kMicroSecondsPerSecond * 1000);
  ::nanosleep(&ts, NULL);
}
//已创建的线程数目
AtomicInt32 Thread::numCreated_;

Thread::Thread(ThreadFunc func, const string& n)
  : started_(false),
    joined_(false),
    pthreadId_(0),
    tid_(0),
//使用右值引用
    func_(std::move(func)),
    name_(n),
    latch_(1)
{
  setDefaultName();
}

Thread::~Thread()
{
  if (started_ && !joined_)
  {
    pthread_detach(pthreadId_);
  }
}

void Thread::setDefaultName()
{
  //线程数加一
  int num = numCreated_.incrementAndGet();
  //设置默认线程名Thread+序号
  if (name_.empty())
  {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", num);
    name_ = buf;
  }
}

void Thread::start()
{
  //如果线程已经开始则中断程序
  assert(!started_);
  //将线程状态改为开始
  started_ = true;
  // FIXME: move(func_)
  //动态创建线程信息对象
  detail::ThreadData* data = new detail::ThreadData(func_, name_, &tid_, &latch_);
  //创建线程
  if (pthread_create(&pthreadId_, NULL, &detail::startThread, data))
  {
    //线程创建失败处理
    started_ = false;
    delete data; // or no delete?
    //日志输出
    LOG_SYSFATAL << "Failed in pthread_create";
  }
  else
  {
    //等待线程执行成功
    latch_.wait();
    assert(tid_ > 0);
  }
}

int Thread::join()
{
  assert(started_);
  assert(!joined_);
  joined_ = true;
  return pthread_join(pthreadId_, NULL);
}

}  // namespace muduo
