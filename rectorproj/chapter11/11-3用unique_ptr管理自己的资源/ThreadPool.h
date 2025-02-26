#include <iostream>
#include <mutex>
#include <unistd.h>
#include <thread>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>
#include <vector>
#include <queue>
#include <sys/syscall.h>

class ThreadPool
{
private:
    // 线程池中的线程
    std::vector<std::thread> threads_;
    // 任务队列
    std::queue<std::function<void()>> taskqueue_;
    // 任务队列同步的互斥锁
    std::mutex mutex_;
    // 任务队列同步的条件变量
    std::condition_variable condition_;
    // 在析构函数中，把stop_的值设置为true，全部的线程将退出
    std::atomic_bool stop_;
    // 线程种类："IO"，"WORKS"
    std::string threadtype_;
public:
    // 在构造函数中将启动threadnum个线程
    ThreadPool(size_t threadnum,const std::string& threadtype_);
    // 把任务添加到队列中
    void addtask(std::function<void()> task);
    // 在析构函数中停止线程
    ~ThreadPool();
};













