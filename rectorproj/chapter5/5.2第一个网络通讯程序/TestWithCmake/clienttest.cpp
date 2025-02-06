#include <iostream>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
int main(int argc, char *argv[])
{
    if (argc != 3){
        std::cout << "Using:./client 服务端的IP 服务端的端口\n Example:./client";
        return -1;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        perror("socket");
        return -1;
    }
    struct hostent *ip;
    if ((ip = gethostbyname(argv[1])) == 0){
        std::cout << "gethostbyname failed.\n" << std::endl;
        close(sockfd);
        return -1;
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    memcpy(&servaddr.sin_addr, ip->h_addr_list[0], ip->h_length);
    servaddr.sin_port = htons(atoi(argv[2]));

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0){
        perror("connect");
        close(sockfd);
        return -1;
    }

    char buffer[1024];
    for(int i = 0; i < 5; i++){
        int iret;
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "  这是第%d个数据包", i + 1);
        iret = send(sockfd, buffer, strlen(buffer), 0);
        if (iret <= 0){
            perror("send"); break;
        }
        std::cout << "发送的数据是：" << buffer << std::endl;
        memset(buffer, 0, sizeof(buffer));
        iret = recv(sockfd, buffer, sizeof(buffer), 0);
        if (iret <= 0){
         perror("recv");   break;
        }
        std::cout << "接收到的数据是：" << buffer << std::endl;
        sleep(1);
    }
    close(sockfd);
}
