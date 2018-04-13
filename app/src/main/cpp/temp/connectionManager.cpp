//
// Created by 赵勇 on 2018/4/10.
//

// F24E0: using guessed type void *;
// F2520: using guessed type void *;
// 2FEF4C: using guessed type int dword_2FEF4C;
// 2FEF50: using guessed type int dword_2FEF50;

//----- (00026A50) --------------------------------------------------------
_DWORD *__fastcall ConnectionManager::ConnectionManager(int a1, int a2, int a3, int a4)
{
    _DWORD *v4; // r4
    _DWORD *v5; // r0
    _DWORD *v6; // r3
    _DWORD *v7; // r2
    _DWORD *result; // r0

    v4 = (_DWORD *)a1;
    *(_DWORD *)(a1 + 16) = a2;
    *(_DWORD *)a1 = a4;
    *(_DWORD *)(a1 + 20) = a3;
    *(_DWORD *)(a1 + 4) = 0;
    *(_DWORD *)(a1 + 8) = 0;
    pthread_mutex_init((pthread_mutex_t *)(a1 + 28), 0);
    v4[8] = 0;
    v4[9] = 0;
    v4[10] = 0;
    v5 = malloc(0x10u);
    v4[6] = v5;
    *v5 = 0;
    v6 = v5 + 2;
    v7 = v5;
    result = v4;
    v7[1] = 0;
    *v6 = 0;
    v6[1] = 0;
    return result;
}

//----- (00026AB8) --------------------------------------------------------
int __fastcall ConnectionManager::setLocalAddress(ConnectionManager *this, sockaddr_in *a2)
{
    ConnectionManager *v2; // r4
    _DWORD *v3; // r3
    in_addr_t v4; // r12
    int v5; // r0
    int v6; // r2
    int v7; // r0
    int v8; // r12
    int v9; // r0
    int v10; // r12
    int result; // r0

    v2 = this;
    v3 = (_DWORD *)*((_DWORD *)this + 6);
    v4 = a2->sin_addr.s_addr;
    v5 = *(_DWORD *)a2->sin_zero;
    v6 = *(_DWORD *)&a2->sin_zero[4];
    *v3 = *(_DWORD *)&a2->sin_family;
    v3[1] = v4;
    v3[3] = v6;
    v3[2] = v5;
    v7 = (*(int (__cdecl **)(_DWORD, _DWORD))(**((_DWORD **)v2 + 4) + 8))(
            *((_DWORD *)v2 + 4),
            *(_DWORD *)(**((_DWORD **)v2 + 4) + 8));
    v8 = *((_DWORD *)v2 + 4);
    *((_DWORD *)v2 + 3) = v7;
    v9 = (*(int (__fastcall **)(int, _DWORD, signed int, _DWORD, _DWORD (__fastcall *)(void *), ConnectionManager *))(*(_DWORD *)v8 + 8))(
            v8,
            *(_DWORD *)(*(_DWORD *)v8 + 8),
            15000000,
            0,
            cbClear,
            v2);
    v10 = *((_DWORD *)v2 + 4);
    *((_DWORD *)v2 + 3) = v9;
    result = (*(int (__fastcall **)(int, _DWORD, signed int, _DWORD, _DWORD (__fastcall *)(void *), ConnectionManager *))(*(_DWORD *)v10 + 8))(
            v10,
            *(_DWORD *)(*(_DWORD *)v10 + 8),
            6000000,
            0,
            cbCheckDead,
            v2);
    *((_DWORD *)v2 + 3) = result;
    return result;
}

//----- (00026B8C) --------------------------------------------------------
int __fastcall ConnectionManager::isSameHost(ConnectionManager *this, sockaddr_in *a2, sockaddr_in *a3)
{
    unsigned int v4; // r3

    if ( a2->sin_addr.s_addr != a3->sin_addr.s_addr )
        return 0;
    v4 = a2->sin_port - a3->sin_port;
    return v4 + (v4 <= 0) + a3->sin_port - a2->sin_port;
}

//----- (00026BBC) --------------------------------------------------------
int __fastcall ConnectionManager::isAlreadyStacked(ConnectionManager *this, sockaddr_in *a2)
{
    ConnectionManager *v2; // r5
    sockaddr_in *v3; // r7
    int result; // r0
    pthread_mutex_t *v5; // r8
    int v6; // r3
    int v7; // r4
    sockaddr_in *v8; // r2
    int v9; // r6

    v2 = this;
    v3 = a2;
    if ( !((*((_DWORD *)this + 9) - *((_DWORD *)this + 8)) >> 2) )
    return 0;
    v5 = (pthread_mutex_t *)((char *)this + 28);
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 28));
    v6 = *((_DWORD *)v2 + 8);
    if ( *((_DWORD *)v2 + 9) - v6 <= 3 )
    {
        LABEL_9:
        pthread_mutex_unlock(v5);
        result = 0;
    }
    else
    {
        v7 = 0;
        while ( 1 )
        {
            v8 = *(sockaddr_in **)(v6 + 4 * v7++);
            v9 = ConnectionManager::isSameHost(v2, v3, v8);
            if ( v9 )
                break;
            v6 = *((_DWORD *)v2 + 8);
            if ( v7 >= (*((_DWORD *)v2 + 9) - v6) >> 2 )
                goto LABEL_9;
        }
        pthread_mutex_unlock(v5);
        result = v9;
    }
    return result;
}

