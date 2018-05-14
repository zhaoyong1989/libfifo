//
// Created by 赵勇 on 2018/4/13.
//

#ifndef LIBFIFO_TSPIECEDOWNLOAD_H
#define LIBFIFO_TSPIECEDOWNLOAD_H

#include "link_manager.h"

class TsPieceDownload {
public:
    TsPieceDownload();
    virtual ~TsPieceDownload();

    void downloadPieceDataWithPieceid();
    void downloadPieceDataWithDataUnit();
    bool initTsRangeWithPieceId();

private:
    LinkManager* linkManager;

    int getTsInfoWithPieceId();
    void lockTsList();
    void unlockTsList();
};
#endif //LIBFIFO_TSPIECEDOWNLOAD_H
