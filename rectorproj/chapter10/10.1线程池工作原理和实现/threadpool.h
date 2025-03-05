#pragma once
#ifndef _THREADPOOL_H
#define _THREADPOOL_H

typedef struct ThreadPool ThreadPool;
//创建线程池并初始化
ThreadPool *threadPoolCreate(int min,int max,int queueSize)
{
    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    do
    {
        if(pool == NULL)
        {
            printf("malloc threadpool fail....");
            return NULL;
        }
        pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t) *max);
        if(pool->threadIDs == NULL)
        {
            printf("malloc threadIDs fail...\n");
            return NULL;
        }
        memset(pool->threadIDs, 0, sizeof(pthread_t)*max);
        pool->minNum = min;
        pool->maxNum = max;
        pool->busyNum = 0;
        pool->liveNum = min; //和最小个数相等
        pool->exitNum = 0;
    
        if (pthread_mutex_init (&pool->mutexPool, NULL) != 0 ||
            pthread_mutex_init (&pool->mutexBusy, NULL) != 0 ||
            pthread_cond_init (&pool->notEmpty, NULL) != 0   ||
            pthread_cond_init (&pool->notFull, NULL) != 0 )
            {
                printf("malloc threadIDs fail...\n");
                return 0;
            }
    
        //任务队列
        pool->taskQ = (Task*)malloc(sizeof(Task)* queueSize);
        pool->queueCapacity = 0;
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueRear = 0;
        pool->shutdown = 0;
    
        //创建线程
        pthread_create (&pool->managerID, NULL, manager, NULL);
        for (int i = 0; i < min; i++)
        {
            pthread_create(&pool->threadIDs[i], NULL, worker,pool);
        }
        return pool;
    } while (0);
    
    //释放资源
    if (pool->threadIDs) free(pool->threadIDs);
    if (pool->taskQ)     free(pool->taskQ);
    if (pool) free(pool);

    return NULL;
}

void*  worker(void* arg)
{
    ThreadPool* pool  = (ThreadPool*)arg;
    while (1)
    {
        
    }
    
    return NULL;
}
//销毁线程池


//给线程池添加任务

//获取线程池中工作的线程个数


//获取线程池中活着的线程个数

#endif

