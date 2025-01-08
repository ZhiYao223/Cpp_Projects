// 导入必要的头文件。
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>   // 提供IP协议族定义。
#include <sys/socket.h>   // 提供socket函数及数据结构。
#include <arpa/inet.h>    // 提供IP地址转换函数。
#include <time.h>         // 提供时间相关函数。

int main(int argc, char *argv[])
{
    // 判断命令行参数是否符合要求，若不符合则输出提示信息并退出程序。
    if (argc != 3)
    {
        printf("usage:./client ip port\n"); return -1;
    }

    int sockfd;  // 定义客户端socket描述符。
    struct sockaddr_in servaddr;  // 定义服务器地址结构体。
    char buf[1024];  // 定义缓冲区用于存放发送和接收的数据。
 
    // 创建socket，如果创建失败，输出错误信息并退出。
    if ((sockfd=socket(AF_INET,SOCK_STREAM,0))<0) 
    { 
        printf("socket() failed.\n"); return -1; 
    }
    
    // 初始化服务器地址结构体，将内存清零。
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;  // 设置地址族为IPv4。
    servaddr.sin_port=htons(atoi(argv[2]));  // 设置端口号（命令行参数转为整数后转为网络字节序）。
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);  // 将命令行输入的IP地址转为二进制格式。

    // 尝试连接服务器，如果连接失败，输出提示信息并关闭socket。
    if (connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)) != 0)
    {
        printf("connect(%s:%s) failed.\n",argv[1],argv[2]); 
        close(sockfd);  
        return -1;
    }

    printf("connect ok.\n");  // 连接成功，输出提示信息。

    // printf("开始时间：%d",time(0));  // （注释掉）打印开始时间。

    // 发送和接收数据的循环，限制循环次数为20万次。
    for (int ii=0;ii<200000;ii++)
    {
        // 清空缓冲区，准备输入数据。
        memset(buf,0,sizeof(buf));
        printf("please input:");  // 提示用户输入数据。
        scanf("%s",buf);  // 读取用户输入并存入缓冲区。

        // 发送数据到服务器，如果发送失败，输出错误信息并关闭socket。
        if (send(sockfd,buf,strlen(buf),0) <=0)
        { 
            printf("write() failed.\n");  
            close(sockfd);  
            return -1;
        }
        
        // 清空缓冲区，准备接收服务器返回的数据。
        memset(buf,0,sizeof(buf));
        // 接收服务器返回的数据，如果接收失败，输出错误信息并关闭socket。
        if (recv(sockfd,buf,sizeof(buf),0) <=0) 
        { 
            printf("read() failed.\n");  
            close(sockfd);  
            return -1;
        }

        // 打印服务器返回的数据。
        printf("recv:%s\n",buf);
    }

    // printf("结束时间：%d",time(0));  // （注释掉）打印结束时间。
}
