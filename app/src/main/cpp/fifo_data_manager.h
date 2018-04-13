//
// Created by 赵勇 on 2018/4/10.
//

#ifndef LIBFIFO_FIFO_DATA_MANAGER_H
#define LIBFIFO_FIFO_DATA_MANAGER_H

class FifoDataManager {
public:
    FifoDataManager();
    FifoDataManager(int);
    virtual ~FifoDataManager();
    double getWriteDataTime();
};
#endif //LIBFIFO_FIFO_DATA_MANAGER_H
