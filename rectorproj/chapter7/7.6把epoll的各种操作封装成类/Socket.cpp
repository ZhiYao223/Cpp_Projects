#include "Socket.h"
#include <iostream>
#include <netinet/tcp.h>

// 创建一个非阻塞的socket。
int createnonblocking()
{
    //创建服务端用于监听的listenf
    int listenfd = socket(AF_INET, SOCK_STREAM /SOCK_NONBLOCK, IPPROTO_TCP);
    if (listenfd < 0){
        printf("%s:%s:%d listen socket create error:%d\n", __FILE__, __FUNCTION__, __LINE__, errno);
        exit(-1);
    }
    return listenfd;
}

// 构造函数，传入一个已准备好的fd。
Socket::Socket(int fd):fd_(fd)
{

}

// 在析构函数中，将关闭fd_。
Socket::~Socket()
{
    ::close(fd_);
}

// 返回fd_成员。
int Socket::fd()  const
{
    return fd_;
}

// 
void Socket::settcpnodelay(bool on)
{
    int optval = on ? 1 : 0;
    // TCP_NODELAY包含头文件 <netinet/tcp.h>
    ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
}

void Socket::setreuseaddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

void Socket::setreuseport(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}

void Socket::setkeepalive(bool on)
{
    int  optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
}

// 服务端的socket将调用此绑定函数。
void Socket::bind(const InetAddress& servaddr)
{
    if(::bind(fd_, servaddr.addr(), sizeof(sockaddr)) < 0){
        perror("bind() faliled");
        close(fd_);
        exit(-1);
    }
}

// 服务端的socket将调用此监听函数。
void Socket::listen(int n)
{
    if(::listen(fd_, n) != 0){
        perror("listen() failed");
        close(fd_);
        exit(-1);
    }
}

int Socket::accept(InetAddress& clientaddr)
{
    sockaddr_in peeraddr;
    socklen_t len = sizeof(peeraddr);
    int clientfd = accept4(fd_, (struct sockaddr*)&peeraddr, &len, SOCK_NONBLOCK);
    if(clientfd < 0){
        printf("%s:%s:%d accept error:%d\n", __FILE__, __FUNCTION__, __LINE__, errno);
        exit(-1);
    }
    clientaddr.setaddr(peeraddr);
    return clientfd;
}
