#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>

int main()
{
    const char *fifo = "rectorproj/chapter1/myfifo";
    mkfifo(fifo, 0660); //创建管道

    //打开管道用于写入
    int fd = open(fifo, O_WRONLY);
    const char *message = "Hello, Consumer!";
    //向管道写入数据
    write(fd, message, strlen(message)+1);
    //关闭管道
    close(fd);
    return 0;
}