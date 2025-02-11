#pragma once

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

// socket的地址协议类
class InetAddress{
    private:
        sockaddr_in addr_;  // socket地址结构体
    public:
        InetAddress();
        //如果是监听的socket，需要绑定IP和端口，用该构造函数
        InetAddress(const std::string &ip, uint16_t port);
        //如果是客户端的socket，需要连接服务器，用该构造函数
        InetAddress(const sockaddr_in addr);
        ~InetAddress();

        //返回字符串表示的地址，例如：
        const char *ip() const; 
        //返回整数表示的端口，例如：
        uint16_t port() const;
        //返回addr_成员的地址，转换成了sockaddr
        const sockaddr *addr() const;
        //设置addr_成员的值。
        void setaddr(sockaddr_in clientaddr);
};