//----- (00026C60) --------------------------------------------------------
int __fastcall ConnectionManager::removeClient(ConnectionManager *this, int a2)
{
pthread_mutex_t *v2; // r5
ConnectionManager *v3; // r4
int v4; // r6
char *v5; // r0
void *v6; // r6
int v7; // r3
int v8; // r3
const void *v9; // r1
int v11; // r3

v2 = (pthread_mutex_t *)((char *)this + 28);
v3 = this;
v4 = a2;
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 28));
v5 = (char *)(*((_DWORD *)v3 + 8) + 4 * v4);
v6 = *(void **)v5;
if ( *(_DWORD *)(*(_DWORD *)v5 + 20) )
{
v11 = *((_DWORD *)v3 + 2);
if ( v11 > 0 )
*((_DWORD *)v3 + 2) = v11 - 1;
}
else
{
v7 = *((_DWORD *)v3 + 1);
if ( v7 > 0 )
*((_DWORD *)v3 + 1) = v7 - 1;
}
v8 = *((_DWORD *)v3 + 9);
v9 = v5 + 4;
if ( v5 + 4 == (char *)v8 )
{
v8 = (int)(v5 + 4);
}
else if ( (v8 - (signed int)v9) >> 2 )
{
memmove(v5, v9, 4 * ((v8 - (signed int)v9) >> 2));
v8 = *((_DWORD *)v3 + 9);
}
*((_DWORD *)v3 + 9) = v8 - 4;
deleteConnection();
operator delete(v6);
pthread_mutex_unlock(v2);
return 0;
}

//----- (00026D08) --------------------------------------------------------
int __fastcall ConnectionManager::removeAllClients(int result)
{
    int v1; // r5
    pthread_mutex_t *v2; // r6
    int v3; // r3
    int v4; // r4
    void *v5; // r0

    v1 = result;
    if ( (unsigned int)(*(_DWORD *)(result + 36) - *(_DWORD *)(result + 32)) >> 2 )
    {
        v2 = (pthread_mutex_t *)(result + 28);
        pthread_mutex_lock((pthread_mutex_t *)(result + 28));
        v3 = *(_DWORD *)(v1 + 32);
        if ( *(_DWORD *)(v1 + 36) - v3 > 3 )
        {
            v4 = 0;
            do
            {
                v5 = *(void **)(v3 + 4 * v4++);
                operator delete(v5);
                v3 = *(_DWORD *)(v1 + 32);
            }
            while ( v4 < (*(_DWORD *)(v1 + 36) - v3) >> 2 );
        }
        *(_DWORD *)(v1 + 36) = v3;
        result = pthread_mutex_unlock(v2);
    }
    return result;
}

//----- (00026D78) --------------------------------------------------------
ConnectionManager *__fastcall ConnectionManager::~ConnectionManager(ConnectionManager *this)
{
    ConnectionManager *v1; // r4
    void *v2; // r0
    void *v3; // r0

    v1 = this;
    ConnectionManager::removeAllClients((int)this);
    v2 = (void *)*((_DWORD *)v1 + 6);
    *(_DWORD *)v1 = 0;
    *((_DWORD *)v1 + 1) = 0;
    *((_DWORD *)v1 + 2) = 0;
    free(v2);
    v3 = (void *)*((_DWORD *)v1 + 8);
    if ( v3 )
        operator delete(v3);
    pthread_mutex_destroy((pthread_mutex_t *)((char *)v1 + 28));
    return v1;
}

//----- (00026DD8) --------------------------------------------------------
int __fastcall ConnectionManager::announce(int a1, const void *a2)
{
    pthread_mutex_t *v2; // r8
    int *v3; // r5
    const void *v4; // r6
    int v5; // r3
    int v6; // r4
    const struct sockaddr *addr; // r12

    v2 = (pthread_mutex_t *)(a1 + 28);
    v3 = (int *)a1;
    v4 = a2;
    pthread_mutex_lock((pthread_mutex_t *)(a1 + 28));
    v5 = v3[8];
    if ( v3[9] - v5 > 3 )
    {
        v6 = 0;
        do
        {
            addr = *(const struct sockaddr **)(v5 + 4 * v6++);
            sendto(v3[5], v4, 0xA8u, 0, addr, 0x10u);
            v5 = v3[8];
        }
        while ( v6 < (v3[9] - v5) >> 2 );
    }
    return pthread_mutex_unlock(v2);
}

