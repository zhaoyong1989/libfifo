//
// Created by 赵勇 on 2018/4/16.
//

#ifndef LIBFIFO_LINK_MANAGER_H
#define LIBFIFO_LINK_MANAGER_H

class LinkManager {
public:
    LinkManager();
    virtual ~LinkManager();

    long initElement();
    void destroyElement();
    void lockTheLink();
    void unlockTheLink();
    void insertElement();
    void deleteElement();
    void deepDestroyElement();
};

#endif //LIBFIFO_LINK_MANAGER_H
