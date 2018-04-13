//
// Created by 赵勇 on 2018/4/10.
//


//----- (00031608) --------------------------------------------------------
signed int __fastcall P2PManager::writeLocalAndNatAddr(P2PManager *this)
{
    P2PManager *v1; // r4
    char *v2; // r0
    int v3; // r5
    size_t v4; // r10
    size_t v5; // r9
    double v6; // r4
    const char *v7; // r1
    int v9; // [sp+1Ch] [bp-D4h]
    int v10; // [sp+20h] [bp-D0h]
    char s; // [sp+24h] [bp-CCh]
    char v12; // [sp+2Ch] [bp-C4h]
    char v13; // [sp+38h] [bp-B8h]
    char v14; // [sp+68h] [bp-88h]
    char v15; // [sp+A1h] [bp-4Fh]

    v1 = this;
    v2 = inet_ntoa(*(struct in_addr *)(*((_DWORD *)this + 376) + 4));
    strcpy(&v13, v2);
    sprintf(&s, "%d", (unsigned __int16)__rev16(*(unsigned __int16 *)(*((_DWORD *)v1 + 376) + 2)));
    v3 = (int)v1 + 1226;
    sprintf((char *)v1 + 1226, "%s:%s:%s:%s", &v13, &s, (char *)v1 + 1180, &s);
    v4 = strlen(&v13);
    v5 = strlen(&s);
    v9 = 1;
    *((_BYTE *)v1 + 2 * v5 + v4 + strlen((const char *)v1 + 1180) + 1229) = 0;
    LODWORD(v6) = 0;
    strcpy(&v14, "http://mobile.kukuplay.com/core/a/addrInfo.php?addrInfo=");
    memset(&v15, 0, 0x2Bu);
    v7 = (const char *)v3;
    HIDWORD(v6) = 1076887552;
    strcat(&v14, v7);
    v10 = 10;
    return doRequest(&v9, &v14, &v12, &v10, v6, 0, 0, 0);
}

//----- (00031788) --------------------------------------------------------
int __fastcall P2PManager::stopStunClient(P2PManager *this)
{
    int result; // r0

    result = *((_DWORD *)this + 294);
    if ( result )
        result = StunClient::stop(result);
    return result;
}

//----- (00031798) --------------------------------------------------------
signed int __fastcall P2PManager::fyzbGetLocalIp(P2PManager *this)
{
    P2PManager *v1; // r7
    signed int result; // r0
    int v3; // r6
    unsigned int v4; // r5
    int *v5; // r4
    char *v6; // r4
    size_t v7; // r0
    int v8; // [sp+0h] [bp-22Ch]
    unsigned int v9; // [sp+208h] [bp-24h]
    int *v10; // [sp+20Ch] [bp-20h]

    v1 = this;
    result = socket(2, 2, 0);
    v3 = result;
    if ( result >= 0 )
    {
        v10 = &v8;
        v9 = 512;
        if ( !ioctl(result, 0x8912u, &v9) )
        {
            v4 = (v9 >> 5) - 1;
            v5 = &v8 + 8 * v4;
            while ( 1 )
            {
                v5 -= 8;
                if ( (signed int)(v4 + 1) <= 0 )
                    break;
                if ( !ioctl(v3, 0x8915u) )
                {
                    v6 = inet_ntoa((struct in_addr)*(&v8 + 8 * v4 + 5));
                    goto LABEL_8;
                }
                --v4;
            }
        }
        v6 = 0;
        LABEL_8:
        close(v3);
        v7 = strlen(v6);
        memcpy((char *)v1 + 1180, v6, v7);
        result = (signed int)v1 + strlen(v6);
        *(_BYTE *)(result + 1180) = 0;
    }
    return result;
}

//----- (00031880) --------------------------------------------------------
int __fastcall P2PManager::destroyLocalSocket(P2PManager *this)
{
    P2PManager *v1; // r4
    int result; // r0

    v1 = this;
    result = *((_DWORD *)this + 374);
    if ( result > 0 )
    {
        result = close(result);
        *((_DWORD *)v1 + 374) = -1;
    }
    return result;
}

//----- (000318A4) --------------------------------------------------------
int __fastcall P2PManager::initLocalSocket(P2PManager *this)
{
    P2PManager *v1; // r4
    int v2; // r0
    int v3; // r3
    int v4; // r0
    int result; // r0

    v1 = this;
    if ( *((_DWORD *)this + 374) > 0 )
    P2PManager::destroyLocalSocket(this);
    v2 = socket(2, 2, 0);
    *((_DWORD *)v1 + 374) = v2;
    if ( v2 < 0 )
    {
        P2PManager::destroyLocalSocket(v1);
        result = -1;
    }
    else
    {
        P2PManager::fyzbGetLocalIp(v1);
        v3 = *((_DWORD *)v1 + 371);
        v4 = *((_DWORD *)v1 + 374);
        *(_WORD *)v3 = 2;
        *(_WORD *)(v3 + 2) = 0;
        *(_DWORD *)(v3 + 4) = 0;
        result = bind(v4, (const struct sockaddr *)v3, 0x10u);
        if ( result )
        {
            P2PManager::destroyLocalSocket(v1);
            result = -2;
        }
    }
    return result;
}

//----- (0003192C) --------------------------------------------------------
pthread_t *__fastcall P2PManager::requestPeers(P2PManager *this)
{
    return TrackerClient::requestPeer(*((pthread_t **)this + 282), (pthread_t)notifyTracker);
}

//----- (00031940) --------------------------------------------------------
pthread_t *notifyRequestPeer(void)
{
    return P2PManager::requestPeers((P2PManager *)gP2PManager);
}
// F3D68: using guessed type int gP2PManager;

//----- (00031954) --------------------------------------------------------
int __fastcall P2PManager::initInfoId(P2PManager *this, const char *a2, const char *a3, int a4)
{
P2PManager *v4; // r6
const char *v5; // r8
const char *v6; // r7
int v7; // r9
char s; // [sp+8h] [bp-88h]

v4 = this;
v5 = a2;
v6 = a3;
v7 = a4;
memset(&s, 0, 0x64u);
sprintf(&s, "%s_%s_%d", v5, v6, v7);
*((_DWORD *)v4 + 281) = strdup(&s);
return 0;
}

//----- (000319E0) --------------------------------------------------------
signed int __fastcall P2PManager::addHttpTaskWithPath(P2PManager *this, unsigned int a2)
{
return AcquireChannelPlayInfo::downloadPieceDataWithPieceid(*((AcquireChannelPlayInfo **)this + 377), a2);
}

//----- (000319E8) --------------------------------------------------------
signed int __fastcall notifyToHttpDownload(unsigned int a1)
{
    return P2PManager::addHttpTaskWithPath((P2PManager *)gP2PManager, a1);
}
// F3D68: using guessed type int gP2PManager;

//----- (00031A00) --------------------------------------------------------
signed int __fastcall P2PManager::addHttpTaskWithPath(P2PManager *this, unsigned int a2, int a3, int a4)
{
return AcquireChannelPlayInfo::downloadPieceDataWithPieceid(*((AcquireChannelPlayInfo **)this + 377), a2, a3, a4);
}

//----- (00031A08) --------------------------------------------------------
int __fastcall notifyOneFile(int result)
{
    OneFile *v1; // r4
    int v2; // r0
    int v3; // r8
    OneData *v4; // r0
    int v5; // r0
    P2PManager *v6; // r7
    int v7; // r10
    int v8; // r9
    int v9; // r8
    int v10; // r0
    char v11; // [sp+4h] [bp-34h]

    v1 = (OneFile *)result;
    if ( result && gLocalMemory )
    {
        result = OneFile::isFinished((OneFile *)result);
        if ( !result )
        {
            v5 = OneFile::getTotalSize(v1);
            addP2pDownloadAvailableBytes(v5);
            v6 = (P2PManager *)gP2PManager;
            v7 = OneFile::getFileId(v1);
            v8 = OneFile::getTotalSize(v1);
            v9 = OneFile::getFileSize(v1);
            v10 = OneFile::getTotalSize(v1);
            P2PManager::addHttpTaskWithPath(v6, v7, v8, v9 - v10);
            result = (int)LocalMemory::addIncompletePendingFile((LocalMemory *)gLocalMemory, v1);
        }
        if ( gLocalMemory )
        {
            result = OneFile::isFinished(v1);
            if ( result )
            {
                v2 = OneFile::getTotalSize(v1);
                addP2pDownloadAvailableBytes(v2);
                add_FlvP2pReceiveCount();
                v3 = OneFile::getFileId(v1);
                OneData::OneData((int)&v11);
                v4 = LocalMemory::cacheFileDataToOneData((LocalMemory *)gLocalMemory, v1, (OneData *)&v11);
                switch ( AcquireChannelPlayInfo::isDataValid(v4) )
                {
                    case 0:
                    case 2:
                    case 3:
                        LocalMemory::addPendingFile(gLocalMemory, v1);
                        break;
                    case 1:
                        add_FlvP2pLenVerifyFailCount();
                        goto LABEL_9;
                    case 4:
                        add_FlvP2pDataVerifyFailCount();
                    LABEL_9:
                        AcquireChannelPlayInfo::downloadPieceDataWithPieceid(*(AcquireChannelPlayInfo **)(gP2PManager + 1508), v3);
                        LocalMemory::recycleOneFile(gLocalMemory, v1);
                        break;
                    default:
                        break;
                }
                result = (int)OneData::~OneData((OneData *)&v11);
            }
        }
    }
    return result;
}
// F3D68: using guessed type int gP2PManager;
// F3D6C: using guessed type int gLocalMemory;

//----- (00031B90) --------------------------------------------------------
int __fastcall reFreshStatus(void *a1)
{
    return P2PManager::collectstatus_cb((P2PManager *)a1, 0, 0, 0);
}

//----- (00031BA0) --------------------------------------------------------
int __fastcall P2PManager::checkCDNMargin(int result)
{
    int v1; // r4
    signed int v2; // r1

    v1 = result;
    if ( !*(_DWORD *)(result + 56) )
    {
        v2 = (signed int)FifoDataManager::getWriteDataTime((FifoDataManager *)*(_DWORD *)(result + 1516));
        if ( v2 > 0 )
        {
            if ( *(_BYTE *)(v1 + 1493) )
                P2PClient::checkCDNMargin(*(_DWORD *)(v1 + 1132), v2 + dword_F3008);
        }
        result = (*(int (__cdecl **)(_DWORD, _DWORD))(**(_DWORD **)(v1 + 64) + 8))(
                *(_DWORD *)(v1 + 64),
                *(_DWORD *)(**(_DWORD **)(v1 + 64) + 8));
    }
    return result;
}
// F3008: using guessed type int dword_F3008;

//----- (00031C40) --------------------------------------------------------
char *__fastcall P2PManager::getFifoPath(P2PManager *this)
{
    return (char *)this + 96;
}

//----- (00031C48) --------------------------------------------------------
int __fastcall P2PManager::getFifoFd(P2PManager *this)
{
    return *((_DWORD *)this + 280);
}

//----- (00031C50) --------------------------------------------------------
int __fastcall P2PManager::refreshBitmap(P2PManager *this, int a2)
{
pthread_mutex_t *v2; // r4
P2PManager *v3; // r5
int v4; // r6

v2 = (pthread_mutex_t *)((char *)this + 1156);
v3 = this;
v4 = a2;
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 1156));
*(_BYTE *)(*((_DWORD *)v3 + 285) + v4) = 1;
return pthread_mutex_unlock(v2);
}

//----- (00031C84) --------------------------------------------------------
int __fastcall notifyRefreshBitmap(int a1)
{
    return P2PManager::refreshBitmap((P2PManager *)gP2PManager, a1);
}
// F3D68: using guessed type int gP2PManager;

//----- (00031C9C) --------------------------------------------------------
int __fastcall P2PManager::moveOnStep(P2PManager *this)
{
    pthread_mutex_t *v1; // r5
    P2PManager *v2; // r4
    signed int v3; // r2
    int v4; // r3
    int v5; // r3
    char v6; // t1
    LocalMemory *v7; // r0

    v1 = (pthread_mutex_t *)((char *)this + 1156);
    v2 = this;
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 1156));
    v3 = 1;
    do
    {
        v4 = *((_DWORD *)v2 + 285);
        v6 = *(_BYTE *)(v4 + v3);
        v5 = v4 + v3++;
        *(_BYTE *)(v5 - 1) = v6;
    }
    while ( v3 != 160 );
    *(_BYTE *)(*((_DWORD *)v2 + 285) + 159) = 0;
    v7 = (LocalMemory *)*((_DWORD *)v2 + 284);
    ++*(_DWORD *)(*((_DWORD *)v2 + 283) + 11000);
    LocalMemory::moveOnStep(v7);
    return pthread_mutex_unlock(v1);
}

//----- (00031D04) --------------------------------------------------------
int __fastcall P2PManager::setFlvHeadFinished(int result)
{
    *(_BYTE *)(result + 1492) = 1;
    return result;
}