//----- (00026E58) --------------------------------------------------------
signed int __fastcall ConnectionManager::onAnnounce(int a1, int a2, sockaddr_in *a3)
{
    int v3; // r9
    ConnectionManager *v4; // r5
    sockaddr_in *v5; // r7
    pthread_mutex_t *v6; // r8
    int v7; // r3
    int v8; // r4
    int v9; // r6
    int v11; // [sp+0h] [bp-28h]
    int v12; // [sp+4h] [bp-24h]

    v3 = a2;
    v4 = (ConnectionManager *)a1;
    v5 = a3;
    if ( !a2 )
        return -1;
    v6 = (pthread_mutex_t *)(a1 + 28);
    pthread_mutex_lock((pthread_mutex_t *)(a1 + 28));
    v7 = *((_DWORD *)v4 + 8);
    if ( *((_DWORD *)v4 + 9) - v7 > 3 )
    {
        v8 = 0;
        while ( 1 )
        {
            v9 = *(_DWORD *)(v7 + 4 * v8++);
            if ( ConnectionManager::isSameHost(v4, v5, (sockaddr_in *)v9) )
                break;
            v7 = *((_DWORD *)v4 + 8);
            if ( v8 >= (*((_DWORD *)v4 + 9) - v7) >> 2 )
                goto LABEL_7;
        }
        memcpy((void *)(v9 + 72), (const void *)(v3 + 8), 0xA0u);
        *(_DWORD *)(v9 + 68) = *(_DWORD *)(v3 + 4);
        gettimeofday((struct timeval *)&v11, 0);
        *(_QWORD *)(v9 + 240) = (1000LL * v11 + v12 / 0x3E8uLL) / 0x3E8;
    }
    LABEL_7:
    pthread_mutex_unlock(v6);
    return 0;
}

//----- (00026F40) --------------------------------------------------------
int __fastcall ConnectionManager::onPacketRecved(ConnectionManager *this, sockaddr_in *a2, double a3)
{
pthread_mutex_t *v3; // r8
ConnectionManager *v4; // r5
double v5; // d8
sockaddr_in *v6; // r7
int v7; // r3
int v8; // r4
int v9; // r6
int v10; // r3
bool v11; // nf
double v12; // d6
double v13; // d7
double v14; // d8
signed int v15; // r2
int v17; // [sp+0h] [bp-28h]
int v18; // [sp+4h] [bp-24h]

v3 = (pthread_mutex_t *)((char *)this + 28);
v4 = this;
v5 = a3;
v6 = a2;
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 28));
v7 = *((_DWORD *)v4 + 8);
if ( *((_DWORD *)v4 + 9) - v7 > 3 )
{
v8 = 0;
while ( 1 )
{
v9 = *(_DWORD *)(v7 + 4 * v8++);
if ( ConnectionManager::isSameHost(v4, v6, (sockaddr_in *)v9) )
break;
v7 = *((_DWORD *)v4 + 8);
if ( v8 >= (*((_DWORD *)v4 + 9) - v7) >> 2 )
return pthread_mutex_unlock(v3);
}
v10 = *(_DWORD *)(v9 + 64) + 1;
v11 = *(_DWORD *)(v9 + 64) - 2047 < 0;
++*(_DWORD *)(v9 + 24);
if ( !((unsigned __int8)(v11 ^ __OFSUB__(v10, 2048)) | (v10 == 2048)) )
v10 = 2048;
*(_DWORD *)(v9 + 64) = v10;
--*(_DWORD *)(v9 + 32);
gettimeofday((struct timeval *)&v17, 0);
*(_QWORD *)(v9 + 240) = (1000LL * v17 + v18 / 0x3E8uLL) / 0x3E8;
if ( v5 != 0.0 )
{
v12 = *(double *)(v9 + 48);
if ( v12 == 0.0 )
{
v13 = v5 * 0.5;
}
else
{
v14 = v5 - v12;
v13 = *(double *)(v9 + 56) + (fabs(v14) - *(double *)(v9 + 56)) * 0.25;
v5 = v12 + v14 * 0.125;
}
*(double *)(v9 + 48) = v5;
*(double *)(v9 + 56) = v13;
v15 = (signed int)((v5 + v13 * 4.0) * 1000.0);
if ( v15 >= 6000000 )
v15 = 6000000;
*(double *)(v9 + 40) = (float)v15;
}
}
return pthread_mutex_unlock(v3);
}

