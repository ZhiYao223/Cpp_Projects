#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

using namespace std;

class SocketClient {
private:
    int sockfd;
    struct sockaddr_in serverAddr;
public:
    //构造函数，初始化socket对象
    SocketClient() {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            perror("Socket creation failed");
            return;
        }
    }
    //创建socket并返回socket描述符
    bool createSocket() {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            perror("Socket creation failed");
            return false;
        }
        return true;
    }
    // 连接服务器，设置服务器IP和端口
    bool setServerAddr(const string &ip, const int port) {
        serverAddr.sin_family = AF_INET; // 使用IPv4地址
        serverAddr.sin_port = htons(port); // 设置端口
        struct hostent* h; // 用于存放服务端IP地址的结构体指针
        if ((h = gethostbyname(ip.c_str())) == nullptr) {
            close(sockfd);
            sockfd = -1;
            return false;
        }
        // 将解析得到的IP地址复制到servaddr结构体中。
        memcpy(&serverAddr.sin_addr, h->h_addr, h->h_length);
        return true;
    }
    // 连接服务器
    bool connectToServer() {
        if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            close(sockfd);
            sockfd = -1;
            return false;
        }
        return true;
    }
    // 发送数据
    bool sentData(const string &buffer) {
        if (sockfd == -1) return false;
        if (send(sockfd, buffer.c_str(), buffer.size(), 0) == -1) {
            return false;
        }
        return true;
    }
    // 接收数据
    bool receiveData(string &buffer, const size_t maxlen) {
        buffer.clear();
        buffer.resize(maxlen);
        int readn = recv(sockfd, &buffer[0], buffer.size(), 0);
        if (readn <= 0) return false;
        buffer[readn] = '\0'; // 添加字符串结束符
        return true;
    }

    // 析构函数
    ~SocketClient() {
        if(sockfd != -1) {
            close(sockfd);
        }
    }

};
int main(int argc, char* argv[]){
    if (argc != 3){
        cout << "Usage: ./socketClient ip port" << endl;
        return -1;
    }
    SocketClient client;
    // 创建socket
    if (!client.createSocket()){
        return -1;
    }

    // 设置服务器IP和端口
    if (!client.setServerAddr(argv[1], atoi(argv[2]))){
        return -1;
    }

    // 连接服务器
    if (!client.connectToServer()){
        return -1;
    }

    // 发送数据
    string buffer = "Hello, Server!";
    if (!client.sentData(buffer)){
        return -1;
    }
    // 接收数据
    string recvBuffer;
    if (!client.receiveData(recvBuffer, 1024)){
        return -1;
    }
    cout << "Received: " << recvBuffer << endl;
    return 0;
}