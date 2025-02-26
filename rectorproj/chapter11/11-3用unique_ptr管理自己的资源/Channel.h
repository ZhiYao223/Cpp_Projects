#pragma once
#include <sys/epoll.h>
#include <functional>
#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"
 
class EventLoop;

class Channel
{
private:
    // Channel拥有的fd，Channel和fd是一对一的关系。
    int fd_=-1;                             
    // Channel对应的事件循环，Channel与EventLoop是多对一的关系，一个Channel只对应一个EventLoop。
    EventLoop *loop_=nullptr;   
    // Channel是否已添加到epoll树上，如果未添加，调用epoll_ctl()的时候用EPOLL_CTL_ADD，否则用EPOLL_CTL_MOD。
    bool inepoll_=false;             
    // fd_需要监视的事件。listenfd和clientfd需要监视EPOLLIN，clientfd还可能需要监视EPOLLOUT。
    uint32_t events_=0;              
    // fd_已发生的事件。
    uint32_t revents_=0;              
    // fd_读事件的回调函数，如果是acceptchannel，将回调Acceptor::newconnection()，如果是clientchannel，将回调Connection::onmessage()。
    std::function<void()> readcallback_;         
    // 关闭fd_的回调函数，将回调Connection::closecallback()。
    std::function<void()> closecallback_;        
    // fd_发生了错误的回调函数，将回调Connection::errorcallback()。
    std::function<void()> errorcallback_;        
    // fd_写事件的回调函数，将回调Connection::writecallback()。
    std::function<void()> writecallback_;        

public:
    Channel(EventLoop* loop,int fd);      // 构造函数。                      Channel是Acceptor和Connection的下层类。
    // 析构函数。
    ~Channel();                                         
    // 返回fd_成员。
    int fd();                                            
    // 采用边缘触发。
    void useet();                                    
    // 让epoll_wait()监视fd_的读事件，注册读事件。
    void enablereading();                     
    // 取消读事件。
    void disablereading();                    
    // 注册写事件。
    void enablewriting();               
    // 取消写事件。       
    void disablewriting();
    // 取消全部的事件   
    void disableall();
    // 从事件循环中删除Channel
    void remove();
    // 把inepoll_成员的值设置为true。
    void setinepoll();                            
    // 设置revents_成员的值为参数ev。
    void setrevents(uint32_t ev);         
    // 返回inepoll_成员。
    bool inpoll();                                  
    // 返回events_成员。
    uint32_t events();                           
    // 返回revents_成员。 
    uint32_t revents();                          
    // 事件处理函数，epoll_wait()返回的时候，执行它。
    void handleevent();         
    // 设置fd_读事件的回调函数。
    void setreadcallback(std::function<void()> fn);    
    // 设置关闭fd_的回调函数。
    void setclosecallback(std::function<void()> fn);   
    // 设置fd_发生了错误的回调函数。
    void seterrorcallback(std::function<void()> fn);   
    // 设置写事件的回调函数。
    void setwritecallback(std::function<void()> fn);   
};