#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    //创建命名管道的路径
    const char *fifo = "rectorproj/chapter1/myfifo";
    //打开管道用于读取
    int fd = open(fifo, O_RDONLY);
    //读取缓冲区,初始化
    char buffer[100] = {0};
    //从管道读取数据，留一个字节给'\0'
    read(fd,buffer,sizeof(buffer)-1);
    //确保字符串结束
    buffer[sizeof(buffer)-1] = '\0';
    //输出接收到的数据
    std::cout << "Received:"<<buffer<<std::endl;
    //关闭管道
    close(fd);
    return 0;
}