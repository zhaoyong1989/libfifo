//
// Created by 赵勇 on 2018/4/13.
//

#include "third_m3u8_manager.h"

ThirdM3U8Manager::ThirdM3U8Manager() {

}

ThirdM3U8Manager::~ThirdM3U8Manager() {

}

int ThirdM3U8Manager::clientStart() {
    pthread_create(&threadId, 0, ThirdthreadProcess, 0);
    ThirdM3U8Manager::freeThirdM3U8Manager();
    return 0;
}

void ThirdM3U8Manager::freeThirdM3U8Manager() {

}

void* ThirdM3U8Manager::ThirdthreadProcess(void *mySelf) {
    ThirdM3U8Manager* thirdM3U8Manager = (ThirdM3U8Manager*) mySelf;
    thirdM3U8Manager->ThirdM3U8ManagerRoutine();
    return 0;
}

void ThirdM3U8Manager::ThirdM3U8ManagerRoutine() {

}