//----- (00031D10) --------------------------------------------------------
bool __fastcall P2PManager::fifoCopy(int a1, unsigned int a2, int a3)
{
    int v3; // r4
    unsigned int v4; // r8
    int v5; // r7
    time_t v6; // r0
    LocalMemory *v7; // r9
    int v8; // r1
    int v9; // r3
    int v10; // r2
    int v11; // r0
    _DWORD **v12; // r4
    int v13; // r12
    int v14; // r3
    int v15; // r0
    _DWORD **v16; // r5
    unsigned int v17; // r6
    signed int v18; // r0

    v3 = a1;
    v4 = a2;
    v5 = a3;
    v6 = time(0);
    if ( startChangeCdnTime && (signed int)(v6 - startChangeCdnTime) > 59 )
    {
        ChannelPlayInfoManager::setCdnSrcIndex(
                *(ChannelPlayInfoManager **)(v3 + 1512),
                *(_DWORD *)(*(_DWORD *)(v3 + 1512) + 32072));
        startChangeCdnTime = 0;
    }
    v7 = *(LocalMemory **)(v3 + 1136);
    if ( !v7 )
        return 0;
    v8 = *(_DWORD *)(v3 + 36);
    v9 = *(_DWORD *)(v3 + 24);
    v10 = ((*(_DWORD *)(v3 + 40) - *(_DWORD *)(v3 + 44)) >> 2)
          + ((((*(_DWORD *)(v3 + 52) - v8) >> 2) - 1) << 7)
          + ((*(_DWORD *)(v3 + 32) - v9) >> 2);
    if ( v10 <= 0 )
    {
        v13 = 0;
    }
    else
    {
        v11 = *(_DWORD *)(v3 + 28);
        v12 = *(_DWORD ***)(v3 + 24);
        v13 = 0;
        v14 = (v9 - v11) >> 2;
        v15 = ~v14;
        while ( 1 )
        {
            v16 = v12;
            if ( (unsigned int)v14 > 0x7F )
            {
                v17 = v14 >> 7;
                if ( v14 <= 0 )
                    v17 = ~((unsigned int)(v15 - v13) >> 7);
                v16 = (_DWORD **)(*(_DWORD *)(v8 + 4 * v17) + 4 * (v14 - (v17 << 7)));
            }
            ++v14;
            ++v12;
            if ( **v16 == v4 )
                break;
            if ( ++v13 == v10 )
                return 0;
        }
    }
    if ( v13 == v10 )
        return 0;
    *(_DWORD *)v5 = v4;
    *(_DWORD *)(v5 + 4) = 0;
    v18 = LocalMemory::readMemory(v7, (unsigned __int8 **)(v5 + 12), v4);
    *(_DWORD *)(v5 + 8) = v18;
    return v18 > 0;
}
// F5728: using guessed type int startChangeCdnTime;

//----- (00031E64) --------------------------------------------------------
bool __fastcall cbFifoCopy(unsigned int a1, int a2)
{
    return P2PManager::fifoCopy(gP2PManager, a1, a2);
}
// F3D68: using guessed type int gP2PManager;

//----- (00031E80) --------------------------------------------------------
double __fastcall P2PManager::getCurrentPlayTime(P2PManager *this)
{
    FifoDataManager *v1; // r0
    double result; // r0

    if ( *((_DWORD *)this + 14) || (v1 = (FifoDataManager *)*((_DWORD *)this + 379)) == 0 )
    result = 0.0;
    else
    result = FifoDataManager::getWriteDataTime(v1);
    return result;
}

//----- (00031EA8) --------------------------------------------------------
int __fastcall P2PManager::getCurrentContinuousPieceBytes(P2PManager *this)
{
    P2PManager *v1; // r4
    FifoDataManager *v2; // r0
    LocalMemory *v3; // r5
    double v4; // r0
    int result; // r0

    v1 = this;
    v2 = (FifoDataManager *)*((_DWORD *)this + 379);
    if ( v2 && (v3 = (LocalMemory *)*((_DWORD *)v1 + 284)) != 0 )
    {
        v4 = FifoDataManager::getWriteDataTime(v2);
        result = LocalMemory::getAvaliablePieceBytes(v3, (unsigned int)v4, (int *)v1 + 382);
        *((_DWORD *)v1 + 381) = result;
    }
    else
    {
        *((_DWORD *)v1 + 381) = 0;
        result = 0;
        *((_DWORD *)v1 + 382) = 0;
    }
    return result;
}

//----- (00031F04) --------------------------------------------------------
int __fastcall P2PManager::getCurrentContinuousPieceNum(P2PManager *this)
{
    return *((_DWORD *)this + 382);
}

//----- (00031F0C) --------------------------------------------------------
int __fastcall P2PManager::getCurrentPieceBytes(P2PManager *this)
{
    P2PManager *v1; // r4
    LocalMemory *v2; // r0
    int result; // r0

    v1 = this;
    if ( *((_DWORD *)this + 379) && (v2 = (LocalMemory *)*((_DWORD *)this + 284)) != 0 )
    {
        result = LocalMemory::getCurrentPieceBytes(v2, (int *)v1 + 384);
        *((_DWORD *)v1 + 383) = result;
    }
    else
    {
        *((_DWORD *)v1 + 383) = 0;
        result = 0;
        *((_DWORD *)v1 + 384) = 0;
    }
    return result;
}

//----- (00031F50) --------------------------------------------------------
int __fastcall P2PManager::getCurrentPieceNum(P2PManager *this)
{
    return *((_DWORD *)this + 384);
}

//----- (00031F58) --------------------------------------------------------
void **__fastcall std::_Deque_base<FILEINFO *,std::allocator<FILEINFO *>>::~_Deque_base(void **a1)
{
    void **v1; // r6
    void *v2; // r0
    void **v3; // r4
    unsigned int v4; // r5
    void *v5; // t1

    v1 = a1;
    v2 = *a1;
    if ( v2 )
    {
        v3 = (void **)v1[5];
        v4 = (unsigned int)v1[9] + 4;
        if ( (unsigned int)v3 < v4 )
        {
            do
            {
                v5 = *v3;
                ++v3;
                operator delete(v5);
            }
            while ( v4 > (unsigned int)v3 );
            v2 = *v1;
        }
        operator delete(v2);
    }
    return v1;
}

//----- (00031FA0) --------------------------------------------------------
void __fastcall std::vector<tagInfo,std::allocator<tagInfo>>::_M_insert_aux(int a1, char *a2, char *a3)
{
int v3; // r4
char *v4; // r0
char *v5; // r6
char *v6; // r9
unsigned int v7; // r7
_BYTE *v8; // r2
int v9; // r3
unsigned int v10; // r8
int v11; // r10
void *v12; // r0
char *v13; // r3
int v14; // r2
int v15; // r6
char *v16; // r1
int v17; // [sp+0h] [bp-828h]
_BYTE *v18; // [sp+804h] [bp-24h]

v3 = a1;
v4 = *(char **)(a1 + 4);
v5 = a2;
v6 = a3;
if ( v4 == *(char **)(v3 + 8) )
{
v8 = *(_BYTE **)v3;
v9 = -133956095 * ((signed int)&v4[-*(_DWORD *)v3] >> 2);
if ( !v9 )
{
v10 = 2052;
v11 = -133956095 * ((a2 - v8) >> 2);
goto LABEL_13;
}
v7 = -267912190 * ((signed int)&v4[-*(_DWORD *)v3] >> 2);
if ( -133956095 * ((signed int)&v4[-*(_DWORD *)v3] >> 2) <= (unsigned int)(-267912190
* ((signed int)&v4[-*(_DWORD *)v3] >> 2)) )
goto LABEL_26;
goto LABEL_12;
}
if ( v4 )
{
memcpy(v4, v4 - 2052, 0x804u);
v7 = *(_DWORD *)(v3 + 4);
}
else
{
v7 = 0;
}
*(_DWORD *)(v3 + 4) = v7 + 2052;
memcpy(&v17, v6, 0x804u);
if ( -133956095 * ((signed int)(v7 - 2052 - (_DWORD)v5) >> 2) )
memmove(
(void *)(v7 - 4 * ((signed int)(v7 - 2052 - (_DWORD)v5) >> 2)),
v5,
4 * ((signed int)(v7 - 2052 - (_DWORD)v5) >> 2));
memcpy(v5, &v17, 0x804u);
while ( 1 )
{
v8 = v18;
v9 = _stack_chk_guard;
if ( v18 == (_BYTE *)_stack_chk_guard )
break;
LABEL_26:
if ( v7 > 0x1FF007 )
{
LABEL_12:
        v10 = -2020;
v11 = -133956095 * ((v5 - v8) >> 2);
LABEL_13:
        v7 = (unsigned int)operator new(v10);
goto LABEL_14;
}
v10 = 4 * (v7 + (v9 << 10));
v11 = -133956095 * ((v5 - v8) >> 2);
if ( v7 )
goto LABEL_13;
LABEL_14:
        v12 = (void *)(v7 + 2052 * v11);
if ( v12 )
memcpy(v12, v6, 0x804u);
if ( -133956095 * ((signed int)&v5[-*(_DWORD *)v3] >> 2) )
{
v6 = (char *)(4 * ((signed int)&v5[-*(_DWORD *)v3] >> 2));
memmove((void *)v7, *(const void **)v3, (size_t)v6);
}
else
{
v6 = 0;
}
v13 = &v6[v7 + 2052];
v14 = -133956095 * ((*(_DWORD *)(v3 + 4) - (signed int)v5) >> 2);
if ( v14 )
{
v16 = v5;
v15 = 4 * ((*(_DWORD *)(v3 + 4) - (signed int)v5) >> 2);
v13 = (char *)memmove(&v6[v7 + 2052], v16, 2052 * v14);
}
else
{
v15 = 0;
}
v5 = &v13[v15];
if ( *(_DWORD *)v3 )
operator delete(*(void **)v3);
*(_DWORD *)v3 = v7;
*(_DWORD *)(v3 + 4) = v5;
*(_DWORD *)(v3 + 8) = v7 + v10;
}
}

//----- (000321EC) --------------------------------------------------------
void **__fastcall std::_Deque_base<Json::Reader::ErrorInfo,std::allocator<Json::Reader::ErrorInfo>>::~_Deque_base(void **a1)
{
    void **v1; // r6
    void *v2; // r0
    void **v3; // r4
    unsigned int v4; // r5
    void *v5; // t1

    v1 = a1;
    v2 = *a1;
    if ( v2 )
    {
        v3 = (void **)v1[5];
        v4 = (unsigned int)v1[9] + 4;
        if ( (unsigned int)v3 < v4 )
        {
            do
            {
                v5 = *v3;
                ++v3;
                operator delete(v5);
            }
            while ( v4 > (unsigned int)v3 );
            v2 = *v1;
        }
        operator delete(v2);
    }
    return v1;
}

//----- (00032234) --------------------------------------------------------
Json::Reader *__fastcall Json::Reader::~Reader(Json::Reader *this)
{
    Json::Reader *v1; // r5
    int v2; // r3
    void *v3; // r0
    int v4; // r3
    void *v5; // r0
    int v6; // r12
    int v7; // r2
    int v8; // r3
    int v9; // r8
    int v10; // r7
    int v11; // r6
    int v12; // r4
    void *v13; // r0
    void **v14; // r4
    unsigned int v15; // r6
    void *v16; // t1
    unsigned int *v18; // r3
    signed int v19; // r2
    unsigned int *v20; // r3
    signed int v21; // r2
    int v22; // [sp+0h] [bp-38h]
    int v23; // [sp+4h] [bp-34h]
    int v24; // [sp+8h] [bp-30h]
    int v25; // [sp+Ch] [bp-2Ch]
    int v26; // [sp+10h] [bp-28h]
    int v27; // [sp+14h] [bp-24h]
    int v28; // [sp+18h] [bp-20h]
    int v29; // [sp+1Ch] [bp-1Ch]

    v1 = this;
    v2 = *((_DWORD *)this + 26);
    v3 = (void *)(v2 - 12);
    if ( (int *)(v2 - 12) != &dword_2FEF3C )
    {
        v18 = (unsigned int *)(v2 - 4);
        __dmb(0xFu);
        do
            v19 = __ldrex(v18);
        while ( __strex(v19 - 1, v18) );
        __dmb(0xFu);
        if ( v19 <= 0 )
            operator delete(v3);
    }
    v4 = *((_DWORD *)v1 + 20);
    v5 = (void *)(v4 - 12);
    if ( (int *)(v4 - 12) != &dword_2FEF3C )
    {
        v20 = (unsigned int *)(v4 - 4);
        __dmb(0xFu);
        do
            v21 = __ldrex(v20);
        while ( __strex(v21 - 1, v20) );
        __dmb(0xFu);
        if ( v21 <= 0 )
            operator delete(v5);
    }
    v6 = *((_DWORD *)v1 + 18);
    v7 = *((_DWORD *)v1 + 19);
    v8 = *((_DWORD *)v1 + 12);
    v9 = *((_DWORD *)v1 + 13);
    v10 = *((_DWORD *)v1 + 14);
    v11 = *((_DWORD *)v1 + 15);
    v12 = *((_DWORD *)v1 + 16);
    v27 = *((_DWORD *)v1 + 17);
    v28 = v6;
    v29 = v7;
    v22 = v8;
    v23 = v9;
    v24 = v10;
    v25 = v11;
    v26 = v12;
    sub_3126C(&v22, &v26);
    std::_Deque_base<Json::Reader::ErrorInfo,std::allocator<Json::Reader::ErrorInfo>>::~_Deque_base((void **)v1 + 10);
    v13 = *(void **)v1;
    if ( *(_DWORD *)v1 )
    {
        v14 = (void **)*((_DWORD *)v1 + 5);
        v15 = *((_DWORD *)v1 + 9) + 4;
        if ( (unsigned int)v14 < v15 )
        {
            do
            {
                v16 = *v14;
                ++v14;
                operator delete(v16);
            }
            while ( v15 > (unsigned int)v14 );
            v13 = *(void **)v1;
        }
        operator delete(v13);
    }
    return v1;
}
// 2FEF3C: using guessed type int dword_2FEF3C;

