/*
 * 程序名：demo5.cpp，此程序用于演示socket的客户端
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>     // 提供与域名解析相关的函数和结构体
#include <sys/types.h> // 定义数据类型，如socket的类型
#include <sys/socket.h>// 提供socket相关函数和数据结构
#include <arpa/inet.h> // 提供IP地址转换函数
using namespace std;

class ctcpclient{
public:
    int m_clientfd; // 客户端的socket，-1表示未连接。>=0 表示已连接。
    string m_ip;    // 服务端IP地址/域名
    unsigned short m_port; // 服务端端口
    // 构造函数
    ctcpclient():m_clientfd(-1){}       

    // 向服务器发起连接请求，成功返回true，失败返回false。
    bool connect(const string &in_ip,const unsigned short in_port){
        if (m_clientfd != -1) return false; // 如果已经连接，返回false。
        m_ip = in_ip;       // 把服务端IP地址保存到成员变量中。
        m_port = in_port;   // 把服务端端口号保存到成员变量中。
        // 第1步：创建客户端的socket，指定使用IPv4 (AF_INET)、流式套接字 (SOCK_STREAM)，使用TCP协议(0)。
        if (m_clientfd = socket(AF_INET,SOCK_STREAM,0) == -1) return false;  // 创建失败，返回false。
        
        // 第2步：向服务器发起连接请求。
        // 用于存放服务器IP和端口的结构体。
        struct sockaddr_in servaddr;  
        // 将结构体清零，初始化。
        memset(&servaddr,0,sizeof(servaddr)); 
        // 协议族，固定填写AF_INET表示IPv4。
        servaddr.sin_family = AF_INET;        
        // 指定服务器端口，使用htons()转换为网络字节序。
        servaddr.sin_port = htons(m_port);  
        // 定义一个指向hostent结构体的指针，用于存放域名解析的结果。
        struct hostent* h;  
        // 解析传入的IP地址或域名，将字符串形式的IP或域名转换成网络字节序的IP地址。
        if ( (h = gethostbyname(m_ip.c_str())) == nullptr ) { 
            // 关闭套接字，释放资源。
            close(m_clientfd);  m_clientfd = -1; return false;
        }
        
        // 将解析得到的IP地址复制到servaddr结构体中。
        memcpy(&servaddr.sin_addr,h->h_addr,h->h_length);
        // 另一种方式：直接使用IP字符串，不进行域名解析。
        // servaddr.sin_addr.s_addr=inet_addr(argv[1]); 

        // 发起连接请求，connect()函数阻塞直到连接成功或失败。
        // connect与类成员函数重名，需要使用作用域解析符::connect表示库函数。
        if (::connect(m_clientfd, (struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
        { 
            // 关闭套接字，释放资源。
            close(m_clientfd); m_clientfd = -1; return false;
        }
        return true;  // 连接成功，返回true。
    }
    ~ctcpclient() {}      // 析构函数
};


int main(int argc,char *argv[])
{
  // 检查命令行参数，如果参数个数不等于3，则提示使用方法并退出
  if (argc!=3)
  {
    cout << "Using:./demo5 服务端的IP 服务端的端口\nExample:./demo5 192.168.101.138 5005\n\n"; 
    return -1;
  }


  ctcpclient tcpclient;  // 创建一个客户端对象。
  if (tcpclient.connect(argv[1],atoi(argv[2]))==false)
  {
    perror("connect()"); return -1;  // 返回-1。
  }
  // 第3步：与服务器进行数据通信。
  char buffer[1024];  // 定义缓冲区存储通信数据。
  for (int ii=0;ii<10;ii++)  // 循环发送10次数据。
  {
    int iret;  // 存放send/recv函数的返回值。
    // 清空缓冲区。
    // 生成待发送的请求报文，格式化字符串，将编号填入。
    memset(buffer,0,sizeof(buffer));  
    sprintf(buffer,"这是第%d个超级女生，编号%03d。",ii+1,ii+1);  
    // 向服务器发送请求报文，返回值表示实际发送的字节数。
    if ( (iret=send(tcpclient.m_clientfd,buffer,strlen(buffer),0))<=0)
    { 
      perror("send");  // 发送失败，打印错误信息并中断循环。
      break; 
    }
    cout << "发送：" << buffer << endl;
    // 清空缓冲区，准备接收服务器响应。
    memset(buffer,0,sizeof(buffer));  
    //接收服务器返回的数据,返回值为接收到的字节数, 0表示连接关闭,负值表示出错。
    if ( (iret=recv(tcpclient.m_clientfd,buffer,sizeof(buffer),0))<=0)
    {
       cout << "iret=" << iret << endl;  // 打印返回值，方便调试。
       break;  // 连接关闭或出错，退出循环。
    }
    cout << "接收：" << buffer << endl;  // 打印服务器响应内容。
    sleep(1);  // 暂停1秒，再发送下一个请求。
  }

  // 第4步：关闭socket，释放资源。
  close(tcpclient.m_clientfd);  // 关闭客户端socket。
}
