// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_COUNTDOWNLATCH_H
#define MUDUO_BASE_COUNTDOWNLATCH_H

#include "muduo/base/Condition.h"
#include "muduo/base/Mutex.h"

namespace muduo
{

class CountDownLatch : noncopyable
{
 public:

  explicit CountDownLatch(int count);
  //一般时主线程调用 wait等待直到count变为零
  void wait();
  //一般执行线程调用 将任务数减一
  void countDown();

  int getCount() const;

 private:
  mutable MutexLock mutex_;
  //使用变量condition前必须对mutex_加锁
  Condition condition_ GUARDED_BY(mutex_);
  //同上
  int count_ GUARDED_BY(mutex_);
};

}  // namespace muduo
#endif  // MUDUO_BASE_COUNTDOWNLATCH_H
