/*
 * 程序名：tcpepoll.cpp，此程序用于演示采用epoll模型实现网络通讯的服务端。
 * 作者：吴从周
*/
#include "EchoServer.h"

int main(int argc,char *argv[])
{
    if (argc != 3) 
    { 
        printf("usage: ./tcpepoll ip port\n"); 
        printf("example: ./tcpepoll 192.168.206.128 5005\n\n"); 
        return -1; 
    }

    // TcpServer tcpserver(argv[1],atoi(argv[2]));
    // tcpserver.start();      // 运行事件循环。

    EchoServer echoserver(argv[1],atoi(argv[2]));
    echoserver.Start();

    return 0;
}