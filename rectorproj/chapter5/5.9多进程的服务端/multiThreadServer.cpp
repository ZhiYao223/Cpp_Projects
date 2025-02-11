//这个示例展示了如何使用多线程实现一个简单的并发服务器。你可以根据需要扩展功能，例如添加协议解析、日志记录、线程池等。
/*
总结修改步骤：
1. 引入必要的头文件：<thread>, <mutex>, <vector>。
2. 创建一个处理客户端连接的函数handle_client，接收客户端套接字作为参数。
3. 在主循环中，每当accept成功时，创建新线程处理该客户端，并将线程存储或分离。
4. 使用互斥锁保护共享资源，如std::cout。
5. 调整主函数结构，确保主线程持续接受新连接，而子线程处理客户端通信。
6. 处理线程的分离或加入，避免资源泄漏。
7. 修改数据发送逻辑，确保每个线程独立处理自己的客户端。
*/

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx; //全局互斥锁保护共享资源
//客户端处理线程函数
void handle_client(int clientfd){
    char buffer[1024];
    while(true){
        memset(buffer, 0, sizeof(buffer));
        int iret = recv(clientfd,buffer,sizeof(buffer),0);
        if(iret <= 0){
            std::lock_guard<std::mutex> lock(mtx); //加锁
            std::cout << "客户端断开连接，套接字：" << clientfd << std::endl;
            break;
        }
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "接收到的数据（客户端" << clientfd << "）：" << buffer << std::endl;

        // 构造响应消息
        strcpy(buffer, "发送成功，服务端已处理");
        if (send(clientfd, buffer, strlen(buffer), 0) <= 0) {
                std::lock_guard<std::mutex> lock(mtx);
                std::cout << "向客户端发送数据失败。\n";
                break;
        }
    }
    close(clientfd); // 关闭客户端套接字
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        std::cout << "Using:./server 通讯端口\nExample:./server 5005\n\n";
        std::cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
        std::cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
        return -1;
    }
    //创建监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        perror("socket");
        return -1;
    }
    //设置服务器地址
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    //绑定地址和端口
    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0){
        perror("bind");
        close(listenfd);
        return -1;
    }

    //开始监听
    int backlog = 5;
    if(listen(listenfd, backlog) != 0){
        perror("listen");
        close(listenfd);
        return -1;
    }
    std::cout << "服务器启动成功，等待客户端连接...\n";
    std::vector<std::thread> threads; //存储线程对象
    while(true){
        //接受客户端连接
        struct sockaddr_in clientaddr;
        socklen_t clientaddr_len = sizeof(clientaddr);
        int clientfd = accept(listenfd,(struct sockaddr *)&clientaddr, &clientaddr_len);
        if(clientfd == -1){
            perror("accept");
            continue; //继续等待其他客户端连接
        }
        std::lock_guard<std::mutex> lock(mtx); //加锁
        std::cout << "客户端连接成功，IP地址：" << inet_ntoa(clientaddr.sin_addr) << ":"<< ntohs(clientaddr.sin_port) << ", 分配套接字："<< clientfd << std::endl;
        //创建新线程处理客户端
        threads.push_back(std::thread(handle_client, clientfd));
        //分离线程,自动回收资源
        threads.back().detach();
    }
    //清理资源(正常情况下不会执行到这里)
    close(listenfd);
    for(auto &th : threads){
        if(th.joinable()){
            th.join();
        }
    }
    return 0;          

}