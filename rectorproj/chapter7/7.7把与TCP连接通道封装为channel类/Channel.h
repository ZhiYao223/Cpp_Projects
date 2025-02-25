#pragma once
#include <sys/epoll.h>
#include "Epoll.h"

class Epoll;

class Channel{
private:
    //Channel拥有的fd，一对一关系
    int fd_;
    //Channel对应的红黑树，与Epoll是多对一的关系
    Epoll *ep_ = nullptr;
    //Channel是否已添加到epoll树上，如果未添加，调用epoll_ctl()
    bool inepoll_ = false;
    //fd_需要监视的事件，listenfd和clientfd需要监视EPOLLIN，clientfd可能还需要监视EPOLLOUT
    uint32_t events_ = 0;
public:

};
