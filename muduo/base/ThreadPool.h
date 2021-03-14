// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_THREADPOOL_H
#define MUDUO_BASE_THREADPOOL_H

#include "muduo/base/Condition.h"
#include "muduo/base/Mutex.h"
#include "muduo/base/Thread.h"
#include "muduo/base/Types.h"

#include <deque>
#include <vector>

namespace muduo
{

class ThreadPool : noncopyable
{
 public:
 //Task为具体的任务接口
  typedef std::function<void ()> Task;

  explicit ThreadPool(const string& nameArg = string("ThreadPool"));
  ~ThreadPool();
  //必须在调用start前调用
  // Must be called before start().
  void setMaxQueueSize(int maxSize) { maxQueueSize_ = maxSize; }
  //设置线程初始化回调函数
  void setThreadInitCallback(const Task& cb)
  { threadInitCallback_ = cb; }
  //线程池开始
  void start(int numThreads);
  //线程池结束
  void stop();

  const string& name() const
  { return name_; }

  size_t queueSize() const;

  // Could block if maxQueueSize > 0
  // Call after stop() will return immediately.
  // There is no move-only version of std::function in C++ as of C++14.
  // So we don't need to overload a const& and an && versions
  // as we do in (Bounded)BlockingQueue.
  // https://stackoverflow.com/a/25408989
  void run(Task f);

 private:
  bool isFull() const REQUIRES(mutex_);
  //每个工作线程的入口函数（主循环）
  void runInThread();
  //从线程池取任务
  Task take();

  mutable MutexLock mutex_;
  //使用消费者生产者模型
  Condition notEmpty_ GUARDED_BY(mutex_);
  Condition notFull_ GUARDED_BY(mutex_);
  //线程池的名称
  string name_;
  //？
  Task threadInitCallback_;
  //线程队列
  std::vector<std::unique_ptr<muduo::Thread>> threads_;
  //任务队列
  std::deque<Task> queue_ GUARDED_BY(mutex_);
  //线程池大小
  size_t maxQueueSize_;
  //运行标志
  bool running_;
};

}  // namespace muduo

#endif  // MUDUO_BASE_THREADPOOL_H
