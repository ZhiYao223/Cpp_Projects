#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>
#include <chrono>

//缓冲区大小
const int BUFFER_SIZE = 5;

//模拟信号量，空槽和填充槽
std::mutex mtx;
std::condition_variable empty_slots; //空槽信号量
std::condition_variable filled_slots;//已填充槽信号量
std::queue<int> buffer; //缓冲区

//生产者线程
void producer(int id){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 100);
    while(true){
        int item = dis(gen); //生成一个随机商品
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));//模拟生产时间
        //获取空槽信号量
        std::unique_lock<std::mutex> lock(mtx);
        empty_slots.wait(lock, []{return buffer.size() < BUFFER_SIZE;});
        //生产商品并放入缓冲区
        buffer.push(item);
        
    }
} 

int main(){
    //创建并启动生产者和消费者线程
    std::thread producer1(producer, 1);
    std::thread producer2(producer, 2);

    //等待线程完成
    producer1.join();

    return 0;
}