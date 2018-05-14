//
// Created by 赵勇 on 2018/4/10.
//

#include "m3u8manager.h"

LocalMemory* M3U8Manager::gTSLocalMemory = new LocalMemory();
P2PClient* M3U8Manager::gTSP2PClient = new P2PClient();

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

void M3U8Manager::createFifoProcess() {
    if(fifoDataManager != NULL) {
        fifoDataManager->start();
    }
}

void M3U8Manager::initP2P() {
    oneFile = new OneFile();
    oneRequest = new OneRequest();
    onePacket = new OnePacket();
    oneData = new OneData();
}

void M3U8Manager::notifyM3u8RefreshBitmap() {
    refreshBitmap();
}

void M3U8Manager::notifyM3u8ToHttpDownload() {
    downloadP2PFailedPiece();
}

void M3U8Manager::notifyM3u8OneFile() {

}

void M3U8Manager::notifyM3u8RequestPeer() {

}

void M3U8Manager::refreshBitmap() {

}

void M3U8Manager::downloadP2PFailedPiece() {
    if(tsPieceDownload != NULL) {
        tsPieceDownload->downloadPieceDataWithPieceid();
    }
}

void M3U8Manager::initWindow() {
    if (gTSLocalMemory != NULL) {
        gTSLocalMemory->initPendingData();
    }

    if (tsPieceDownload != NULL) {
        tsPieceDownload->downloadPieceDataWithPieceid();
    }
}

void M3U8Manager::generateUrl() {
    assignMission();
}

void M3U8Manager::assignMission() {
    if(fifoDataManager != NULL) {
        fifoDataManager->getWriteDataTime();
    }
    moveOnStep();
    if(gTSLocalMemory != NULL) {
        gTSLocalMemory->initPendingData();
    }

    if(gTSP2PClient != NULL) {
        gTSP2PClient->addMission();
    }
    if(tsPieceDownload != NULL) {
        tsPieceDownload->downloadPieceDataWithPieceid();
    }
}

void M3U8Manager::moveOnStep() {
    if(gTSLocalMemory != NULL) {
        gTSLocalMemory->moveOnStep();
    }
}

void M3U8Manager::checkDownload() {
    if(linkManager != NULL) {
        linkManager->lockTheLink();
    }

    if(tsPieceDownload != NULL) {
        tsPieceDownload->initTsRangeWithPieceId();
    }
}

void* M3U8Manager::ThreadProcess(void *mySelf) {
    M3U8Manager* manager = (M3U8Manager*)mySelf;
    manager->M3U8ManagerRoutine();
    return 0;
}

void* M3U8Manager::generateM3u8Process(void *mySelf) {
    M3U8Manager* manager = (M3U8Manager*)mySelf;
    manager->createFifoProcess();
    manager->initP2P();
    manager->initWindow();
    manager->generateUrl();
    manager->checkDownload();
    return 0;
}