//----- (00032374) --------------------------------------------------------
void *__fastcall P2PManager::parseConf(P2PManager *this, char *a2, char *a3)
{
    double v3; // r10
    char *v4; // r5
    void **v5; // r4
    int v6; // r3
    unsigned __int64 v7; // r10
    int v8; // r7
    void *v9; // r0
    int *v10; // r0
    int v11; // r2
    void *v12; // r0
    int *v13; // r0
    int v14; // r2
    void *v15; // r0
    int *v16; // r0
    int v17; // r2
    void *v18; // r0
    int *v19; // r0
    int v20; // r2
    void *v21; // r0
    int *v22; // r0
    int v23; // r2
    void *v24; // r0
    int *v25; // r0
    int v26; // r2
    void *v27; // r0
    int *v28; // r0
    int v29; // r2
    void *v30; // r0
    int *v31; // r0
    int v32; // r2
    void *v33; // r0
    int *v34; // r0
    int v35; // r2
    void *v36; // r0
    int *v37; // r0
    int v38; // r2
    void *v39; // r0
    int *v40; // r0
    int v41; // r2
    void *v42; // r0
    int *v43; // r0
    int v44; // r2
    void *v45; // r0
    int *v46; // r0
    int v47; // r2
    void *v48; // r0
    int *v49; // r0
    int v50; // r2
    void *v51; // r0
    int *v52; // r0
    int v53; // r2
    void *v54; // r0
    int *v55; // r0
    int v56; // r2
    void *v57; // r0
    int *v58; // r0
    int v59; // r2
    void *v60; // r0
    int *v61; // r0
    int v62; // r2
    void *v63; // r0
    char *v64; // r3
    signed int v65; // r7
    double v66; // r0
    char *v67; // r0
    int v68; // r3
    void *result; // r0
    int v70; // r3
    void *v71; // r0
    int v72; // r3
    int v73; // lr
    int v74; // r6
    int v75; // r12
    int v76; // r11
    int v77; // r3
    char *v78; // r0
    void *v79; // t1
    char *v80; // r0
    int v81; // r3
    bool v82; // zf
    char *v83; // r2
    char *v84; // r10
    int v85; // t1
    bool v86; // zf
    char *v87; // r0
    int v88; // r3
    bool v89; // zf
    char *v90; // r2
    char *v91; // r10
    int v92; // t1
    bool v93; // zf
    float v94; // s14
    float v95; // s15
    float v96; // s15
    float v97; // s15
    float v98; // s15
    float v99; // s15
    unsigned int *v100; // r3
    signed int v101; // r2
    unsigned int *v102; // r3
    signed int v103; // r2
    unsigned int *v104; // r3
    signed int v105; // r2
    unsigned int *v106; // r3
    signed int v107; // r2
    unsigned int *v108; // r3
    signed int v109; // r2
    unsigned int *v110; // r2
    signed int v111; // r1
    unsigned int *v112; // r3
    signed int v113; // r2
    unsigned int *v114; // r3
    signed int v115; // r2
    unsigned int *v116; // r3
    signed int v117; // r2
    unsigned int *v118; // r3
    signed int v119; // r2
    unsigned int *v120; // r3
    signed int v121; // r2
    unsigned int *v122; // r3
    signed int v123; // r2
    unsigned int *v124; // r3
    signed int v125; // r2
    unsigned int *v126; // r3
    signed int v127; // r2
    unsigned int *v128; // r3
    signed int v129; // r2
    unsigned int *v130; // r3
    signed int v131; // r2
    unsigned int *v132; // r3
    signed int v133; // r2
    unsigned int *v134; // r3
    signed int v135; // r2
    unsigned int *v136; // r3
    signed int v137; // r2
    unsigned int *v138; // r3
    signed int v139; // r2
    unsigned int *v140; // r3
    signed int v141; // r2
    unsigned int *v142; // r3
    signed int v143; // r2
    P2PManager *v144; // [sp+20h] [bp-500h]
    char *v145; // [sp+2Ch] [bp-4F4h]
    int v146; // [sp+34h] [bp-4ECh]
    char *v147; // [sp+38h] [bp-4E8h]
    int v148; // [sp+3Ch] [bp-4E4h]
    char v149; // [sp+40h] [bp-4E0h]
    char v150; // [sp+44h] [bp-4DCh]
    char v151; // [sp+48h] [bp-4D8h]
    char v152; // [sp+4Ch] [bp-4D4h]
    char v153; // [sp+50h] [bp-4D0h]
    char v154; // [sp+54h] [bp-4CCh]
    char v155; // [sp+58h] [bp-4C8h]
    char v156; // [sp+5Ch] [bp-4C4h]
    char v157; // [sp+60h] [bp-4C0h]
    char v158; // [sp+64h] [bp-4BCh]
    char v159; // [sp+68h] [bp-4B8h]
    char v160; // [sp+6Ch] [bp-4B4h]
    char v161; // [sp+70h] [bp-4B0h]
    char v162; // [sp+74h] [bp-4ACh]
    char v163; // [sp+78h] [bp-4A8h]
    char v164; // [sp+7Ch] [bp-4A4h]
    char v165; // [sp+80h] [bp-4A0h]
    int v166; // [sp+94h] [bp-48Ch]
    int v167; // [sp+98h] [bp-488h]
    int v168; // [sp+9Ch] [bp-484h]
    int v169; // [sp+A0h] [bp-480h]
    int v170; // [sp+A4h] [bp-47Ch]
    int v171; // [sp+A8h] [bp-478h]
    int v172; // [sp+ACh] [bp-474h]
    int v173; // [sp+B0h] [bp-470h]
    const char *v174[15]; // [sp+B4h] [bp-46Ch]
    const char *v175[15]; // [sp+DCh] [bp-444h]
    int v176; // [sp+F0h] [bp-430h]
    int v177; // [sp+11Ch] [bp-404h]
    char v178; // [sp+124h] [bp-3FCh]
    char v179; // [sp+12Bh] [bp-3F5h]
    int v180; // [sp+524h] [bp+4h]
    int v181; // [sp+18ACh] [bp+138Ch]

    v144 = this;
    v3 = COERCE_DOUBLE(__PAIR__((unsigned int)a2, (unsigned int)a3));
    memset(&v180, 0, 0x1388u);
    v4 = (char *)v174;
    v146 = -1;
    memset(&v178, 0, 0x400u);
    Json::Reader::Reader((Json::Reader *)v174);
    Json::Value::Value((int)&v165, 0);
    v5 = (void **)&dword_2FEF3C;
    v147 = (char *)&unk_2FEF48;
    add_conf();
    v6 = LODWORD(v3);
    LODWORD(v3) = 0;
    sprintf(&v178, "%s?key=-net-nativelive-%s", HIDWORD(v3), v6);
    v7 = __PAIR__(1076887552, downloadPath((volatile int *)v144 + 15, &v178, (char *)&v180, &v146, v3, 0, 0, 0));
    add_confSuc();
    if ( (v7 & 0x80000000) != 0LL )
    {
        add_confFail();
        v65 = -1;
        v64 = v147;
    }
    else
    {
        sub_C1C58((void **)&v148, (char *)&v180);
        v8 = Json::Reader::parse(v174, (int)&v148, (Json::Value *)&v165, 1);
        v9 = (void *)(v148 - 12);
        if ( (int *)(v148 - 12) != &dword_2FEF3C )
        {
            v110 = (unsigned int *)(v148 - 4);
            __dmb(0xFu);
            do
                v111 = __ldrex(v110);
            while ( __strex(v111 - 1, v110) );
            __dmb(0xFu);
            if ( v111 <= 0 )
                operator delete(v9);
        }
        if ( v8 )
        {
            v10 = Json::Value::operator[]((Json::Value *)&v165, "window_s");
            Json::Value::asString((Json::Value *)&v149, (int)v10, v11);
            sub_C1700(&v147, &v149);
            v12 = (void *)(*(_DWORD *)&v149 - 12);
            if ( (int *)(*(_DWORD *)&v149 - 12) != &dword_2FEF3C )
            {
                v108 = (unsigned int *)(*(_DWORD *)&v149 - 4);
                __dmb(0xFu);
                do
                    v109 = __ldrex(v108);
                while ( __strex(v109 - 1, v108) );
                __dmb(0xFu);
                if ( v109 <= 0 )
                    operator delete(v12);
            }
            if ( *((_DWORD *)v147 - 3) )
            {
                v98 = strtod(v147, 0);
                unk_F300C = LODWORD(v98);
            }
            v13 = Json::Value::operator[]((Json::Value *)&v165, "window_i");
            Json::Value::asString((Json::Value *)&v150, (int)v13, v14);
            sub_C1700(&v147, &v150);
            v15 = (void *)(*(_DWORD *)&v150 - 12);
            if ( (int *)(*(_DWORD *)&v150 - 12) != &dword_2FEF3C )
            {
                v122 = (unsigned int *)(*(_DWORD *)&v150 - 4);
                __dmb(0xFu);
                do
                    v123 = __ldrex(v122);
                while ( __strex(v123 - 1, v122) );
                __dmb(0xFu);
                if ( v123 <= 0 )
                    operator delete(v15);
            }
            if ( *((_DWORD *)v147 - 3) )
            {
                v97 = strtod(v147, 0);
                unk_F3010 = LODWORD(v97);
            }
            v16 = Json::Value::operator[]((Json::Value *)&v165, "window_p");
            Json::Value::asString((Json::Value *)&v151, (int)v16, v17);
            sub_C1700(&v147, &v151);
            v18 = (void *)(*(_DWORD *)&v151 - 12);
            if ( (int *)(*(_DWORD *)&v151 - 12) != &dword_2FEF3C )
            {
                v116 = (unsigned int *)(*(_DWORD *)&v151 - 4);
                __dmb(0xFu);
                do
                    v117 = __ldrex(v116);
                while ( __strex(v117 - 1, v116) );
                __dmb(0xFu);
                if ( v117 <= 0 )
                    operator delete(v18);
            }
            if ( *((_DWORD *)v147 - 3) )
            {
                v99 = strtod(v147, 0);
                unk_F3014 = LODWORD(v99);
            }
            v19 = Json::Value::operator[]((Json::Value *)&v165, "cdn_mragin");
            Json::Value::asString((Json::Value *)&v152, (int)v19, v20);
            sub_C1700(&v147, &v152);
            v21 = (void *)(*(_DWORD *)&v152 - 12);
            if ( (int *)(*(_DWORD *)&v152 - 12) != &dword_2FEF3C )
            {
                v126 = (unsigned int *)(*(_DWORD *)&v152 - 4);
                __dmb(0xFu);
                do
                    v127 = __ldrex(v126);
                while ( __strex(v127 - 1, v126) );
                __dmb(0xFu);
                if ( v127 <= 0 )
                    operator delete(v21);
            }
            if ( *((_DWORD *)v147 - 3) )
                dword_F3D60 = atoi(v147);
            v22 = Json::Value::operator[]((Json::Value *)&v165, "max_con");
            Json::Value::asString((Json::Value *)&v153, (int)v22, v23);
            sub_C1700(&v147, &v153);
            v24 = (void *)(*(_DWORD *)&v153 - 12);
            if ( (int *)(*(_DWORD *)&v153 - 12) != &dword_2FEF3C )
            {
                v124 = (unsigned int *)(*(_DWORD *)&v153 - 4);
                __dmb(0xFu);
                do
                    v125 = __ldrex(v124);
                while ( __strex(v125 - 1, v124) );
                __dmb(0xFu);
                if ( v125 <= 0 )
                    operator delete(v24);
            }
            if ( *((_DWORD *)v147 - 3) )
                off_F3018[0] = (int *)atoi(v147);
            v25 = Json::Value::operator[]((Json::Value *)&v165, "kick_con");
            Json::Value::asString((Json::Value *)&v154, (int)v25, v26);
            sub_C1700(&v147, &v154);
            v27 = (void *)(*(_DWORD *)&v154 - 12);
            if ( (int *)(*(_DWORD *)&v154 - 12) != &dword_2FEF3C )
            {
                v118 = (unsigned int *)(*(_DWORD *)&v154 - 4);
                __dmb(0xFu);
                do
                    v119 = __ldrex(v118);
                while ( __strex(v119 - 1, v118) );
                __dmb(0xFu);
                if ( v119 <= 0 )
                    operator delete(v27);
            }
            if ( *((_DWORD *)v147 - 3) )
                dword_F301C = atoi(v147);
            v28 = Json::Value::operator[]((Json::Value *)&v165, "min_con");
            Json::Value::asString((Json::Value *)&v155, (int)v28, v29);
            sub_C1700(&v147, &v155);
            v30 = (void *)(*(_DWORD *)&v155 - 12);
            if ( (int *)(*(_DWORD *)&v155 - 12) != &dword_2FEF3C )
            {
                v120 = (unsigned int *)(*(_DWORD *)&v155 - 4);
                __dmb(0xFu);
                do
                    v121 = __ldrex(v120);
                while ( __strex(v121 - 1, v120) );
                __dmb(0xFu);
                if ( v121 <= 0 )
                    operator delete(v30);
            }
            if ( *((_DWORD *)v147 - 3) )
                dword_F3020 = atoi(v147);
            v31 = Json::Value::operator[]((Json::Value *)&v165, "rtt_s");
            Json::Value::asString((Json::Value *)&v156, (int)v31, v32);
            sub_C1700(&v147, &v156);
            v33 = (void *)(*(_DWORD *)&v156 - 12);
            if ( (int *)(*(_DWORD *)&v156 - 12) != &dword_2FEF3C )
            {
                v106 = (unsigned int *)(*(_DWORD *)&v156 - 4);
                __dmb(0xFu);
                do
                    v107 = __ldrex(v106);
                while ( __strex(v107 - 1, v106) );
                __dmb(0xFu);
                if ( v107 <= 0 )
                    operator delete(v33);
            }
            if ( *((_DWORD *)v147 - 3) )
            {
                v96 = strtod(v147, 0);
                unk_F3024 = LODWORD(v96);
            }
            v34 = Json::Value::operator[]((Json::Value *)&v165, "rtt_r");
            Json::Value::asString((Json::Value *)&v157, (int)v34, v35);
            sub_C1700(&v147, &v157);
            v36 = (void *)(*(_DWORD *)&v157 - 12);
            if ( (int *)(*(_DWORD *)&v157 - 12) != &dword_2FEF3C )
            {
                v128 = (unsigned int *)(*(_DWORD *)&v157 - 4);
                __dmb(0xFu);
                do
                    v129 = __ldrex(v128);
                while ( __strex(v129 - 1, v128) );
                __dmb(0xFu);
                if ( v129 <= 0 )
                    operator delete(v36);
            }
            if ( *((_DWORD *)v147 - 3) )
            {
                v95 = strtod(v147, 0);
                unk_F3028 = LODWORD(v95);
            }
            v37 = Json::Value::operator[]((Json::Value *)&v165, "cdn_ration");
            Json::Value::asString((Json::Value *)&v158, (int)v37, v38);
            sub_C1700(&v147, &v158);
            v39 = (void *)(*(_DWORD *)&v158 - 12);
            if ( (int *)(*(_DWORD *)&v158 - 12) != &dword_2FEF3C )
            {
                v130 = (unsigned int *)(*(_DWORD *)&v158 - 4);
                __dmb(0xFu);
                do
                    v131 = __ldrex(v130);
                while ( __strex(v131 - 1, v130) );
                __dmb(0xFu);
                if ( v131 <= 0 )
                    operator delete(v39);
            }
            if ( *((_DWORD *)v147 - 3) )
            {
                v94 = strtod(v147, 0);
                CDN_RATION = (signed int)(float)(v94 * 100.0);
            }
            v40 = Json::Value::operator[]((Json::Value *)&v165, "httpxstun");
            Json::Value::asString((Json::Value *)&v159, (int)v40, v41);
            sub_C1700(&v147, &v159);
            v42 = (void *)(*(_DWORD *)&v159 - 12);
            if ( (int *)(*(_DWORD *)&v159 - 12) != &dword_2FEF3C )
            {
                v136 = (unsigned int *)(*(_DWORD *)&v159 - 4);
                __dmb(0xFu);
                do
                    v137 = __ldrex(v136);
                while ( __strex(v137 - 1, v136) );
                __dmb(0xFu);
                if ( v137 <= 0 )
                    operator delete(v42);
            }
            if ( !*((_DWORD *)v147 - 3) )
                goto LABEL_190;
            memset(&v178, 0, 0x400u);
            strcpy(&v178, v147);
            if ( strstr(&v178, "http://") )
                v87 = &v179;
            else
                v87 = &v178;
            v88 = (unsigned __int8)*v87;
            v89 = v88 == 0;
            if ( *v87 )
                v89 = v88 == 58;
            if ( v89 )
            {
                v91 = v87;
            }
            else
            {
                v90 = v87 + 1;
                do
                {
                    v91 = v90;
                    v92 = (unsigned __int8)*v90++;
                    v88 = v92;
                    v93 = v92 == 0;
                    if ( v92 )
                        v93 = v88 == 58;
                }
                while ( !v93 );
            }
            if ( v88 )
            {
                *v91 = 0;
                v145 = strdup(v87);
                *((_DWORD *)v144 + 18) = v145;
                *((_DWORD *)v144 + 19) = strdup(v91 + 1);
            }
            else
            {
                LABEL_190:
                v145 = (char *)*((_DWORD *)v144 + 18);
            }
            if ( !v145 || !*((_DWORD *)v144 + 19) )
            {
                *((_DWORD *)v144 + 18) = strdup("50.115.126.85");
                *((_DWORD *)v144 + 19) = strdup("20000");
            }
            v43 = Json::Value::operator[]((Json::Value *)&v165, "backhttpxstun");
            Json::Value::asString((Json::Value *)&v160, (int)v43, v44);
            sub_C1700(&v147, &v160);
            v45 = (void *)(*(_DWORD *)&v160 - 12);
            if ( (int *)(*(_DWORD *)&v160 - 12) != &dword_2FEF3C )
            {
                v134 = (unsigned int *)(*(_DWORD *)&v160 - 4);
                __dmb(0xFu);
                do
                    v135 = __ldrex(v134);
                while ( __strex(v135 - 1, v134) );
                __dmb(0xFu);
                if ( v135 <= 0 )
                    operator delete(v45);
            }
            if ( *((_DWORD *)v147 - 3) )
            {
                memset(&v178, 0, 0x400u);
                strcpy(&v178, v147);
                if ( strstr(&v178, "http://") )
                    v80 = &v179;
                else
                    v80 = &v178;
                v81 = (unsigned __int8)*v80;
                v82 = v81 == 0;
                if ( *v80 )
                    v82 = v81 == 58;
                if ( v82 )
                {
                    v84 = v80;
                }
                else
                {
                    v83 = v80 + 1;
                    do
                    {
                        v84 = v83;
                        v85 = (unsigned __int8)*v83++;
                        v81 = v85;
                        v86 = v85 == 0;
                        if ( v85 )
                            v86 = v81 == 58;
                    }
                    while ( !v86 );
                }
                if ( v81 )
                {
                    *v84 = 0;
                    *((_DWORD *)v144 + 21) = strdup(v80);
                    *((_DWORD *)v144 + 22) = strdup(v84 + 1);
                }
            }
            v46 = Json::Value::operator[]((Json::Value *)&v165, "tracker");
            Json::Value::asString((Json::Value *)&v161, (int)v46, v47);
            sub_C1700(&v147, &v161);
            v48 = (void *)(*(_DWORD *)&v161 - 12);
            if ( (int *)(*(_DWORD *)&v161 - 12) != &dword_2FEF3C )
            {
                v142 = (unsigned int *)(*(_DWORD *)&v161 - 4);
                __dmb(0xFu);
                do
                    v143 = __ldrex(v142);
                while ( __strex(v143 - 1, v142) );
                __dmb(0xFu);
                if ( v143 <= 0 )
                    operator delete(v48);
            }
            if ( *((_DWORD *)v147 - 3) )
                *((_DWORD *)v144 + 20) = strdup(v147);
            v49 = Json::Value::operator[]((Json::Value *)&v165, "backtracker");
            Json::Value::asString((Json::Value *)&v162, (int)v49, v50);
            sub_C1700(&v147, &v162);
            v51 = (void *)(*(_DWORD *)&v162 - 12);
            if ( (int *)(*(_DWORD *)&v162 - 12) != &dword_2FEF3C )
            {
                v140 = (unsigned int *)(*(_DWORD *)&v162 - 4);
                __dmb(0xFu);
                do
                    v141 = __ldrex(v140);
                while ( __strex(v141 - 1, v140) );
                __dmb(0xFu);
                if ( v141 <= 0 )
                    operator delete(v51);
            }
            if ( *((_DWORD *)v147 - 3) )
                *((_DWORD *)v144 + 23) = strdup(v147);
            v52 = Json::Value::operator[]((Json::Value *)&v165, "protect_w");
            Json::Value::asString((Json::Value *)&v163, (int)v52, v53);
            sub_C1700(&v147, &v163);
            v54 = (void *)(*(_DWORD *)&v163 - 12);
            if ( (int *)(*(_DWORD *)&v163 - 12) != &dword_2FEF3C )
            {
                v138 = (unsigned int *)(*(_DWORD *)&v163 - 4);
                __dmb(0xFu);
                do
                    v139 = __ldrex(v138);
                while ( __strex(v139 - 1, v138) );
                __dmb(0xFu);
                if ( v139 <= 0 )
                    operator delete(v54);
            }
            if ( *((_DWORD *)v147 - 3) )
                dword_F3008 = atoi(v147);
            v55 = Json::Value::operator[]((Json::Value *)&v165, "status_server");
            Json::Value::asString((Json::Value *)&v164, (int)v55, v56);
            sub_C1700(&v147, &v164);
            v57 = (void *)(*(_DWORD *)&v164 - 12);
            if ( (int *)(*(_DWORD *)&v164 - 12) != &dword_2FEF3C )
            {
                v132 = (unsigned int *)(*(_DWORD *)&v164 - 4);
                __dmb(0xFu);
                do
                    v133 = __ldrex(v132);
                while ( __strex(v133 - 1, v132) );
                __dmb(0xFu);
                if ( v133 <= 0 )
                    operator delete(v57);
            }
            if ( *((_DWORD *)v147 - 3) )
                resetReportUrl(v147);
            v58 = Json::Value::operator[]((Json::Value *)&v165, "cont_blk_sec");
            Json::Value::asString((Json::Value *)&v166, (int)v58, v59);
            sub_C1700(&v147, &v166);
            v60 = (void *)(v166 - 12);
            if ( (int *)(v166 - 12) != &dword_2FEF3C )
            {
                v104 = (unsigned int *)(v166 - 4);
                __dmb(0xFu);
                do
                    v105 = __ldrex(v104);
                while ( __strex(v105 - 1, v104) );
                __dmb(0xFu);
                if ( v105 <= 0 )
                    operator delete(v60);
            }
            if ( *((_DWORD *)v147 - 3) )
                unk_F3030 = strtod(v147, 0);
            v61 = Json::Value::operator[]((Json::Value *)&v165, "src_invalid_sec");
            Json::Value::asString((Json::Value *)&v170, (int)v61, v62);
            sub_C1700(&v147, &v170);
            v63 = (void *)(v170 - 12);
            if ( (int *)(v170 - 12) != &dword_2FEF3C )
            {
                v112 = (unsigned int *)(v170 - 4);
                __dmb(0xFu);
                do
                    v113 = __ldrex(v112);
                while ( __strex(v113 - 1, v112) );
                __dmb(0xFu);
                if ( v113 <= 0 )
                    operator delete(v63);
            }
            v64 = v147;
            v65 = *((_DWORD *)v147 - 3);
            if ( v65 )
            {
                v66 = strtod(v147, 0);
                v65 = 0;
                v64 = v147;
                unk_F3038 = *(_QWORD *)&v66;
            }
        }
        else
        {
            add_confErr();
            v65 = -1;
            v64 = v147;
        }
    }
    v67 = v64 - 12;
    if ( v64 - 12 != (char *)&dword_2FEF3C )
    {
        v114 = (unsigned int *)(v64 - 4);
        __dmb(0xFu);
        do
            v115 = __ldrex(v114);
        while ( __strex(v115 - 1, v114) );
        __dmb(0xFu);
        if ( v115 <= 0 )
            operator delete(v67);
    }
    Json::Value::~Value((Json::Value *)&v165);
    v68 = v177;
    result = (void *)(v177 - 12);
    if ( (int *)(v177 - 12) != &dword_2FEF3C )
        goto LABEL_100;
    while ( 1 )
    {
        v70 = *((_DWORD *)v4 + 20);
        v71 = (void *)(v70 - 12);
        if ( (void **)(v70 - 12) != v5 )
        {
            v102 = (unsigned int *)(v70 - 4);
            __dmb(0xFu);
            do
                v103 = __ldrex(v102);
            while ( __strex(v103 - 1, v102) );
            __dmb(0xFu);
            if ( v103 <= 0 )
                operator delete(v71);
        }
        v72 = *((_DWORD *)v4 + 19);
        v5 = (void **)v175;
        v73 = *((_DWORD *)v4 + 12);
        v168 = *((_DWORD *)v4 + 14);
        v173 = v72;
        v74 = *((_DWORD *)v4 + 13);
        v166 = v73;
        v75 = *((_DWORD *)v4 + 17);
        v76 = *((_DWORD *)v4 + 16);
        v169 = v176;
        v77 = *((_DWORD *)v4 + 18);
        v167 = v74;
        v170 = v76;
        v171 = v75;
        v172 = v77;
        sub_3126C(&v166, &v170);
        std::_Deque_base<Json::Reader::ErrorInfo,std::allocator<Json::Reader::ErrorInfo>>::~_Deque_base((void **)v175);
        v78 = (char *)v174[0];
        if ( v174[0] )
        {
            v5 = (void **)*((_DWORD *)v4 + 5);
            v4 = (char *)(*((_DWORD *)v4 + 9) + 4);
            if ( v5 < (void **)v4 )
            {
                do
                {
                    v79 = *v5;
                    ++v5;
                    operator delete(v79);
                }
                while ( v4 > (char *)v5 );
                v78 = (char *)v174[0];
            }
            operator delete(v78);
        }
        result = (void *)v65;
        v68 = _stack_chk_guard;
        if ( v181 == _stack_chk_guard )
            break;
        LABEL_100:
        v100 = (unsigned int *)(v68 - 4);
        __dmb(0xFu);
        do
            v101 = __ldrex(v100);
        while ( __strex(v101 - 1, v100) );
        __dmb(0xFu);
        if ( v101 <= 0 )
            operator delete(result);
    }
    return result;
}
// F3008: using guessed type int dword_F3008;
// F3018: using guessed type int *off_F3018[2];
// F301C: using guessed type int dword_F301C;
// F3020: using guessed type int dword_F3020;
// F30EC: using guessed type int CDN_RATION;
// F3D60: using guessed type int dword_F3D60;
// 2FEF3C: using guessed type int dword_2FEF3C;

