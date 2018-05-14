//
// Created by 赵勇 on 2018/4/10.
//

#include "global_manager.h"
#include "regularInfo.h"

GlobalManager::GlobalManager(const char *currentChannelId, const char *packageName,
                             char *signatureHashCode) {
    initSingleChannelStatistic();
    add_fifo_cr();
    currentStreamType = 0;
    currentAvailableStreamNum = 0;
    cpIsNull = 1;
    pthread_create(&threadId, 0, downloadChannelInfoThreadWithFifo, this);
}

GlobalManager::~GlobalManager() {

}

int GlobalManager::getStreamType() {
    return 1;
}

void GlobalManager::add_fifo_cr() {

}

void GlobalManager::initSingleChannelStatistic() {
    firstRecvData = 1;
    firstCard = 0;
    ioAllow = 1;
    fsdCount = 0;
    RegularInfo::rest(lastChannelInfo);
    RegularInfo::rest(currentChannelInfo);
    RegularInfo::rest(lastSecondInfo);
    RegularInfo::rest(currentSecondInfo);

    //dword_2F6194 = 1;
    pthread_mutex_init(&fsd_report_lock, 0);
    pthread_create(&channelReqularReportThread, 0, channelRegularReporterProcess, 0);
    pthread_create(&dataRateThread, 0, generateDataRate, 0);
    //result = ThreadManager::saveThreadInfo((pthread_mutex_t *)threadManager, channelReqularReportThread, 1);
    if ( isSwitchEntry ) {
        if ( continueSwitchCount == 1 && firstVout );
            //unk_F4490 = noDataStartTime;
    }
    else {
        set_real_start_time();
    }
    firstVout = 0;
    isSwitchEntry = 0;
}

void GlobalManager::set_real_start_time() {
    //unk_F4490 = getTime();
}

int GlobalManager::startRoutine(int type) {
    char* backupapi = "http://backupapi.mobile.kukuplay.com/SourceManager/playinfo?cid=%s&version=%s&key=%s";
    char* api = "http://api.kukuplay.com/SourceManager/playinfo?cid=%s&version=%s&key=%s";
    char* url;

    while ( !interrupt ) {
        fyzbEncode();
        pthread_create(&parallelDownloadDataThread, 0, parallelDownloadData, 0);
    }

    return 0;
}

void GlobalManager::fyzbEncode() {

}

int GlobalManager::nativeStart() {
    return 0;
}

int GlobalManager::nativeRestart() {
    return 0;
}

int GlobalManager::createWriteChannel() {
    //创建socket通信
    return 0;
}

int GlobalManager::read_android_file(char *) {
    return 0;
}

char* GlobalManager::getPlayUrl() {
    return 0;
}

void GlobalManager::setCurrentSourceInvalid() {

}

void GlobalManager::add_play_cp2() {

}

void GlobalManager::add_play_cp() {

}

void GlobalManager::add_play_rtmpToFifo() {

}

int GlobalManager::cloneChannelInfo() {
    return 0;
}

void GlobalManager::sendEventToPlayer(int event) {

}

void GlobalManager::add_play_cpnull() {

}

void GlobalManager::add_play_cpFail() {

}

void* GlobalManager::getRegularContent(RegularInfo *, RegularInfo *, int, int) {
    return 0;
}

void GlobalManager::generateRegularInfo() {

}

void GlobalManager::sendReportContent() {
    downloadPath();
}

void GlobalManager::downloadPath() {
    downloadInit();
    parse_addr2();
}

bool GlobalManager::parse_addr2() {
    checkDnsBuffer();
    ares_library_init();
    return 0;
}

void GlobalManager::httpDownload() {

}

void GlobalManager::ares_library_init() {

}

bool GlobalManager::checkDnsBuffer() {
    return 0;
}

void GlobalManager::downloadInit() {

}

void GlobalManager::notifyPlayerToChangeSource() {

}

void GlobalManager::notifyPlayerToRestart() {

}

bool GlobalManager::doRequest() {
    return 0;
}

void* GlobalManager::channelRegularReporterProcess(void *mySelf) {
    GlobalManager* globalManager = (GlobalManager*)mySelf;
    globalManager->notifyPlayerToChangeSource();
    globalManager->notifyPlayerToRestart();
    return 0;
}

void* GlobalManager::downloadChannelInfoThreadWithFifo(void *mySelf) {
    GlobalManager* globalManager = (GlobalManager*)mySelf;
    globalManager->startRoutine(1);
    return 0;
}

void* GlobalManager::generateDataRate(void *mySelf) {
    return 0;
}

void* GlobalManager::parallelDownloadData(void *mySelf) {
    GlobalManager* globalManager = (GlobalManager*)mySelf;
    globalManager->doRequest();
    return 0;
}