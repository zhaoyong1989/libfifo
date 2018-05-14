//
// Created by 赵勇 on 2018/4/16.
//

#ifndef LIBFIFO_ONE_FILE_H
#define LIBFIFO_ONE_FILE_H

class OneFile {
public:
    OneFile();
    virtual ~OneFile();

    void setFileId();
    void releasePackets();
    void reset();
};

#endif //LIBFIFO_ONE_FILE_H
