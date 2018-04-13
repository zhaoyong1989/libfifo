//
// Created by 赵勇 on 2018/4/10.
//

#include "p2pmanager.h"

P2PManager::P2PManager() {

}

P2PManager::~P2PManager() {

}

double P2PManager::getCurrentPlayTime() {
    FifoDataManager *fifoDataManager = new FifoDataManager();
    return fifoDataManager->getWriteDataTime();
}