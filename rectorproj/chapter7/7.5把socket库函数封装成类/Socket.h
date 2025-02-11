#pragma
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include "InetAddress.h"

// 创建一个非阻塞的socket。
int createnonblocking();

//socket类
class Socket
{
private:
    const int fd_;// Socket持有的fd，在构造函数中传进来。
public:
    // 构造函数，传入一个已准备好的fd。
    Socket(int fd);
    // 在析构函数中，将关闭fd_。
    ~Socket();

    int fd() const; // 返回fd_成员。
    // 设置SO_REUSEADDR选项，true-打开，false-关闭。    
    void setreuseaddr(bool on);
    // 设置SO_REUSEPORT选项。
    void setresueport(bool on);
    // 设置TCP_NODELAY选项。
    void settcpnodelay(bool on);
    // 设置SO_KEEPALIVE选项。
    void setkeepalive(bool on);

    // 服务端的socket将调用此绑定函数。
    void bind(const InetAddress& servaddr);
    // 服务端的socket将调用此监听函数。
    void listen(int n = 128);
    // 服务端的socket将调用此接收函数。
    int accept(InetAddress& clientaddr);
};