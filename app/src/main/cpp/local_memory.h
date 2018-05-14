//
// Created by 赵勇 on 2018/4/16.
//

#ifndef LIBFIFO_LOCAL_MEMORY_H
#define LIBFIFO_LOCAL_MEMORY_H

#include "one_data.h"

class LocalMemory {
public:
    LocalMemory();
    virtual ~LocalMemory();

    void initPendingData();
    void moveOnStep();

private:
    OneData* oneData;
};

#endif //LIBFIFO_LOCAL_MEMORY_H
