#include "InetAddress.h"

InetAddress::InetAddress()
{

}
// 如果是监听的socket，需要绑定IP和端口，用该构造函数
InetAddress::InetAddress(const std::string &ip, uint16_t port)
{
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

// 如果是客户端的socket，需要连接服务器，用该构造函数
InetAddress::InetAddress(const struct sockaddr_in addr):addr_(addr)
{
    
}

InetAddress::~InetAddress()
{

}

// 返回字符串表示的地址，例如：192.168.150.128
const char *InetAddress::ip() const
{
    return inet_ntoa(addr_.sin_addr);
}

// 返回整数表示的端口，例如：80、8080
uint16_t InetAddress::port() const
{
    return ntohs(addr_.sin_port);
}

// 返回addr_成员的地址，转换成了sockaddr
const sockaddr *InetAddress::addr() const
{
    return (sockaddr*)&addr_;
};

// 设置addr_成员的值。
void InetAddress::setaddr(sockaddr_in clientaddr)
{
    addr_=clientaddr;
}
