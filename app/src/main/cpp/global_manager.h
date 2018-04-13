//
// Created by 赵勇 on 2018/4/10.
//

#ifndef LIBFIFO_GLOBAL_MANAGER_H
#define LIBFIFO_GLOBAL_MANAGER_H

#include <pthread.h>
#include "regularInfo.h"

class GlobalManager {
public:
    GlobalManager(const char* currentChannelId, const char* packageName, char *signatureHashCode);
    virtual ~GlobalManager();
    int getStreamType();
    void initSingleChannelStatistic();
    void add_fifo_cr();
    void set_real_start_time(void);
    int startRoutine(int);
    void fyzbEncode();
    int nativeStart();
    int nativeRestart();
    int createWriteChannel();
    int read_android_file(char*);
    char* getPlayUrl();
    void setCurrentSourceInvalid();
    void add_play_cp2();
    void add_play_cp();
    void add_play_rtmpToFifo();
    int cloneChannelInfo();
    void sendEventToPlayer(int);
    void add_play_cpnull();
    void add_play_cpFail();
    void* getRegularContent(RegularInfo*, RegularInfo*, int, int);
    void generateRegularInfo();
    void sendReportContent();
    void downloadPath();
    void downloadInit();
    bool parse_addr2();
    bool checkDnsBuffer();
    void ares_library_init();
    void httpDownload();
    void notifyPlayerToChangeSource();
    void notifyPlayerToRestart();
    bool doRequest();

    static void* downloadChannelInfoThreadWithFifo(void* mySelf);
    static void* channelRegularReporterProcess(void* mySelf);
    static void* generateDataRate(void* mySelf);
    static void* parallelDownloadData(void* mySelf);

private:
    int currentStreamType;
    int currentAvailableStreamNum;
    bool cpIsNull;

    pthread_t threadId;
    pthread_t channelReqularReportThread;
    pthread_t dataRateThread;
    pthread_t parallelDownloadDataThread;

    bool firstRecvData;
    bool firstCard;
    bool ioAllow;
    int fsdCount;
    bool isSwitchEntry;
    int continueSwitchCount;
    bool firstVout;
    double noDataStartTime;

    RegularInfo* lastChannelInfo;
    RegularInfo* currentChannelInfo;
    RegularInfo* lastSecondInfo;
    RegularInfo* currentSecondInfo;

    pthread_mutex_t fsd_report_lock;

    bool interrupt;
    void* proxyParseDoneCb;
    void* proxyInterruptCb;
    void* cbReadSource;
    int currentPlayMode;

    char* currentSourceId;
    char* currentSourceSrc;
    void* invalidSource;
    bool allowRtmpChangeToData;
    bool rtmpChangedToData;

    int channelEventCount;
    int channelEventDelay;

    long currentTime;
    bool isNeedToSwitch;
    long lastSwitchTime;

    int cdnDownloadRate;
    int tdnDownloadRate;
    int p2pDownloadRate;

};

#endif //LIBFIFO_GLOBAL_MANAGER_H
