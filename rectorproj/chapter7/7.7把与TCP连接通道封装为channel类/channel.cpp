#include "Channel.h"

// 构造函数
Channel::Channel(Epoll* ep, int fd):ep_(ep),fd_(fd)
{

}

// 析构函数
Channel::~Channel()
{
    // 在析构函数中，不要销毁ep_，也不能关闭fd_，因为这两个东西不属于Channel类，Channel类只是需要它们，使用它们而已。
}

int Channel::fd()
{
    return fd_;
}

void Channel::enablereading()
{
    events_ |= EPOLLIN;
    ep_->updatechannel(this);
}

void Channel::setinepoll()
{
    inepoll_ = true;
}


void Channel::setrevents(uint32_t ev)
{
    revents_ = ev;
}

bool Channel::inpoll()
{
    return inepoll_;
}

// 返回events_成员。
uint32_t Channel::events()
{
    return revents_;
}

// 返回revents_成员
uint32_t Channel::revents()
{
    return revents_;
}
