//
// Created by 赵勇 on 2018/4/10.
//

#ifndef LIBFIFO_M3U8MANAGER_H
#define LIBFIFO_M3U8MANAGER_H

#include <pthread.h>
#include "fifo_data_manager.h"
#include "lib_event_task_scheduler.h"
#include "curlwrapper.h"
#include "m3u8protocol.h"

class M3U8Manager {
public:
    M3U8Manager();
    virtual ~M3U8Manager();

    double getCurrentPlayTime();
    int clientStart();
    void M3U8ManagerRoutine();
    void freeM3U8Manager();
    void loadConf();

    static void* ThreadProcess(void* mySelf);
    static void* generateM3u8Process(void* mySelf);

private:

    LibEventTaskScheduler* libEventTaskScheduler;
    pthread_t threadId;
    pthread_t generateM3u8ProcessThread;
    CurlWrapper* curlWrapper;
    M3U8Protocol* m3U8Protocol;
};

#endif //LIBFIFO_M3U8MANAGER_H
