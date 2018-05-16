#include <jni.h>
#include <string>
#include <pthread.h>
#include <memory.h>

#include "thread_manager.h"
#include "m3u8manager.h"
#include "global_manager.h"
#include "p2pmanager.h"
#include "encrypt/encrypt.h"
#include "tools/CommonTools.h"

#define LOG_TAG "libbase64"

typedef int (*fifo_callback)(int event);

const char *packageName;

char* version = "2016080211";

const char* device = "android_phone";

const char* platform = "android";

const char* clientId;

const char* sysinfo;

const char* reportPartnerId = "androidPlayer";

bool isInitialized = false;

pthread_mutex_t stat_lock;

char* defaultCookie = "Cookie: Hm_lvt_55b8664487df0e9e029ab5649d0325e9=1396245928,1396930405,1397109279; pgv_pvi=181122048; __utma=250245265.2092736739.1344319038.1355985326.1355999926.4; _ga=GA1.2.2092736739.1344319038; Hm_lvt_3e775b3a5795c4d9856a8c514bc85728=1396245928,1396930406; Hm_lvt_a54646c20401445b3c45e4c916b25cc2=1376535381; Hm_lvt_85850cee9798a15ac882dfecf040eaff=1397109281; __auc=9bc4056a14231e35da9294cf8ae; stat=wxlg8n8u46716146m47ajfkh03837596#1#1389008963863";

char* debugInfo = "Cookie: Hm_lvt_55b8664487df0e9e029ab5649d0325e9=1396245928,1396930405,1397109279; pgv_pvi=181122048; __utma=250245265.2092736739.1344319038.1355985326.1355999926.4; _ga=GA1.2.2092736739.1344319038; Hm_lvt_3e775b3a5795c4d9856a8c514bc85728=1396245928,1396930406; Hm_lvt_a54646c20401445b3c45e4c916b25cc2=1376535381; Hm_lvt_85850cee9798a15ac882dfecf040eaff=1397109281; __auc=9bc4056a14231e35da9294cf8ae; stat=wxlg8n8u46716146m47ajfkh03837596#1#1389008963863";

ThreadManager* threadManager;

JNIEnv* myEnv;

jmethodID callback;

jobject eventHandlerObject;

bool isPlayerStarted;

bool isCardToSwitch;

bool isSwitchEntry;

int continueSwitchCount;

bool firstVout;

bool firstCard;

int currentPlayMode = 2;

int currentStreamType;

int currentState;

double lastCardPoint = -1.0;

double noDataStartTime;

double cardLongTime;

GlobalManager* gM;

int isThirdSource;

bool ioAllow;

bool interrupt;

int startChangeCdnTime;

char* currentSourceId;

char* currentSourceSrc;

int preReadBytes;

bool isMovieChannel;

int wifiState = 2;

int playerReadBytes;

fifo_callback player_callback;

const char *currentChannelId;

char* signatureHashCode;

bool lowDelayChannel;

const char* bitrate;

bool rtmpChangedToData;

bool isCompatible;

int procSelfPlay()
{
    int result; // r0

    result = 0;
    lastCardPoint = -1.0;
    currentState = 2;
    cardLongTime = 0LL;
    noDataStartTime = 0LL;
    return result;
}

int initAppStatistic() {

    threadManager = new ThreadManager();
    return pthread_mutex_init(&stat_lock, NULL);
}

int initStatistic() {
    int result;

    if ( !isInitialized )
    {
        result = initAppStatistic();
        isInitialized = 1;
    }
    return result;
}

void clientPlayerVout() {
    continueSwitchCount = 0;
    if ( !firstVout ) {
        firstVout = true;
        if ( currentPlayMode )
        {
            if ( currentPlayMode == 1 );
                //add_play_vo2();
        }
        else
        {
            //add_play_vo();
            switch ( currentStreamType )
            {
                case 1:
                    //add_flv_vo();
                    break;
                case 2:
                    //add_ts_vo();
                    break;
                case 3:
                    //add_direct_vo();
                    break;
            }
        }
    }
}