//----- (00033764) --------------------------------------------------------
void *__fastcall P2PManager::netWorkPrepareRoutine(P2PManager *this)
{
    P2PManager *v1; // r5
    void *result; // r0
    int v3; // r4
    char *v4; // r3
    int v5; // r11
    signed int v6; // r7
    _WORD *v7; // r8
    int v8; // r8
    int v9; // r3
    struct in_addr *v10; // r3
    char *v11; // r0
    int v12; // r3
    char *v13; // r1
    int v14; // r2
    int v15; // r3
    char *v16; // r1
    int v17; // r2
    void *v18; // r0
    void *v19; // r0
    void *v20; // r0
    void *v21; // r0
    void *v22; // r0
    void *v23; // r0
    const char *v24; // r0
    char *v25; // r0
    signed int v26; // [sp+18h] [bp-60h]
    time_t timer; // [sp+28h] [bp-50h]
    int v28; // [sp+2Ch] [bp-4Ch]
    int v29; // [sp+30h] [bp-48h]
    int v30; // [sp+34h] [bp-44h]
    int v31; // [sp+38h] [bp-40h]
    int v32; // [sp+3Ch] [bp-3Ch]
    int v33; // [sp+40h] [bp-38h]
    int v34; // [sp+44h] [bp-34h]
    __int16 v35; // [sp+48h] [bp-30h]
    char v36; // [sp+50h] [bp-28h]

    v1 = this;
    v28 = 0;
    v29 = 0;
    v30 = 0;
    v31 = 0;
    v32 = 0;
    v33 = 0;
    v34 = 0;
    v35 = 0;
    if ( currentVideoDefinitionInfo[0] == 2 )
        P2PManager::initInfoId(
        this,
                (const char *)(*((_DWORD *)this + 378) + 8),
    VideoDefinitionString[currentVideoDefinitionInfo[dword_F4164 + 8]],
            10016);
    else
    P2PManager::initInfoId(this, (const char *)(*((_DWORD *)this + 378) + 8), "default", 10016);
    result = P2PManager::parseConf(v1, "http://liveconf.kukuplay.com:6060/FrontEndConfServer/Conf", *((char **)v1 + 281));
    if ( result != (void *)-1 )
    {
        v3 = 0;
        v4 = (char *)*((_DWORD *)v1 + 19);
        v5 = 0;
        v6 = 0;
        v26 = 0;
        while ( 1 )
        {
            while ( 1 )
            {
                v7 = (_WORD *)*((_DWORD *)v1 + 375);
                *v7 = 2;
                v7[1] = __rev16(atoi(v4));
                v8 = *((_DWORD *)v1 + 375);
                result = (void *)inet_addr(*((const char **)v1 + 18));
                v9 = *((_DWORD *)v1 + 14);
                *(_DWORD *)(v8 + 4) = result;
                if ( v9 )
                    return result;
                add_stun();
                StunClient::start(
                        *((StunClient **)v1 + 294),
                        *((const char **)v1 + 18),
                        *((sockaddr_in **)v1 + 376),
                        *((_DWORD *)v1 + 374));
                v10 = (struct in_addr *)*((_DWORD *)v1 + 376);
                if ( !v10 )
                    break;
                v11 = inet_ntoa(v10[1]);
                result = (void *)strcmp(v11, "0.0.0.0");
                if ( !result && !*((_DWORD *)v1 + 14) )
                    break;
                if ( *((_DWORD *)v1 + 14) )
                    return result;
                add_stunConn();
                if ( wifiState )
                {
                    if ( wifiState == 1 )
                    {
                        add_3g();
                    }
                    else if ( wifiState == 2 )
                    {
                        add_uncertain();
                    }
                }
                else
                {
                    add_wifi();
                }
                sprintf((char *)&v28, "%s%s", *((_DWORD *)v1 + 18), *((_DWORD *)v1 + 19));
                v12 = v5;
                while ( 1 )
                {
                    v14 = *((unsigned __int8 *)&v28 + v12);
                    v5 = v12;
                    if ( !*((_BYTE *)&v28 + v12) )
                        break;
                    ++v12;
                    if ( v14 != 46 )
                    {
                        v13 = &v36 + v3++;
                        *(v13 - 36) = v14;
                    }
                }
                *(&v36 + v3 - 36) = v14;
                time(&timer);
                localtime(&timer);
                v15 = *((_DWORD *)v1 + 376);
                v16 = (char *)*((_DWORD *)v1 + 20);
                v17 = *((_DWORD *)v1 + 371);
                *(_WORD *)(v17 + 2) = *(_WORD *)(v15 + 2);
                if ( !v16 || wifiState & 0xFFFFFFFD )
                    goto LABEL_22;
                result = (void *)TrackerClient::start(
                        *((_DWORD *)v1 + 282),
                        v16,
                        (const char *)&v28,
                        (signed int *)v15,
                        v17,
                        *((const char **)v1 + 281),
                        (void (__fastcall *)(_DWORD, signed int *))notifyTracker);
                if ( !result || *((_DWORD *)v1 + 14) )
                {
                    if ( *((_DWORD *)v1 + 14) )
                        return result;
                    TrackerClient::heartbeat(*((TrackerClient **)v1 + 282));
                    LABEL_22:
                    v18 = (void *)*((_DWORD *)v1 + 18);
                    if ( v18 )
                    {
                        free(v18);
                        *((_DWORD *)v1 + 18) = 0;
                    }
                    v19 = (void *)*((_DWORD *)v1 + 19);
                    if ( v19 )
                    {
                        free(v19);
                        *((_DWORD *)v1 + 19) = 0;
                    }
                    v20 = (void *)*((_DWORD *)v1 + 20);
                    if ( v20 )
                    {
                        free(v20);
                        *((_DWORD *)v1 + 20) = 0;
                    }
                    v21 = (void *)*((_DWORD *)v1 + 23);
                    if ( v21 )
                    {
                        free(v21);
                        *((_DWORD *)v1 + 23) = 0;
                    }
                    add_rock();
                    for ( result = (void *)P2PClient::startToRock(
                            *((P2PClient **)v1 + 283),
                            *((sockaddr_in **)v1 + 376),
                            *((sockaddr_in **)v1 + 375),
                            *((_DWORD *)v1 + 374)); !*((_BYTE *)v1 + 1492); result = (void *)usleep(0x2710u) )
                    {
                        if ( *((_DWORD *)v1 + 14) )
                            break;
                    }
                    if ( !*((_DWORD *)v1 + 14) )
                        *((_BYTE *)v1 + 1493) = 1;
                    return result;
                }
                if ( ++v26 <= 100000 )
                {
                    if ( v26 == 3 && (v24 = (const char *)*((_DWORD *)v1 + 23)) != 0 )
                    {
                        if ( *((_DWORD *)v1 + 20) )
                        {
                            free(*((void **)v1 + 20));
                            v24 = (const char *)*((_DWORD *)v1 + 23);
                        }
                        v25 = strdup(v24);
                        v4 = (char *)*((_DWORD *)v1 + 19);
                        *((_DWORD *)v1 + 20) = v25;
                    }
                    else
                    {
                        LABEL_44:
                        v4 = (char *)*((_DWORD *)v1 + 19);
                    }
                }
                else
                {
                    v4 = (char *)*((_DWORD *)v1 + 19);
                    v26 = 4;
                }
            }
            if ( ++v6 <= 100000 )
            {
                if ( v6 != 3 || !*((_DWORD *)v1 + 21) || !*((_DWORD *)v1 + 22) )
                    goto LABEL_44;
                v22 = (void *)*((_DWORD *)v1 + 18);
                if ( v22 )
                    free(v22);
                v23 = (void *)*((_DWORD *)v1 + 19);
                if ( v23 )
                    free(v23);
                *((_DWORD *)v1 + 18) = strdup(*((const char **)v1 + 21));
                v4 = strdup(*((const char **)v1 + 22));
                *((_DWORD *)v1 + 19) = v4;
            }
            else
            {
                v4 = (char *)*((_DWORD *)v1 + 19);
                v6 = 4;
            }
        }
    }
    return result;
}
// F3944: using guessed type int wifiState;
// F4160: using guessed type int currentVideoDefinitionInfo[];
// F4164: using guessed type int dword_F4164;

