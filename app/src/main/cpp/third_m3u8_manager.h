//
// Created by 赵勇 on 2018/4/13.
//

#ifndef LIBFIFO_THIRD_M3U8_MANAGER_H
#define LIBFIFO_THIRD_M3U8_MANAGER_H

#include <pthread.h>

class ThirdM3U8Manager {
public:
    ThirdM3U8Manager();
    virtual ~ThirdM3U8Manager();

    int clientStart();
    void freeThirdM3U8Manager();
    void ThirdM3U8ManagerRoutine();

    static void* ThirdthreadProcess(void* mySelf);

private:
    pthread_t threadId;
};

#endif //LIBFIFO_THIRD_M3U8_MANAGER_H
