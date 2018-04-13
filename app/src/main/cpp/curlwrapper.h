//
// Created by 赵勇 on 2018/4/13.
//

#ifndef LIBFIFO_CURLWRAPPER_H
#define LIBFIFO_CURLWRAPPER_H

class CurlWrapper {
public:
    CurlWrapper();
    ~CurlWrapper();
    void createNew();

    int new_session();
};

#endif //LIBFIFO_CURLWRAPPER_H
