//
// Created by 赵勇 on 2018/4/10.
//

#ifndef LIBFIFO_M3U8MANAGER_H
#define LIBFIFO_M3U8MANAGER_H

#include <pthread.h>
#include "fifo_data_manager.h"
#include "lib_event_task_scheduler.h"
#include "curlwrapper.h"
#include "m3u8protocol.h"
#include "one_data.h"
#include "one_packet.h"
#include "one_file.h"
#include "one_request.h"
#include "local_memory.h"
#include "p2p_client.h"
#include "tspiecedownload.h"
#include "link_manager.h"

class M3U8Manager {
public:
    M3U8Manager();
    virtual ~M3U8Manager();

    double getCurrentPlayTime();
    int clientStart();
    void M3U8ManagerRoutine();
    void freeM3U8Manager();
    void loadConf();
    void createFifoProcess();
    void initP2P();
    void initWindow();
    void generateUrl();
    void checkDownload();

    void notifyM3u8RefreshBitmap();
    void notifyM3u8ToHttpDownload();
    void notifyM3u8OneFile();
    void notifyM3u8RequestPeer();

    static void* ThreadProcess(void* mySelf);
    static void* generateM3u8Process(void* mySelf);

private:

    LibEventTaskScheduler* libEventTaskScheduler;
    pthread_t threadId;
    pthread_t generateM3u8ProcessThread;
    CurlWrapper* curlWrapper;
    M3U8Protocol* m3U8Protocol;
    FifoDataManager* fifoDataManager;
    OneData* oneData;
    OnePacket* onePacket;
    OneFile* oneFile;
    OneRequest* oneRequest;
    TsPieceDownload* tsPieceDownload;
    LinkManager* linkManager;

    static LocalMemory* gTSLocalMemory;
    static P2PClient* gTSP2PClient;

    void refreshBitmap();
    void downloadP2PFailedPiece();
    void assignMission();
    void moveOnStep();
};

#endif //LIBFIFO_M3U8MANAGER_H
