//
// Created by 赵勇 on 2018/4/10.
//

#ifndef LIBFIFO_THREAD_MANAGER_H
#define LIBFIFO_THREAD_MANAGER_H

#include <pthread.h>

class ThreadManager : public pthread_mutex_t{
public:
    ThreadManager();
    virtual ~ThreadManager();

    int removeThreadInfo();
    int saveThreadInfo(pthread_mutex_t *a1, int a2, int a3);
private:
};

#endif //LIBFIFO_THREAD_MANAGER_H