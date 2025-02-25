// #include <iostream>
// #include <thread>
// void task()
// {
//     std::cout << "子线程执行中...." << std::endl;
// }

// int main()
// {
//     std::thread t(task);
//     if (t.joinable())
//     {
//         t.join(); // 等待子线程结束。
//     }
//     std::cout << "主线程结束。" << std::endl;
//     return 0;
// }

#if 0
#include <iostream>
#include <thread>

void func(int id, std::string& message)
{
    std::cout << "线程" << id << "接收到消息：" << message << std::endl;
}
int main()
{
    std::string message = "hello, world";
    std::thread t(func, 1, std::ref(message));
    t.join(); // 等待子线程结束。
}
#endif

#if 0
#include <iostream>
#include <thread>
#include <mutex>
std::mutex mtx;

void increment()
{
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < 5; i++)
    {
        std::cout << "线程" << std::this_thread::get_id() << "输出：" << i << std::endl;
    }
}
int main()
{
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    return 0;
}

#endif

#if 1
#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>
std::queue<int> data_queue;//
std::mutex mtx; // 互斥量
std::condition_variable cv; // 条件变量

void producer(){
    for(int i = 0; i < 10; i++){
        std::lock_guard<std::mutex> lock(mtx);
        data_queue.push(i);
        std::cout << "生产者生产数据：" << i << std::endl;
        cv.notify_one(); // 通知一个等待线程
    }
}
 void consumer()
 {
        for (int i = 0; i < 10; i++)
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return !data_queue.empty(); });
            int data = data_queue.front();
            data_queue.pop();
            std::cout << "消费者消费数据：" << data << std::endl;
        }
 }

 int main()
 {
        std::thread t1(producer);
        std::thread t2(consumer);
        t1.join();
        t2.join();
        return 0;
 }

#endif

