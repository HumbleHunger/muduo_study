// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_SINGLETON_H
#define MUDUO_BASE_SINGLETON_H

#include "muduo/base/noncopyable.h"

#include <assert.h>
#include <pthread.h>
#include <stdlib.h> // atexit

namespace muduo
{

namespace detail
{
// This doesn't detect inherited member functions!
// http://stackoverflow.com/questions/1966362/sfinae-to-check-for-inherited-member-functions
template<typename T>
struct has_no_destroy
{
  template <typename C> static char test(decltype(&C::no_destroy));
  template <typename C> static int32_t test(...);
  const static bool value = sizeof(test<T>(0)) == 1;
};
}  // namespace detail

template<typename T>
class Singleton : noncopyable
{
 public:
  Singleton() = delete;
  ~Singleton() = delete;

  static T& instance()
  {
    //pthread_once保证只调用一次init，即只初始化一次
    pthread_once(&ponce_, &Singleton::init);
    assert(value_ != NULL);
    return *value_;
  }

 private:
 //初始化
  static void init()
  {
    value_ = new T();
    //???
    if (!detail::has_no_destroy<T>::value)
    {
      //在进程结束时调用destroy
      ::atexit(destroy);
    }
  }

  static void destroy()
  {
    //定义一个名为T_must_be_complete_type的char数组的类型
    typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    //判断T是否是完整的类型，如果不是完整类型则数组长度为-1则编译期间会报错
    T_must_be_complete_type dummy; (void) dummy;

    delete value_;
    value_ = NULL;
  }

 private:
  //保证一个函数只被执行一次
  static pthread_once_t ponce_;
  //指向对像，提供访问接口
  static T*             value_;
};

template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;

}  // namespace muduo

#endif  // MUDUO_BASE_SINGLETON_H
