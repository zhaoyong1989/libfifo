//
// Created by 赵勇 on 2018/4/13.
//

#include <stdint.h>
#include "tspiecedownload.h"

TsPieceDownload::TsPieceDownload() {

}

TsPieceDownload::~TsPieceDownload() {

}

void TsPieceDownload::downloadPieceDataWithPieceid() {
    if(linkManager != NULL) {
        linkManager->initElement();
    }
    downloadPieceDataWithDataUnit();
}

void TsPieceDownload::downloadPieceDataWithDataUnit() {
    if(linkManager != NULL) {
        linkManager->destroyElement();
        linkManager->lockTheLink();
        linkManager->insertElement();
        linkManager->unlockTheLink();
    }
}

bool TsPieceDownload::initTsRangeWithPieceId() {
    getTsInfoWithPieceId();
    return 0;
}

int TsPieceDownload::getTsInfoWithPieceId() {
    lockTsList();
    unlockTsList();
    return 0;
}

void TsPieceDownload::lockTsList() {

}

void TsPieceDownload::unlockTsList() {

}