//----- (00033BFC) --------------------------------------------------------
int __fastcall netWorkPrepareProcess(void *a1)
{
    P2PManager::netWorkPrepareRoutine((P2PManager *)a1);
    return 0;
}

//----- (00033C0C) --------------------------------------------------------
void *__fastcall std::deque<FILEINFO *,std::allocator<FILEINFO *>>::_M_push_back_aux(void **a1, _DWORD *a2)
{
void **v2; // r4
int v3; // r3
_DWORD *v4; // r6
char *v5; // r0
unsigned int v6; // r2
void **v7; // t0
int v8; // r7
void *result; // r0
_DWORD *v10; // r3
_DWORD *v11; // r3
int v12; // r3
char *v13; // r1
int v14; // r7
int v15; // r5
unsigned int v16; // r8
char *v17; // r0
_BYTE *v18; // r1
int v19; // r2
char *v20; // r9
char *v21; // r5
int v22; // r2
int v23; // r3
int v24; // r3
int v25; // r3
int v26; // r3

v2 = a1;
v3 = (int)a1[9];
v4 = a2;
v7 = a1;
v5 = (char *)*a1;
v6 = (unsigned int)v7[1];
if ( v6 - ((v3 - (signed int)v5) >> 2) <= 1 )
{
v13 = (char *)v2[5];
v14 = ((v3 - (signed int)v13) >> 2) + 1;
v15 = ((v3 - (signed int)v13) >> 2) + 2;
if ( v6 > 2 * v15 )
{
v25 = v3 + 4 - (_DWORD)v13;
v21 = &v5[4 * ((v6 - v15) >> 1)];
if ( v13 <= v21 )
{
v26 = v25 >> 2;
if ( v26 )
memmove(&v21[4 * v14 + -4 * v26], v13, 4 * v26);
}
else if ( v25 >> 2 )
{
memmove(v21, v13, 4 * (v25 >> 2));
}
}
else
{
if ( v6 )
{
v16 = 2 * v6 + 2;
if ( v16 > 0x3FFFFFFF )
sub_BFA08();
}
else
{
v16 = 3;
}
v17 = (char *)operator new(4 * v16);
v18 = v2[5];
v19 = ((_BYTE *)v2[9] + 4 - v18) >> 2;
v20 = v17;
v21 = &v17[4 * ((v16 - v15) >> 1)];
if ( v19 )
memmove(v21, v18, 4 * v19);
operator delete(*v2);
*v2 = v20;
v2[1] = (void *)v16;
}
v2[5] = v21;
v22 = v14 + 0x3FFFFFFF;
v23 = *(_DWORD *)v21;
v8 = (int)&v21[4 * (v14 + 0x3FFFFFFF)];
v2[9] = (void *)v8;
v2[4] = (void *)(v23 + 512);
v2[3] = (void *)v23;
v24 = *(_DWORD *)&v21[4 * v22];
v2[8] = (void *)(v24 + 512);
v2[7] = (void *)v24;
}
else
{
v8 = v3;
}
result = operator new(0x200u);
*(_DWORD *)(v8 + 4) = result;
v10 = v2[6];
if ( v10 )
*v10 = *v4;
v11 = v2[9];
v2[9] = v11 + 1;
v12 = v11[1];
v2[8] = (void *)(v12 + 512);
v2[7] = (void *)v12;
v2[6] = (void *)v12;
return result;
}

//----- (00033D84) --------------------------------------------------------
int __fastcall P2PManager::assignMission(int result)
{
    int v1; // r11
    int v2; // r6
    int *v3; // r1
    int v4; // r0
    int v5; // r2
    unsigned int v6; // r0
    int v7; // r0
    int v8; // r4
    int v9; // r1
    char *v10; // r4
    signed int v11; // r7
    int v12; // r4
    pthread_mutex_t *v13; // r6
    _BYTE *v14; // r0
    int v15; // r2
    _DWORD *v16; // r3
    int v17; // r3
    pthread_mutex_t *mutex; // [sp+4h] [bp-3Ch]
    _BYTE *v19; // [sp+14h] [bp-2Ch]

    v1 = result;
    if ( *(_DWORD *)(result + 40) != *(_DWORD *)(result + 24) )
    {
        v2 = result + 1152;
        mutex = (pthread_mutex_t *)(result + 1164);
        pthread_mutex_lock((pthread_mutex_t *)(result + 1164));
        v3 = *(int **)(v1 + 24);
        v4 = (int)v3 - *(_DWORD *)(v1 + 28);
        v5 = v4 >> 2;
        if ( (unsigned int)(v4 >> 2) > 0x7F )
        {
            if ( v5 <= 0 )
                v6 = ~((unsigned int)~v5 >> 7);
            else
                v6 = v4 >> 9;
            v3 = (int *)(*(_DWORD *)(*(_DWORD *)(v1 + 36) + 4 * v6) + 4 * (v5 - (v6 << 7)));
        }
        v7 = *v3;
        v8 = *(_DWORD *)(*(_DWORD *)(v1 + 1508) + 48);
        v9 = *(unsigned __int8 *)(v1 + 1493);
        v19 = (_BYTE *)v7;
        if ( v9 )
        {
            v10 = (char *)delay_time + v8;
            if ( (signed int)v10 < 10 )
                v10 = byte_9 + 1;
        }
        else
        {
            v10 = (char *)dword_F3008;
        }
        v11 = (signed int)&v10[(unsigned int)FifoDataManager::getWriteDataTime((FifoDataManager *)*(_DWORD *)(v1 + 1516))
                               - *(_DWORD *)(v1 + 1488)];
        if ( v11 > 0 )
        {
            v12 = 0;
            v13 = (pthread_mutex_t *)(v2 + 4);
            do
            {
                if ( (unsigned int)(((*(_DWORD *)(v1 + 40) - *(_DWORD *)(v1 + 44)) >> 2)
                                    + ((((*(_DWORD *)(v1 + 52) - *(_DWORD *)(v1 + 36)) >> 2) - 1) << 7)
                                    + ((*(_DWORD *)(v1 + 32) - *(_DWORD *)(v1 + 24)) >> 2)) > 0x9F )
                    P2PManager::moveOnStep((P2PManager *)v1);
                v14 = operator new(0xCu);
                v14[4] = 0;
                v15 = *(_DWORD *)(v1 + 1488);
                v19 = v14;
                *((_DWORD *)v14 + 2) = 0;
                *(_DWORD *)v14 = v15;
                v14[4] = 1;
                pthread_mutex_lock(v13);
                v16 = *(_DWORD **)(v1 + 40);
                if ( v16 == (_DWORD *)(*(_DWORD *)(v1 + 48) - 4) )
                {
                    std::deque<FILEINFO *,std::allocator<FILEINFO *>>::_M_push_back_aux((void **)(v1 + 16), &v19);
                }
                else
                {
                    if ( v16 )
                    {
                        *v16 = v19;
                        v16 = *(_DWORD **)(v1 + 40);
                    }
                    *(_DWORD *)(v1 + 40) = v16 + 1;
                }
                LocalMemory::initPendingData(*(LocalMemory **)(v1 + 1136), *(_DWORD *)(v1 + 1488));
                pthread_mutex_unlock(v13);
                v17 = lrand48() % 100;
                if ( (v17 < 0 || v17 >= CDN_RATION) && *(_BYTE *)(v1 + 1493) )
                    P2PClient::addMission(*(P2PClient **)(v1 + 1132), *(_DWORD *)(v1 + 1488));
                else
                    AcquireChannelPlayInfo::downloadPieceDataWithPieceid(
                            *(AcquireChannelPlayInfo **)(v1 + 1508),
                            *(_DWORD *)(v1 + 1488));
                ++v12;
                ++*(_DWORD *)(v1 + 1488);
            }
            while ( v11 != v12 );
        }
        result = pthread_mutex_unlock(mutex);
    }
    return result;
}
// F3008: using guessed type int dword_F3008;
// F30DC: using guessed type int *delay_time;
// F30EC: using guessed type int CDN_RATION;

//----- (00033FE0) --------------------------------------------------------
int __fastcall P2PManager::generateUrl(int result)
{
    int v1; // r4

    v1 = result;
    if ( !*(_BYTE *)(result + 1492) )
    {
        while ( !*(_DWORD *)(v1 + 56) )
        {
            result = usleep(0x186A0u);
            if ( *(_BYTE *)(v1 + 1492) )
            {
                if ( *(_DWORD *)(v1 + 56) )
                    return result;
                goto LABEL_7;
            }
        }
    }
    if ( !*(_DWORD *)(v1 + 56) )
    {
        LABEL_7:
        P2PManager::assignMission(v1);
        result = (*(int (__cdecl **)(_DWORD, _DWORD))(**(_DWORD **)(v1 + 64) + 8))(
                *(_DWORD *)(v1 + 64),
                        *(_DWORD *)(**(_DWORD **)(v1 + 64) + 8));
    }
    return result;
}