void clientPlayerCard(void)
{
    if ( currentPlayMode )
    {
        if ( currentPlayMode == 1 );
            //add_ses_play_pc2();
    }
    else
    {
        //add_ses_play_pc();
        switch ( currentStreamType )
        {
            case 1:
                //add_ses_flv_pc();
                break;
            case 2:
                //add_ses_ts_pc();
                break;
            case 3:
                //add_ses_direct_pc();
                break;
        }
    }
    if ( !firstCard )
    {
        firstCard = 1;
        if ( currentPlayMode )
        {
            if ( currentPlayMode == 1 );
                //add_play_pc2();
        }
        else
        {
            //add_play_pc();
            switch ( currentStreamType )
            {
                case 1:
                    //add_flv_pc();
                    break;
                case 2:
                    //add_ts_pc();
                    break;
                case 3:
                    //add_direct_pc();
                    break;
            }
        }
    }
}

double getTime()
{
    signed int v0; // r4
    double v1; // d7
    double v2; // d6
    signed int v4; // [sp+0h] [bp-30h]
    signed int v5; // [sp+4h] [bp-2Ch]
    struct timeval tv; // [sp+8h] [bp-28h]

    v0 = 10;
    while ( 1 )
    {
        gettimeofday((struct timeval *)&v4, 0);
        gettimeofday(&tv, 0);
        v1 = (double)tv.tv_sec + (double)tv.tv_usec * 0.000001;
        v2 = v1 - ((double)v4 + (double)v5 * 0.000001);
        if ( v2 >= 0.0 && v2 <= 1.0 )
            break;
        if ( !--v0 )
        {
            gettimeofday((struct timeval *)&v4, 0);
            v1 = (double)v4 + (double)v5 * 0.000001;
            return v1;
        }
    }
    return v1;
}

double procSelfPause()
{
    double result; // r0

    currentState = 3;
    if ( lastCardPoint == -1.0 )
    {
        result = getTime();
        lastCardPoint = result;
        if ( !continueSwitchCount )
        {
            result = getTime();
            noDataStartTime = result;
        }
    }
    else
    {
        result = getTime();
        cardLongTime = result - lastCardPoint;
    }
    return result;
}

void attachEvent(fifo_callback callback)
{
    player_callback = callback;
}

int fifo_event_callback(int event)
{
    if(myEnv == NULL || eventHandlerObject == NULL || callback == NULL) {
        return -1;
    }
    myEnv->CallVoidMethod(eventHandlerObject, callback, event);
    return 0;
}

void p2pStart(const char *channelId) {
    if ( channelId ) {
        currentChannelId = channelId;
        gM = new GlobalManager(currentChannelId, packageName, signatureHashCode);
    }
}

