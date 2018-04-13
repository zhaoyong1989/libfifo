//
// Created by 赵勇 on 2018/4/10.
//

#ifndef LIBFIFO_P2PMANAGER_H
#define LIBFIFO_P2PMANAGER_H

#include "fifo_data_manager.h"

class P2PManager {
public:
    P2PManager();
    virtual ~P2PManager();

    double getCurrentPlayTime();
};

#endif //LIBFIFO_P2PMANAGER_H
