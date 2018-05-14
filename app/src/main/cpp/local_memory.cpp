//
// Created by 赵勇 on 2018/4/16.
//

#include <stdint.h>
#include <clocale>
#include "local_memory.h"

LocalMemory::LocalMemory() {

}

LocalMemory::~LocalMemory() {

}

void LocalMemory::initPendingData() {
    if(oneData != NULL) {
        oneData->setDataId();
    }
}

void LocalMemory::moveOnStep() {
    if(oneData != NULL) {
        oneData->reset();
    }
}