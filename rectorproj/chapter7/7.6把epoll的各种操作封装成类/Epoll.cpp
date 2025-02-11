#include "Epoll.h"

Epoll::Epoll()
{
    // 创建epoll句柄（红黑树）。
    if ((epollfd_ = epoll_create(1)) == -1){
        printf("epoll_create() failed(%d).\n", errno);
        exit(-1);
    }
}

Epoll::~Epoll()
{
    close(epollfd_); // 在析构函数中关闭epollfd_。
}

// 把fd和它需要监视的事件添加到红黑树上。
void Epoll::addfd(int fd, uint32_t op)
{
    // 声明事件的数据结构。
    epoll_event ev; 
    //指定事件自定义数据，随epoll_wait()返回的事件返回。
    ev.data.fd = fd; 
    // 让epoll监视fd的。
    ev.events = op; 

    if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1) // 把需要监视的fd和它的事件加入epollfd中。
    {
        printf("epoll_ctl() failed(%d).\n", errno);
        exit(-1);
    }
}