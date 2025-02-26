#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadnum,const std::string& threadtype):stop_(false),threadtype_(threadtype)
{
    //启动threadnum个线程，每个线程将阻塞在条件变量上
    for(size_t i = 0; i < threadnum; i++){
        //用lambda函数创建线程
        threads_.emplace_back([this]
        {
            //显示线程类型和线程ID
            printf("%s(%ld) execute task.\n", threadtype_.c_str(),syscall(SYS_gettid));
            //std::cout << "子线程："<<std::this_thread::get_id()<<std::endl;
            while(stop_ == false){
                //用于存放出队的元素
                std::function<void()> task;
                {//锁作用域的开始
                    std::unique_lock<std::mutex> lock(this->mutex_);
                    //等待生产者的条件变量
                    this->condition_.wait(lock,[this]
                    {
                        return((this->stop_==true)||(this->taskqueue_.empty()==false));
                    });
                    //在线程池停止之前，如果队列中还有任务，执行完再退出
                    if((this->stop_==true)&&(this->taskqueue_.empty()==true)) return ;
                    //出队一个任务
                    task = std::move(this->taskqueue_.front());
                    this->taskqueue_.pop();
                }//锁作用域的结束
                printf("%s(%ld) execute task.\n", threadtype_.c_str(),syscall(SYS_gettid));
                task(); //执行任务
            }
        });
    }
}

void ThreadPool::addtask(std::function<void()> task)
{
    {//锁作用域的开始
        std::lock_guard<std::mutex> lock(mutex_);
        taskqueue_.push(task);
    }//锁作用域的结束
    // 唤醒一个线程
    condition_.notify_one();
}

ThreadPool::~ThreadPool()
{
    stop_ = true;
    // 唤醒全部的线程
    condition_.notify_all();
    //等待全部线程执行完任务后退出
    for(std::thread &th:threads_)
    th.join();
}
/*
void show(int no, const std::string &name)
{
    printf("Hello, 这里是第%d个消息%s。\n", no, name.c_str());
}

void test()
{
    printf("Hello, world.\n");
}

int main()
{
    // 创建线程池，一共3个线程
    ThreadPool threadpool(3);
    std::string name = "zhiyao";
    threadpool.addtask(std::bind(show,8,name));
    sleep(1);
    threadpool.addtask(std::bind(test));
    sleep(1);
    threadpool.addtask(std::bind([]{printf("Hello, HUD.\n");}));
    sleep(1);
}
*/