//----- (000270C8) --------------------------------------------------------
int __fastcall ConnectionManager::onRequestTimeout(ConnectionManager *this, sockaddr_in *a2)
{
    pthread_mutex_t *v2; // r8
    ConnectionManager *v3; // r5
    sockaddr_in *v4; // r7
    int v5; // r3
    int v6; // r4
    int v7; // r6
    signed int v8; // r3

    v2 = (pthread_mutex_t *)((char *)this + 28);
    v3 = this;
    v4 = a2;
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 28));
    v5 = *((_DWORD *)v3 + 8);
    if ( *((_DWORD *)v3 + 9) - v5 > 3 )
    {
        v6 = 0;
        while ( 1 )
        {
            v7 = *(_DWORD *)(v5 + 4 * v6++);
            if ( ConnectionManager::isSameHost(v3, v4, (sockaddr_in *)v7) )
            break;
            v5 = *((_DWORD *)v3 + 8);
            if ( v6 >= (*((_DWORD *)v3 + 9) - v5) >> 2 )
                return pthread_mutex_unlock(v2);
        }
        v8 = (signed int)vcvts_n_f32_s32(*(_DWORD *)(v7 + 64), 1u);
        if ( v8 <= 3 )
            v8 = 4;
        *(_DWORD *)(v7 + 64) = v8;
        --*(_DWORD *)(v7 + 32);
    }
    return pthread_mutex_unlock(v2);
}

//----- (00027164) --------------------------------------------------------
int __fastcall ConnectionManager::onUploadPacket(ConnectionManager *this, sockaddr_in *a2)
{
    pthread_mutex_t *v2; // r8
    ConnectionManager *v3; // r5
    sockaddr_in *v4; // r7
    int v5; // r3
    int v6; // r4
    int v7; // r6

    v2 = (pthread_mutex_t *)((char *)this + 28);
    v3 = this;
    v4 = a2;
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 28));
    v5 = *((_DWORD *)v3 + 8);
    if ( *((_DWORD *)v3 + 9) - v5 > 3 )
    {
        v6 = 0;
        while ( 1 )
        {
            v7 = *(_DWORD *)(v5 + 4 * v6++);
            if ( ConnectionManager::isSameHost(v3, v4, (sockaddr_in *)v7) )
            break;
            v5 = *((_DWORD *)v3 + 8);
            if ( v6 >= (*((_DWORD *)v3 + 9) - v5) >> 2 )
                return pthread_mutex_unlock(v2);
        }
        ++*(_DWORD *)(v7 + 28);
    }
    return pthread_mutex_unlock(v2);
}

//----- (000271E4) --------------------------------------------------------
int __fastcall ConnectionManager::checkDeadRoutine(ConnectionManager *this)
{
    int v1; // r3
    int v2; // r2
    ConnectionManager *v3; // r7
    int v4; // r4
    int v5; // r8
    unsigned __int64 v6; // r0
    bool v7; // cf
    bool v8; // zf
    int result; // r0
    struct timeval tv; // [sp+8h] [bp-28h]

    v1 = *((_DWORD *)this + 8);
    v2 = *((_DWORD *)this + 9) - v1;
    v3 = this;
    if ( (unsigned int)v2 >> 2 && v2 > 3 )
    {
        v4 = 0;
        do
        {
            v5 = *(_DWORD *)(v1 + 4 * v4);
            gettimeofday(&tv, 0);
            v6 = (1000LL * tv.tv_sec + tv.tv_usec / 0x3E8uLL) / 0x3E8 - *(_QWORD *)(v5 + 240);
            v7 = 1;
            v8 = HIDWORD(v6) == 0;
            if ( !HIDWORD(v6) )
            {
                v7 = (unsigned int)v6 >= 5;
                v8 = (_DWORD)v6 == 5;
            }
            if ( !v8 && v7 )
                ConnectionManager::removeClient(v3, v4);
            v1 = *((_DWORD *)v3 + 8);
            ++v4;
        }
        while ( v4 < (*((_DWORD *)v3 + 9) - v1) >> 2 );
    }
    result = (*(int (__cdecl **)(_DWORD, _DWORD))(**((_DWORD **)v3 + 4) + 8))(
            *((_DWORD *)v3 + 4),
            *(_DWORD *)(**((_DWORD **)v3 + 4) + 8));
    *((_DWORD *)v3 + 3) = result;
    return result;
}

//----- (000272D4) --------------------------------------------------------
int __fastcall ConnectionManager::clearRoutine(ConnectionManager *this)
{
    int *v1; // r3
    ConnectionManager *v2; // r4
    int v3; // r12
    int v4; // r12
    int v5; // t1
    int result; // r0

    v1 = (int *)*((_DWORD *)this + 8);
    v2 = this;
    v3 = (*((_DWORD *)this + 9) - (signed int)v1) >> 2;
    if ( v3 > 0 )
    {
        v4 = (int)&v1[v3];
        do
        {
            v5 = *v1;
            ++v1;
            *(_DWORD *)(v5 + 32) = 0;
        }
        while ( v1 != (int *)v4 );
    }
    result = (*(int (__cdecl **)(_DWORD, _DWORD))(**((_DWORD **)this + 4) + 8))(
            *((_DWORD *)this + 4),
    *(_DWORD *)(**((_DWORD **)this + 4) + 8));
    *((_DWORD *)v2 + 3) = result;
    return result;
}

