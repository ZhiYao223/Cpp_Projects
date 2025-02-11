#pragma once
#include  <sys/epoll.h>
#include  "Epoll.h"

class Epoll;

class Channel
{
private:
    // Channel拥有的fd，Channel和fd是一对一的关系。
    int fd_ = -1;
    // Channel对应的红黑树，Channel与Epoll是多对一的关系，一个Channel只对应一个Epoll。
    Epoll *ep_ = nullptr;
    // Channel是否已添加到epoll树上，如果未添加，调用epoll_ctl()的时候用EPOLL_CTL_ADD，否则用EPOLL_CTL_MOD。
    bool inepoll_ = false;
    // fd_需要监视的事件。listenfd和clientfd需要监视EPOLLIN，clientfd还可能需要监视EPOLLOUT。
    uint32_t events_ = 0;
    // fd_已发生的事件。
    uint32_t revents_ = 0;
public:
    Channel(Epoll* ep, int fd); // 构造函数。
    ~Channel(); // 析构函数。
    int fd(); // 返回fd_成员。
    void useet(); // 采用边缘触发。
    void enablereading(); // 让epoll_wait()监视fd_的读事件。
    void setinepoll(); // 把inepoll_成员的值设置为true。
    void setrevents(uint32_t ev); // 设置revents_成员的值为参数ev。
    bool inpoll(); // 返回inepoll_成员。
    uint32_t events(); // 返回events_成员。
    uint32_t revents(); // 返回revents_成员。
};

