/*
代码流程概述
    1. 创建服务器socket，使用 socket 创建一个监听套接字。
    2. 绑定地址和端口，绑定到指定的 IP 地址和端口。
    3. 监听连接，调用 listen 让服务器处于监听状态，等待客户端连接。
    4. 初始化 select 相关的描述符集合，将服务器socket和客户端socket都加入到监听集合中。
    5. 调用 select 监听，阻塞等待客户端连接或数据到来。
    6. 处理新连接或数据：
    7. 如果服务器socket有事件发生，调用 accept 接收新客户端。
    8. 如果客户端socket有数据到达，调用 read 读取数据。
    9. 如果客户端断开连接，关闭socket并将其置为0。
*/
#include <iostream>  // 标准输入输出库
#include <sys/socket.h>  // 提供socket函数及结构体
#include <netinet/in.h>  // 包含IP地址结构体定义
#include <unistd.h>  // 提供read、write、close等系统调用
#include <cstring>  // 提供字符串操作函数
#include <fcntl.h>  // 文件控制（fcntl）
#include <sys/select.h>  // select函数及相关操作

#define PORT 8080  // 服务器监听端口号
#define MAX_CLIENTS 10  // 最大客户端连接数

int main() {
    // 1.定义服务器socket描述符，新socket描述符，客户端socket数组(初始化为0)
    int server_fd, new_socket, client_socket[MAX_CLIENTS] = {0};  
    struct sockaddr_in address;  // 服务器地址结构体
    int addrlen = sizeof(address);  // 地址长度
    char buffer[1024] = {0};  // 数据缓冲区初始化

    // 2. 创建服务器socket (AF_INET表示IPv4，SOCK_STREAM表示TCP协议)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);  
    if (server_fd == 0) {  // 如果socket创建失败，打印错误信息并退出
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // 3. 配置服务器地址和端口
    address.sin_family = AF_INET;           // 使用IPv4地址族
    address.sin_addr.s_addr = INADDR_ANY;   // 监听所有网络接口 (0.0.0.0)
    address.sin_port = htons(PORT);         // 端口号转换为网络字节序
    
    // 4. 绑定socket到指定地址和端口
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // 5. 监听端口，等待客户端连接，最多同时处理3个未完成连接请求
    listen(server_fd, 3);
    
    std::cout << "Listening on port " << PORT << "...\n";

    fd_set readfds;  // 定义文件描述符集合
    int max_sd;  // 记录最大描述符

    // 6. 服务器主循环，持续监听客户端连接和消息
    while (true) {
        // 每次循环都需要重新初始化描述符集
        FD_ZERO(&readfds);  // 清空描述符集合
        FD_SET(server_fd, &readfds);  // 将服务器socket加入监听集合
        max_sd = server_fd;  // 初始化最大描述符为服务器socket

        // 遍历客户端socket，将有效的socket加入集合
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_socket[i];  // 获取当前客户端socket
            if (sd > 0) FD_SET(sd, &readfds);  // 将有效socket添加到描述符集合中
            if (sd > max_sd) max_sd = sd;  // 更新最大描述符
        }

        // 设置超时时间为5秒
        struct timeval timeout;
        timeout.tv_sec = 5;  // 秒
        timeout.tv_usec = 0; // 微秒，0表示不加额外微秒时间

        // 调用select监听所有描述符是否有事件发生，阻塞等待最多5秒，如果没有事件则返回0
        int activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);
        
        if (activity == 0) {
            // 5秒内无活动，继续下一轮循环
            std::cout << "Timeout, no activity within 5 seconds\n";
            continue;
        }
        // 如果select调用出错且不是被信号中断，打印错误
        if ((activity < 0) && (errno != EINTR)) {
            perror("select error");
        }

        // 处理新的客户端连接请求
        if (FD_ISSET(server_fd, &readfds)) {
            // 接受新连接，返回新的客户端socket
            new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
            std::cout << "New connection\n";

            // 将新客户端socket存入客户端数组中
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_socket[i] == 0) {  // 找到空闲位置存入新socket
                    client_socket[i] = new_socket;
                    break;  // 添加完成后退出循环
                }
            }
        }

        // 处理现有客户端发送的消息
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_socket[i];  // 获取客户端socket
            if (FD_ISSET(sd, &readfds)) {  // 如果该socket有数据可读
                int valread = read(sd, buffer, 1024);  // 读取数据到buffer中
                if (valread == 0) {  // 如果读取到0，说明客户端断开连接
                    close(sd);  // 关闭socket
                    client_socket[i] = 0;  // 将客户端socket置为0，表示空闲
                    std::cout << "Client disconnected\n";
                } else {
                    buffer[valread] = '\0';  // 在读取的数据末尾加字符串结束符
                    std::cout << "Received: " << buffer << "\n";  // 打印客户端发送的数据
                    send(sd, buffer, strlen(buffer), 0);  // 将数据回送给客户端，实现echo
                }
            }
        }
    }
    
    return 0;
}
