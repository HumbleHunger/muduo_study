// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_TIMER_H
#define MUDUO_NET_TIMER_H

#include "muduo/base/Atomic.h"
#include "muduo/base/Timestamp.h"
#include "muduo/net/Callbacks.h"

namespace muduo
{
namespace net
{

///
/// Internal class for timer event.
///
// 定时操作的高层抽象
class Timer : noncopyable
{
 public:
  Timer(TimerCallback cb, Timestamp when, double interval)
    : callback_(std::move(cb)),
      expiration_(when),
      interval_(interval),
      repeat_(interval > 0.0),
      // 原子操作
      sequence_(s_numCreated_.incrementAndGet())
  { }

  void run() const
  {
    callback_();
  }

  Timestamp expiration() const  { return expiration_; }
  bool repeat() const { return repeat_; }
  int64_t sequence() const { return sequence_; }
  // 重置定时器
  void restart(Timestamp now);

  static int64_t numCreated() { return s_numCreated_.get(); }

 private:
  // 定时器回调函数
  const TimerCallback callback_;
  // 下一次的(超时)时刻
  Timestamp expiration_;
  // （超时）时间间隔。如果是一次性定时器，该值为0
  const double interval_;
  // 定时器是否重复使用
  const bool repeat_;
  // 定时器序号
  const int64_t sequence_;
  // 定时器计数器，当前已经创建的定时器数量
  static AtomicInt64 s_numCreated_;
};

}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_TIMER_H
