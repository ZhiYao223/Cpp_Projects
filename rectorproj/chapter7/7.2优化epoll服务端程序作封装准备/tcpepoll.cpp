/*
 * 程序名：tcpepoll.cpp，此程序用于演示采用epoll模型实现网络通讯的服务端。
 * 作者：吴从周
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>          
#include <arpa/inet.h>
#include <sys/fcntl.h>
#include <sys/epoll.h>
#include <netinet/tcp.h>      // TCP_NODELAY需要包含这个头文件。

// 设置非阻塞的IO。
void setnonblocking(int fd)
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int main(int argc,char *argv[])
{
    if (argc != 3) 
    { 
        printf("usage: ./tcpepoll ip port\n"); 
        printf("example: ./tcpepoll 192.168.150.128 5085\n\n"); 
        return -1; 
    }

    // 创建服务端用于监听的listenfd。
    int listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (listenfd < 0)
    {
        perror("socket() failed"); return -1;
    }

    // 设置listenfd的属性，如果对这些属性不熟悉，百度之。
    int opt = 1; 
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,static_cast<socklen_t>(sizeof opt));  //必须的。
    setsockopt(listenfd,SOL_SOCKET,TCP_NODELAY   ,&opt,static_cast<socklen_t>(sizeof opt));//必须的。
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT ,&opt,static_cast<socklen_t>(sizeof opt)); //有用但在Reactor中意义不大。
    setsockopt(listenfd,SOL_SOCKET,SO_KEEPALIVE   ,&opt,static_cast<socklen_t>(sizeof opt));//可能有用但建议自己做心跳。

    setnonblocking(listenfd);    // 把服务端的listenfd设置为非阻塞的。

    struct sockaddr_in servaddr;                        // 服务端地址的结构体。
    servaddr.sin_family = AF_INET;                      // IPv4网络协议的套接字类型。
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);      // 服务端用于监听的ip地址。
    servaddr.sin_port = htons(atoi(argv[2]));           // 服务端用于监听的端口。

    if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 )
    {
        perror("bind() failed"); close(listenfd); return -1;
    }

    if (listen(listenfd,128) != 0 )        // 在高并发的网络服务器中，第二个参数要大一些。
    {
        perror("listen() failed"); close(listenfd); return -1;
    }

    int epollfd=epoll_create(1);        // 创建epoll句柄（红黑树）。

    // 为服务端的listenfd准备读事件。
    struct epoll_event ev;              // 声明事件的数据结构。
    ev.data.fd=listenfd;                 // 指定事件的自定义数据，会随着epoll_wait()返回的事件一并返回。
    ev.events=EPOLLIN;                // 让epoll监视listenfd的读事件，采用水平触发。

    epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&ev);     // 把需要监视的listenfd和它的事件加入epollfd中。

    struct epoll_event evs[10];      // 存放epoll_wait()返回事件的数组。

    while (true)        // 事件循环。
    {
        int infds=epoll_wait(epollfd,evs,10,-1);       // 等待监视的fd有事件发生。

        // 返回失败。
        if (infds < 0)
        {
            perror("epoll_wait() failed"); break;
        }

        // 超时。
        if (infds == 0)
        {
            printf("epoll_wait() timeout.\n"); continue;
        }

        // 如果infds>0，表示有事件发生的fd的数量。
        for (int i=0;i<infds;i++)       // 遍历epoll返回的数组evs。
        {
            // 1、如果是listenfd有事件，表示有新的客户端连上来。
            if (evs[i].data.fd==listenfd)   
            {
                struct sockaddr_in clientaddr;        // 客户端地址的结构体。
                socklen_t len = sizeof(clientaddr);   // 客户端地址结构体的长度。
                // 接受客户端的连接。
                int clientfd = accept(listenfd,(struct sockaddr*)&clientaddr,&len); 
                setnonblocking(clientfd);         // 客户端连接的fd必须设置为非阻塞的。
                // 输出客户端的ip地址和端口号。
                printf ("accept client(fd=%d,ip=%s,port=%d) ok.\n",clientfd,inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

                // 为新客户端连接准备读事件，并添加到epoll中。
                ev.data.fd=clientfd;            // 指定事件的自定义数据，会随着epoll_wait()返回的事件一并返回。
                ev.events=EPOLLIN|EPOLLET;      // 让epoll监视clientfd的读事件，采用边缘触发。
                epoll_ctl(epollfd,EPOLL_CTL_ADD,clientfd,&ev); // 把需要监视的clientfd和它的事件加入epollfd中。
            }
            //2、 如果是客户端连接的fd有事件。
            else                                        
            {
                // 对方已关闭，有些系统检测不到，可以使用EPOLLIN，recv()返回0。
                if (evs[i].events & EPOLLRDHUP)                     
                {
                    printf("1client(eventfd=%d) disconnected.\n",evs[i].data.fd);
                    close(evs[i].data.fd);       // 关闭客户端的fd。
                }                                //  普通数据  带外数据
                else if (evs[i].events & (EPOLLIN|EPOLLPRI))   // 接收缓冲区中有数据可以读。
                {
                    char buffer[1024];
                    // 由于使用非阻塞IO，一次读取buffer大小数据，直到全部的数据读取完毕。
                    while (true)             
                    {    
                        bzero(&buffer, sizeof(buffer)); // 清空缓冲区。
                        // 这行代码用了read()，也可以用recv()，一样的，不要纠结。nread是实际读取到的数据长度。
                        ssize_t nread = read(evs[i].data.fd, buffer, sizeof(buffer));    
                        if (nread > 0)      // 成功读取到了数据。
                        {
                            // 把接收到的报文内容原封不动的发回去。
                            printf("recv(eventfd=%d):%s\n",evs[i].data.fd,buffer);
                            send(evs[i].data.fd,buffer,strlen(buffer),0);
                        } 
                        // 读取数据的时候被信号中断，继续读取。
                        else if (nread == -1 && errno == EINTR){  
                            continue;
                        } 
                        // 全部的数据已读取完毕。
                        else if (nread == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {
                            break;
                        } 
                        // 客户端连接已断开。
                        else if (nread == 0)  {  
                            printf("2client(eventfd=%d) disconnected.\n",evs[i].data.fd);
                            close(evs[i].data.fd);            // 关闭客户端的fd。
                            break;
                        }
                    }
                }
                // 有数据需要写，暂时没有代码，以后再说。
                else if (evs[i].events & EPOLLOUT)                  
                {

                }
                // 其它事件，都视为错误。
                else                                                                    
                {
                    printf("3client(eventfd=%d) error.\n",evs[i].data.fd);
                    close(evs[i].data.fd);            // 关闭客户端的fd。
                }
            }
        }
    }

  return 0;
}