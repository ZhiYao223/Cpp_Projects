/*
    Linux 文件操作
    文件描述符（File Descriptor，简称 FD）是一个整数，表示已打开的文件。
    每个进程都有三个默认的文件描述符：
    标准输入：stdin (0)
    标准输出：stdout (1)
    标准错误：stderr (2)
*/
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main(){
    // 打开文件
    int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    if(fd == -1){
        perror("open error");
        return -1;
    }
    const char *text = "Hello Linux file!";
    // 写入文件
    write(fd, text, strlen(text));
    // 移动文件指针到文件开头
    lseek(fd, 0, SEEK_SET);
    // 读取文件
    char buf[100] = {0};
    // 读取文件
    read(fd, buf, sizeof(buf));
    std::cout << "file data: " << buf << std::endl;
    // 关闭文件
    close(fd);
    return 0;
}