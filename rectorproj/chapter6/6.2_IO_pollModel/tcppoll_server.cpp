/*
 * 程序名：tcppoll.cpp，此程序用于演示采用poll模型实现网络通讯的服务端。
 * 作者：吴从周
*/
#include <stdio.h>      // 标准输入输出库
#include <unistd.h>     // 提供对POSIX操作系统API的访问，如read、write等
#include <stdlib.h>     // 提供内存管理、进程控制等函数
#include <string.h>     // 字符串操作函数
#include <poll.h>       // poll函数的头文件，用于IO多路复用
#include <sys/socket.h> // 套接字接口
#include <arpa/inet.h>  // 提供IP地址转换函数
#include <sys/fcntl.h>  // 文件控制，如非阻塞模式设置

// 初始化服务端的监听端口，返回监听socket描述符
int initserver(int port);

int main(int argc,char *argv[])
{
    // 参数数量判断，确保传入端口号
    if (argc != 2) { 
        printf("usage: ./tcppoll port\n"); 
        return -1; 
    }

    // 初始化服务端监听socket
    int listensock = initserver(atoi(argv[1])); // 将传入的端口号字符串转为整数
    printf("listensock=%d\n",listensock);

    // 监听socket初始化失败
    if (listensock < 0) { 
        printf("initserver() failed.\n"); 
        return -1; 
    }

    // 定义pollfd结构体数组，用于存放需要监视的socket
    pollfd fds[2048]; 

    // 初始化fds数组，将所有socket置为-1，表示poll将忽略这些位置
    for (int ii=0;ii<2048;ii++)             
        fds[ii].fd=-1;   

    // 让poll监视监听socket的读事件
    fds[listensock].fd = listensock;          // 监听socket添加到fds数组中
    fds[listensock].events = POLLIN;          // 监视读事件（POLLIN）

    int maxfd = listensock;                   // 记录需要监视的最大socket描述符

    // 事件循环，持续监测事件发生
    while (true)        
    {
        // 调用poll函数，等待事件发生，超时时间为10秒（10000毫秒）
        int infds=poll(fds,maxfd+1,10000); 

        // poll调用失败
        if (infds < 0)
        {
            perror("poll() failed"); 
            break;
        }

        // poll超时，无事件发生
        if (infds == 0)
        {
            printf("poll() timeout.\n"); 
            continue;
        }

        // poll返回，说明有事件发生
        for (int eventfd=0; eventfd<=maxfd; eventfd++)
        {
            if (fds[eventfd].fd<0) continue;    // 如果socket描述符无效，继续下一个循环

            // 如果该socket没有读事件发生，跳过
            if ((fds[eventfd].revents&POLLIN)==0)  
                continue;  

            // 如果监听socket发生事件，说明有新的客户端连接
            if (eventfd==listensock)
            {
                struct sockaddr_in client;      
                socklen_t len = sizeof(client);
                // 接收客户端连接
                int clientsock = accept(listensock,(struct sockaddr*)&client,&len);
                if (clientsock < 0) { 
                    perror("accept() failed"); 
                    continue; 
                }

                printf ("accept client(socket=%d) ok.\n",clientsock);

                // 将新的客户端socket加入fds数组，监视其读事件
                fds[clientsock].fd=clientsock;
                fds[clientsock].events=POLLIN;

                // 更新最大描述符
                if (maxfd<clientsock) 
                    maxfd=clientsock;    
            }
            else
            {
                // 如果发生事件的是客户端socket，可能是有数据到达或客户端断开

                char buffer[1024]; // 定义缓冲区，存放接收的数据
                memset(buffer,0,sizeof(buffer));
                
                // 读取客户端数据，如果返回值<=0，说明客户端断开连接
                if (recv(eventfd,buffer,sizeof(buffer),0)<=0)
                {
                    printf("client(eventfd=%d) disconnected.\n",eventfd);

                    close(eventfd);               // 关闭socket
                    fds[eventfd].fd=-1;           // 将对应位置的socket置为-1，不再监视该socket
          
                    // 如果断开的socket是maxfd，需要重新计算最大描述符
                    if (eventfd == maxfd)
                    {
                        for (int ii=maxfd;ii>0;ii--)  
                        {
                            if (fds[ii].fd!=-1)
                            {
                                maxfd = ii; 
                                break;
                            }
                        }
                    }
                }
                else
                {
                    // 如果客户端有数据到达，打印数据并回传给客户端
                    printf("recv(eventfd=%d):%s\n",eventfd,buffer);
                    send(eventfd,buffer,strlen(buffer),0);
                }
            }
        }
    }

    return 0;
}

// 初始化服务端的监听端口
int initserver(int port)
{
    // 创建socket，使用IPv4和TCP协议
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if (sock < 0)
    {
        perror("socket() failed"); 
        return -1;
    }

    // 设置socket选项，端口复用
    int opt = 1; 
    unsigned int len = sizeof(opt); 
    //是一个用于设置 socket 选项的系统调用，允许对 socket 进行配置，以控制其行为。
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,len);

    struct sockaddr_in servaddr;              // 定义服务器地址结构体
    servaddr.sin_family = AF_INET;            // 使用IPv4地址族
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 监听所有地址
    servaddr.sin_port = htons(port);          // 设置监听端口号

    // 绑定socket和地址
    if (bind(sock,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 )
    {
        perror("bind() failed"); 
        close(sock); 
        return -1;
    }

    // 开始监听，最大监听队列长度为5
    if (listen(sock,5) != 0 )
    {
        perror("listen() failed"); 
        close(sock); 
        return -1;
    }

    return sock;  // 返回监听socket描述符
}
