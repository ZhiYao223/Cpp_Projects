#include "../include/server.h"

int MAX_EVENTS = 100;

Server::Server() {
    LOG_TRACK << "server at constructor function start";
    // 创建服务器套接字
    serverFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (serverFd == -1) {
        LOG_ERROR << "server at create socket function failed";
        exit(-1);
    }
    //设置端口复用
    int opt = 1;
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        LOG_ERROR << "server at SO_REUSEADDR failed";
        close(serverFd);
        exit(-1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(12345);

    if (bind(serverFd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        LOG_ERROR << "server at bind function failed";
        close(serverFd);
        exit(-1);
    }

    if (listen(serverFd, 10) == -1) {
        LOG_ERROR << "server at listen function failed";
        close(serverFd);
        exit(-1);
    }
    LOG_TRACK << "server start successful";
}

void Server::start() {
    // 创建 epoll 实例
    int epollFd = epoll_create1(0);
    if (epollFd == -1) {
        LOG_ERROR << "epoll_create1 failed";
        return;
    }

    // 将服务器套接字添加到 epoll 中
    struct epoll_event event;
    event.data.fd = serverFd;
    event.events = EPOLLIN;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, serverFd, &event) == -1) {
        LOG_ERROR << "epoll_ctl failed";
        close(epollFd);
        return;
    }

    // 事件循环
    struct epoll_event events[MAX_EVENTS];
    while (1) {
        int nfds = epoll_wait(epollFd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            LOG_ERROR << "epoll_wait failed";
            break;
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == serverFd) {
                // 新客户端连接
                int clientFd = accept(serverFd, NULL, NULL);
                if (clientFd == -1) {
                    LOG_ERROR << "accept failed";
                    continue;
                }

                // 设置非阻塞，ET模式下必须设置非阻塞
                if (Tool::setNonBlocking(clientFd) == -1) {
                    LOG_ERROR << "setNonBlocking failed";
                    close(clientFd);
                    continue;
                }

                // 将客户端套接字添加到 epoll 中
                event.data.fd = clientFd;
                event.events = EPOLLIN | EPOLLET; //边缘触发模式
                if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &event) == -1) {
                    LOG_ERROR << "epoll_ctl failed";
                    close(clientFd);
                }

            } else {
                //开始处理客户端接收到的请求
                recvInfo(events[n].data.fd);
                // 处理完请求后关闭连接
            }
        }
    }

    close(epollFd);
}

void Server::recvInfo(int fd) {
    char buffer[1024];
    while (true) {
        ssize_t n = read(fd, buffer, sizeof(buffer)); // 读取数据
        if (n == -1) { // 错误情况
            if (errno == EAGAIN) {
                // 表示数据读取完毕，没有更多数据
                break;
            }
            LOG_ERROR << "read from client fd: " << fd <<" error";
            close(fd); // 关闭文件描述符
            break;
        } else if (n == 0) {
            // 对端关闭连接
            LOG_WARNING << "client fd " << fd << " connection closed by peer";
            close(fd);
            break;
        } else {
            // 处理读取到的数据
            
        }
    }
    std::cout << "recv from client message : " << buffer << std::endl;
}