//----- (00034080) --------------------------------------------------------
int __fastcall P2PManager::Routine(P2PManager *this)
{
    pthread_mutex_t *v1; // r5
    P2PManager *v2; // r4
    StunClient *v3; // r7
    _DWORD *v4; // r7
    _DWORD *v5; // r7
    void *v6; // r7

    v1 = (pthread_mutex_t *)((char *)this + 1156);
    v2 = this;
    *((_DWORD *)this + 292) = 0;
    *((_DWORD *)this + 293) = 0;
    while ( pthread_mutex_lock(v1) == 4 )
        ;
    P2PManager::initLocalSocket(v2);
    v3 = (StunClient *)operator new(0x178u);
    StunClient::StunClient(v3);
    *((_DWORD *)v2 + 294) = v3;
    v4 = operator new(0x60u);
    TrackerClient::TrackerClient(v4, *((_DWORD *)v2 + 16));
    *((_DWORD *)v2 + 282) = v4;
    v5 = operator new(0x6Cu);
    LocalMemory::LocalMemory(
            v5,
            *((_DWORD *)v2 + 1),
    *((_DWORD *)v2 + 2),
    (int)v2 + 16,
            (int)notifyRefreshBitmap,
            (int)notifyToHttpDownload,
            *((_DWORD *)v2 + 3));
    *((_DWORD *)v2 + 284) = v5;
    gLocalMemory = (int)v5;
    v6 = operator new(0x2B28u);
    P2PClient::P2PClient(
            (int)v6,
    *((_DWORD *)v2 + 16),
    *(_DWORD *)v2,
            *((_DWORD *)v2 + 1),
    *((_DWORD *)v2 + 2),
    (int)notifyOneFile,
            (int)notifyToHttpDownload,
            *((_DWORD *)v2 + 284),
    *((_DWORD *)v2 + 285),
    (int)v2 + 16,
            (int)notifyRequestPeer,
            *((_DWORD *)v2 + 374));
    *((_DWORD *)v2 + 283) = v6;
    gP2PClient = (int)v6;
    pthread_create((pthread_t *)v2 + 292, 0, (void *(*)(void *))generateProcess, (void *)v2);
    pthread_create((pthread_t *)v2 + 293, 0, (void *(*)(void *))netWorkPrepareProcess, (void *)v2);
    pthread_mutex_unlock(v1);
    P2PManager::generateUrl((int)v2);
    P2PManager::checkCDNMargin((int)v2);
    (*(void (**)(void))(**((_DWORD **)v2 + 16) + 28))();
    return 0;
}
// F3D6C: using guessed type int gLocalMemory;
// F3D70: using guessed type int gP2PClient;

//----- (0003424C) --------------------------------------------------------
void *__fastcall P2PManager::initProtectWindow(P2PManager *this)
{
    P2PManager *v1; // r10
    int v2; // r0
    int v3; // r7
    int v4; // r4
    _BYTE *v5; // r0
    _DWORD *v6; // r3
    int v7; // r2
    unsigned int v8; // r1
    void *result; // r0
    _BYTE *v10; // [sp+4h] [bp-24h]

    v1 = this;
    v2 = AcquireChannelPlayInfo::getStartPieceId(*((AcquireChannelPlayInfo **)this + 377));
    v3 = v2 + 6;
    v4 = v2;
    do
    {
        v5 = operator new(0xCu);
        v5[4] = 1;
        v6 = (_DWORD *)*((_DWORD *)v1 + 10);
        v7 = *((_DWORD *)v1 + 12) - 4;
        v10 = v5;
        *((_DWORD *)v5 + 2) = 0;
        *(_DWORD *)v5 = v4;
        if ( v6 == (_DWORD *)v7 )
        {
            std::deque<FILEINFO *,std::allocator<FILEINFO *>>::_M_push_back_aux((void **)v1 + 4, &v10);
        }
        else
        {
            if ( v6 )
            {
                *v6 = v5;
                v6 = (_DWORD *)*((_DWORD *)v1 + 10);
            }
            *((_DWORD *)v1 + 10) = v6 + 1;
        }
        v8 = v4++;
        result = LocalMemory::initPendingData(*((LocalMemory **)v1 + 284), v8);
    }
    while ( v4 != v3 );
    *((_DWORD *)v1 + 372) = v4;
    return result;
}

//----- (000342EC) --------------------------------------------------------
int __fastcall generateProcess(P2PManager *this)
{
    P2PManager *v1; // r4
    int v2; // r3
    void (*v3)(void); // r3
    void *v4; // r5
    int v5; // r6
    int v6; // r0

    v1 = this;
    if ( !*((_DWORD *)this + 14) )
    {
        while ( 1 )
        {
            v2 = *(_DWORD *)(*((_DWORD *)v1 + 377) + 20);
            if ( v2 == 2 )
                break;
            if ( v2 == 3 )
                return 0;
            usleep(0x2710u);
            if ( *((_DWORD *)v1 + 14) )
            goto LABEL_8;
        }
        v3 = (void (*)(void))*((_DWORD *)v1 + 380);
        if ( v3 )
            v3();
    }
    LABEL_8:
    if ( !*((_DWORD *)v1 + 14) && *(_DWORD *)(*((_DWORD *)v1 + 377) + 20) != 3 )
    {
        P2PManager::initProtectWindow(v1);
        P2PManager::setFlvHeadFinished((int)v1);
        FifoDataManager::setHeaderBytes(*((FifoDataManager **)v1 + 379), *((char **)v1 + 377));
        v4 = (void *)*((_DWORD *)v1 + 379);
        v5 = P2PManager::getFifoFd(v1);
        v6 = AcquireChannelPlayInfo::getStartPieceId(*((AcquireChannelPlayInfo **)v1 + 377));
        FifoDataManager::start(v4, v5, (int)cbFifoCopy, v6, 1);
    }
    return 0;
}

//----- (000343C4) --------------------------------------------------------
void **__fastcall std::_Deque_base<long,std::allocator<long>>::~_Deque_base(void **a1)
{
    void **v1; // r6
    void *v2; // r0
    void **v3; // r4
    unsigned int v4; // r5
    void *v5; // t1

    v1 = a1;
    v2 = *a1;
    if ( v2 )
    {
        v3 = (void **)v1[5];
        v4 = (unsigned int)v1[9] + 4;
        if ( (unsigned int)v3 < v4 )
        {
            do
            {
                v5 = *v3;
                ++v3;
                operator delete(v5);
            }
            while ( v4 > (unsigned int)v3 );
            v2 = *v1;
        }
        operator delete(v2);
    }
    return v1;
}

//----- (0003440C) --------------------------------------------------------
void __fastcall P2PManager::destroyAllResManager(P2PManager *this)
{
    P2PManager *v1; // r5
    int v2; // r6
    OnePacket *v3; // r3
    OnePacket *v4; // r4
    void *v5; // r0
    int v6; // r6
    OneFile *v7; // r3
    OneFile *v8; // r4
    void *v9; // r0
    int v10; // r6
    OneRequest *v11; // r0
    OneRequest *v12; // r4
    void *v13; // r0
    int v14; // r6
    OneData *v15; // r0
    OneData *v16; // r4
    void *v17; // r0

    v1 = this;
    v2 = *((_DWORD *)this + 2);
    if ( v2 )
    {
        v3 = *(OnePacket **)(v2 + 4);
        if ( v3 )
        {
            v4 = (OnePacket *)((char *)v3 + 1256 * *((_DWORD *)v3 - 1));
            while ( v4 != v3 )
            {
                v4 = (OnePacket *)((char *)v4 - 1256);
                OnePacket::~OnePacket(v4);
                v3 = *(OnePacket **)(v2 + 4);
            }
            operator delete[]((char *)v4 - 8);
        }
        v5 = *(void **)(v2 + 8);
        if ( v5 )
            operator delete[](v5);
        pthread_mutex_destroy((pthread_mutex_t *)(v2 + 52));
        std::_Deque_base<long,std::allocator<long>>::~_Deque_base((void **)(v2 + 12));
        operator delete((void *)v2);
        *((_DWORD *)v1 + 2) = 0;
    }
    v6 = *((_DWORD *)v1 + 1);
    if ( v6 )
    {
        v7 = *(OneFile **)(v6 + 4);
        if ( v7 )
        {
            v8 = (OneFile *)((char *)v7 + 28 * *((_DWORD *)v7 - 1));
            while ( v8 != v7 )
            {
                v8 = (OneFile *)((char *)v8 - 28);
                OneFile::~OneFile(v8);
                v7 = *(OneFile **)(v6 + 4);
            }
            operator delete[]((char *)v8 - 8);
        }
        v9 = *(void **)(v6 + 8);
        if ( v9 )
            operator delete[](v9);
        pthread_mutex_destroy((pthread_mutex_t *)(v6 + 52));
        std::_Deque_base<long,std::allocator<long>>::~_Deque_base((void **)(v6 + 12));
        operator delete((void *)v6);
        *((_DWORD *)v1 + 1) = 0;
    }
    v10 = *(_DWORD *)v1;
    if ( *(_DWORD *)v1 )
    {
        v11 = *(OneRequest **)(v10 + 4);
        if ( v11 )
        {
            v12 = (OneRequest *)((char *)v11 + 6856 * *((_DWORD *)v11 - 1));
            while ( v11 != v12 )
            {
                v12 = (OneRequest *)((char *)v12 - 6856);
                OneRequest::~OneRequest(v12);
                v11 = *(OneRequest **)(v10 + 4);
            }
            operator delete[]((char *)v11 - 8);
        }
        v13 = *(void **)(v10 + 8);
        if ( v13 )
            operator delete[](v13);
        pthread_mutex_destroy((pthread_mutex_t *)(v10 + 52));
        std::_Deque_base<long,std::allocator<long>>::~_Deque_base((void **)(v10 + 12));
        operator delete((void *)v10);
        *(_DWORD *)v1 = 0;
    }
    v14 = *((_DWORD *)v1 + 3);
    if ( v14 )
    {
        v15 = *(OneData **)(v14 + 4);
        if ( v15 )
        {
            v16 = (OneData *)((char *)v15 + 20 * *((_DWORD *)v15 - 1));
            while ( v15 != v16 )
            {
                v16 = (OneData *)((char *)v16 - 20);
                OneData::~OneData(v16);
                v15 = *(OneData **)(v14 + 4);
            }
            operator delete[]((char *)v15 - 8);
        }
        v17 = *(void **)(v14 + 8);
        if ( v17 )
            operator delete[](v17);
        pthread_mutex_destroy((pthread_mutex_t *)(v14 + 52));
        std::_Deque_base<long,std::allocator<long>>::~_Deque_base((void **)(v14 + 12));
        operator delete((void *)v14);
        *((_DWORD *)v1 + 3) = 0;
    }
}

//----- (00034648) --------------------------------------------------------
P2PManager *__fastcall P2PManager::~P2PManager(P2PManager *this)
{
    P2PManager *v1; // r4
    int v2; // r0
    int v3; // r0
    int v4; // r3
    pthread_t v5; // r0
    pthread_t v6; // r0
    pthread_t v7; // r0
    void *v8; // r6
    void *v9; // r0
    void *v10; // r0
    void *v11; // r0
    void *v12; // r6
    void *v13; // r6
    void *v14; // r0
    TrackerClient *v15; // r0
    void *v16; // r6
    void *v17; // r6
    void *v18; // r6
    int v19; // r0
    void *v20; // r6
    void **i; // r3
    void *v22; // r5
    int v23; // r3
    int v24; // r3

    v1 = this;
    P2PManager::stopStunClient(this);
    v2 = *((_DWORD *)v1 + 377);
    if ( v2 )
        AcquireChannelPlayInfo::stopDownloadThread(v2);
    v3 = *((_DWORD *)v1 + 379);
    if ( v3 )
        FifoDataManager::stopWriteThread(v3);
    v4 = *((_DWORD *)v1 + 282);
    if ( v4 )
    {
        *(_DWORD *)(v4 + 40) = 0;
        *(_DWORD *)(v4 + 48) = 0;
    }
    if ( !*((_DWORD *)v1 + 14) )
    {
        v5 = *((_DWORD *)v1 + 288);
        *((_DWORD *)v1 + 14) = -1;
        *((_DWORD *)v1 + 15) = 0;
        if ( v5 )
        {
            pthread_join(v5, 0);
            v6 = *((_DWORD *)v1 + 292);
            *((_DWORD *)v1 + 288) = 0;
            if ( !v6 )
            {
                LABEL_10:
                v7 = *((_DWORD *)v1 + 293);
                if ( !v7 )
                    goto LABEL_11;
                goto LABEL_44;
            }
        }
        else
        {
            v6 = *((_DWORD *)v1 + 292);
            if ( !v6 )
                goto LABEL_10;
        }
        pthread_join(v6, 0);
        v7 = *((_DWORD *)v1 + 293);
        *((_DWORD *)v1 + 292) = 0;
        if ( v7 )
        {
            LABEL_44:
            pthread_join(v7, 0);
            *((_DWORD *)v1 + 293) = 0;
            goto LABEL_11;
        }
    }
    LABEL_11:
    v8 = (void *)*((_DWORD *)v1 + 294);
    if ( v8 )
    {
        StunClient::~StunClient(*((StunClient **)v1 + 294));
        operator delete(v8);
        *((_DWORD *)v1 + 294) = 0;
    }
    v9 = (void *)*((_DWORD *)v1 + 375);
    if ( v9 )
    {
        free(v9);
        *((_DWORD *)v1 + 375) = 0;
    }
    v10 = (void *)*((_DWORD *)v1 + 376);
    if ( v10 )
    {
        free(v10);
        *((_DWORD *)v1 + 376) = 0;
    }
    v11 = (void *)*((_DWORD *)v1 + 371);
    if ( v11 )
    {
        free(v11);
        *((_DWORD *)v1 + 371) = 0;
    }
    v12 = (void *)*((_DWORD *)v1 + 377);
    if ( v12 )
    {
        AcquireChannelPlayInfo::~AcquireChannelPlayInfo(*((AcquireChannelPlayInfo **)v1 + 377));
        operator delete(v12);
        *((_DWORD *)v1 + 377) = 0;
    }
    v13 = (void *)*((_DWORD *)v1 + 379);
    if ( v13 )
    {
        FifoDataManager::~FifoDataManager(*((FifoDataManager **)v1 + 379));
        operator delete(v13);
    }
    v14 = (void *)*((_DWORD *)v1 + 281);
    if ( v14 )
    {
        free(v14);
        *((_DWORD *)v1 + 281) = 0;
    }
    v15 = (TrackerClient *)*((_DWORD *)v1 + 282);
    if ( v15 )
    {
        TrackerClient::exit(v15);
        v16 = (void *)*((_DWORD *)v1 + 282);
        if ( v16 )
        {
            TrackerClient::~TrackerClient(*((TrackerClient **)v1 + 282));
            operator delete(v16);
        }
        *((_DWORD *)v1 + 282) = 0;
    }
    v17 = (void *)*((_DWORD *)v1 + 284);
    if ( v17 )
    {
        LocalMemory::~LocalMemory(*((LocalMemory **)v1 + 284));
        operator delete(v17);
        *((_DWORD *)v1 + 284) = 0;
        gLocalMemory = 0;
    }
    v18 = (void *)*((_DWORD *)v1 + 283);
    if ( v18 )
    {
        P2PClient::~P2PClient(*((P2PClient **)v1 + 283));
        operator delete(v18);
        *((_DWORD *)v1 + 283) = 0;
        gP2PClient = 0;
    }
    v19 = *((_DWORD *)v1 + 16);
    if ( v19 )
    {
        (*(void (**)(void))(*(_DWORD *)v19 + 4))();
        *((_DWORD *)v1 + 16) = 0;
    }
    v20 = (void *)*((_DWORD *)v1 + 17);
    if ( v20 )
    {
        CurlWrapper::~CurlWrapper(*((CurlWrapper **)v1 + 17));
        operator delete(v20);
        *((_DWORD *)v1 + 17) = 0;
    }
    P2PManager::destroyAllResManager(v1);
    free(*((void **)v1 + 285));
    for ( i = (void **)*((_DWORD *)v1 + 6); *((void ***)v1 + 10) != i; i = (void **)*((_DWORD *)v1 + 6) )
    {
        v22 = *i;
        if ( i == (void **)(*((_DWORD *)v1 + 8) - 4) )
        {
            operator delete(*((void **)v1 + 7));
            v23 = *((_DWORD *)v1 + 9);
            *((_DWORD *)v1 + 9) = v23 + 4;
            v24 = *(_DWORD *)(v23 + 4);
            *((_DWORD *)v1 + 8) = v24 + 512;
            *((_DWORD *)v1 + 7) = v24;
            *((_DWORD *)v1 + 6) = v24;
        }
        else
        {
            *((_DWORD *)v1 + 6) = i + 1;
        }
        operator delete(v22);
    }
    P2PManager::destroyLocalSocket(v1);
    pthread_mutex_destroy((pthread_mutex_t *)((char *)v1 + 1156));
    pthread_cond_destroy((pthread_cond_t *)((char *)v1 + 1160));
    pthread_mutex_destroy((pthread_mutex_t *)((char *)v1 + 1164));
    std::_Deque_base<FILEINFO *,std::allocator<FILEINFO *>>::~_Deque_base((void **)v1 + 4);
    return v1;
}
// F3D6C: using guessed type int gLocalMemory;
// F3D70: using guessed type int gP2PClient;

