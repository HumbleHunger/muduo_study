// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_SOCKETSOPS_H
#define MUDUO_NET_SOCKETSOPS_H

#include <arpa/inet.h>

namespace muduo
{
namespace net
{
// 全局函数，封装了socket的操作，在Socket类中大量使用
namespace sockets
{

///
/// Creates a non-blocking socket file descriptor,
/// abort if any error.
// 创建非阻塞套接字
int createNonblockingOrDie(sa_family_t family);
// 链接
int  connect(int sockfd, const struct sockaddr* addr);
// bind
void bindOrDie(int sockfd, const struct sockaddr* addr);
// 监听
void listenOrDie(int sockfd);
int  accept(int sockfd, struct sockaddr_in6* addr);
ssize_t read(int sockfd, void *buf, size_t count);
// 将读取的内容放入多个缓冲区
ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);
ssize_t write(int sockfd, const void *buf, size_t count);
void close(int sockfd);
void shutdownWrite(int sockfd);
// 网际地址转为主机序的字符串
void toIpPort(char* buf, size_t size,
              const struct sockaddr* addr);
// 网际序IP地址转为主机序的字符串
void toIp(char* buf, size_t size,
          const struct sockaddr* addr);
// 主机序的字符串转为网际地址
void fromIpPort(const char* ip, uint16_t port,
                struct sockaddr_in* addr);
// Ipv6主机序的字符串转为网际地址
void fromIpPort(const char* ip, uint16_t port,
                struct sockaddr_in6* addr);
// 获得socket错误
int getSocketError(int sockfd);
// 将网际地址转为通用地址
const struct sockaddr* sockaddr_cast(const struct sockaddr_in* addr);
// 将ipv6网际地址转为通用地址
const struct sockaddr* sockaddr_cast(const struct sockaddr_in6* addr);
struct sockaddr* sockaddr_cast(struct sockaddr_in6* addr);
const struct sockaddr_in* sockaddr_in_cast(const struct sockaddr* addr);
const struct sockaddr_in6* sockaddr_in6_cast(const struct sockaddr* addr);
// 获取套接字的本地地址
struct sockaddr_in6 getLocalAddr(int sockfd);
// 获取套接字的对端地址
struct sockaddr_in6 getPeerAddr(int sockfd);
bool isSelfConnect(int sockfd);

}  // namespace sockets
}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_SOCKETSOPS_H
