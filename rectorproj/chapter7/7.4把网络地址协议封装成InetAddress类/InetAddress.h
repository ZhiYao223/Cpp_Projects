#pragma

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

// socket的地址协议类
class InetAddress{
    private:
        struct sockaddr_in addr_;  // socket地址结构体
    public:
        //如果是监听的socket，需要绑定IP和端口，用该构造函数
        InetAddress(const std::string &ip, uint16_t port){
            addr_.sin_family = AF_INET;  // 设置地址族为IPv4
            addr_.sin_port = htons(port);  // 设置端口号
            addr_.sin_addr.s_addr = inet_addr(ip.c_str());  // 设置IP地址
        }
        //如果是客户端的socket，需要连接服务器，用该构造函数
        InetAddress(const struct sockaddr_in &addr):addr_(addr){

        }
        ~InetAddress(){}

        //返回字符串表示的地址，例如：
        const char *ip() const; 
        //返回整数表示的端口，例如：
        uint16_t port() const;
        //返回addr_成员的地址，转换成了sockaddr
        const struct sockaddr_in *addr() const;

};