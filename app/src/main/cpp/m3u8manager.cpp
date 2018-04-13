//
// Created by 赵勇 on 2018/4/10.
//

#include "m3u8manager.h"

M3U8Manager::M3U8Manager() {

}

M3U8Manager::~M3U8Manager() {

}

double M3U8Manager::getCurrentPlayTime() {
    FifoDataManager *fifoDataManager = new FifoDataManager(); // r0
    return fifoDataManager->getWriteDataTime();
}

int M3U8Manager::clientStart() {
    return pthread_create(&threadId, 0, ThreadProcess, 0);
}

void M3U8Manager::M3U8ManagerRoutine() {
    libEventTaskScheduler->createNew();
    freeM3U8Manager();
    curlWrapper->createNew();
    m3U8Protocol->createNew();
    pthread_create(&generateM3u8ProcessThread, 0, generateM3u8Process, 0);
    loadConf();
}

void M3U8Manager::freeM3U8Manager() {

}

void M3U8Manager::loadConf() {
    curlWrapper->new_session();
}

void* M3U8Manager::ThreadProcess(void *mySelf) {
    M3U8Manager* manager = (M3U8Manager*)mySelf;
    manager->M3U8ManagerRoutine();
}

void* M3U8Manager::generateM3u8Process(void *mySelf) {
    M3U8Manager* manager = (M3U8Manager*)mySelf;
    M3U8Manager::createFifoProcess((M3U8Manager *)a1);
    M3U8Manager::initP2P(v2);
    M3U8Manager::initWindow(v2);
    M3U8Manager::generateUrl((int)v2);
    M3U8Manager::checkDownload(v2);
}