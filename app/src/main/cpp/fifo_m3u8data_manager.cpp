//
// Created by 赵勇 on 2018/4/13.
//

#include "fifo_m3u8data_manager.h"

FifoM3u8DataManager::FifoM3u8DataManager() {

}

FifoM3u8DataManager::~FifoM3u8DataManager() {

}

void FifoM3u8DataManager::writeFifoThread() {
    pthread_create(&threadId, 0, writeFifoThreadProcess, 0);
}

void* FifoM3u8DataManager::writeFifoThreadProcess(void * mySelf) {
    FifoM3u8DataManager* manager = (FifoM3u8DataManager*)mySelf;
    manager->writeBytesToChannel();
    manager->consumeXBytes();
    manager->addXWriteFifoBytes();
}

void FifoM3u8DataManager::consumeXBytes() {

}

void FifoM3u8DataManager::addXWriteFifoBytes() {

}