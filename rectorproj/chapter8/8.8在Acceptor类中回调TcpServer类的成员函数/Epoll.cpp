#include "Epoll.h"

Epoll::Epoll()
{
    if ((epollfd_=epoll_create(1))==-1)       // 创建epoll句柄（红黑树）。
    {
        printf("epoll_create() failed(%d).\n",errno); exit(-1);
    }
}

Epoll::~Epoll()                                          
{
    close(epollfd_);           // 在析构函数中关闭epollfd_。
}

// 把channel添加/更新到红黑树上，channel中有fd，也有需要监视的事件。
void Epoll::updatechannel(Channel *ch)
{
    epoll_event ev;                 // 声明事件的数据结构。
    ev.data.ptr=ch;                 // 指定channel。
    ev.events=ch->events();  // 指定事件。

    if (ch->inpoll())         // 如果channel已经在树上了。
    {
        if (epoll_ctl(epollfd_,EPOLL_CTL_MOD,ch->fd(),&ev)==-1)
        {
            perror("epoll_ctl() failed.\n"); exit(-1);
        }
    }
    else                           // 如果channel不在树上。
    {
        if (epoll_ctl(epollfd_,EPOLL_CTL_ADD,ch->fd(),&ev)==-1)
        {
            perror("epoll_ctl() failed.\n"); exit(-1);
        }
        ch->setinepoll();   // 把channel的inepoll_成员设置为true。
    }
}

// 运行epoll_wait()，等待事件的发生，已发生的事件用vector容器返回。
std::vector<Channel *> Epoll::loop(int timeout)   
{
    // 存放epoll_wait()返回的事件。
    std::vector<Channel *> channels;
    // 清空events_数组。
    bzero(events_,sizeof(events_));
    // 等待监视的fd有事件发生。
    int infds=epoll_wait(epollfd_,events_,MaxEvents,timeout);       
    // 返回失败,退出。
    if (infds < 0)
    {
        perror("epoll_wait() failed"); exit(-1);
    }
    // 超时,返回。
    if (infds == 0)
    {
        printf("epoll_wait() timeout.\n"); return channels;
    }
    // 如果infds>0，表示有事件发生的fd的数量。
    for (int ii=0;ii<infds;ii++)       // 遍历epoll返回的数组events_。
    {
        // 取出已发生事件的channel。
        Channel *ch=(Channel *)events_[ii].data.ptr;
        // 设置channel的revents_成员。       
        ch->setrevents(events_[ii].events); 
        // 把channel添加到vector容器中。
        channels.push_back(ch);
    }
    // 返回已发生事件的channel。
    return channels;
}
