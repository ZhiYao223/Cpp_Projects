#pragma once
#include "TcpServer.h"
#include "EventLoop.h"
#include "Connection.h"

/*
    EchoServer类，用于实现回显服务器。
*/
class EchoServer
{
private:
    TcpServer tcpServer_;  // TcpServer对象。

public:
    EchoServer(const std::string &ip,const uint16_t port);
    ~EchoServer();

    void start();   // 启动服务器。
    // 处理新的客户端连接。
    void HandleNewConnection(Socket *clientsock);
    // 关闭客户端的连接，在TcpServer中调用此函数。
    void HandleClose(Connection *conn);
    // 客户端的连接错误，在TcpServer中调用此函数。
    void HandleError(Connection *conn);
    // 处理客户端的请求报文，在TcpServer中调用此函数。
    void HandleMessage(Connection *conn);
    // 发送数据给客户端后，在TcpServer中调用此函数。
    void HandleSendComplete(Connection *conn);
    // epoll_wait超时，在TcpServer中调用此函数。
    void HandleTimeOut(EventLoop *loop);
};