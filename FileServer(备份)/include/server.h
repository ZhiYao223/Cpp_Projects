#ifndef SERVER_H
#define SERVER_H


#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include "log.h"
#include "../tool/tool.h"

class Server {
public:
    Server();
    void start();
private:
    int serverFd;
private:
    void recvInfo(int fd);
};


#endif