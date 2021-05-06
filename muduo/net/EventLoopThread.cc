// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "muduo/net/EventLoopThread.h"

#include "muduo/net/EventLoop.h"

using namespace muduo;
using namespace muduo::net;

EventLoopThread::EventLoopThread(const ThreadInitCallback& cb,
                                 const string& name)
  : loop_(NULL),
    exiting_(false),
    thread_(std::bind(&EventLoopThread::threadFunc, this), name),
    mutex_(),
    cond_(mutex_),
    callback_(cb)
{
}

EventLoopThread::~EventLoopThread()
{
  exiting_ = true;
  if (loop_ != NULL) // not 100% race-free, eg. threadFunc could be running callback_.
  {
    // still a tiny chance to call destructed object, if threadFunc exits just now.
    // but when EventLoopThread destructs, usually programming is exiting anyway.
    loop_->quit();
    thread_.join();
  }
}
// startloop由用户调用，与threadFunc并发执行
EventLoop* EventLoopThread::startLoop()
{
  assert(!thread_.started());
  // IO线程开始，thread对象调用回调函数threadFunc
  thread_.start();

  EventLoop* loop = NULL;
  // 使用条件变量，等待threadFunc函数设置loop_，即loop被创建
  {
    MutexLockGuard lock(mutex_);
    while (loop_ == NULL)
    {
      cond_.wait();
    }
    loop = loop_;
  }

  return loop;
}

void EventLoopThread::threadFunc()
{
  // 创建Eventloop
  EventLoop loop;
  // 如果用户设置了回调函数则先调用
  if (callback_)
  {
    callback_(&loop);
  }
  // 设置loop_
  {
    MutexLockGuard lock(mutex_);
    loop_ = &loop;
    cond_.notify();
  }
  // 执行loop
  loop.loop();
  //assert(exiting_);
  MutexLockGuard lock(mutex_);
  loop_ = NULL;
}