//----- (00027350) --------------------------------------------------------
int __fastcall ConnectionManager::evaluateRoutine(ConnectionManager *this)
{
    unsigned int v1; // r5
    int v2; // r3
    int v3; // r1
    ConnectionManager *v4; // r8
    int v5; // r2
    int v6; // r10
    int v7; // r9
    int v8; // r11
    int v9; // r4
    int v10; // r2
    int v11; // r4
    unsigned __int64 v12; // r0
    bool v13; // cf
    bool v14; // zf
    int result; // r0
    struct timeval tv; // [sp+10h] [bp-30h]

    v2 = *((_DWORD *)this + 8);
    v3 = *((_DWORD *)this + 9);
    v4 = this;
    v5 = (v3 - v2) >> 2;
    if ( v5 )
    {
        v6 = 0;
        if ( v5 <= 0 )
            v1 = 0;
        v7 = *(_DWORD *)(*(_DWORD *)v2 + 28) + *(_DWORD *)(*(_DWORD *)v2 + 24);
        if ( v5 > 0 )
        {
            v1 = 0;
            do
            {
                v8 = *(_DWORD *)(v2 + 4 * v1);
                v9 = *(_DWORD *)(v8 + 28);
                v10 = *(_DWORD *)(v8 + 24);
                *(_DWORD *)(v8 + 28) = 0;
                v11 = v9 + v10;
                *(_DWORD *)(v8 + 24) = 0;
                if ( v11 < v7 )
                {
                    gettimeofday(&tv, 0);
                    v12 = (1000LL * tv.tv_sec + tv.tv_usec / 0x3E8uLL) / 0x3E8 - *(_QWORD *)(v8 + 232);
                    v2 = *((_DWORD *)v4 + 8);
                    v13 = 1;
                    v14 = HIDWORD(v12) == 0;
                    if ( !HIDWORD(v12) )
                    {
                        v13 = (unsigned int)v12 >= 0x1E;
                        v14 = (_DWORD)v12 == 30;
                    }
                    if ( !v14 && v13 )
                    {
                        v7 = v11;
                        v3 = *((_DWORD *)v4 + 9);
                        v6 = v1;
                    }
                    else
                    {
                        v3 = *((_DWORD *)v4 + 9);
                    }
                }
                ++v1;
                v5 = (v3 - v2) >> 2;
            }
            while ( (signed int)v1 < v5 );
        }
        if ( (unsigned int)v5 > 0x20 && v1 < v5 )
            ConnectionManager::removeClient(v4, v6);
    }
    result = (*(int (__cdecl **)(_DWORD, _DWORD))(**((_DWORD **)v4 + 4) + 8))(
            *((_DWORD *)v4 + 4),
            *(_DWORD *)(**((_DWORD **)v4 + 4) + 8));
    *((_DWORD *)v4 + 3) = result;
    return result;
}

//----- (0002749C) --------------------------------------------------------
int __fastcall ConnectionManager::selectPeer(ConnectionManager *this, unsigned int a2)
{
int v2; // r6
int result; // r0
int v4; // r4
int v5; // r3
_DWORD *v6; // r12
unsigned int v7; // r2

v2 = *((_DWORD *)this + 8);
result = (*((_DWORD *)this + 9) - v2) >> 2;
if ( result )
{
v4 = 0;
v5 = 0;
while ( 1 )
{
v6 = *(_DWORD **)(v2 + 4 * v4);
v4 = ++v5;
v7 = v6[17];
if ( v7 )
{
if ( v7 + 160 > a2 && a2 >= v7 && *((_BYTE *)v6 + a2 - v7 + 72) == 1 && v6[8] < v6[16] )
break;
}
if ( v5 == result )
return 0;
}
result = (int)v6;
}
return result;
}

//----- (00027528) --------------------------------------------------------
int __fastcall ConnectionManager::getCurrentConnection(ConnectionManager *this)
{
    return *((_DWORD *)this + 2) + *((_DWORD *)this + 1);
}

