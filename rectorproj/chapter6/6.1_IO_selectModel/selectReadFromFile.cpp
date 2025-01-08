/*
    执行过程解析:
    -打开一个名为 example.txt 的文件，返回文件描述符 fd。
    -使用 select 等待文件变为可读状态，超时时间设置为 5 秒。
    -如果 5 秒内文件中有数据到达，read 读取数据并打印到终端。
    -如果超时或出错，给出相应提示。
*/
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main(){
    int fd = open("test.txt", O_RDONLY);
    if(fd == -1){ 
        perror("open");
        return -1;
    }
    fd_set read_fds; 
    FD_ZERO(&read_fds); 
    FD_SET(fd, &read_fds);

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    
    printf("Waiting for data...\n");
    // 5秒内没有数据可读，select返回0
    int result = select(fd+1,&read_fds,NULL,NULL,&timeout);
    if(result > 0){
        if(FD_ISSET(fd, &read_fds)){
            char buffer[1024] = {0};
            int bytesRead = read(fd, buffer, sizeof(buffer));
            if(bytesRead == -1){
                perror("read");
                return -1;
            }
            printf("Read %d bytes: %s\n", bytesRead, buffer);
        }
    }else if(result == 0){
        printf("Timeout, no data available\n");
    }else{
        perror("select");
    }
    close(fd);
    return 0;
}