// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_THREADLOCAL_H
#define MUDUO_BASE_THREADLOCAL_H

#include "muduo/base/Mutex.h"
#include "muduo/base/noncopyable.h"

#include <pthread.h>

namespace muduo
{

template<typename T>
class ThreadLocal : noncopyable
{
 public:
  ThreadLocal()
  {
    //线程私有数据创建
    MCHECK(pthread_key_create(&pkey_, &ThreadLocal::destructor));
  }

  ~ThreadLocal()
  {
    //线程私有数据销毁
    MCHECK(pthread_key_delete(pkey_));
  }

  T& value()
  {
    //取出线程私有数据
    T* perThreadValue = static_cast<T*>(pthread_getspecific(pkey_));
    //如果线程数据未被设置则设置
    if (!perThreadValue)
    {
      T* newObj = new T();
      MCHECK(pthread_setspecific(pkey_, newObj));
      perThreadValue = newObj;
    }
    return *perThreadValue;
  }

 private:
//析构线程局部数据所关联的对象
  static void destructor(void *x)
  {
    T* obj = static_cast<T*>(x);
    typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    T_must_be_complete_type dummy; (void) dummy;
    delete obj;
  }

 private:
  pthread_key_t pkey_;
};

}  // namespace muduo

#endif  // MUDUO_BASE_THREADLOCAL_H
