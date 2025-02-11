#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <vector>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Epoll类
class Epoll
{
private:
    // epoll_wait()返回事件数组的大小
    static const int MaxEvents = 100;
    // epoll句柄，在构造函数中创建
    int epollfd_ = -1;
    // 存放poll_wait()返回事件的数组，在构造函数中分配内存
    epoll_event events[MaxEvents];
public:
    Epoll(); // 在构造函数中创建了epollfd_
    ~Epoll(); // 在析构函数中关闭epollfd_
    // 把fd和它需要监视的事件添加到红黑树上
    void addfd(int fd, uint32_t op); 
    // 运行epoll_wait()，等待事件的发生，已发生的事件用vector容器返回
    std::vector<epoll_event> loop(int timeout = -1);
};