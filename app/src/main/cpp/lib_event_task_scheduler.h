//
// Created by 赵勇 on 2018/4/13.
//

#ifndef LIBFIFO_LIB_EVENT_TASK_SCHEDULER_H
#define LIBFIFO_LIB_EVENT_TASK_SCHEDULER_H

class LibEventTaskScheduler {
public:
    LibEventTaskScheduler();
    virtual ~LibEventTaskScheduler();

    void createNew();
};

#endif //LIBFIFO_LIB_EVENT_TASK_SCHEDULER_H
