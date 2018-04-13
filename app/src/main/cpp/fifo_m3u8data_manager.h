//
// Created by 赵勇 on 2018/4/13.
//

#ifndef LIBFIFO_FIFO_M3U8DATA_MANAGER_H
#define LIBFIFO_FIFO_M3U8DATA_MANAGER_H

#include <pthread.h>

class FifoM3u8DataManager {
public:
    FifoM3u8DataManager();
    virtual ~FifoM3u8DataManager();

    void writeFifoThread();
    void writeBytesToChannel();
    void consumeXBytes();
    void addXWriteFifoBytes();

    static void* writeFifoThreadProcess(void*);

private:
    pthread_t threadId;
};
#endif //LIBFIFO_FIFO_M3U8DATA_MANAGER_H
