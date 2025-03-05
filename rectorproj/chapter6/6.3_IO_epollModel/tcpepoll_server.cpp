/*
 * 程序名：tcpepoll.cpp，此程序用于演示采用epoll模型实现网络通讯的服务端。
 * 作者：zhiyao
 * 功能：通过epoll模型实现高效的多客户端并发通信。服务端监听指定端口，接收客户端请求并回显收到的消息。
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>          
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>

// 初始化服务端监听端口，返回监听socket的描述符
int initserver(int port);

int main(int argc, char *argv[])
{
    // 判断命令行参数是否合法，程序需要传入监听端口号
    if (argc != 2) {
        printf("usage: ./tcpepoll port\n");
        return -1;
    }

    // 初始化监听socket，绑定端口并开始监听
    int listensock = initserver(atoi(argv[1]));
    printf("listensock=%d\n", listensock);
    
    if (listensock < 0) {
        printf("initserver() failed.\n");
        return -1;
    }

    // 创建epoll实例
    int epollfd = epoll_create(1);  // 参数1是提示内核所需的事件数量，不影响实际功能

    // 准备监听socket的事件
    epoll_event ev;
    ev.data.fd = listensock;  // 指定监听socket
    ev.events = EPOLLIN;      // 监听“可读”事件，即新的连接请求

    // 将监听socket的事件注册到epoll实例中
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listensock, &ev);

    epoll_event evs[10];  // 用于存放epoll_wait返回的事件信息

    // 事件循环，不断等待并处理socket事件
    while (true) {
        // 等待epoll监视的socket事件，最大监听10个事件，-1表示无限等待
        int infds = epoll_wait(epollfd, evs, 10, -1);

        // 发生错误
        if (infds < 0) {
            perror("epoll() failed");
            break;
        }

        // 超时（由于设置了-1等待方式，实际上不会超时）
        if (infds == 0) {
            printf("epoll() timeout.\n");
            continue;
        }

        // 有事件发生，处理事件
        for (int i = 0; i < infds; i++) {
            //如果是监听 socket 的事件，表示有新客户端连接，
            //调用 accept 接收连接，并将新 socket 加入 epoll 监控。
            if (evs[i].data.fd == listensock) { 
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                // 接收客户端连接请求
                int clientsock = accept(listensock, (struct sockaddr*)&client, &len);
                printf("accept client(socket=%d) ok.\n", clientsock);

                // 为新连接的客户端创建可读事件，并加入epoll监控
                ev.data.fd = clientsock;
                ev.events = EPOLLIN;  // 监听“可读”事件，即客户端发来的数据
                epoll_ctl(epollfd, EPOLL_CTL_ADD, clientsock, &ev);
            }
            // 如果是客户端 socket 的事件，表示有数据到达，调用 recv 接收数据并回显。
            else {
                // 处理客户端发来的数据
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));

                // 接收客户端数据
                if (recv(evs[i].data.fd, buffer, sizeof(buffer), 0) <= 0) {
                    // 客户端关闭连接或发生错误
                    printf("client(eventfd = %d) disconnected.\n", evs[i].data.fd);
                    close(evs[i].data.fd);  // 关闭客户端socket
                }
                else {
                    // 打印接收的消息并回显给客户端
                    printf("recv(eventfd = %d): %s\n", evs[i].data.fd, buffer);
                    send(evs[i].data.fd, buffer, strlen(buffer), 0);
                    // 继续监听该 socket 的后续事件
                    ev.data.fd = evs[i].data.fd;
                    ev.events = EPOLLIN;
                    epoll_ctl(epollfd, EPOLL_CTL_MOD, evs[i].data.fd, &ev);
                }
            }
        }
    }
    return 0;
}

/*
 * 初始化服务端监听端口
 * 1. 创建socket
 * 2. 绑定指定端口
 * 3. 开始监听请求
 * 参数：port - 监听的端口号
 * 返回值：成功返回监听socket，失败返回-1
 */
int initserver(int port)
{
    // 创建TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket() failed");
        return -1;
    }

    // 设置端口复用，避免端口占用导致bind失败
    int opt = 1;
    unsigned int len = sizeof(opt);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, len);

    // 定义服务端地址结构
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;           // 使用IPv4地址族
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 监听所有可用网络接口
    servaddr.sin_port = htons(port);         // 设置监听端口（网络字节序）

    // 绑定socket到指定端口
    if (bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind() failed");
        close(sock);
        return -1;
    }

    // 开始监听，最多允许5个客户端排队
    if (listen(sock, 5) != 0) {
        perror("listen() failed");
        close(sock);
        return -1;
    }
    // 返回监听socket
    return sock;
}
