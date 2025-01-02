#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    const char* message = "downloadfile,filename.txt";

    // 创建客户端套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Socket creation failed!" << std::endl;
        return 1;
    }

    // 设置服务器地址信息
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);  // 目标端口
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 连接本机

    // 连接到服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Connection failed!" << std::endl;
        close(clientSocket);
        return 1;
    }

    // 发送消息
    if (send(clientSocket, message, strlen(message), 0) == -1) {
        std::cerr << "Send failed!" << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Message sent: " << message << std::endl;

    // 关闭套接字
    close(clientSocket);

    return 0;
}
