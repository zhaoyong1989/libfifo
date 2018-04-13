//
// Created by 赵勇 on 2018/4/10.
//

#include "thread_manager.h"

ThreadManager::ThreadManager() {

}

ThreadManager::~ThreadManager() {

}

int ThreadManager::saveThreadInfo(pthread_mutex_t *a1, int a2, int a3) {
    /*pthread_mutex_t *v3; // r4
    int v4; // r5
    int v5; // r6
    _DWORD *v6; // r3
    _DWORD *v8; // r0

    v3 = a1;
    v4 = a2;
    v5 = a3;
    pthread_mutex_lock(a1);
    v6 = (_DWORD *)v3->__count;
    while ( 1 )
    {
        v6 = (_DWORD *)v6[2];
        if ( !v6 )
            break;
        if ( *v6 == v4 )
        {
            *v6 = v4;
            v6[1] = v5;
            return j_pthread_mutex_unlock(v3);
        }
    }
    v8 = operator new(0xCu);
    *v8 = v4;
    v8[1] = v5;
    v8[2] = *(_DWORD *)(v3->__count + 8);
    *(_DWORD *)(v3->__count + 8) = v8;
    return j_pthread_mutex_unlock(v3);*/

    return 0;
}

int ThreadManager::removeThreadInfo() {

}