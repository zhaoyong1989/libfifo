//
// Created by 赵勇 on 2018/4/16.
//

#include <stdint.h>
#include "p2p_client.h"

P2PClient::P2PClient() {

}

P2PClient::~P2PClient() {

}

bool P2PClient::isDownloading() {
    return 0;
}

void P2PClient::addMission() {
    isDownloading();
    if(oneFile != NULL) {
        oneFile->setFileId();
    }

    if(oneRequest != NULL) {
        oneRequest->setRequestData();
    }

    if(oneFile != NULL) {
        oneFile->releasePackets();
        oneFile->reset();
    }
}