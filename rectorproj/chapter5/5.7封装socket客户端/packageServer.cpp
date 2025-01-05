#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

using namespace std;

class SocketServer {
private:
    int server_fd;
    struct sockaddr_in server_addr;
    int port;

public:
    // 构造函数：初始化 server_fd
    SocketServer(int port) : port(port) {
        server_fd = -1;
        memset(&server_addr, 0, sizeof(server_addr));
    }

    // 析构函数：关闭socket
    ~SocketServer() {
        if (server_fd != -1) {
            close(server_fd);
            cout << "Server socket closed." << endl;
        }
    }

    // 创建socket
    bool createSocket() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            perror("Socket creation failed");
            return false;
        }
        cout << "Socket created successfully." << endl;
        return true;
    }
 
    // 绑定IP和端口
    bool bindSocket() {
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;  // 绑定到任意IP
        server_addr.sin_port = htons(port);

        if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            perror("Bind failed");
            return false;
        }
        cout << "Socket bound to port " << port << endl;
        return true;
    }

    // 开始监听客户端连接
    bool startListening(int backlog = 5) {
        if (listen(server_fd, backlog) == -1) {
            perror("Listen failed");
            return false;
        }
        cout << "Listening for connections..." << endl;
        return true;
    }

    // 接受客户端连接
    int acceptClient() {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        if (client_fd == -1) {
            perror("Accept failed");
        } else {
            cout << "Client connected." << endl;
        }
        return client_fd;
    }

    // 处理客户端通信（接收并发送消息）
    void handleClient(int client_fd) {
        char buffer[1024] = {0};

        // 接收数据
        int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            cout << "Client disconnected." << endl;
            close(client_fd);
            return;
        }

        cout << "Message received: " << buffer << endl;

        // 发送响应
        const char* response = "Hello from server";
        send(client_fd, response, strlen(response), 0);
        cout << "Response sent to client." << endl;

        // 关闭客户端连接
        close(client_fd);
    }

    // 启动服务器
    void run() {
        if (!createSocket()) return;
        if (!bindSocket()) return;
        if (!startListening()) return;

        while (true) {
            int client_fd = acceptClient();
            if (client_fd != -1) {
                // 每个客户端连接都在新线程中处理
                thread t(&SocketServer::handleClient, this, client_fd);
                t.detach();  // 线程分离，独立处理客户端
            }
        }
    }
};

// 主函数
int main() {
    SocketServer server(8080);  // 启动服务器监听8080端口
    server.run();
    return 0;
}
