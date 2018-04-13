//
// Created by 赵勇 on 2018/4/11.
//

#ifndef LIBFIFO_REGULARINFO_H
#define LIBFIFO_REGULARINFO_H

class RegularInfo {
public:
    RegularInfo();
    virtual ~RegularInfo();
    void clone();

    static void rest(RegularInfo*);
    static void resetRegularStatistic(RegularInfo*);
};

#endif //LIBFIFO_REGULARINFO_H