//----- (000349C4) --------------------------------------------------------
char *__fastcall std::_Deque_base<long,std::allocator<long>>::_M_initialize_map(_DWORD *a1, unsigned int a2)
{
_DWORD *v2; // r6
unsigned int v3; // r0
char v4; // r9
int v5; // r5
char *result; // r0
unsigned int v7; // r10
unsigned int v8; // r7
char *v9; // r8
unsigned int v10; // r5
char *v11; // r4
int v12; // r2
int v13; // r3

v2 = a1;
v3 = (a2 >> 7) + 3;
if ( v3 < 8 )
v3 = 8;
v2[1] = v3;
v4 = a2;
v5 = (a2 >> 7) + 1;
result = (char *)operator new(4 * v3);
v7 = (unsigned int)(v2[1] - v5) >> 1;
v8 = (unsigned int)&result[4 * v7];
v9 = result;
v10 = v8 + 4 * v5;
*v2 = result;
if ( v8 < v10 )
{
v11 = &result[4 * v7];
do
{
result = (char *)operator new(0x200u);
*(_DWORD *)v11 = result;
v11 += 4;
}
while ( v10 > (unsigned int)v11 );
}
v2[5] = v8;
v12 = *(_DWORD *)&v9[4 * v7];
v2[9] = v10 - 4;
v2[4] = v12 + 512;
v2[3] = v12;
v13 = *(_DWORD *)(v10 - 4);
v2[2] = v12;
v2[6] = v13 + 4 * (v4 & 0x7F);
v2[7] = v13;
v2[8] = v13 + 512;
return result;
}

//----- (00034ABC) --------------------------------------------------------
_DWORD *__fastcall std::deque<long,std::allocator<long>>::deque(_DWORD *a1, _DWORD *a2)
{
_DWORD *v2; // r4
_DWORD *v3; // r5
int v4; // lr
int v5; // r2
int v6; // r12
int v7; // r1
int v8; // r7
int *v9; // r3
int v10; // r0
_DWORD *v11; // r2
int v12; // r6
int v13; // r1
int v14; // r8
int v15; // t1
int v16; // r12

v2 = a2;
v3 = a1;
v4 = a2[4];
v5 = a2[6] - a2[7];
v6 = (a2[9] - a2[5]) >> 2;
v7 = a2[2];
*a1 = 0;
a1[1] = 0;
a1[2] = 0;
a1[3] = 0;
a1[4] = 0;
a1[5] = 0;
a1[6] = 0;
a1[7] = 0;
a1[8] = 0;
a1[9] = 0;
std::_Deque_base<long,std::allocator<long>>::_M_initialize_map(a1, (v5 >> 2) + ((v6 - 1) << 7) + ((v4 - v7) >> 2));
v8 = v2[5];
v9 = (int *)v2[2];
v10 = v2[4];
v11 = (_DWORD *)v3[2];
v12 = v3[4];
v13 = ((v2[6] - v2[7]) >> 2) + ((((v2[9] - v8) >> 2) - 1) << 7) + ((v10 - (signed int)v9) >> 2);
v14 = v3[5];
if ( v13 > 0 )
{
do
{
v15 = *v9;
++v9;
v16 = (int)(v11 + 1);
*v11 = v15;
++v11;
if ( v9 == (int *)v10 )
{
v9 = *(int **)(v8 + 4);
v8 += 4;
v10 = (int)(v9 + 128);
}
if ( v16 == v12 )
{
v11 = *(_DWORD **)(v14 + 4);
v14 += 4;
v12 = (int)(v11 + 128);
}
--v13;
}
while ( v13 );
}
return v3;
}

//----- (00034BBC) --------------------------------------------------------
P2PManager *__fastcall P2PManager::P2PManager(P2PManager *this, ChannelPlayInfoManager *a2, int a3, void (*a4)(void))
{
P2PManager *v4; // r7
ChannelPlayInfoManager *v5; // r6
int v6; // r9
int v7; // r3
_DWORD *v8; // r0
unsigned int v9; // r5
_DWORD *v10; // r4
int v11; // r8
int v12; // r12
int v13; // r2
pthread_mutex_t *v14; // r8
void *v15; // r0
void *v16; // r5
volatile int *v17; // r1
char *v18; // r0
void *v19; // r1
int v20; // r5
unsigned int v21; // r2
size_t v22; // r9
unsigned int v23; // r4
int v24; // r3
CurlWrapper *v25; // r0
void *v26; // r3
void *v27; // r0
void *v28; // r4
_DWORD *v29; // r0
_DWORD *v30; // r3
_DWORD *v31; // r0
_DWORD *v32; // r3
_DWORD *v33; // r0
_DWORD *v34; // r3
char *v35; // r4
_DWORD *v36; // r0
int v37; // r9
signed int v38; // r6
OneFile *v39; // r5
_BYTE *v40; // r0
int v41; // r5
_DWORD *v42; // r3
int v43; // r2
int v44; // r9
_DWORD *v45; // r3
int v46; // r3
int v47; // r3
char *v48; // r5
_DWORD *v49; // r0
int v50; // r9
signed int v51; // r6
OneRequest *v52; // r4
_BYTE *v53; // r0
int v54; // r4
_DWORD *v55; // r3
int v56; // r2
int v57; // r9
_DWORD *v58; // r3
int v59; // r3
int v60; // r3
char *v61; // r5
_DWORD *v62; // r0
int v63; // r9
OnePacket *v64; // r4
signed int v65; // r6
_BYTE *v66; // r0
int v67; // r4
_DWORD *v68; // r3
int v69; // r2
int v70; // r9
_DWORD *v71; // r3
int v72; // r3
int v73; // r3
char *v74; // r4
_DWORD *v75; // r0
int v76; // r10
signed int v77; // r5
int v78; // r6
_BYTE *v79; // r0
int v80; // r5
_DWORD *v81; // r3
int v82; // r2
int v83; // r9
_DWORD *v84; // r3
int v85; // r3
int v86; // r3
void *v88; // r0
int v89; // [sp+14h] [bp-904h]
int v90; // [sp+14h] [bp-904h]
int v91; // [sp+14h] [bp-904h]
void (*v92)(void); // [sp+2Ch] [bp-8ECh]
void *src; // [sp+30h] [bp-8E8h]
int v94; // [sp+34h] [bp-8E4h]
int v95; // [sp+38h] [bp-8E0h]
void *v96; // [sp+3Ch] [bp-8DCh]
int v97; // [sp+40h] [bp-8D8h]
unsigned int v98; // [sp+44h] [bp-8D4h]
int v99; // [sp+48h] [bp-8D0h]
int v100; // [sp+4Ch] [bp-8CCh]
int v101; // [sp+50h] [bp-8C8h]
int v102; // [sp+54h] [bp-8C4h]
int v103; // [sp+58h] [bp-8C0h]
int v104; // [sp+5Ch] [bp-8BCh]
int v105; // [sp+60h] [bp-8B8h]
int v106; // [sp+64h] [bp-8B4h]
int v107; // [sp+68h] [bp-8B0h]
int v108; // [sp+6Ch] [bp-8ACh]
int v109; // [sp+70h] [bp-8A8h]
int v110; // [sp+74h] [bp-8A4h]
int v111; // [sp+78h] [bp-8A0h]
int v112; // [sp+7Ch] [bp-89Ch]
int v113; // [sp+80h] [bp-898h]
int v114; // [sp+84h] [bp-894h]
int v115; // [sp+88h] [bp-890h]
int v116; // [sp+8Ch] [bp-88Ch]
int v117; // [sp+90h] [bp-888h]
int v118; // [sp+94h] [bp-884h]
int v119; // [sp+98h] [bp-880h]
int v120; // [sp+9Ch] [bp-87Ch]
int v121; // [sp+A0h] [bp-878h]
int v122; // [sp+A4h] [bp-874h]
int v123; // [sp+A8h] [bp-870h]
int v124; // [sp+ACh] [bp-86Ch]
int v125; // [sp+B0h] [bp-868h]
int v126; // [sp+B4h] [bp-864h]
int v127; // [sp+B8h] [bp-860h]
int v128; // [sp+BCh] [bp-85Ch]
int v129; // [sp+C0h] [bp-858h]
int v130; // [sp+C4h] [bp-854h]
int v131; // [sp+C8h] [bp-850h]
int v132; // [sp+CCh] [bp-84Ch]
int v133; // [sp+D0h] [bp-848h]
int v134; // [sp+D4h] [bp-844h]
int v135; // [sp+D8h] [bp-840h]
int v136; // [sp+DCh] [bp-83Ch]
int v137; // [sp+E0h] [bp-838h]
int v138; // [sp+E4h] [bp-834h]
char dest; // [sp+E8h] [bp-830h]
int v140; // [sp+8E8h] [bp-30h]
int v141; // [sp+8ECh] [bp-2Ch]

v4 = this;
v5 = a2;
v92 = a4;
v6 = a3;
*((_DWORD *)this + 5) = 8;
v7 = _stack_chk_guard;
*((_DWORD *)this + 4) = 0;
*((_DWORD *)this + 6) = 0;
*((_DWORD *)this + 7) = 0;
*((_DWORD *)this + 8) = 0;
*((_DWORD *)this + 9) = 0;
*((_DWORD *)this + 10) = 0;
*((_DWORD *)this + 11) = 0;
*((_DWORD *)this + 12) = 0;
*((_DWORD *)this + 13) = 0;
v141 = v7;
v8 = operator new(0x20u);
v9 = (unsigned int)(*((_DWORD *)v4 + 5) - 1) >> 1;
v10 = v8;
*((_DWORD *)v4 + 4) = v8;
v11 = (int)&v8[v9];
v8[v9] = operator new(0x200u);
*((_DWORD *)v4 + 9) = v11;
v12 = v10[v9];
*((_DWORD *)v4 + 13) = v11;
*((_DWORD *)v4 + 7) = v12;
*((_DWORD *)v4 + 8) = v12 + 512;
v13 = v10[v9];
*((_DWORD *)v4 + 6) = v12;
*((_DWORD *)v4 + 14) = 0;
*((_DWORD *)v4 + 11) = v13;
*((_DWORD *)v4 + 10) = v13;
*((_DWORD *)v4 + 12) = v13 + 512;
*((_DWORD *)v4 + 16) = 0;
*((_DWORD *)v4 + 18) = 0;
*((_DWORD *)v4 + 20) = 0;
*((_DWORD *)v4 + 21) = 0;
*((_DWORD *)v4 + 23) = 0;
*((_DWORD *)v4 + 282) = 0;
*((_DWORD *)v4 + 286) = 0;
*((_DWORD *)v4 + 287) = 0;
*((_DWORD *)v4 + 15) = 1;
pthread_mutex_init((pthread_mutex_t *)((char *)v4 + 1164), 0);
*((_DWORD *)v4 + 280) = v6;
v14 = (pthread_mutex_t *)((char *)v4 + 1156);
*((_BYTE *)v4 + 1492) = 0;
*((_DWORD *)v4 + 378) = v5;
*((_DWORD *)v4 + 372) = 0;
*((_BYTE *)v4 + 1493) = 0;
*((_DWORD *)v4 + 374) = 0;
pthread_mutex_init((pthread_mutex_t *)((char *)v4 + 1156), 0);
pthread_cond_init((pthread_cond_t *)((char *)v4 + 1160), 0);
v15 = malloc(0xA0u);
*((_DWORD *)v4 + 285) = v15;
memset(v15, 0, 0xA0u);
gettimeofday((struct timeval *)&src, 0);
srand48(v94 / 0x3E8uLL + 1000 * (_DWORD)src);
v16 = operator new(0x58u);
FifoDataManager::FifoDataManager((int)v16);
*((_DWORD *)v4 + 379) = v16;
*((_DWORD *)v4 + 16) = LibEventTaskScheduler::createNew((P2PManager *)((char *)v4 + 56), v17);
src = 0;
v94 = 0;
v95 = 0;
v18 = (char *)memcpy(
        &dest,
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:6.0.2) Gecko/20100101 Firefox/6.0.2 Fengyun",
        0x5Fu);
