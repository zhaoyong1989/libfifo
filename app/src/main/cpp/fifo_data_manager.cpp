//
// Created by 赵勇 on 2018/4/10.
//

#include "fifo_data_manager.h"

FifoDataManager::FifoDataManager() {

}

FifoDataManager::FifoDataManager(int) {

}

FifoDataManager::~FifoDataManager() {

}

double FifoDataManager::getWriteDataTime() {
   /* FifoDataManager *v1; // r4
    double v2; // d8
    double v3; // d6
    double result; // r0

    v1 = this;
    v2 = (double)*(signed int *)this;
    v3 = v2 + COERCE_DOUBLE(getTime()) - *((double *)this + 10);
    if ( (double)*((signed int *)v1 + 5) + 0.0 >= v3 )
        result = v3;
    else
        result = (double)*((signed int *)v1 + 5) + 0.0;
    return result;*/
    return 0;
}

void FifoDataManager::start() {
    pthread_create(&writeVideoDataThreadId, 0, writeVideoData, 0);
}

void* FifoDataManager::writeVideoData(void * mySelf) {
    FifoDataManager* fifoDataManager = (FifoDataManager*)(mySelf);
    fifoDataManager->writeBytesToFd();
    fifoDataManager->decryptChunk();
    fifoDataManager->rewriteData();
    return 0;
}

void FifoDataManager::writeBytesToFd() {

}

void FifoDataManager::decryptChunk() {

}

void FifoDataManager::rewriteData() {

}