//----- (00027534) --------------------------------------------------------
void __fastcall std::vector<PeerConnection *,std::allocator<PeerConnection *>>::_M_insert_aux(const void **a1, _DWORD *a2, _DWORD *a3)
{
_DWORD *v3; // r5
char *v4; // r3
const void **v5; // r4
int v6; // r4
int v7; // r1
_BYTE *v8; // r1
unsigned int v9; // r3
_DWORD *v10; // r6
int v11; // r1
int v12; // r7
unsigned int v13; // r8
_DWORD *v14; // ST04_4
_DWORD *v15; // r0
int v16; // r7
char *v17; // r12
int v18; // r7
int v19; // r7

v3 = a2;
v4 = (char *)a1[1];
v5 = a1;
if ( v4 != a1[2] )
{
if ( v4 )
{
*(_DWORD *)v4 = *((_DWORD *)v4 - 1);
v4 = (char *)a1[1];
}
a1[1] = v4 + 4;
v6 = *a3;
v7 = (v4 - 4 - (char *)a2) >> 2;
if ( v7 )
memmove(&v4[-4 * v7], v3, 4 * v7);
*v3 = v6;
return;
}
v8 = *a1;
v9 = (v4 - (_BYTE *)*a1) >> 2;
if ( v9 )
{
v10 = (_DWORD *)(2 * v9);
v11 = (char *)v3 - v8;
if ( v9 > 2 * v9 || (unsigned int)v10 > 0x3FFFFFFF )
{
v12 = v11 >> 2;
v13 = -1;
}
else
{
v13 = 2 * v9;
v12 = v11 >> 2;
if ( !v10 )
goto LABEL_12;
}
}
else
{
v13 = 1;
v12 = ((char *)v3 - v8) >> 2;
}
v14 = a3;
v15 = operator new(v13 * 4);
a3 = v14;
v10 = v15;
LABEL_12:
if ( &v10[v12] )
v10[v12] = *a3;
v16 = ((char *)v3 - (_BYTE *)*v5) >> 2;
if ( v16 )
{
v16 *= 4;
memmove(v10, *v5, v16);
}
v17 = (char *)v10 + v16 + 4;
v18 = ((_BYTE *)v5[1] - (_BYTE *)v3) >> 2;
if ( v18 )
{
v18 *= 4;
v17 = (char *)memmove(v17, v3, v18);
}
v19 = (int)&v17[v18];
if ( *v5 )
operator delete((void *)*v5);
*v5 = v10;
v5[1] = (const void *)v19;
v5[2] = &v10[v13];
}

//----- (00027684) --------------------------------------------------------
int __fastcall ConnectionManager::onConnectSuccess(int result, int a2)
{
    int v2; // r6
    __int16 v3; // r3
    pthread_mutex_t *v4; // r9
    int v5; // r4
    int v6; // r3
    _DWORD *v7; // r10
    int v8; // r2
    int v9; // r1
    int v10; // r2
    int v11; // r1
    int v12; // r2
    int v13; // r3
    int v14; // r7
    _DWORD *v15; // r3
    _DWORD *v16; // r2
    _DWORD *v17; // [sp+0h] [bp-40h]
    struct timeval tv; // [sp+4h] [bp-3Ch]
    __int16 v19; // [sp+Ch] [bp-34h]
    __int16 v20; // [sp+Eh] [bp-32h]
    int v21; // [sp+10h] [bp-30h]
    int v22; // [sp+14h] [bp-2Ch]
    int v23; // [sp+18h] [bp-28h]

    v2 = result;
    if ( a2 && *(_DWORD *)(result + 4) + *(_DWORD *)(result + 8) <= 64 )
    {
        v3 = __rev16(__rev16(bswap32(*(_DWORD *)(a2 + 16))));
        v4 = (pthread_mutex_t *)(result + 28);
        v21 = *(_DWORD *)(a2 + 8);
        v20 = v3;
        v5 = 0;
        v22 = 0;
        v19 = 2;
        v23 = 0;
        pthread_mutex_lock((pthread_mutex_t *)(result + 28));
        v6 = *(_DWORD *)(v2 + 32);
        if ( *(_DWORD *)(v2 + 36) - v6 > 3 )
        {
            while ( !ConnectionManager::isSameHost(
                    (ConnectionManager *)v2,
                    (sockaddr_in *)&v19,
                    *(sockaddr_in **)(v6 + 4 * v5)) )
            {
                v6 = *(_DWORD *)(v2 + 32);
                if ( ++v5 >= (*(_DWORD *)(v2 + 36) - v6) >> 2 )
                    goto LABEL_9;
            }
        }
        else
        {
            LABEL_9:
            if ( !ConnectionManager::isSameHost((ConnectionManager *)v2, (sockaddr_in *)&v19, *(sockaddr_in **)(v2 + 24)) )
            {
                ++*(_DWORD *)(v2 + 4);
                v7 = operator new(0xF8u);
                memset(v7, 0, 0xF8u);
                v8 = *(_DWORD *)(v2 + 24);
                v9 = v21;
                v17 = v7;
                v10 = *(_DWORD *)(v8 + 4);
                v7[5] = 1;
                if ( v9 == v10 )
                {
                    *((_BYTE *)v7 + 16) = 1;
                    *((_QWORD *)v7 + 5) = 4704770604115427328LL;
                    *((_QWORD *)v7 + 7) = 4652007308841189376LL;
                    v7[16] = 64;
                }
                else
                {
                    *((_QWORD *)v7 + 5) = 4704770604115427328LL;
                    *((_QWORD *)v7 + 7) = 4652007308841189376LL;
                    v7[16] = 16;
                }
                v11 = v21;
                v12 = v22;
                v13 = v23;
                *v7 = *(_DWORD *)&v19;
                v7[1] = v11;
                v7[2] = v12;
                v7[3] = v13;
                gettimeofday(&tv, 0);
                v14 = (int)v17;
                *((_QWORD *)v17 + 29) = (1000LL * tv.tv_sec + tv.tv_usec / 0x3E8uLL) / 0x3E8;
                gettimeofday(&tv, 0);
                v15 = *(_DWORD **)(v2 + 36);
                v16 = *(_DWORD **)(v2 + 40);
                *(_QWORD *)(v14 + 240) = (1000LL * tv.tv_sec + tv.tv_usec / 0x3E8uLL) / 0x3E8;
                if ( v15 == v16 )
                {
                    std::vector<PeerConnection *,std::allocator<PeerConnection *>>::_M_insert_aux(
                            (const void **)(v2 + 32),
                            v15,
                            &v17);
                }
                else
                {
                    if ( v15 )
                    {
                        *v15 = v17;
                        v15 = *(_DWORD **)(v2 + 36);
                    }
                    *(_DWORD *)(v2 + 36) = v15 + 1;
                }
                addConnection();
            }
        }
        result = pthread_mutex_unlock(v4);
    }
    return result;
}

