#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <signal.h> 
#include <sys/wait.h>

#define PORT 12345 // 服务器端口
#define BACKLOG 5  // 限制的是等待连接的数量，而非最大连接数量。
//并不意味着只能有 5 个客户端连接，而是指最多有 5 个客户端连接在等待服务器 accept。
using namespace std;

//处理子进程结束信号，避免僵尸进程
void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(){
    // 创建服务器套接字
    int serverSocket, clientSocket;
    // 服务器地址用于绑定端口和监听, 客户端地址用于接收客户端连接
    struct sockaddr_in serverAddr, clientAddr;
    // 客户端地址长度，用于accept函数
    socklen_t addrLen = sizeof(clientAddr);

    // 创建服务器套接字，返回-1表示创建失败
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // 绑定地址和端口
    memset(&serverAddr, 0, sizeof(serverAddr));// 初始化服务器地址
    serverAddr.sin_family = AF_INET; // 使用IPv4地址
    serverAddr.sin_addr.s_addr = INADDR_ANY; // 任意IP地址
    serverAddr.sin_port = htons(PORT); // 设置端口
    // 绑定地址和端口，返回-1表示绑定失败
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Bind failed");
        return -1;
    }

    // 开始监听, 返回-1表示监听失败, BACKLOG表示最大同时连接数
    if (listen(serverSocket, BACKLOG) == -1) {
        perror("Listen failed");
        close(serverSocket);
        return -1;
    }
    cout << "Server is listening on port " << PORT << "..." << endl;

    // 处理子进程结束信号，避免僵尸进程
    signal(SIGCHLD, sigchld_handler);

    // 接收客户端连接并处理请求
    while (true) {
        // 接收客户端连接
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket == -1) {
            perror("Accept failed");
            continue;
        }
        // 打印客户端地址, inet_ntoa将网络地址转换为点分十进制地址
        cout << "Client connected: " << inet_ntoa(clientAddr.sin_addr)<< endl;

        // 创建子进程处理客户端请求
        // 子进程处理客户端请求，父进程继续监听
        pid_t pid = fork(); // fork返回0表示子进程，返回>0表示父进程
        if (pid == -1) {perror("Fork failed"); close(clientSocket);}
        else if (fork() == 0) { 
            close(serverSocket);  // 子进程关闭监听套接字
            // 处理客户端请求, 读取客户端发送的消息并回复, 直到客户端断开连接
            char buffer[1024] = {0}; // 缓冲区
            while (true) {
                // 接收客户端请求
                int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesRead <= 0) {
                    cout << "Client disconnected." << endl;
                    break;
                }
                cout << "Message received: " << buffer << endl;
                // 回传消息给客户端
                const char* response = "Hello from server!";
                send(clientSocket, response, strlen(response), 0);
                cout << "Response sent to client." << endl;
            }
            close(clientSocket);  // 子进程关闭客户端
            return 0; // 子进程结束
        }
        close(clientSocket); // 父进程关闭客户端，继续监听其他客户端
    }
    close(serverSocket);     // 关闭服务器套接字
    return 0;
}
