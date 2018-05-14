//
// Created by 赵勇 on 2018/4/10.
//

#ifndef LIBFIFO_FIFO_DATA_MANAGER_H
#define LIBFIFO_FIFO_DATA_MANAGER_H

#include "pthread.h"

class FifoDataManager {
public:
    FifoDataManager();
    FifoDataManager(int);
    virtual ~FifoDataManager();
    double getWriteDataTime();
    void start();
    void writeBytesToFd();
    void decryptChunk();
    void rewriteData();

    static void* writeVideoData(void* mySelf);

private:
    pthread_t writeVideoDataThreadId;
};
#endif //LIBFIFO_FIFO_DATA_MANAGER_H
