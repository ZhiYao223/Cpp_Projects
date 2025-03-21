#include <iostream>
#include <ThreadPool.h>

class ThreadPool{
private:
    struct NWORKER{
        pthread_t threadid;
        bool terminate;
        int isWorking;
        ThreadPool* pool;
    }*m_workers;
    struct NJOB{
        void(*func)(void *arg);
        void *user_data;
    };
public:
    //线程池初始化
    //numWorkers:线程数量
    ThreadPool(int numWorkers, int max_jobs);
    //销毁线程池
    ~ThreadPool();
    int pushJob(void(*func)(void *data),void *arg, int len);
private:
    //向线程池中添加任务
    bool _addJob(NJOB* job);
};