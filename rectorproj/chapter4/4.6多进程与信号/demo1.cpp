#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;
void FathEXIT(int sig);//父进程的信号处理函数。
void ChlldExit(int sig);//子进程的信号处理函数

int main()
{
    //忽略全部的信号，不希望被打扰
    for(int i = 1; i < 64; i++){
        signal(i, SIG_IGN);
    }
        //设置信号，在shell状态下可用，“kill + 进程号”
        //不要用"kill -9 + 进程号"强行终止
        //SIGTERM 15   SIGINT 2
        signal(SIGTERM, FathEXIT);
        signal(SIGINT, FathEXIT);
    while(true){d
        if (fork() > 0) //父进程的流程
        {
            sleep(5); continue;
        } else {
            //子进程流程
            //子进程的退出函数与父进程不一样
            signal(SIGTERM, ChlldExit);
            //子进程不需要补货SIGINT信号
            signal(SIGINT, SIG_IGN);
            while (true){
                cout << "子进程" << getpid() << "正在运行中。\n"; 
                sleep(3);
                continue;
            }
        }
    }
}

// 父进程的信号处理函数。
void FathEXIT(int sig)
{
  // 以下代码是为了防止信号处理函数在执行的过程中再次被信号中断。
  signal(SIGINT,SIG_IGN); signal(SIGTERM,SIG_IGN);
  cout << "父进程退出, sig=" << sig << endl;
  kill(0,SIGTERM);     // 向全部的子进程发送15的信号，通知它们退出。
  // 在这里增加释放资源的代码（全局的资源）。
  exit(0);
}

//子进程的信号处理函数
void ChlldExit(int sig){
    //防止信号处理函数在执行的过程中再次被信号中断。
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    cout << "子进程" << getpid() <<"退出， sig = " << sig << endl;
    //在这里增加释放资源的代码(只释放子进程的资源)。
    exit(0);
}
