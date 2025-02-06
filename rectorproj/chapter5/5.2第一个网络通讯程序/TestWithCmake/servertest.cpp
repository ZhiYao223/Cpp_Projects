#include <iostream>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    if (argc != 2){
        std::cout << "Using:./servertest 通讯端口\n Example:./servertest 5005\n\n";
        std::cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
        std::cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
        return -1;
    }
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1){
        perror("socket");
        return -1;
    }
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0){
        perror("bind");
        close(listenfd);
        return -1;
    }
    if (listen(listenfd, 5) != 0){
        perror("listen");
        close(listenfd);
        return -1;
    }
    int clientfd = accept(listenfd, 0, 0);
    if (clientfd == -1){
        perror("accept");
        close(listenfd);
        return -1;
    }
    std::cout << "客户端已连接。\n";
    char buffer[1024];
    while(true){
        memset(buffer, 0, sizeof(buffer));
        int iret = recv(clientfd, buffer, sizeof(buffer), 0);
        if (iret <= 0){
            break;
        }
        std::cout << "接收到的数据是：" << buffer << std::endl;
        strcpy(buffer, "发送成功，客户端已接收");
        send(clientfd, buffer, strlen(buffer), 0);
    }
}