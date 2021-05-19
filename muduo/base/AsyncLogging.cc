// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "muduo/base/AsyncLogging.h"
#include "muduo/base/LogFile.h"
#include "muduo/base/Timestamp.h"

#include <stdio.h>

using namespace muduo;

AsyncLogging::AsyncLogging(const string& basename,
                           off_t rollSize,
                           int flushInterval)
  : flushInterval_(flushInterval),
    running_(false),
    basename_(basename),
    rollSize_(rollSize),
    thread_(std::bind(&AsyncLogging::threadFunc, this), "Logging"),
    latch_(1),
    mutex_(),
    cond_(mutex_),
    currentBuffer_(new Buffer),
    nextBuffer_(new Buffer),
    buffers_()
{
  currentBuffer_->bzero();
  nextBuffer_->bzero();
  buffers_.reserve(16);
}

void AsyncLogging::append(const char* logline, int len)
{
  muduo::MutexLockGuard lock(mutex_);
  // 当前缓冲区有足够空间储存数据，则直接写入
  if (currentBuffer_->avail() > len)
  {
    currentBuffer_->append(logline, len);
  }
  else
  {
    // 如果当前缓冲区没有足够空间储存数据，则将当前缓冲区加入到待写入队列
    buffers_.push_back(std::move(currentBuffer_));
    // 将预备缓冲区设为当前缓冲区
    if (nextBuffer_)
    {
      currentBuffer_ = std::move(nextBuffer_);
    }
    // 如果前端写入速度太快，一下把两块缓冲区都写完，那么分配一块新的缓冲区
    else
    {
      currentBuffer_.reset(new Buffer); // Rarely happens
    }
    // 添加数据
    currentBuffer_->append(logline, len);
    // 因为已有填满的缓冲区，所以唤醒日志线程写日志
    cond_.notify();
  }
}

void AsyncLogging::threadFunc()
{
  assert(running_ == true);
  latch_.countDown();
  LogFile output(basename_, rollSize_, false);
  BufferPtr newBuffer1(new Buffer);
  BufferPtr newBuffer2(new Buffer);
  newBuffer1->bzero();
  newBuffer2->bzero();
  BufferVector buffersToWrite;
  buffersToWrite.reserve(16);
  while (running_)
  {
    assert(newBuffer1 && newBuffer1->length() == 0);
    assert(newBuffer2 && newBuffer2->length() == 0);
    assert(buffersToWrite.empty());

    {
      muduo::MutexLockGuard lock(mutex_);
      if (buffers_.empty())  // unusual usage!(非常规用法，因为只有一个日志线程)
      {
        cond_.waitForSeconds(flushInterval_);
      }
      // 将当前缓冲区push到buffers_中(日志线程被唤醒，意味着当前缓冲区有数据)
      buffers_.push_back(std::move(currentBuffer_));
      // 将空闲的newbuffer1设置为当前缓冲区
      currentBuffer_ = std::move(newBuffer1);
      // buffers_与buffersToWrite（栈上对象）交换，这样之后的代码可以在临界区之外访问（相当于将buffers_的数据暂时储存）
      buffersToWrite.swap(buffers_);
      if (!nextBuffer_)
      {
        // 确保前端始终有一个预备buffer可供调配，减少前端临界区分配内存的概率，缩短前端临界区
        nextBuffer_ = std::move(newBuffer2);
      }
    }

    assert(!buffersToWrite.empty());
    // 防止出现消息堆积问题
    // 前端一直发送日志消息，超过后端处理能力。造成数据在内存中堆积，严重时引发性能问题（可用内存不足）
    if (buffersToWrite.size() > 25)
    {
      char buf[256];
      snprintf(buf, sizeof buf, "Dropped log messages at %s, %zd larger buffers\n",
               Timestamp::now().toFormattedString().c_str(),
               buffersToWrite.size()-2);
      fputs(buf, stderr);
      output.append(buf, static_cast<int>(strlen(buf)));
      // 如果出现消息堆积问题，则丢掉多余的日志，以腾出内存，只保留两块缓冲区
      buffersToWrite.erase(buffersToWrite.begin()+2, buffersToWrite.end());
    }

    for (const auto& buffer : buffersToWrite)
    {
      //将日志信息输出
      // FIXME: use unbuffered stdio FILE ? or use ::writev ?
      output.append(buffer->data(), buffer->length());
    }

    if (buffersToWrite.size() > 2)
    {
      // drop non-bzero-ed buffers, avoid trashing
      // 只保留两块缓冲区
      buffersToWrite.resize(2);
    }
    //  如果newBuffer为空则把buffers中的缓冲区给它（此时，buffers中缓冲区的内容已经写入到日志）
    if (!newBuffer1)
    {
      assert(!buffersToWrite.empty());
      newBuffer1 = std::move(buffersToWrite.back());
      buffersToWrite.pop_back();
      newBuffer1->reset();
    }

    if (!newBuffer2)
    {
      assert(!buffersToWrite.empty());
      newBuffer2 = std::move(buffersToWrite.back());
      buffersToWrite.pop_back();
      newBuffer2->reset();
    }
    // 清空
    buffersToWrite.clear();
    output.flush();
  }
  output.flush();
}

