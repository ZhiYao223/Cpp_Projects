/*
    Socket 编程（套接字编程）
1. 什么是 Socket
    Socket 是网络通信的端点，通过它可以在两个或多个主机之间进行数据传输。
    本质上，socket 是一种特殊的文件，read 和 write 操作同样适用。
2. 套接字类型
    流式套接字 (SOCK_STREAM)：基于 TCP 协议，提供可靠的面向连接的通信。
    数据报套接字 (SOCK_DGRAM)：基于 UDP 协议，无连接，速度快但不可靠。
3.基本 Socket 操作流程
    创建套接字：socket()
    绑定地址：bind()
    监听连接（TCP）：listen()
    接受连接（TCP）：accept()
    连接服务器（客户端）：connect()
    数据发送/接收：send() 和 recv()
    关闭套接字：close()
*/

//简单 TCP 服务器

