/*
 * 程序名：server.cpp，此程序用于演示socket通信的服务端
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc,char *argv[])
{
  // 第1步：检查参数数量是否等于2，如果不等于2，说明用户没有提供正确的参数数量。
  if (argc!=2) {
    cout << "Using:./server 通讯端口\nExample:./server 5005\n\n";   // 端口大于1024，不与其它的重复。
    cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
    cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
    return -1;
  }
  // 第1步：创建服务端的socket。 
  int listenfd = socket(AF_INET,SOCK_STREAM,0);
  // 如果创建失败，输出错误信息并返回-1。
  if (listenfd==-1) {
    perror("socket"); return -1; 
  }
  
  // 第2步：把服务端用于通信的IP和端口绑定到socket上。 
  struct sockaddr_in servaddr;          // 用于存放服务端IP和端口的数据结构。
  // 初始化 servaddr 结构体，清零操作，以免里面含有之前的数据。
  memset(&servaddr,0,sizeof(servaddr));
  // 通信协议为IPv4协议，IP地址为本机IP地址，端口号为命令行参数指定的端口号。
  servaddr.sin_family = AF_INET;       
  // IP地址设置为 INADDR_ANY，表示服务端可以使用任意可用的网络接口。
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  // 指定通信端口，普通用户只能用1024以上的端口。
  // 从命令行参数获取服务端通信端口号，转换为整数后，转换为网络字节序，并存放在sin_port 字段。
  servaddr.sin_port = htons(atoi(argv[1]));     
  // 通过 bind() 函数将服务端IP地址和端口号与套接字进行绑定。
  if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) != 0 ){ 
    // 如果绑定失败，输出错误信息并关闭套接字 listenfd，然后返回 -1。
    perror("bind"); close(listenfd); return -1; 
  }
 
  // 第3步：把socket设置为可连接（监听）的状态。
  if (listen(listenfd,5) != 0 ) { 
    // 如果设置监听状态失败，输出错误信息并关闭套接字 listenfd，然后返回 -1。
    perror("listen"); close(listenfd); return -1; 
  }
 
  // 第4步：受理客户端的连接请求，如果没有客户端连上来，accept()函数将阻塞等待。
  int clientfd = accept(listenfd,0,0);
  if (clientfd==-1){
    // 如果accept被信号中断，返回-1，否则accept会一直阻塞等待。
    perror("accept"); close(listenfd); return -1; 
  }
  cout << "客户端已连接。\n";
 
  // 第5步：与客户端通信，接收客户端发过来的报文后，回复ok。
  char buffer[1024];
  while (true)
  {
    int iret;
    // 清空接收缓冲区，准备接收数据。
    memset(buffer,0,sizeof(buffer));
    // 接收客户端的请求报文，如果客户端没有发送请求报文，recv()函数将阻塞等待。
    // 如果客户端已断开连接，recv()函数将返回0。
    if ( (iret=recv(clientfd,buffer,sizeof(buffer),0))<=0) 
    {
       cout << "iret=" << iret << endl;  break;   
    }
    cout << "接收：" << buffer << endl;
    // 准备回应客户端的请求报文内容。
    strcpy(buffer,"ok"); // 回应ok。 
    // 向客户端发送回应报文。
    if ( (iret=send(clientfd, buffer, strlen(buffer),0))<=0) 
    { 
      perror("send"); break; 
    }
    cout << "发送：" << buffer << endl;
  }
 
  // 第6步：关闭socket，释放资源。
  close(listenfd);   // 关闭服务端用于监听的socket。
  close(clientfd);   // 关闭客户端连上来的socket。
}