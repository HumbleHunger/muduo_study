// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_THREAD_H
#define MUDUO_BASE_THREAD_H

#include "muduo/base/Atomic.h"
#include "muduo/base/CountDownLatch.h"
#include "muduo/base/Types.h"

#include <functional>
#include <memory>
#include <pthread.h>

namespace muduo
{

class Thread : noncopyable
{
 public:
  typedef std::function<void ()> ThreadFunc;

  explicit Thread(ThreadFunc, const string& name = string());
  // FIXME: make it movable in C++11
  ~Thread();
  //开始
  void start();
  //等待结束回收资源
  int join(); // return pthread_join()
  //查询是否开始
  bool started() const { return started_; }
  // pthread_t pthreadId() const { return pthreadId_; }
  //返回tid
  pid_t tid() const { return tid_; }
  //返回name
  const string& name() const { return name_; }
  //返回当前存在线程数目
  static int numCreated() { return numCreated_.get(); }

 private:
  void setDefaultName();

  bool       started_;
  bool       joined_;
  pthread_t  pthreadId_;
  pid_t      tid_;
  ThreadFunc func_;
  string     name_;
  //倒数门阀使用条件变量实现
  CountDownLatch latch_;
  //已存在的线程个数（封装原子操作的int32_t
  static AtomicInt32 numCreated_;
};

}  // namespace muduo
#endif  // MUDUO_BASE_THREAD_H
