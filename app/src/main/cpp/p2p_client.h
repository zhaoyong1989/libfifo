//
// Created by 赵勇 on 2018/4/16.
//

#ifndef LIBFIFO_P2P_CLIENT_H
#define LIBFIFO_P2P_CLIENT_H

#include "one_file.h"
#include "one_request.h"

class P2PClient {
public:
    P2PClient();
    virtual ~P2PClient();

    void addMission();

private:
    bool isDownloading();

    OneFile* oneFile;
    OneRequest* oneRequest;
};

#endif //LIBFIFO_P2P_CLIENT_H