v140 = 94;
std::vector<tagInfo,std::allocator<tagInfo>>::_M_insert_aux((int)&src, 0, v18);
v19 = src;
v96 = 0;
v97 = 0;
v98 = 0;
v20 = *((_DWORD *)v4 + 16);
v21 = -133956095 * ((v94 - (signed int)src) >> 2);
if ( v21 )
{
if ( v21 > 0x1FF007 )
sub_BFA08();
v23 = 4 * ((v94 - (signed int)src) >> 2);
v88 = operator new(v23);
v19 = src;
v24 = (int)v88;
v21 = -133956095 * ((v94 - (signed int)src) >> 2);
v22 = 4 * ((v94 - (signed int)src) >> 2);
}
else
{
v22 = -133956095 * ((v94 - (signed int)src) >> 2);
v23 = -133956095 * ((v94 - (signed int)src) >> 2);
v24 = -133956095 * ((v94 - (signed int)src) >> 2);
}
v96 = (void *)v24;
v98 = v24 + v23;
v97 = v24;
if ( v21 )
v24 = (int)memmove((void *)v24, v19, v22);
v97 = v24 + v22;
v25 = CurlWrapper::createNew(v20, (int)&v96);
v26 = v96;
*((_DWORD *)v4 + 17) = v25;
if ( v26 )
operator delete(v26);
v27 = src;
if ( 133956095 * ((v94 - (signed int)src) >> 2) )
{
src = 0;
v94 = 0;
v95 = 0;
if ( v27 )
operator delete(v27);
}
v28 = operator new(0x70u);
AcquireChannelPlayInfo::AcquireChannelPlayInfo(
        (int)v28,
        *((_DWORD *)v4 + 17),
*((_DWORD *)v4 + 16),
(int)v5,
(int)notifyHttpFileFinished,
6,
*((_DWORD *)v4 + 379));
*((_DWORD *)v4 + 377) = v28;
v29 = malloc(0x10u);
*v29 = 0;
v30 = v29 + 2;
*((_DWORD *)v4 + 375) = v29;
v29[1] = 0;
*v30 = 0;
v30[1] = 0;
v31 = malloc(0x10u);
*((_DWORD *)v4 + 376) = v31;
*v31 = 0;
v32 = v31 + 2;
v31[1] = 0;
*v32 = 0;
v32[1] = 0;
v33 = malloc(0x10u);
*((_DWORD *)v4 + 371) = v33;
*v33 = 0;
v34 = v33 + 2;
v33[1] = 0;
*v34 = 0;
v34[1] = 0;
v35 = (char *)operator new(0x38u);
*(_DWORD *)v35 = 400;
v99 = 0;
v100 = 0;
v101 = 0;
v102 = 0;
v103 = 0;
v104 = 0;
v105 = 0;
v106 = 0;
v107 = 0;
v108 = 0;
std::_Deque_base<long,std::allocator<long>>::_M_initialize_map(&v99, 0);
std::deque<long,std::allocator<long>>::deque((_DWORD *)v35 + 3, &v99);
std::_Deque_base<long,std::allocator<long>>::~_Deque_base((void **)&v99);
pthread_mutex_init((pthread_mutex_t *)(v35 + 52), 0);
v36 = operator new[](0x2BC8u);
v37 = (int)(v36 + 2802);
v38 = 399;
v39 = (OneFile *)(v36 + 2);
v89 = (int)(v36 + 2);
*v36 = 28;
v36[1] = 400;
do
{
OneFile::OneFile(v39);
v39 = (OneFile *)((char *)v39 + 28);
--v38;
}
while ( v39 != (OneFile *)v37 );
*((_DWORD *)v35 + 1) = v89;
v40 = operator new[](0x190u);
*((_DWORD *)v35 + 2) = v40;
v41 = 0;
while ( 1 )
{
v42 = (_DWORD *)*((_DWORD *)v35 + 9);
v43 = *((_DWORD *)v35 + 11) - 4;
v40[v41] = 1;
if ( v42 != (_DWORD *)v43 )
break;
v44 = *((_DWORD *)v35 + 12);
if ( (unsigned int)(*((_DWORD *)v35 + 4) - ((v44 - *((_DWORD *)v35 + 3)) >> 2)) <= 1 )
{
std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)v35 + 3, 1u, 0);
v44 = *((_DWORD *)v35 + 12);
}
*(_DWORD *)(v44 + 4) = operator new(0x200u);
v45 = (_DWORD *)*((_DWORD *)v35 + 9);
if ( v45 )
*v45 = v41;
++v41;
v46 = *((_DWORD *)v35 + 12);
*((_DWORD *)v35 + 12) = v46 + 4;
v47 = *(_DWORD *)(v46 + 4);
*((_DWORD *)v35 + 11) = v47 + 512;
*((_DWORD *)v35 + 10) = v47;
*((_DWORD *)v35 + 9) = v47;
if ( v41 == 400 )
goto LABEL_23;
LABEL_16:
        v40 = (_BYTE *)*((_DWORD *)v35 + 2);
}
if ( v42 )
*v42 = v41;
++v41;
*((_DWORD *)v35 + 9) = v42 + 1;
if ( v41 != 400 )
goto LABEL_16;
LABEL_23:
*((_DWORD *)v4 + 1) = v35;
v48 = (char *)operator new(0x38u);
*(_DWORD *)v48 = 400;
v109 = 0;
v110 = 0;
v111 = 0;
v112 = 0;
v113 = 0;
v114 = 0;
v115 = 0;
v116 = 0;
v117 = 0;
v118 = 0;
std::_Deque_base<long,std::allocator<long>>::_M_initialize_map(&v109, 0);
std::deque<long,std::allocator<long>>::deque((_DWORD *)v48 + 3, &v109);
std::_Deque_base<long,std::allocator<long>>::~_Deque_base((void **)&v109);
pthread_mutex_init((pthread_mutex_t *)(v48 + 52), 0);
v49 = operator new[](0x29D888u);
v50 = (int)(v49 + 685602);
v51 = 399;
v90 = (int)(v49 + 2);
v52 = (OneRequest *)(v49 + 2);
*v49 = 6856;
v49[1] = 400;
do
{
OneRequest::OneRequest(v52);
--v51;
v52 = (OneRequest *)((char *)v52 + 6856);
}
while ( v52 != (OneRequest *)v50 );
*((_DWORD *)v48 + 1) = v90;
v53 = operator new[](0x190u);
*((_DWORD *)v48 + 2) = v53;
v54 = 0;
while ( 2 )
{
v55 = (_DWORD *)*((_DWORD *)v48 + 9);
v56 = *((_DWORD *)v48 + 11) - 4;
v53[v54] = 1;
if ( v55 == (_DWORD *)v56 )
{
v57 = *((_DWORD *)v48 + 12);
if ( (unsigned int)(*((_DWORD *)v48 + 4) - ((v57 - *((_DWORD *)v48 + 3)) >> 2)) <= 1 )
{
std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)v48 + 3, 1u, 0);
v57 = *((_DWORD *)v48 + 12);
}
*(_DWORD *)(v57 + 4) = operator new(0x200u);
v58 = (_DWORD *)*((_DWORD *)v48 + 9);
if ( v58 )
*v58 = v54;
++v54;
v59 = *((_DWORD *)v48 + 12);
*((_DWORD *)v48 + 12) = v59 + 4;
v60 = *(_DWORD *)(v59 + 4);
*((_DWORD *)v48 + 11) = v60 + 512;
*((_DWORD *)v48 + 10) = v60;
*((_DWORD *)v48 + 9) = v60;
if ( v54 == 400 )
break;
goto LABEL_29;
}
if ( v55 )
*v55 = v54;
++v54;
*((_DWORD *)v48 + 9) = v55 + 1;
if ( v54 != 400 )
{
LABEL_29:
        v53 = (_BYTE *)*((_DWORD *)v48 + 2);
continue;
}
break;
}
*(_DWORD *)v4 = v48;
v61 = (char *)operator new(0x38u);
*(_DWORD *)v61 = 8000;
v119 = 0;
v120 = 0;
v121 = 0;
v122 = 0;
v123 = 0;
v124 = 0;
v125 = 0;
v126 = 0;
v127 = 0;
v128 = 0;
std::_Deque_base<long,std::allocator<long>>::_M_initialize_map(&v119, 0);
std::deque<long,std::allocator<long>>::deque((_DWORD *)v61 + 3, &v119);
std::_Deque_base<long,std::allocator<long>>::~_Deque_base((void **)&v119);
pthread_mutex_init((pthread_mutex_t *)(v61 + 52), 0);
v62 = operator new[](0x995208u);
v63 = (int)(v62 + 2512002);
v64 = (OnePacket *)(v62 + 2);
v65 = 7999;
v91 = (int)(v62 + 2);
*v62 = 1256;
v62[1] = 8000;
do
{
OnePacket::OnePacket(v64);
--v65;
v64 = (OnePacket *)((char *)v64 + 1256);
}
while ( v64 != (OnePacket *)v63 );
*((_DWORD *)v61 + 1) = v91;
v66 = operator new[](0x1F40u);
*((_DWORD *)v61 + 2) = v66;
v67 = 0;
while ( 2 )
{
v68 = (_DWORD *)*((_DWORD *)v61 + 9);
v69 = *((_DWORD *)v61 + 11) - 4;
v66[v67] = 1;
if ( v68 == (_DWORD *)v69 )
{
v70 = *((_DWORD *)v61 + 12);
if ( (unsigned int)(*((_DWORD *)v61 + 4) - ((v70 - *((_DWORD *)v61 + 3)) >> 2)) <= 1 )
{
std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)v61 + 3, 1u, 0);
v70 = *((_DWORD *)v61 + 12);
}
*(_DWORD *)(v70 + 4) = operator new(0x200u);
v71 = (_DWORD *)*((_DWORD *)v61 + 9);
if ( v71 )
*v71 = v67;
++v67;
v72 = *((_DWORD *)v61 + 12);
*((_DWORD *)v61 + 12) = v72 + 4;
v73 = *(_DWORD *)(v72 + 4);
*((_DWORD *)v61 + 11) = v73 + 512;
*((_DWORD *)v61 + 10) = v73;
*((_DWORD *)v61 + 9) = v73;
if ( v67 == 8000 )
break;
goto LABEL_42;
}
if ( v68 )
*v68 = v67;
++v67;
*((_DWORD *)v61 + 9) = v68 + 1;
if ( v67 != 8000 )
{
LABEL_42:
        v66 = (_BYTE *)*((_DWORD *)v61 + 2);
continue;
}
break;
}
*((_DWORD *)v4 + 2) = v61;
v74 = (char *)operator new(0x38u);
*(_DWORD *)v74 = 400;
v129 = 0;
v130 = 0;
v131 = 0;
v132 = 0;
v133 = 0;
v134 = 0;
v135 = 0;
v136 = 0;
v137 = 0;
v138 = 0;
std::_Deque_base<long,std::allocator<long>>::_M_initialize_map(&v129, 0);
std::deque<long,std::allocator<long>>::deque((_DWORD *)v74 + 3, &v129);
std::_Deque_base<long,std::allocator<long>>::~_Deque_base((void **)&v129);
pthread_mutex_init((pthread_mutex_t *)(v74 + 52), 0);
v75 = operator new[](0x1F48u);
v76 = (int)(v75 + 2);
v77 = 399;
v78 = (int)(v75 + 2);
*v75 = 20;
v75[1] = 400;
do
{
OneData::OneData(v78);
--v77;
v78 += 20;
}
while ( v77 != -1 );
*((_DWORD *)v74 + 1) = v76;
v79 = operator new[](0x190u);
*((_DWORD *)v74 + 2) = v79;
v80 = 0;
while ( 2 )
{
v81 = (_DWORD *)*((_DWORD *)v74 + 9);
v82 = *((_DWORD *)v74 + 11) - 4;
v79[v80] = 1;
if ( v81 == (_DWORD *)v82 )
{
v83 = *((_DWORD *)v74 + 12);
if ( (unsigned int)(*((_DWORD *)v74 + 4) - ((v83 - *((_DWORD *)v74 + 3)) >> 2)) <= 1 )
{
std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)v74 + 3, 1u, 0);
v83 = *((_DWORD *)v74 + 12);
}
*(_DWORD *)(v83 + 4) = operator new(0x200u);
v84 = (_DWORD *)*((_DWORD *)v74 + 9);
if ( v84 )
*v84 = v80;
++v80;
v85 = *((_DWORD *)v74 + 12);
*((_DWORD *)v74 + 12) = v85 + 4;
v86 = *(_DWORD *)(v85 + 4);
*((_DWORD *)v74 + 11) = v86 + 512;
*((_DWORD *)v74 + 10) = v86;
*((_DWORD *)v74 + 9) = v86;
if ( v80 == 400 )
break;
goto LABEL_55;
}
if ( v81 )
*v81 = v80;
++v80;
*((_DWORD *)v74 + 9) = v81 + 1;
if ( v80 != 400 )
{
LABEL_55:
        v79 = (_BYTE *)*((_DWORD *)v74 + 2);
continue;
}
break;
}
*((_DWORD *)v4 + 3) = v74;
*((_DWORD *)v4 + 281) = 0;
gP2PClient = 0;
gLocalMemory = 0;
*((_DWORD *)v4 + 380) = v92;
while ( pthread_mutex_lock(v14) == 4 )
;
pthread_create((pthread_t *)v4 + 288, 0, (void *(*)(void *))P2PManager::P2PManagerThread, (void *)v4);
pthread_mutex_unlock(v14);
gP2PManager = (int)v4;
if ( src )
operator delete(src);
return v4;
}
// F3D68: using guessed type int gP2PManager;
// F3D6C: using guessed type int gLocalMemory;
// F3D70: using guessed type int gP2PClient;