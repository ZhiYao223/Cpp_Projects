// 让VSCode识别为C++代码
// -*- coding: utf-8; mode: c++; -*-

#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

#define SHM_SIZE 1024 //共享内存大小

int main(){
    key_t key = ftok("/tmp", 'A'); //生成key
    if(key == -1){
        perror("fork");
        exit(1);
    }
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);//创建共享内存
    if (shmid == -1){
        perror("shmget");
        exit(1);
    }
    printf("共享内存ID: %d\n", shmid);
    return 0;
}

// 仅作为占位代码
#include <iostream>
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