//----- (000278F4) --------------------------------------------------------
void __fastcall ConnectionManager::onConnectDirectly(ConnectionManager *this, sockaddr_in *a2, int a3)
{
int v3; // r5
ConnectionManager *v4; // r8
sockaddr_in *v5; // r6
pthread_mutex_t *v6; // r7
int v7; // r3
int v8; // r4
sockaddr_in *v9; // r2
_DWORD *v10; // r9
int v11; // r1
in_addr_t v12; // r12
int v13; // r2
int v14; // r3
int v15; // r6
_DWORD *v16; // r3
_DWORD *v17; // r2
_DWORD *v18; // [sp+4h] [bp-2Ch]
struct timeval tv; // [sp+8h] [bp-28h]

v3 = a3;
v4 = this;
v5 = a2;
if ( *((_DWORD *)this + 2) + *((_DWORD *)this + 1) > 64 )
return;
v6 = (pthread_mutex_t *)((char *)this + 28);
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 28));
v7 = *((_DWORD *)v4 + 8);
if ( *((_DWORD *)v4 + 9) - v7 > 3 )
{
v8 = 0;
do
{
v9 = *(sockaddr_in **)(v7 + 4 * v8++);
if ( ConnectionManager::isSameHost(v4, v5, v9) )
goto LABEL_7;
v7 = *((_DWORD *)v4 + 8);
}
while ( v8 < (*((_DWORD *)v4 + 9) - v7) >> 2 );
}
if ( ConnectionManager::isSameHost(v4, v5, *((sockaddr_in **)v4 + 6)) )
{
LABEL_7:
        pthread_mutex_unlock(v6);
return;
}
if ( v3 )
{
++*((_DWORD *)v4 + 1);
v10 = operator new(0xF8u);
memset(v10, 0, 0xF8u);
v18 = v10;
}
else
{
++*((_DWORD *)v4 + 2);
v10 = operator new(0xF8u);
memset(v10, 0, 0xF8u);
v18 = v10;
v10[5] = 1;
}
if ( v5->sin_addr.s_addr == *(_DWORD *)(*((_DWORD *)v4 + 6) + 4) )
{
*((_BYTE *)v10 + 16) = 1;
*((_QWORD *)v10 + 5) = 4704770604115427328LL;
*((_QWORD *)v10 + 7) = 4652007308841189376LL;
LABEL_22:
        v10[16] = 64;
goto LABEL_15;
}
v11 = *((unsigned __int8 *)v10 + 16);
*((_QWORD *)v10 + 5) = 4704770604115427328LL;
*((_QWORD *)v10 + 7) = 4652007308841189376LL;
if ( v11 )
goto LABEL_22;
v10[16] = 16;
LABEL_15:
        v12 = v5->sin_addr.s_addr;
v13 = *(_DWORD *)v5->sin_zero;
v14 = *(_DWORD *)&v5->sin_zero[4];
*v10 = *(_DWORD *)&v5->sin_family;
v10[1] = v12;
v10[2] = v13;
v10[3] = v14;
gettimeofday(&tv, 0);
v15 = (int)v18;
*((_QWORD *)v18 + 29) = (1000LL * tv.tv_sec + tv.tv_usec / 0x3E8uLL) / 0x3E8;
gettimeofday(&tv, 0);
v16 = (_DWORD *)*((_DWORD *)v4 + 9);
v17 = (_DWORD *)*((_DWORD *)v4 + 10);
*(_QWORD *)(v15 + 240) = (1000LL * tv.tv_sec + tv.tv_usec / 0x3E8uLL) / 0x3E8;
if ( v16 == v17 )
{
std::vector<PeerConnection *,std::allocator<PeerConnection *>>::_M_insert_aux((const void **)v4 + 8, v16, &v18);
}
else
{
if ( v16 )
{
*v16 = v18;
v16 = (_DWORD *)*((_DWORD *)v4 + 9);
}
*((_DWORD *)v4 + 9) = v16 + 1;
}
pthread_mutex_unlock(v6);
addConnection();
}

