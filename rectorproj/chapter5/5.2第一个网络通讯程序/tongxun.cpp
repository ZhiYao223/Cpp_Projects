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

int main(int argc, char *argv[]){
    if(argc != 3){
        cout << "Using: ./demo1 服务器的ip地址 端口号\n Example: ./demo1 192.168.101.139 5005" << endl;
        return -1;
    }
    //第一步：创建客户端的socket 
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1){
        perror("socket error");
        return -1;
    }
    //第二步：向服务器发起连接请求
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[2]));
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(ret == -1){
        perror("connect error");
        return -1;
    }
    //第三步：与服务器通信，发送数据或接收数据
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    while(1){
        cout << "请输入要发送的数据：";
        //cin >> sendbuf;
        cin.getline(sendbuf, sizeof(sendbuf));
        send(clientfd, sendbuf, strlen(sendbuf), 0);
        recv(clientfd, recvbuf, sizeof(recvbuf), 0);
        cout << "接收到服务器的数据：" << recvbuf << endl;
   }
    //第四步：关闭socket 关闭连接
    close(clientfd);
    return 0;
}