int* fifoInit(JNIEnv *env, jclass clazz,
               jstring fifoName, jstring channelId)
{
    const char* localChannelId = env->GetStringUTFChars(channelId, NULL);
    jmethodID isWifiState = env->GetStaticMethodID(clazz, "isWifiState", "()Z");
    if ( isWifiState )
        wifiState = env->CallStaticBooleanMethod(clazz, isWifiState);
    else
        wifiState = 2;
    //unvisibleBufferSize = 0LL;
    playerReadBytes = 0;
    attachEvent(fifo_event_callback);
    p2pStart(localChannelId);
    currentState = 0;
    lastCardPoint = -1.0;
    return NULL;
}


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_libfifo_FifoController_decryptVipPlayInfo(JNIEnv *env, jclass clazz,
                                                   jstring encryptPlayInfo) {
    char* destString;

    if (packageName) {
        if (!strcmp(packageName, "com.entgroup") || !strcmp(packageName, "air.fyzb3")) {
            if (encryptPlayInfo != NULL) {
                const char* playInfo = env->GetStringUTFChars(encryptPlayInfo, NULL);
                byte* base64;
                long base64Len;
                Encrypt::base64Decode(playInfo, &base64, &base64Len);
                destString = Encrypt::decrypt(base64, base64Len);
            }
        }
    }

    return env->NewStringUTF(destString);
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_createFifo(JNIEnv *env, jclass clazz,
                                           jstring fifoName, jstring channelId) {
    /*if ( gM )
    {
        delete gM;
        gM = NULL;
    }
    currentPlayMode = 0;
    interrupt = 0;
    startChangeCdnTime = 0;
    cardLongTime = 0LL;
    currentSourceId = NULL;
    currentSourceSrc = NULL;
    isPlayerStarted = 0;
    preReadBytes = 0;
    fifoInit(env, clazz, fifoName, channelId);*/
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_multiStreamCreateFifo(JNIEnv *env, jclass clazz,
                                                      jstring channelId, jstring br) {
    /*if ( gM ) {
        delete gM;
        gM = NULL;
    }
    currentPlayMode = 1;
    lowDelayChannel = 1;
    interrupt = 0;
    startChangeCdnTime = 0;
    cardLongTime = 0LL;
    if ( bitrate )
        bitrate = env->GetStringUTFChars(br, NULL);
    else
        bitrate = "origin";
    isPlayerStarted = 0;
    preReadBytes = 0;
    attachEvent(fifo_event_callback);

    if ( channelId ) {
        currentChannelId = env->GetStringUTFChars(channelId, NULL);
        isMovieChannel = false;//暂时设置为false，跟channelId计算得出，但目前还不知道计算方法
        gM = new GlobalManager(currentChannelId, packageName, signatureHashCode);
    }*/
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_createFifo2(JNIEnv *env, jclass clazz, jstring channelId) {
    /*if ( gM )
    {
        delete gM;
        gM = NULL;
    }
    lowDelayChannel = 1;
    interrupt = 0;
    startChangeCdnTime = 0;
    cardLongTime = 0LL;
    isPlayerStarted = 0;
    preReadBytes = 0;
    attachEvent(fifo_event_callback);
    if ( channelId )
    {
        currentChannelId = env->GetStringUTFChars(channelId, NULL);
        isMovieChannel = false;//暂时设置为false，跟channelId计算得出，但目前还不知道计算方法
        gM = new GlobalManager(currentChannelId, packageName, signatureHashCode);
    }*/
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_writeFifo(JNIEnv *env, jclass clazz,
                                          jbyteArray bytes, jint len) {
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_getKey(JNIEnv *env, jclass clazz, jobject obj) {
    jclass contextClazz = env->GetObjectClass(obj);
    jmethodID getPackageName = env->GetMethodID(contextClazz, "getPackageName",
                                                "()Ljava/lang/String;");

    jstring name = static_cast<jstring>(env->CallObjectMethod(obj, getPackageName));
    packageName = env->GetStringUTFChars(name, NULL);
}

int fifoClose(JNIEnv *env, jclass clazz)
{
    /*jmethodID isWifiState = env->GetStaticMethodID(clazz, "isWifiState", "()Z");
    if ( isWifiState ) {
        isCompatible = true;
        wifiState = env->CallStaticBooleanMethod(clazz, isWifiState);
        if (wifiState) {
            isCardToSwitch = 0;
        }
    }
    else {
        isCompatible = false;
    }*/

    return 0;
}

double add_play_cl2(void)
{
    double v0; // d8
    double result; // r0

    /*++dword_F4328;
    v0 = COERCE_DOUBLE(getTime());
    result = COERCE_DOUBLE(getPlayerStartTime());
    unk_F4488 = unk_F4488 + (v0 - result) * 1000.0;
    if ( !isSwitchEntry )
    {
        ++dword_F44BC;
        result = COERCE_DOUBLE(getTime());
        unk_F44B0 = unk_F44B0 + (result - unk_F4490) * 1000.0;
    }*/
    return result;
}

double add_play_cl(void)
{
    double v0; // d8
    double result; // r0

    /*++dword_F4324;
    v0 = COERCE_DOUBLE(getTime());
    result = COERCE_DOUBLE(getPlayerStartTime());
    unk_F4480 = unk_F4480 + (v0 - result) * 1000.0;
    if ( !isSwitchEntry )
    {
        ++dword_F44B8;
        result = COERCE_DOUBLE(getTime());
        unk_F44A8 = unk_F44A8 + (result - unk_F4490) * 1000.0;
    }*/
    return result;
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_closeFifo(JNIEnv *env, jclass clazz) {
    /*fifoClose(env, clazz);
    bitrate = "origin";
    interrupt = true;
    isPlayerStarted = false;
    rtmpChangedToData = false;
    lowDelayChannel = false;
    if ( gM )
    {
        if ( isSwitchEntry )
        {
            delete gM;
            gM = NULL;
            return;
        }
        if ( currentPlayMode )
        {
            if ( currentPlayMode != 1 ) {
                delete gM;
                gM = NULL;
            }
            add_play_cl2();
        }
        else
        {
            add_play_cl();
        }
    }*/
}

JNIEXPORT jint JNICALL
Java_com_libfifo_FifoController_getFifoLength(JNIEnv *env, jclass clazz) {
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_libfifo_FifoController_getFifoSize(JNIEnv *env, jclass clazz) {
    return 0;
}

JNIEXPORT jstring JNICALL
Java_com_libfifo_FifoController_getFifoVersion(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF(version);
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setClientInfo(JNIEnv *env, jclass clazz,
                                              jstring platform, jstring id, jstring model) {
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setClientInfo2(JNIEnv *env, jclass clazz,
                                               jstring plat, jstring id, jstring model,
                                               jstring deviceName, jstring pid) {
    /*if (plat) {
        platform = env->GetStringUTFChars(plat, NULL);
    }

    if (id) {
        clientId = env->GetStringUTFChars(id, NULL);
    }

    if (model) {
        sysinfo = env->GetStringUTFChars(model, NULL);
    }

    if (deviceName) {
        device = env->GetStringUTFChars(deviceName, NULL);
    }

    if (pid) {
        reportPartnerId = env->GetStringUTFChars(pid, NULL);
    }

    initStatistic();*/
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setVLCPlayStart(JNIEnv *env, jclass clazz) {
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setVLCVout(JNIEnv *env, jclass clazz) {
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setVLCPlayCard(JNIEnv *env, jclass clazz) {
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setDebug(JNIEnv *env, jclass clazz, jboolean param) {
    /*if (param) {
        debugInfo = "%s%s";
    } else {
        debugInfo = defaultCookie;
    }*/
}

JNIEXPORT jdouble JNICALL
Java_com_libfifo_FifoController_getCurrentPlayTime(JNIEnv *env, jclass clazz, jboolean param) {
    double result; // r0
    /*M3U8Manager *m3U8Manager; // r0
    P2PManager* p2PManager;

    if ( !isPlayerStarted || !gM )
        return 0.0;
    if ( gM->getStreamType() == 1 ) {
        if ( isThirdSource ) {
            result = getTime() - 30.0;
        } else {
            if ( !ioAllow )
                return 0.0;
            p2PManager = new P2PManager();
            result = p2PManager->getCurrentPlayTime();
        }
    } else {
        if ( gM->getStreamType() != 2 )
            return 0.0;
        m3U8Manager = new M3U8Manager();
        result = m3U8Manager->getCurrentPlayTime();
    }*/
    return result;
}

JNIEXPORT jint JNICALL
Java_com_libfifo_FifoController_checkCard(JNIEnv *env, jclass clazz, jdouble buffersize,
                                          jdouble vlcReadBytes) {
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_libfifo_FifoController_getP2PDownloadRate(JNIEnv *env, jclass clazz) {
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_libfifo_FifoController_getP2PUploadRate(JNIEnv *env, jclass clazz) {
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_libfifo_FifoController_getCDNDownloadRate(JNIEnv *env, jclass clazz) {
    return 0;
}

JNIEXPORT jstring JNICALL
Java_com_libfifo_FifoController_getPlayUrl(JNIEnv *env, jclass clazz) {
    return 0;
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setFifoEventHandler(JNIEnv *env, jclass clazz,
                                                    jobject eventHandler) {
    myEnv = env;
    jclass eventHandlerClazz = env->GetObjectClass(eventHandler);
    callback = env->GetMethodID(eventHandlerClazz, "callback", "(I)V");
    eventHandlerObject = eventHandler;
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setPlayStatus(JNIEnv *env, jclass clazz) {

}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setCardStatus(JNIEnv *env, jclass clazz) {

}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setDirectPlayStart(JNIEnv *env, jclass clazz) {
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setDirectVout(JNIEnv *env, jclass clazz) {
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setDirectPlayCard(JNIEnv *env, jclass clazz) {
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setPlayerVout(JNIEnv *env, jclass clazz) {
    /*isPlayerStarted = true;
    isCardToSwitch = false;
    isSwitchEntry = false;
    clientPlayerVout();*/
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setPlayerCard(JNIEnv *env, jclass clazz) {
    /*if ( isPlayerStarted )
    {
        clientPlayerCard();
        procSelfPause();
    }*/
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_setPlayerPlay(JNIEnv *env, jclass clazz) {
    /*clientPlayerPlay();
    procSelfPlay();*/
}

JNIEXPORT void JNICALL
Java_com_libfifo_FifoController_updateDataState(JNIEnv *env, jclass clazz, jlong playerReadBytes) {
}

#ifdef __cplusplus
}
#endif