//----- (00027B74) --------------------------------------------------------
int __fastcall ConnectionManager::onConnect(int a1, int a2)
{
    int v2; // r5
    int v3; // r6
    int v4; // r3
    __int16 v5; // r3
    pthread_mutex_t *v6; // r9
    int v7; // r4
    int v8; // r3
    _DWORD *v9; // r10
    int v10; // r2
    int v11; // r1
    int v12; // r2
    int v13; // r1
    int v14; // r2
    int v15; // r3
    int v16; // r7
    _DWORD *v17; // r3
    _DWORD *v18; // r2
    _DWORD *v20; // [sp+0h] [bp-40h]
    struct timeval tv; // [sp+4h] [bp-3Ch]
    __int16 v22; // [sp+Ch] [bp-34h]
    __int16 v23; // [sp+Eh] [bp-32h]
    int v24; // [sp+10h] [bp-30h]
    int v25; // [sp+14h] [bp-2Ch]
    int v26; // [sp+18h] [bp-28h]

    v3 = a1;
    v4 = *(_DWORD *)(a1 + 8) + *(_DWORD *)(a1 + 4);
    if ( v4 > 64 )
        v2 = 0;
    if ( v4 <= 64 )
    {
        v5 = __rev16(__rev16(bswap32(*(_DWORD *)(a2 + 12))));
        v6 = (pthread_mutex_t *)(a1 + 28);
        v24 = *(_DWORD *)(a2 + 4);
        v23 = v5;
        v7 = 0;
        v25 = 0;
        v22 = 2;
        v26 = 0;
        pthread_mutex_lock((pthread_mutex_t *)(a1 + 28));
        v8 = *(_DWORD *)(v3 + 32);
        if ( *(_DWORD *)(v3 + 36) - v8 > 3 )
        {
            while ( 1 )
            {
                v2 = ConnectionManager::isSameHost((ConnectionManager *)v3, (sockaddr_in *)&v22, *(sockaddr_in **)(v8 + 4 * v7));
                if ( v2 )
                    break;
                v8 = *(_DWORD *)(v3 + 32);
                if ( ++v7 >= (*(_DWORD *)(v3 + 36) - v8) >> 2 )
                    goto LABEL_5;
            }
            pthread_mutex_unlock(v6);
        }
        else
        {
            LABEL_5:
            if ( ConnectionManager::isSameHost((ConnectionManager *)v3, (sockaddr_in *)&v22, *(sockaddr_in **)(v3 + 24)) )
            {
                v2 = 0;
                pthread_mutex_unlock(v6);
            }
            else
            {
                ++*(_DWORD *)(v3 + 8);
                v9 = operator new(0xF8u);
                memset(v9, 0, 0xF8u);
                v10 = *(_DWORD *)(v3 + 24);
                v11 = v24;
                v20 = v9;
                v12 = *(_DWORD *)(v10 + 4);
                v9[5] = 1;
                if ( v11 == v12 )
                {
                    *((_BYTE *)v9 + 16) = 1;
                    *((_QWORD *)v9 + 5) = 4704770604115427328LL;
                    *((_QWORD *)v9 + 7) = 4652007308841189376LL;
                    v9[16] = 64;
                }
                else
                {
                    *((_QWORD *)v9 + 5) = 4704770604115427328LL;
                    *((_QWORD *)v9 + 7) = 4652007308841189376LL;
                    v9[16] = 16;
                }
                v13 = v24;
                v14 = v25;
                v15 = v26;
                *v9 = *(_DWORD *)&v22;
                v9[1] = v13;
                v9[2] = v14;
                v9[3] = v15;
                gettimeofday(&tv, 0);
                v16 = (int)v20;
                *((_QWORD *)v20 + 29) = (1000LL * tv.tv_sec + tv.tv_usec / 0x3E8uLL) / 0x3E8;
                gettimeofday(&tv, 0);
                v17 = *(_DWORD **)(v3 + 36);
                v18 = *(_DWORD **)(v3 + 40);
                *(_QWORD *)(v16 + 240) = (1000LL * tv.tv_sec + tv.tv_usec / 0x3E8uLL) / 0x3E8;
                if ( v17 == v18 )
                {
                    std::vector<PeerConnection *,std::allocator<PeerConnection *>>::_M_insert_aux(
                            (const void **)(v3 + 32),
                            v17,
                            &v20);
                }
                else
                {
                    if ( v17 )
                    {
                        *v17 = v20;
                        v17 = *(_DWORD **)(v3 + 36);
                    }
                    *(_DWORD *)(v3 + 36) = v17 + 1;
                }
                addConnection();
                pthread_mutex_unlock(v6);
                v2 = 1;
            }
        }
    }
    return v2;
}