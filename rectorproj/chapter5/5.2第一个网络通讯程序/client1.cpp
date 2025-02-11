/*
 * 程序名：client.cpp，此程序用于演示socket的客户端
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

// argc表示命令行参数的数量，argv是一个指向参数数组的指针。
int main(int argc,char *argv[])
{
  // 第1步：检查参数数量是否等于3，如果不等于3，说明用户没有提供正确的参数数量。
  if (argc!=3) {
    cout << "Using:./client 服务端的IP 服务端的端口\nExample:./client 192.168.101.139 5005\n\n"; 
    return -1;
  }
  /* 第1步：创建客户端的socket。  */
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  // 如果创建失败，输出错误信息并返回-1。
  if (sockfd==-1) {
    perror("socket"); return -1;
  }
 
  /* 第2步：向服务器发起连接请求。*/ 
  // 声明了一个指向 hostent 结构体的指针，用于存放服务端的IP地址信息。
  struct hostent* h;   // IP地址信息的数据结构。
  // 调用 gethostbyname() 函数，把服务端IP地址从字符串类型转换成 hostent 结构体。
  if ( (h = gethostbyname(argv[1])) == 0 ) {  
    // 如果转换失败（返回值为0），则输出错误信息并关闭套接字 sockfd，然后返回 -1。
    cout << "gethostbyname failed.\n" << endl;  // 输出错误信息。
    close(sockfd); // 关闭socket。 
    return -1;     // 返回错误代码。
  }
  //声明 sockaddr_in 结构体变量 servaddr，用于存放服务端的IP地址和端口号信息。
  struct sockaddr_in servaddr;      
  // 初始化结构体，将 servaddr 结构体清零，以便后续使用。。        
  memset(&servaddr,0,sizeof(servaddr));
  // 设置协议簇为AF_INET，IP地址格式为网络字节序，端口号转换为网络字节序。
  servaddr.sin_family = AF_INET; //设置 servaddr 结构体中的地址族为 IPv4。
  // 将通过 gethostbyname() 函数获取的服务端IP地址复制到 servaddr 结构体中的 sin_addr 字段。
  memcpy(&servaddr.sin_addr,h->h_addr,h->h_length); 
  // 将命令行参数中的服务端通信端口号转换成整数并转换成网络字节序（大端序），然后存放在 servaddr  结构体中的 sin_port 字段。
  servaddr.sin_port = htons(atoi(argv[2])); // 指定服务端的通信端口。        
  // 使用 connect() 函数向服务端发起连接请求。
  if (connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))!=0)  { 
    // 如果连接失败，输出错误信息并关闭套接字 sockfd，然后返回 -1。
    perror("connect"); close(sockfd); return -1; 
  }
  
  /* 第3步：与服务端通讯，客户发送一个请求报文后等待服务端的回复，收到回复后，再发下一个请求报文。*/
  // 定义一个缓冲区(长度为1024的字符数组)，用于存放客户端发送和接收的数据。
  char buffer[1024];
  for (int  i=0; i<100; i++)  // 循环5次，将与服务端进行5次通讯。
  {
    int iret;
    // 清空缓冲区，以确保没有之前的残留数据，准备发送数据。
    memset(buffer,0,sizeof(buffer));
    // 向缓冲区中写入数据，格式为：“这是第i条信息，编号i。”，形成一个请求报文的内容。。
    sprintf(buffer,"这是第%d条信息，编号%03d。", i+1, i+1);  // 生成请求报文内容。
    // 将请求报文发送给服务端，如果发送失败则输出错误信息，并跳出循环。
    if ( (iret=send(sockfd,buffer,strlen(buffer),0))<=0)
    { 
      perror("send"); break; 
    }
    cout << "发送：" << buffer << endl;
    // 清空接收缓冲区，以便接收服务端的回应。
    memset(buffer,0,sizeof(buffer));
    /* 接收服务端的回应报文，如果服务端没有发送回应报文，recv()函数将阻塞等待。*/
    if ( (iret=recv(sockfd,buffer,sizeof(buffer),0))<=0) {
       cout << "iret=" << iret << endl; break;
    }
    cout << "接收：" << buffer << endl;
    // 程序暂停1秒钟，然后进行下一次通讯。
    sleep(1);
  }
 
  /* 第4步：关闭socket，释放资源。*/
  close(sockfd);
}