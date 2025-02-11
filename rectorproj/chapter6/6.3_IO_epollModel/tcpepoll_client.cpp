// 网络通信客户端程序，通过poll方法实现非阻塞客户端连接和数据交互
/*
代码中的关键点：
    -使用poll实现非阻塞I/O模型，通过监听POLLOUT事件判断连接是否成功。
    -使用fcntl将socket设置为非阻塞状态，这样即使connect()未立即返回成功，程序也不会卡住。
    -poll的超时时间设置为-1表示一直等待，直到事件发生。
    -在数据传输中，send和recv均有错误处理，防止意外断开连接。
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>

// 将socket设置为非阻塞状态
int setnonblocking(int fd)
{
    int  flags;
    // 获取fd的状态标志
    if  ((flags = fcntl(fd, F_GETFL, 0)) == -1)
        flags = 0;  // 如果失败，则设置为0
    // 将fd设置为非阻塞
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main(int argc, char *argv[])
{
    // 取消的参数错误处理
    if (argc != 3)
    {
        printf("usage: ./client1 ip port\n"); 
        return -1;
    }

    int sockfd;  // 客户端socket接口连接发送接收数据
    struct sockaddr_in servaddr;  // 服务器地址结构体
    char buf[1024];  // 缓冲区存储每次交互数据
 
    // 创建socket，将客户端连接到TCP服务器
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        printf("socket() failed.\n"); 
        return -1;
    }

    // 设置socket为非阻塞
    setnonblocking(sockfd); 
    
    // 配置服务器结构体
    memset(&servaddr, 0, sizeof(servaddr));       // 对servaddr内容进行清零
    servaddr.sin_family = AF_INET;                // IPv4协议
    servaddr.sin_port = htons(atoi(argv[2]));     // 指定渠口，使用htons转换为大字节顺序
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);// 输入的IP地址

    // 尝试连接到服务器
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        // 如果出错且errno为EINPROGRESS，表示连接在进行
        if (errno != EINPROGRESS)
        {
            printf("connect(%s:%s) failed.\n", argv[1], argv[2]); 
            close(sockfd);  
            return -1;
        }
    }

    // 使用poll监听连接状态
    pollfd fds;             // 定义pollfd结构体
    fds.fd = sockfd;        // 监听socket
    fds.events = POLLOUT;   // 关注可写事件
    poll(&fds, 1, -1);      // 等待socket连接完成

    // 如果连接成功
    if (fds.revents == POLLOUT) // 如果是可写事件
        printf("connect successful.\n");
    else
        printf("connect failed.\n");
    
    // 向服务器发送数据
    for (int i = 0; i < 200000; i++) // 200000次交互,发送数据并接收数据
    {
        memset(buf, 0, sizeof(buf));    // 清空缓冲区
        printf("please input:"); 
        scanf("%s", buf);               // 从用户处读取输入

        // 发送数据到服务器
        if (send(sockfd, buf, strlen(buf), 0) <= 0)
        { 
            printf("write() failed.\n");  
            close(sockfd);  
            return -1;
        }
        
        memset(buf, 0, sizeof(buf));  // 清空缓冲区
        // 接收服务器返回数据
        if (recv(sockfd, buf, sizeof(buf), 0) <= 0) 
        { 
            printf("read() failed.\n");  
            close(sockfd);  
            return -1;
        }

        printf("recv: %s\n", buf);  // 显示服务器返回数据
    }
}
