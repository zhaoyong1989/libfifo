//
// Created by 赵勇 on 2018/4/10.
//

//----- (00027DFC) --------------------------------------------------------
OneData *__fastcall LocalMemory::cacheFileDataToOneData(LocalMemory *this, OneFile *a2, OneData *a3)
{
    OneFile *v3; // r8
    OneData *v4; // r7
    int v5; // r9
    int size; // r6
    int v7; // r4
    int v8; // r5
    signed int v9; // r0
    int v10; // r3
    unsigned __int8 *v12; // [sp+Ch] [bp-2Ch]

    v3 = a2;
    v4 = a3;
    v5 = OneFile::getPacketNumb(a2);
    size = OneFile::getTotalSize(v3);
    if ( v5 <= 0 )
    {
        v8 = 0;
    }
    else
    {
        v7 = 0;
        v8 = 0;
        do
        {
            v12 = 0;
            v9 = OneFile::getPacketContent(v3, &v12, (unsigned __int16)v7);
            v10 = v7++;
            if ( v9 > 0 )
            {
                if ( size < v8 + v9 )
                    break;
                v8 += v9;
                OneData::cacheData(v4, v12, v9, v10, size);
            }
        }
        while ( v7 != v5 );
    }
    OneData::setDataLength((int)v4, v8);
    return v4;
}

//----- (00027EA8) --------------------------------------------------------
signed int __fastcall LocalMemory::readMemory(LocalMemory *this, unsigned __int8 **a2, unsigned int a3, unsigned int *a4)
{
pthread_mutex_t *v4; // r8
LocalMemory *v5; // r4
unsigned __int8 **v6; // r7
unsigned int v7; // r6
unsigned int *v8; // r9
int v9; // r3
int v10; // lr
int v11; // r5
int v12; // r12
OneData **v13; // lr
unsigned int v14; // r2
unsigned int v15; // r10
int v16; // r2
int v17; // r3
OneData **v18; // r2
unsigned int v19; // r1
signed int v20; // r11
signed int result; // r0

v4 = (pthread_mutex_t *)((char *)this + 92);
v5 = this;
v6 = a2;
v7 = a3;
v8 = a4;
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 92));
v9 = *((_DWORD *)v5 + 18);
v10 = *((_DWORD *)v5 + 15);
if ( ((*((_DWORD *)v5 + 19) - *((_DWORD *)v5 + 20)) >> 2)
+ ((((*((_DWORD *)v5 + 22) - v9) >> 2) - 1) << 7)
+ ((*((_DWORD *)v5 + 17) - v10) >> 2) <= 0 )
{
LABEL_20:
        pthread_mutex_unlock(v4);
result = -1;
}
else
{
v11 = 0;
while ( 1 )
{
v12 = v11 + ((v10 - *((_DWORD *)v5 + 16)) >> 2);
if ( (unsigned int)v12 > 0x7F )
{
v14 = v12 <= 0 ? ~((unsigned int)~v12 >> 7) : v12 >> 7;
v13 = (OneData **)(*(_DWORD *)(v9 + 4 * v14) + 4 * (v12 - (v14 << 7)));
}
else
{
v13 = (OneData **)(v10 + 4 * v11);
}
v15 = OneData::getDataId(*v13);
if ( v15 >= v7 )
{
v16 = *((_DWORD *)v5 + 15);
v17 = v11 + ((v16 - *((_DWORD *)v5 + 16)) >> 2);
if ( (unsigned int)v17 > 0x7F )
{
v19 = v17 <= 0 ? ~((unsigned int)~v17 >> 7) : v17 >> 7;
v17 -= v19 << 7;
v18 = (OneData **)(*(_DWORD *)(*((_DWORD *)v5 + 18) + 4 * v19) + 4 * v17);
}
else
{
v18 = (OneData **)(v16 + 4 * v11);
}
v20 = OneData::getOneData(*v18, v6, (int)v18, (unsigned __int8 *)v17);
if ( v20 >= 0 )
break;
}
v9 = *((_DWORD *)v5 + 18);
++v11;
v10 = *((_DWORD *)v5 + 15);
if ( v11 >= ((*((_DWORD *)v5 + 19) - *((_DWORD *)v5 + 20)) >> 2)
+ ((((*((_DWORD *)v5 + 22) - v9) >> 2) - 1) << 7)
+ ((*((_DWORD *)v5 + 17) - v10) >> 2) )
goto LABEL_20;
}
*v8 = v15;
pthread_mutex_unlock(v4);
result = v20;
}
return result;
}

//----- (00028020) --------------------------------------------------------
signed int __fastcall LocalMemory::readMemory(size_t n, unsigned __int8 *a2, unsigned int a3, int a4, int na)
{
pthread_mutex_t *v5; // r6
_DWORD *v6; // r4
unsigned int v7; // r5
int v8; // r8
unsigned __int8 *v9; // r7
int v10; // r2
int v11; // r5
unsigned __int8 *v12; // r3
int v13; // r1
int v14; // r12
OneData *v15; // r0
signed int result; // r0
int v17; // [sp+4h] [bp-1Ch]

v5 = (pthread_mutex_t *)(n + 92);
v6 = (_DWORD *)n;
v7 = a3;
v8 = a4;
v9 = a2;
pthread_mutex_lock((pthread_mutex_t *)(n + 92));
v11 = v7 - ***(_DWORD ***)(v6[25] + 8);
if ( v11 < 0 )
{
pthread_mutex_unlock(v5);
result = -2;
}
else
{
v12 = (unsigned __int8 *)v6[15];
v13 = v6[18];
v14 = v11 + ((signed int)&v12[-v6[16]] >> 2);
if ( (unsigned int)v14 > 0x7F )
{
if ( v14 <= 0 )
{
v10 = ~((unsigned int)~v14 >> 7);
v11 = v14 - (v10 << 7);
v12 = *(unsigned __int8 **)(v13 + 4 * v10);
}
else
{
v10 = v14 >> 7;
v11 = v14 - (v14 >> 7 << 7);
v12 = *(unsigned __int8 **)(v13 + 4 * (v14 >> 7));
}
}
v15 = *(OneData **)&v12[4 * v11];
v17 = 0;
if ( OneData::getOneData(v15, (unsigned __int8 **)&v17, v10, v12) <= 0 )
{
pthread_mutex_unlock(v5);
result = -1;
}
else
{
memcpy(v9, (const void *)(v17 + 1158 * v8), na);
pthread_mutex_unlock(v5);
result = 0;
}
}
return result;
}

//----- (00028114) --------------------------------------------------------
signed int __fastcall LocalMemory::readMemoryPieceLength(LocalMemory *this, unsigned int a2)
{
pthread_mutex_t *v2; // r7
LocalMemory *v3; // r4
unsigned int v4; // r6
int v5; // r2
int v6; // r3
int v7; // r5
OneData *v8; // r8
OneData **v9; // r12
int v10; // r3
unsigned int v11; // r1
signed int result; // r0
int v13; // r4

v2 = (pthread_mutex_t *)((char *)this + 92);
v3 = this;
v4 = a2;
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 92));
v5 = *((_DWORD *)v3 + 18);
v6 = *((_DWORD *)v3 + 15);
if ( ((*((_DWORD *)v3 + 19) - *((_DWORD *)v3 + 20)) >> 2)
+ ((((*((_DWORD *)v3 + 22) - v5) >> 2) - 1) << 7)
+ ((*((_DWORD *)v3 + 17) - v6) >> 2) <= 0 )
{
LABEL_10:
        pthread_mutex_unlock(v2);
result = -1;
}
else
{
v7 = 0;
while ( 1 )
{
v9 = (OneData **)(v6 + 4 * v7);
v10 = v7 + ((v6 - *((_DWORD *)v3 + 16)) >> 2);
if ( (unsigned int)v10 > 0x7F )
{
v11 = v10 >> 7;
if ( v10 <= 0 )
v11 = ~((unsigned int)~v10 >> 7);
v9 = (OneData **)(*(_DWORD *)(v5 + 4 * v11) + 4 * (v10 - (v11 << 7)));
}
v8 = *v9;
++v7;
if ( OneData::getDataId(*v9) == v4 )
break;
v5 = *((_DWORD *)v3 + 18);
v6 = *((_DWORD *)v3 + 15);
if ( v7 >= ((*((_DWORD *)v3 + 19) - *((_DWORD *)v3 + 20)) >> 2)
+ ((((*((_DWORD *)v3 + 22) - v5) >> 2) - 1) << 7)
+ ((*((_DWORD *)v3 + 17) - v6) >> 2) )
goto LABEL_10;
}
v13 = OneData::getDataLength(v8);
pthread_mutex_unlock(v2);
result = v13;
}
return result;
}

//----- (00028230) --------------------------------------------------------
int __fastcall LocalMemory::locatePieceData(LocalMemory *this, unsigned int a2, int *a3)
{
LocalMemory *v3; // r4
int *v4; // r7
int v5; // r0
unsigned int v6; // r6
int v7; // r3
int v8; // r5
OneData **v9; // r12
int v10; // r3
unsigned int v11; // r2
int v13; // r2
int v14; // r3
int v15; // r3
int v16; // r2
unsigned int v17; // r1

v3 = this;
v4 = a3;
v5 = *((_DWORD *)this + 18);
v6 = a2;
v7 = *((_DWORD *)v3 + 15);
if ( ((*((_DWORD *)v3 + 19) - *((_DWORD *)v3 + 20)) >> 2)
+ ((((*((_DWORD *)v3 + 22) - v5) >> 2) - 1) << 7)
+ ((*((_DWORD *)v3 + 17) - v7) >> 2) <= 0 )
return 0;
v8 = 0;
while ( 1 )
{
v9 = (OneData **)(v7 + 4 * v8);
v10 = v8 + ((v7 - *((_DWORD *)v3 + 16)) >> 2);
if ( (unsigned int)v10 > 0x7F )
{
v11 = v10 >> 7;
if ( v10 <= 0 )
v11 = ~((unsigned int)~v10 >> 7);
v9 = (OneData **)(*(_DWORD *)(v5 + 4 * v11) + 4 * (v10 - (v11 << 7)));
}
if ( OneData::getDataId(*v9) == v6 )
break;
v5 = *((_DWORD *)v3 + 18);
++v8;
v7 = *((_DWORD *)v3 + 15);
if ( v8 >= ((*((_DWORD *)v3 + 19) - *((_DWORD *)v3 + 20)) >> 2)
+ ((((*((_DWORD *)v3 + 22) - v5) >> 2) - 1) << 7)
+ ((*((_DWORD *)v3 + 17) - v7) >> 2) )
return 0;
}
v13 = *((_DWORD *)v3 + 15);
v14 = *((_DWORD *)v3 + 16);
if ( v4 )
*v4 = v8;
v15 = v8 + ((v13 - v14) >> 2);
if ( (unsigned int)v15 > 0x7F )
{
if ( v15 <= 0 )
v17 = ~((unsigned int)~v15 >> 7);
else
v17 = v15 >> 7;
v16 = *(_DWORD *)(*((_DWORD *)v3 + 18) + 4 * v17) + 4 * (v15 - (v17 << 7));
}
else
{
v16 = v13 + 4 * v8;
}
return *(_DWORD *)v16;
}

//----- (00028370) --------------------------------------------------------
signed int __fastcall LocalMemory::readMemory(LocalMemory *this, unsigned __int8 **a2, unsigned int a3)
{
pthread_mutex_t *v3; // r5
LocalMemory *v4; // r4
unsigned int v5; // r6
unsigned __int8 **v6; // r7
OneData *v7; // r0
int v8; // r2
unsigned __int8 *v9; // r3
signed int v10; // r4

v3 = (pthread_mutex_t *)((char *)this + 92);
v4 = this;
v5 = a3;
v6 = a2;
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 92));
v7 = (OneData *)LocalMemory::locatePieceData(v4, v5, 0);
v10 = (signed int)v7;
if ( v7 )
v10 = OneData::getOneData(v7, v6, v8, v9);
pthread_mutex_unlock(v3);
return v10;
}

//----- (000283C0) --------------------------------------------------------
int __fastcall LocalMemory::getAvaliablePieceBytes(LocalMemory *this, unsigned int a2, int *a3)
{
pthread_mutex_t *v3; // r9
LocalMemory *v4; // r4
int v5; // r10
int *v6; // r8
unsigned int v7; // r6
int v8; // r2
int v9; // r12
int v10; // r5
int v11; // r7
int v12; // r3
OneData **v13; // r12
unsigned int v14; // r1
_DWORD *v15; // r2
int v16; // r1
int v17; // r3
int v18; // r2
int v19; // r3
int v20; // r3
int v21; // r1
int v22; // r2
int v23; // r3
OneData **v24; // r2
unsigned int v25; // r1
int v26; // r0
unsigned int v28; // r1
unsigned int v29; // r1
unsigned int v30; // r0

v3 = (pthread_mutex_t *)((char *)this + 92);
v4 = this;
v5 = 0;
*a3 = 0;
v6 = a3;
v7 = a2;
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 92));
v8 = *((_DWORD *)v4 + 18);
v9 = *((_DWORD *)v4 + 15);
if ( ((*((_DWORD *)v4 + 19) - *((_DWORD *)v4 + 20)) >> 2)
+ ((((*((_DWORD *)v4 + 22) - v8) >> 2) - 1) << 7)
+ ((*((_DWORD *)v4 + 17) - v9) >> 2) > 0 )
{
v10 = 0;
v11 = 0;
while ( 1 )
{
v12 = v10 + ((v9 - *((_DWORD *)v4 + 16)) >> 2);
if ( (unsigned int)v12 > 0x7F )
{
if ( v12 <= 0 )
v14 = ~((unsigned int)~v12 >> 7);
else
v14 = v12 >> 7;
v13 = (OneData **)(*(_DWORD *)(v8 + 4 * v14) + 4 * (v12 - (v14 << 7)));
}
else
{
v13 = (OneData **)(v9 + v5);
}
if ( OneData::getDataId(*v13) >= v7 )
{
v15 = (_DWORD *)*((_DWORD *)v4 + 25);
v16 = v15[2];
v17 = v15[3];
v18 = v15[5];
v19 = v10 + ((v16 - v17) >> 2);
if ( (unsigned int)v19 > 0x7F )
{
if ( v19 <= 0 )
v28 = ~((unsigned int)~v19 >> 7);
else
v28 = v19 >> 7;
if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v18 + 4 * v28) + 4 * (v19 - (v28 << 7))) + 4) != 2 )
{
v29 = v19 <= 0 ? ~((unsigned int)~v19 >> 7) : v19 >> 7;
if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v18 + 4 * v29) + 4 * (v19 - (v29 << 7))) + 4) != 3 )
{
v30 = v19 <= 0 ? ~((unsigned int)~v19 >> 7) : v19 >> 7;
if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v18 + 4 * v30) + 4 * (v19 - (v30 << 7))) + 4) != 4 )
goto LABEL_25;
}
}
}
else
{
v20 = *(unsigned __int8 *)(*(_DWORD *)(v16 + v5) + 4);
if ( v20 != 2 && v20 != 3 )
{
v21 = v16 + v5;
if ( *(_BYTE *)(*(_DWORD *)v21 + 4) != 4 )
goto LABEL_25;
}
}
v22 = *((_DWORD *)v4 + 15);
v23 = v10 + ((v22 - *((_DWORD *)v4 + 16)) >> 2);
if ( (unsigned int)v23 > 0x7F )
{
if ( v23 <= 0 )
v25 = ~((unsigned int)~v23 >> 7);
else
v25 = v23 >> 7;
v24 = (OneData **)(*(_DWORD *)(*((_DWORD *)v4 + 18) + 4 * v25) + 4 * (v23 - (v25 << 7)));
}
else
{
v24 = (OneData **)(v22 + v5);
}
v26 = OneData::getDataLength(*v24);
++*v6;
v11 += v26;
}
v8 = *((_DWORD *)v4 + 18);
++v10;
v5 += 4;
v9 = *((_DWORD *)v4 + 15);
if ( v10 >= ((*((_DWORD *)v4 + 19) - *((_DWORD *)v4 + 20)) >> 2)
+ ((((*((_DWORD *)v4 + 22) - v8) >> 2) - 1) << 7)
+ ((*((_DWORD *)v4 + 17) - v9) >> 2) )
goto LABEL_25;
}
}
v11 = 0;
LABEL_25:
        pthread_mutex_unlock(v3);
return v11;
}

//----- (0002861C) --------------------------------------------------------
int __fastcall LocalMemory::getCurrentPieceBytes(LocalMemory *this, int *a2)
{
    LocalMemory *v2; // r5
    int v3; // r4
    int *v4; // r6
    int v5; // r1
    int v6; // r11
    int v7; // r10
    int v8; // r8
    int v9; // r9
    int v10; // r2
    int v11; // r7
    int v12; // r3
    int v13; // lr
    _DWORD *v14; // r12
    int v15; // lr
    int v16; // r0
    int v17; // r3
    unsigned int v18; // r12
    unsigned int v19; // r12
    unsigned int v20; // r12
    int v21; // r3
    int v22; // r3
    OneData **v23; // r2
    unsigned int v24; // r0
    int v25; // r0
    pthread_mutex_t *mutex; // [sp+4h] [bp-2Ch]

    v2 = this;
    v3 = 0;
    *a2 = 0;
    mutex = (pthread_mutex_t *)((char *)this + 92);
    v4 = a2;
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 92));
    v5 = *((_DWORD *)v2 + 18);
    v6 = *((_DWORD *)v2 + 22);
    v7 = 0;
    v8 = *((_DWORD *)v2 + 19);
    v9 = *((_DWORD *)v2 + 20);
    v10 = *((_DWORD *)v2 + 15);
    v11 = *((_DWORD *)v2 + 17);
    if ( ((v8 - v9) >> 2) + ((((v6 - v5) >> 2) - 1) << 7) + ((v11 - v10) >> 2) > 0 )
    {
        do
        {
            v14 = (_DWORD *)*((_DWORD *)v2 + 25);
            v15 = v14[2];
            v16 = v14[5];
            v17 = v3 + ((v15 - v14[3]) >> 2);
            if ( (unsigned int)v17 <= 0x7F )
            {
                v12 = *(unsigned __int8 *)(*(_DWORD *)(v15 + 4 * v3) + 4);
                if ( v12 == 2 )
                    goto LABEL_22;
                if ( v12 == 3 )
                    goto LABEL_22;
                v13 = v15 + 4 * v3;
                if ( *(_BYTE *)(*(_DWORD *)v13 + 4) == 4 )
                    goto LABEL_22;
            }
            else
            {
                if ( v17 <= 0 )
                    v18 = ~((unsigned int)~v17 >> 7);
                else
                    v18 = v17 >> 7;
                if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v16 + 4 * v18) + 4 * (v17 - (v18 << 7))) + 4) == 2
                     || (v17 <= 0 ? (v19 = ~((unsigned int)~v17 >> 7)) : (v19 = v17 >> 7),
                        *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v16 + 4 * v19) + 4 * (v17 - (v19 << 7))) + 4) == 3
                        || (v17 <= 0 ? (v20 = ~((unsigned int)~v17 >> 7)) : (v20 = v17 >> 7),
                                *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v16 + 4 * v20) + 4 * (v17 - (v20 << 7))) + 4) == 4)) )
                {
                    LABEL_22:
                    v21 = v10 - *((_DWORD *)v2 + 16);
                    ++*v4;
                    v22 = v3 + (v21 >> 2);
                    if ( (unsigned int)v22 > 0x7F )
                    {
                        if ( v22 <= 0 )
                            v24 = ~((unsigned int)~v22 >> 7);
                        else
                            v24 = v22 >> 7;
                        v23 = (OneData **)(*(_DWORD *)(v5 + 4 * v24) + 4 * (v22 - (v24 << 7)));
                    }
                    else
                    {
                        v23 = (OneData **)(v10 + 4 * v3);
                    }
                    v25 = OneData::getDataLength(*v23);
                    v5 = *((_DWORD *)v2 + 18);
                    v10 = *((_DWORD *)v2 + 15);
                    v6 = *((_DWORD *)v2 + 22);
                    v8 = *((_DWORD *)v2 + 19);
                    v9 = *((_DWORD *)v2 + 20);
                    v11 = *((_DWORD *)v2 + 17);
                    v7 += v25;
                    goto LABEL_8;
                }
            }
            LABEL_8:
            ++v3;
        }
        while ( v3 < ((v8 - v9) >> 2) + ((((v6 - v5) >> 2) - 1) << 7) + ((v11 - v10) >> 2) );
    }
    pthread_mutex_unlock(mutex);
    return v7;
}

//----- (0002881C) --------------------------------------------------------
void **__fastcall std::_Deque_base<OneFile *,std::allocator<OneFile *>>::~_Deque_base(void **a1)
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

//----- (00028864) --------------------------------------------------------
void **__fastcall std::_Deque_base<OneData *,std::allocator<OneData *>>::~_Deque_base(void **a1)
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

//----- (000288AC) --------------------------------------------------------
_DWORD *__fastcall LocalMemory::LocalMemory(_DWORD *a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    _DWORD *v7; // r4
    int v8; // r9
    _DWORD *v9; // r0
    unsigned int v10; // r6
    _DWORD *v11; // r5
    int v12; // r10
    int v13; // r1
    int v14; // r2
    _DWORD *v15; // r0
    int v16; // r6
    _DWORD *v17; // r5
    unsigned int v18; // r6
    int v19; // r10
    int v20; // r2
    int v21; // r3
    _DWORD *result; // r0

    v7 = a1;
    v8 = a4;
    *a1 = a2;
    a1[1] = a3;
    a1[2] = a7;
    a1[4] = 8;
    a1[3] = 0;
    a1[5] = 0;
    a1[6] = 0;
    a1[7] = 0;
    a1[8] = 0;
    a1[9] = 0;
    a1[10] = 0;
    a1[11] = 0;
    a1[12] = 0;
    v9 = operator new(0x20u);
    v10 = (unsigned int)(v7[4] - 1) >> 1;
    v11 = v9;
    v7[3] = v9;
    v12 = (int)&v9[v10];
    v9[v10] = operator new(0x200u);
    v7[8] = v12;
    v13 = v11[v10];
    v7[12] = v12;
    v7[7] = v13 + 512;
    v7[6] = v13;
    v14 = v11[v10];
    v7[5] = v13;
    v7[13] = 0;
    v7[10] = v14;
    v7[9] = v14;
    v7[11] = v14 + 512;
    v7[15] = 0;
    v7[16] = 0;
    v7[17] = 0;
    v7[18] = 0;
    v7[19] = 0;
    v7[20] = 0;
    v7[21] = 0;
    v7[22] = 0;
    v7[14] = 8;
    v15 = operator new(0x20u);
    v16 = v7[14];
    v17 = v15;
    v7[13] = v15;
    v18 = (unsigned int)(v16 - 1) >> 1;
    v19 = (int)&v15[v18];
    v15[v18] = operator new(0x200u);
    v7[18] = v19;
    v20 = v17[v18];
    v7[22] = v19;
    v7[17] = v20 + 512;
    v7[16] = v20;
    v21 = v17[v18];
    v7[15] = v20;
    v7[21] = v21 + 512;
    v7[20] = v21;
    v7[19] = v21;
    pthread_mutex_init((pthread_mutex_t *)(v7 + 23), 0);
    v7[25] = v8;
    result = v7;
    v7[24] = a5;
    v7[26] = a6;
    return result;
}

//----- (00028A90) --------------------------------------------------------
void *__fastcall std::deque<OneData *,std::allocator<OneData *>>::_M_push_back_aux(void **a1, _DWORD *a2)
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

//----- (00028C08) --------------------------------------------------------
void *__fastcall LocalMemory::initPendingData(LocalMemory *this, unsigned int a2)
{
LocalMemory *v2; // r5
int v3; // r4
unsigned int v4; // r8
int *v5; // r3
int v6; // r6
int v7; // r2
_BYTE *v8; // r1
void *result; // r0
_DWORD *v10; // r3
int v11; // r3
int v12; // r1
int v13; // r3
void *v14; // [sp+4h] [bp-1Ch]

v2 = this;
v3 = *((_DWORD *)this + 2);
v4 = a2;
pthread_mutex_lock((pthread_mutex_t *)(v3 + 52));
v5 = *(int **)(v3 + 20);
if ( *(int **)(v3 + 36) == v5 )
return (void *)pthread_mutex_unlock((pthread_mutex_t *)(v3 + 52));
v6 = *v5;
v7 = *(_DWORD *)(v3 + 8);
v8 = (_BYTE *)(v7 + *v5);
if ( !*(_BYTE *)(v7 + *v5) )
return (void *)pthread_mutex_unlock((pthread_mutex_t *)(v3 + 52));
if ( v5 == (int *)(*(_DWORD *)(v3 + 28) - 4) )
{
operator delete(*(void **)(v3 + 24));
v11 = *(_DWORD *)(v3 + 32);
v12 = *(_DWORD *)(v3 + 8);
*(_DWORD *)(v3 + 32) = v11 + 4;
v13 = *(_DWORD *)(v11 + 4);
v8 = (_BYTE *)(v12 + v6);
*(_DWORD *)(v3 + 28) = v13 + 512;
*(_DWORD *)(v3 + 24) = v13;
*(_DWORD *)(v3 + 20) = v13;
}
else
{
*(_DWORD *)(v3 + 20) = v5 + 1;
}
*v8 = 0;
pthread_mutex_unlock((pthread_mutex_t *)(v3 + 52));
result = (void *)(*(_DWORD *)(v3 + 4) + 20 * v6);
v14 = result;
if ( result )
{
result = (void *)OneData::setDataId((int)result, v4);
v10 = (_DWORD *)*((_DWORD *)v2 + 19);
if ( v10 == (_DWORD *)(*((_DWORD *)v2 + 21) - 4) )
{
result = std::deque<OneData *,std::allocator<OneData *>>::_M_push_back_aux((void **)v2 + 13, &v14);
}
else
{
if ( v10 )
{
*v10 = v14;
v10 = (_DWORD *)*((_DWORD *)v2 + 19);
}
*((_DWORD *)v2 + 19) = v10 + 1;
}
}
return result;
}

//----- (00028D20) --------------------------------------------------------
void *__fastcall std::deque<OneFile *,std::allocator<OneFile *>>::_M_push_back_aux(void **a1, _DWORD *a2)
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

//----- (00028E98) --------------------------------------------------------
void __fastcall std::deque<OneData *,std::allocator<OneData *>>::_M_pop_front_aux(int a1)
{
_DWORD *v1; // r4
int v2; // r3
int v3; // r3

v1 = (_DWORD *)a1;
operator delete(*(void **)(a1 + 12));
v2 = v1[5];
v1[5] = v2 + 4;
v3 = *(_DWORD *)(v2 + 4);
v1[4] = v3 + 512;
v1[3] = v3;
v1[2] = v3;
}

//----- (00028ECC) --------------------------------------------------------
void __fastcall std::deque<OneFile *,std::allocator<OneFile *>>::_M_pop_front_aux(int a1)
{
_DWORD *v1; // r4
int v2; // r3
int v3; // r3

v1 = (_DWORD *)a1;
operator delete(*(void **)(a1 + 12));
v2 = v1[5];
v1[5] = v2 + 4;
v3 = *(_DWORD *)(v2 + 4);
v1[4] = v3 + 512;
v1[3] = v3;
v1[2] = v3;
}

//----- (00028F00) --------------------------------------------------------
int *__fastcall std::deque<OneFile *,std::allocator<OneFile *>>::erase(int *a1, _DWORD *a2, _DWORD *a3)
{
char *v3; // r8
int v4; // r12
char *v5; // r6
char *v6; // r1
char *v7; // r4
int v8; // r9
bool v9; // zf
int v10; // r1
int v11; // r10
int v12; // r0
char *v13; // r11
int v14; // r5
int v15; // r0
int v16; // r2
char *v17; // r3
int v18; // r5
int v19; // r7
int v20; // r1
unsigned int v21; // r0
int v22; // r12
int v23; // r3
int v24; // r11
char *v25; // r9
int v26; // r8
int v27; // r12
char *v28; // t1
int v29; // r7
unsigned int v30; // r3
int v31; // r10
char *v32; // r3
int v33; // r7
signed int v34; // r5
int v35; // r1
char *v36; // r0
int v37; // r2
int v38; // r3
int v39; // ST04_4
int v40; // r10
unsigned int v41; // r6
int v42; // r3
int v43; // r10
int v44; // r5
int v45; // r12
char *v46; // r11
int v47; // r3
int v48; // r2
int v49; // r2
unsigned int v50; // r1
int v51; // r5
int v52; // r9
int v53; // ST08_4
int v54; // ST04_4
int v55; // r4
unsigned int v56; // r9
int v57; // r0
int v58; // r6
int v59; // r4
int v60; // r3
int *result; // r0
unsigned int v62; // r3
int v63; // t1
int v64; // r1
int v65; // r1
_DWORD *v66; // [sp+Ch] [bp-4Ch]
char *v67; // [sp+10h] [bp-48h]
int *v68; // [sp+14h] [bp-44h]
int v69; // [sp+18h] [bp-40h]
int v70; // [sp+1Ch] [bp-3Ch]
int v71; // [sp+20h] [bp-38h]
int v72; // [sp+24h] [bp-34h]
char *v73; // [sp+28h] [bp-30h]
int v74; // [sp+2Ch] [bp-2Ch]

v5 = (char *)*a3;
v66 = a2;
v6 = (char *)a3[2];
v7 = (char *)(*a3 + 4);
v8 = a3[3];
v9 = v6 == v7;
v72 = a3[2];
if ( v6 == v7 )
{
v4 = v8 + 4;
v7 = *(char **)(v8 + 4);
}
v67 = (char *)a3[1];
if ( v6 == v5 + 4 )
{
v69 = (int)(v7 + 512);
v3 = v7;
}
else
{
v4 = a3[2];
}
if ( v6 == v5 + 4 )
v70 = v4;
else
v69 = v4;
v10 = v66[9];
v11 = v5 - v67;
v68 = a1;
v12 = v66[5];
v73 = (char *)v66[7];
v13 = (char *)v66[6];
v14 = v8 - v12;
v74 = v10;
v15 = v10 - v12;
v16 = v66[4];
v17 = (char *)v66[2];
v18 = (v14 >> 2) - 1;
v19 = (signed int)&v13[-v66[7]] >> 2;
v20 = (v16 - (signed int)v17) >> 2;
v21 = v20 + v19 + (((v15 >> 2) - 1) << 7);
v22 = ((v5 - v67) >> 2) + (v18 << 7) + v20;
if ( !v9 )
{
v70 = v8;
v3 = v67;
}
v71 = ((v5 - v67) >> 2) + (v18 << 7) + v20;
if ( v22 >= v21 >> 1 )
{
if ( v13 != v7 )
{
v43 = v19 + ((((v74 - v70) >> 2) - 1) << 7) + ((v69 - (signed int)v7) >> 2);
if ( v43 > 0 )
{
v44 = v69 - (_DWORD)v7;
v45 = v72;
v46 = v67;
v47 = v8;
while ( 1 )
{
v51 = v44 >> 2;
if ( v51 >= (v45 - (signed int)v5) >> 2 )
v51 = (v45 - (signed int)v5) >> 2;
if ( v51 >= v43 )
v51 = v43;
v52 = (int)&v7[4 * v51];
if ( 4 * v51 >> 2 )
{
v53 = v47;
v54 = v45;
memmove(v5, v7, 4 * (4 * v51 >> 2));
v45 = v54;
v47 = v53;
}
v55 = v51 + ((v7 - v3) >> 2);
if ( (unsigned int)v55 > 0x7F )
{
if ( v55 <= 0 )
v56 = ~((unsigned int)~v55 >> 7);
else
v56 = v55 >> 7;
v48 = 4 * v56;
v3 = *(char **)(v70 + 4 * v56);
v52 = (int)&v3[4 * (v55 - (v56 << 7))];
v70 += v48;
v69 = (int)(v3 + 512);
}
v49 = v51 + ((v5 - v46) >> 2);
if ( (unsigned int)v49 > 0x7F )
{
v50 = v49 <= 0 ? ~((unsigned int)~v49 >> 7) : v49 >> 7;
v46 = *(char **)(v47 + 4 * v50);
v47 += 4 * v50;
v45 = (int)(v46 + 512);
v5 = &v46[4 * (v49 - (v50 << 7))];
}
else
{
v5 += 4 * v51;
}
v43 -= v51;
if ( v43 <= 0 )
break;
v7 = (char *)v52;
v44 = v69 - v52;
}
v13 = (char *)v66[6];
v73 = (char *)v66[7];
}
}
if ( v13 == v73 )
{
operator delete(v13);
v64 = v66[9];
v42 = v66[2];
v66[9] = v64 - 4;
v65 = *(_DWORD *)(v64 - 4);
v16 = v66[4];
v66[7] = v65;
v66[8] = v65 + 512;
v66[6] = v65 + 508;
}
else
{
v42 = v66[2];
v16 = v66[4];
v66[6] = v13 - 4;
}
}
else
{
if ( v5 != v17 && v22 > 0 )
{
v23 = v8;
v24 = v70;
v25 = v3;
v26 = ((v5 - v67) >> 2) + (v18 << 7) + v20;
v27 = v23;
while ( 1 )
{
v31 = v11 >> 2;
v32 = v5;
if ( !v31 )
v20 = *(_DWORD *)(v27 - 4);
v33 = (v7 - v25) >> 2;
if ( v31 )
v34 = v31;
else
v34 = 128;
if ( v31 )
v35 = (int)v5;
else
v35 = v20 + 512;
if ( !v31 )
v32 = (char *)v35;
if ( v33 )
{
v37 = (v7 - v25) >> 2;
v36 = v7;
}
else
{
v36 = *(char **)(v24 - 4);
v37 = 128;
}
if ( !v33 )
v36 += 512;
if ( v34 >= v26 )
v34 = v26;
if ( v34 >= v37 )
v34 = v37;
v20 = v35 - 4 * v34;
v38 = (signed int)&v32[-v20] >> 2;
if ( v38 )
{
v39 = v27;
memmove(&v36[-4 * v38], (const void *)v20, 4 * v38);
v27 = v39;
}
v40 = v31 - v34;
if ( (unsigned int)v40 > 0x7F )
{
v41 = v40 <= 0 ? ~((unsigned int)~v40 >> 7) : v40 >> 7;
v28 = *(char **)(v27 + 4 * v41);
v27 += 4 * v41;
v5 = &v28[4 * (v40 - (v41 << 7))];
v67 = v28;
}
else
{
v5 -= 4 * v34;
}
v29 = v33 - v34;
if ( (unsigned int)v29 > 0x7F )
{
v30 = v29 <= 0 ? ~((unsigned int)~v29 >> 7) : v29 >> 7;
v25 = *(char **)(v24 + 4 * v30);
v24 += 4 * v30;
v7 = &v25[4 * (v29 - (v30 << 7))];
}
else
{
v7 -= 4 * v34;
}
v26 -= v34;
if ( v26 <= 0 )
break;
v11 = v5 - v67;
}
v17 = (char *)v66[2];
v16 = v66[4];
}
if ( v17 == (char *)(v16 - 4) )
{
std::deque<OneFile *,std::allocator<OneFile *>>::_M_pop_front_aux((int)v66);
v42 = v66[2];
v16 = v66[4];
}
else
{
v42 = (int)(v17 + 4);
v66[2] = v42;
}
}
v57 = v66[3];
v58 = v66[5];
v59 = v71 + ((v42 - v57) >> 2);
if ( (unsigned int)v59 > 0x7F )
{
if ( v59 <= 0 )
v62 = ~((unsigned int)~v59 >> 7);
else
v62 = v59 >> 7;
v63 = *(_DWORD *)(v58 + 4 * v62);
v58 += 4 * v62;
v57 = v63;
v60 = v63 + 4 * (v59 - (v62 << 7));
v16 = v63 + 512;
}
else
{
v60 = v42 + 4 * v71;
}
v68[1] = v57;
v68[2] = v16;
v68[3] = v58;
result = v68;
*v68 = v60;
return result;
}

//----- (00029354) --------------------------------------------------------
void __fastcall std::deque<long,std::allocator<long>>::_M_reallocate_map(void **a1, unsigned int a2, int a3)
{
unsigned int v3; // r7
unsigned int v4; // r12
void **v5; // r4
char *v6; // r1
int v7; // r9
unsigned int v8; // r3
int v9; // r6
int v10; // r8
unsigned int v11; // r3
int v12; // r1
int v13; // r3
char *v14; // r5
int v15; // r10
unsigned int v16; // r10
char *v17; // r0
_BYTE *v18; // r1
unsigned int v19; // r8
int v20; // r2
char *v21; // r11
int v22; // r6
int v23; // r3
int v24; // r3
int v25; // r1

v3 = a2;
v4 = (unsigned int)a1[5];
v5 = a1;
v6 = (char *)a1[9];
v7 = a3;
v8 = (unsigned int)a1[1];
v9 = ((signed int)&v6[-v4] >> 2) + 1;
v10 = v9 + v3;
if ( v8 <= 2 * (v9 + v3) )
{
v15 = v8 + 2;
if ( v3 < v8 )
v16 = v15 + v8;
else
v16 = v15 + v3;
if ( v16 > 0x3FFFFFFF )
sub_BFA08();
v17 = (char *)operator new(4 * v16);
v18 = v5[5];
v19 = (v16 - v10) >> 1;
if ( v7 )
v7 = 4 * v3;
v20 = ((_BYTE *)v5[9] + 4 - v18) >> 2;
v21 = v17;
v14 = &v17[4 * v19 + v7];
if ( v20 )
memmove(&v17[4 * v19 + v7], v18, 4 * v20);
operator delete(*v5);
*v5 = v21;
v5[1] = (void *)v16;
}
else
{
v11 = v8 - v10;
if ( a3 )
v7 = 4 * v3;
v12 = (int)&v6[-v4 + 4];
v13 = 4 * (v11 >> 1);
v14 = (char *)*a1 + v7 + v13;
if ( v4 <= (unsigned int)v14 )
{
v25 = v12 >> 2;
if ( v25 )
memmove(&v14[4 * v9 + -4 * v25], a1[5], 4 * v25);
}
else if ( v12 >> 2 )
{
memmove((char *)*a1 + v7 + v13, a1[5], 4 * (v12 >> 2));
}
}
v5[5] = v14;
v22 = v9 + 0x3FFFFFFF;
v23 = *(_DWORD *)v14;
v5[9] = &v14[4 * v22];
v5[4] = (void *)(v23 + 512);
v5[3] = (void *)v23;
v24 = *(_DWORD *)&v14[4 * v22];
v5[8] = (void *)(v24 + 512);
v5[7] = (void *)v24;
}

//----- (000294A0) --------------------------------------------------------
int __fastcall LocalMemory::moveOnStep(LocalMemory *this)
{
    pthread_mutex_t *v1; // r6
    LocalMemory *v2; // r4
    int v3; // r5
    void **v4; // r3
    void *v5; // r7
    int *v6; // r2
    int v7; // r5
    int v8; // r4
    int v9; // r5
    int v11; // r3
    int v12; // r8
    int v13; // r3
    int v14; // r3
    int v15; // r3
    bool v16; // zf
    int v17; // r3
    int v18; // r8
    int *v19; // r3
    int v20; // r3
    int v21; // r3

    v1 = (pthread_mutex_t *)((char *)this + 92);
    v2 = this;
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 92));
    v3 = *((_DWORD *)v2 + 25);
    v4 = *(void ***)(v3 + 8);
    v5 = *v4;
    if ( v4 == (void **)(*(_DWORD *)(v3 + 16) - 4) )
    {
        operator delete(*(void **)(v3 + 12));
        v13 = *(_DWORD *)(v3 + 20);
        *(_DWORD *)(v3 + 20) = v13 + 4;
        v14 = *(_DWORD *)(v13 + 4);
        *(_DWORD *)(v3 + 16) = v14 + 512;
        *(_DWORD *)(v3 + 12) = v14;
        *(_DWORD *)(v3 + 8) = v14;
    }
    else
    {
        *(_DWORD *)(v3 + 8) = v4 + 1;
    }
    operator delete(v5);
    v6 = (int *)*((_DWORD *)v2 + 15);
    v7 = *v6;
    if ( v6 == (int *)(*((_DWORD *)v2 + 17) - 4) )
    std::deque<OneData *,std::allocator<OneData *>>::_M_pop_front_aux((int)v2 + 52);
    else
    *((_DWORD *)v2 + 15) = v6 + 1;
    v8 = *((_DWORD *)v2 + 2);
    v9 = -858993459 * ((v7 - *(_DWORD *)(v8 + 4)) >> 2);
    if ( v9 < 0 || v9 >= *(_DWORD *)v8 || *(_BYTE *)(*(_DWORD *)(v8 + 8) + v9) )
    return pthread_mutex_unlock(v1);
    pthread_mutex_lock((pthread_mutex_t *)(v8 + 52));
    v11 = *(_DWORD *)(v8 + 8);
    v12 = *(unsigned __int8 *)(v11 + v9);
    if ( !*(_BYTE *)(v11 + v9) )
    {
        OneData::reset((OneData *)(*(_DWORD *)(v8 + 4) + 20 * v9));
        v15 = *(_DWORD *)(v8 + 36);
        if ( v15 == *(_DWORD *)(v8 + 44) - 4 )
        {
            if ( (unsigned int)(*(_DWORD *)(v8 + 16) - ((*(_DWORD *)(v8 + 48) - *(_DWORD *)(v8 + 12)) >> 2)) <= 1 )
                std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)(v8 + 12), 1u, v12);
            v18 = *(_DWORD *)(v8 + 48);
            *(_DWORD *)(v18 + 4) = operator new(0x200u);
            v19 = *(int **)(v8 + 36);
            if ( v19 )
                *v19 = v9;
            v20 = *(_DWORD *)(v8 + 48);
            *(_DWORD *)(v8 + 48) = v20 + 4;
            v21 = *(_DWORD *)(v20 + 4);
            *(_DWORD *)(v8 + 44) = v21 + 512;
            *(_DWORD *)(v8 + 40) = v21;
            *(_DWORD *)(v8 + 36) = v21;
        }
        else
        {
            v16 = v15 == 0;
            v17 = v15 + 4;
            if ( !v16 )
                *(_DWORD *)(v17 - 4) = v9;
            *(_DWORD *)(v8 + 36) = v17;
        }
        *(_BYTE *)(*(_DWORD *)(v8 + 8) + v9) = 1;
    }
    pthread_mutex_unlock((pthread_mutex_t *)(v8 + 52));
    return pthread_mutex_unlock(v1);
}

//----- (0002966C) --------------------------------------------------------
int __fastcall LocalMemory::addIncompletePendingData(int *a1, unsigned int *a2, int a3)
{
    LocalMemory *v3; // r5
    int v4; // r1
    int v5; // r2
    unsigned int v6; // r4
    unsigned int v7; // r7
    OneFile *v8; // r6
    int v9; // r0
    unsigned int v10; // r3
    int v11; // r3
    OneFile **v12; // r2
    unsigned int v13; // r0
    int v14; // r2
    int v15; // r3
    int v16; // lr
    int v17; // r12
    int v18; // r7
    int v19; // r2
    unsigned int v20; // r3
    int v21; // r2
    int v22; // t1
    int v23; // r7
    int size; // r11
    int v25; // r4
    signed int v26; // r2
    int v27; // r0
    unsigned int v28; // r3
    bool v29; // cf
    bool v30; // zf
    int v31; // r4
    int v32; // r5
    _DWORD *v34; // r3
    int v35; // r0
    int v36; // r2
    int v37; // r12
    int v38; // r3
    int v39; // r2
    unsigned int v40; // r1
    _DWORD *v41; // r3
    int v42; // r2
    int v43; // r12
    int v44; // r3
    int v45; // r2
    void (*v46)(void); // r3
    unsigned int v47; // r1
    _DWORD *v48; // r3
    int v49; // r2
    int v50; // r0
    int v51; // r3
    int v52; // r2
    _DWORD *v53; // r3
    int v54; // r2
    int v55; // r12
    int v56; // r3
    int v57; // r2
    unsigned int v58; // r2
    unsigned int v59; // r1
    unsigned int v60; // r2
    unsigned int v61; // r1
    int v62; // r3
    int v63; // r3
    int v64; // r7
    int *v65; // r3
    int v66; // r3
    int v67; // r3
    unsigned int *v68; // [sp+8h] [bp-68h]
    int v69; // [sp+Ch] [bp-64h]
    pthread_mutex_t *mutex; // [sp+10h] [bp-60h]
    _DWORD *v71; // [sp+14h] [bp-5Ch]
    char v72; // [sp+18h] [bp-58h]
    int v73; // [sp+2Ch] [bp-44h]
    unsigned __int8 *v74; // [sp+30h] [bp-40h]
    int v75; // [sp+34h] [bp-3Ch]
    int v76; // [sp+38h] [bp-38h]
    int v77; // [sp+3Ch] [bp-34h]
    int v78; // [sp+40h] [bp-30h]

    v3 = (LocalMemory *)a1;
    v68 = a2;
    v69 = a3;
    mutex = (pthread_mutex_t *)(a1 + 23);
    pthread_mutex_lock((pthread_mutex_t *)(a1 + 23));
    v71 = (_DWORD *)LocalMemory::locatePieceData(v3, *v68, &v73);
    if ( !v71 )
        goto LABEL_62;
    if ( v69 == 2 )
    {
        v48 = (_DWORD *)*((_DWORD *)v3 + 25);
        v49 = v48[2];
        v50 = v48[5];
        v51 = v73 + ((v49 - v48[3]) >> 2);
        if ( (unsigned int)v51 > 0x7F )
        {
            if ( v51 <= 0 )
                v58 = ~((unsigned int)~v51 >> 7);
            else
                v58 = v51 >> 7;
            if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v50 + 4 * v58) + 4 * (v51 - (v58 << 7))) + 4) != 4 )
            {
                if ( v51 <= 0 )
                    v59 = ~((unsigned int)~v51 >> 7);
                else
                    v59 = v51 >> 7;
                v52 = *(_DWORD *)(v50 + 4 * v59) + 4 * (v51 - (v59 << 7));
                goto LABEL_58;
            }
        }
        else if ( *(_BYTE *)(*(_DWORD *)(v49 + 4 * v73) + 4) != 4 )
        {
            v52 = v49 + 4 * v73;
            LABEL_58:
            if ( *(_BYTE *)(*(_DWORD *)v52 + 4) != 3 )
            goto LABEL_4;
            addCdnAndThirdDuplicateBytes(v68[2]);
            pthread_mutex_unlock(mutex);
            return 0;
        }
        addCdnAndP2PDuplicateBytes(v68[2]);
        pthread_mutex_unlock(mutex);
        return 0;
    }
    if ( v69 == 3 )
    {
        v53 = (_DWORD *)*((_DWORD *)v3 + 25);
        v54 = v53[2];
        v55 = v53[5];
        v56 = v73 + ((v54 - v53[3]) >> 2);
        if ( (unsigned int)v56 > 0x7F )
        {
            if ( v56 <= 0 )
                v60 = ~((unsigned int)~v56 >> 7);
            else
                v60 = v56 >> 7;
            if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v55 + 4 * v60) + 4 * (v56 - (v60 << 7))) + 4) != 2 )
            {
                if ( v56 <= 0 )
                    v61 = ~((unsigned int)~v56 >> 7);
                else
                    v61 = v56 >> 7;
                v57 = *(_DWORD *)(v55 + 4 * v61) + 4 * (v56 - (v61 << 7));
                goto LABEL_67;
            }
        }
        else if ( *(_BYTE *)(*(_DWORD *)(v54 + 4 * v73) + 4) != 2 )
        {
            v57 = v54 + 4 * v73;
            LABEL_67:
            if ( *(_BYTE *)(*(_DWORD *)v57 + 4) != 4 )
            goto LABEL_4;
            addThirdAndP2PDuplicateBytes(v68[2]);
            pthread_mutex_unlock(mutex);
            return 0;
        }
        addThirdAndCDNDuplicateBytes(v68[2]);
        pthread_mutex_unlock(mutex);
        return 0;
    }
    LABEL_4:
    v4 = *((_DWORD *)v3 + 8);
    v5 = *((_DWORD *)v3 + 5);
    if ( ((*((_DWORD *)v3 + 9) - *((_DWORD *)v3 + 10)) >> 2)
    + ((((*((_DWORD *)v3 + 12) - v4) >> 2) - 1) << 7)
    + ((*((_DWORD *)v3 + 7) - v5) >> 2) )
    {
        v6 = 0;
        v7 = 0;
        while ( 1 )
        {
            v11 = v7 + ((v5 - *((_DWORD *)v3 + 6)) >> 2);
            if ( (unsigned int)v11 > 0x7F )
            {
                v13 = v11 <= 0 ? ~((unsigned int)~v11 >> 7) : v11 >> 7;
                v12 = (OneFile **)(*(_DWORD *)(v4 + 4 * v13) + 4 * (v11 - (v13 << 7)));
            }
            else
            {
                v12 = (OneFile **)(v5 + 4 * v6);
            }
            v8 = *v12;
            v9 = OneFile::getFileId(*v12);
            v10 = *v68;
            if ( v9 == *v68 )
                break;
            v4 = *((_DWORD *)v3 + 8);
            v6 = ++v7;
            v5 = *((_DWORD *)v3 + 5);
            if ( v7 >= ((*((_DWORD *)v3 + 9) - *((_DWORD *)v3 + 10)) >> 2)
            + ((((*((_DWORD *)v3 + 12) - v4) >> 2) - 1) << 7)
            + ((*((_DWORD *)v3 + 7) - v5) >> 2) )
            goto LABEL_61;
        }
        v14 = *((_DWORD *)v3 + 5);
        v15 = *((_DWORD *)v3 + 6);
        v16 = *((_DWORD *)v3 + 7);
        v17 = *((_DWORD *)v3 + 8);
        v18 = v7 + ((v14 - v15) >> 2);
        if ( (unsigned int)v18 > 0x7F )
        {
            if ( v18 <= 0 )
                v20 = ~((unsigned int)~v18 >> 7);
            else
                v20 = v18 >> 7;
            v21 = v18 - (v20 << 7);
            v22 = *(_DWORD *)(v17 + 4 * v20);
            v17 += 4 * v20;
            v15 = v22;
            v19 = v22 + 4 * v21;
            v16 = v22 + 512;
        }
        else
        {
            v19 = v14 + 4 * v6;
        }
        v75 = v19;
        v76 = v15;
        v77 = v16;
        v78 = v17;
        std::deque<OneFile *,std::allocator<OneFile *>>::erase((int *)&v72, (_DWORD *)v3 + 3, &v75);
        if ( v8 )
        {
            v23 = OneFile::getPacketNumb(v8);
            size = OneFile::getTotalSize(v8) + v68[2];
            OneData::OneData((int)&v75);
            OneData::setDataId((int)&v75, *v68);
            if ( v23 > 0 )
            {
                v25 = 0;
                do
                {
                    v74 = 0;
                    v26 = OneFile::getPacketContent(v8, &v74, (unsigned __int16)v25);
                    if ( v26 > 0 )
                        OneData::cacheData((OneData *)&v75, v74, v26, v25, size);
                    ++v25;
                }
                while ( v25 != v23 );
            }
            OneData::cacheData((OneData *)&v75, (unsigned __int8 *)v68[3], v68[2], v23, size);
            OneData::setDataLength((int)&v75, size);
            v27 = AcquireChannelPlayInfo::isDataValid((LinkManager *)&v75);
            if ( v27 == 1 )
            {
                add_FlvP2pLenVerifyFailCount();
                (*((void (__fastcall **)(unsigned int))v3 + 26))(*v68);
            }
            else if ( v27 == 4 )
            {
                add_FlvP2pDataVerifyFailCount();
                (*((void (__fastcall **)(unsigned int))v3 + 26))(*v68);
            }
            else
            {
                v28 = v27 - 2;
                v29 = 1;
                v30 = v27 == 0;
                if ( v27 )
                {
                    v29 = v28 >= 1;
                    v30 = v28 == 1;
                }
                if ( v30 || !v29 )
                {
                    OneData::setDataInfo(v71, &v75);
                    v34 = (_DWORD *)*((_DWORD *)v3 + 25);
                    v35 = v73;
                    v36 = v34[2];
                    v37 = v34[5];
                    v38 = v73 + ((v36 - v34[3]) >> 2);
                    if ( (unsigned int)v38 > 0x7F )
                    {
                        if ( v38 <= 0 )
                            v40 = ~((unsigned int)~v38 >> 7);
                        else
                            v40 = v38 >> 7;
                        v39 = *(_DWORD *)(v37 + 4 * v40) + 4 * (v38 - (v40 << 7));
                    }
                    else
                    {
                        v39 = v36 + 4 * v73;
                    }
                    *(_BYTE *)(*(_DWORD *)v39 + 4) = v69;
                    v41 = (_DWORD *)*((_DWORD *)v3 + 25);
                    v42 = v41[2];
                    v43 = v41[5];
                    v44 = v35 + ((v42 - v41[3]) >> 2);
                    if ( (unsigned int)v44 > 0x7F )
                    {
                        if ( v44 <= 0 )
                            v47 = ~((unsigned int)~v44 >> 7);
                        else
                            v47 = v44 >> 7;
                        v45 = *(_DWORD *)(v43 + 4 * v47) + 4 * (v44 - (v47 << 7));
                    }
                    else
                    {
                        v45 = v42 + 4 * v35;
                    }
                    v46 = (void (*)(void))*((_DWORD *)v3 + 24);
                    *(_DWORD *)(*(_DWORD *)v45 + 8) = size;
                    v46();
                    addCurrentPieceLength(size);
                    addCurrentPieceNum(1);
                }
            }
            OneFile::releasePackets((int)v8, *((_DWORD *)v3 + 1));
            v31 = *(_DWORD *)v3;
            v32 = -1227133513 * (((signed int)v8 - *(_DWORD *)(*(_DWORD *)v3 + 4)) >> 2);
            if ( v32 >= 0 && v32 < *(_DWORD *)v31 && !*(_BYTE *)(*(_DWORD *)(v31 + 8) + v32) )
            {
                pthread_mutex_lock((pthread_mutex_t *)(v31 + 52));
                if ( !*(_BYTE *)(*(_DWORD *)(v31 + 8) + v32) )
                {
                    OneFile::reset(*(_DWORD *)(v31 + 4) + 28 * v32);
                    v62 = *(_DWORD *)(v31 + 36);
                    if ( v62 == *(_DWORD *)(v31 + 44) - 4 )
                    {
                        v64 = *(_DWORD *)(v31 + 48);
                        if ( (unsigned int)(*(_DWORD *)(v31 + 16) - ((v64 - *(_DWORD *)(v31 + 12)) >> 2)) <= 1 )
                        {
                            std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)(v31 + 12), 1u, 0);
                            v64 = *(_DWORD *)(v31 + 48);
                        }
                        *(_DWORD *)(v64 + 4) = operator new(0x200u);
                        v65 = *(int **)(v31 + 36);
                        if ( v65 )
                            *v65 = v32;
                        v66 = *(_DWORD *)(v31 + 48);
                        *(_DWORD *)(v31 + 48) = v66 + 4;
                        v67 = *(_DWORD *)(v66 + 4);
                        *(_DWORD *)(v31 + 44) = v67 + 512;
                        *(_DWORD *)(v31 + 40) = v67;
                        *(_DWORD *)(v31 + 36) = v67;
                    }
                    else
                    {
                        v30 = v62 == 0;
                        v63 = v62 + 4;
                        if ( !v30 )
                            *(_DWORD *)(v63 - 4) = v32;
                        *(_DWORD *)(v31 + 36) = v63;
                    }
                    *(_BYTE *)(*(_DWORD *)(v31 + 8) + v32) = 1;
                }
                pthread_mutex_unlock((pthread_mutex_t *)(v31 + 52));
            }
            pthread_mutex_unlock(mutex);
            OneData::~OneData((OneData *)&v75);
            return 0;
        }
        v10 = *v68;
    }
    else
    {
        v10 = *v68;
    }
    LABEL_61:
    (*((void (__fastcall **)(unsigned int))v3 + 26))(v10);
    LABEL_62:
    pthread_mutex_unlock(mutex);
    return 0;
}

//----- (00029D2C) --------------------------------------------------------
int __fastcall LocalMemory::clearPendingData(LocalMemory *this)
{
    pthread_mutex_t *v1; // r6
    LocalMemory *v2; // r4
    char *v3; // r7
    int *v4; // r3
    int v5; // r9
    int v6; // r5
    int v7; // r9
    int v8; // r3
    int v9; // r11
    int v11; // r3
    bool v12; // zf
    int v13; // r3
    int v14; // r11
    int *v15; // r3
    int v16; // r3
    int v17; // r3

    v1 = (pthread_mutex_t *)((char *)this + 92);
    v2 = this;
    v3 = (char *)this + 52;
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 92));
    while ( 1 )
    {
        v4 = (int *)*((_DWORD *)v2 + 15);
        if ( *((int **)v2 + 19) == v4 )
            break;
        while ( 1 )
        {
            v5 = *v4;
            if ( v4 == (int *)(*((_DWORD *)v2 + 17) - 4) )
            std::deque<OneData *,std::allocator<OneData *>>::_M_pop_front_aux((int)v3);
            else
            *((_DWORD *)v2 + 15) = v4 + 1;
            v6 = *((_DWORD *)v2 + 2);
            v7 = -858993459 * ((v5 - *(_DWORD *)(v6 + 4)) >> 2);
            if ( v7 < 0 || v7 >= *(_DWORD *)v6 || *(_BYTE *)(*(_DWORD *)(v6 + 8) + v7) )
            break;
            pthread_mutex_lock((pthread_mutex_t *)(v6 + 52));
            v8 = *(_DWORD *)(v6 + 8);
            v9 = *(unsigned __int8 *)(v8 + v7);
            if ( !*(_BYTE *)(v8 + v7) )
            {
                OneData::reset((OneData *)(*(_DWORD *)(v6 + 4) + 20 * v7));
                v11 = *(_DWORD *)(v6 + 36);
                if ( v11 == *(_DWORD *)(v6 + 44) - 4 )
                {
                    if ( (unsigned int)(*(_DWORD *)(v6 + 16) - ((*(_DWORD *)(v6 + 48) - *(_DWORD *)(v6 + 12)) >> 2)) <= 1 )
                        std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)(v6 + 12), 1u, v9);
                    v14 = *(_DWORD *)(v6 + 48);
                    *(_DWORD *)(v14 + 4) = operator new(0x200u);
                    v15 = *(int **)(v6 + 36);
                    if ( v15 )
                        *v15 = v7;
                    v16 = *(_DWORD *)(v6 + 48);
                    *(_DWORD *)(v6 + 48) = v16 + 4;
                    v17 = *(_DWORD *)(v16 + 4);
                    *(_DWORD *)(v6 + 44) = v17 + 512;
                    *(_DWORD *)(v6 + 40) = v17;
                    *(_DWORD *)(v6 + 36) = v17;
                }
                else
                {
                    v12 = v11 == 0;
                    v13 = v11 + 4;
                    if ( !v12 )
                        *(_DWORD *)(v13 - 4) = v7;
                    *(_DWORD *)(v6 + 36) = v13;
                }
                *(_BYTE *)(*(_DWORD *)(v6 + 8) + v7) = 1;
            }
            pthread_mutex_unlock((pthread_mutex_t *)(v6 + 52));
            v4 = (int *)*((_DWORD *)v2 + 15);
            if ( *((int **)v2 + 19) == v4 )
                return pthread_mutex_unlock(v1);
        }
    }
    return pthread_mutex_unlock(v1);
}

//----- (00029EB4) --------------------------------------------------------
int __fastcall LocalMemory::recycleOneFile(int result, OneFile *a2)
{
    OneFile *v2; // r6
    int *v3; // r4
    int v4; // r4
    int v5; // r5
    int v6; // r3
    int v7; // r7
    int v8; // r3
    bool v9; // zf
    int v10; // r3
    int v11; // r7
    int *v12; // r3
    int v13; // r3
    int v14; // r3

    v2 = a2;
    v3 = (int *)result;
    if ( a2 )
    {
        result = OneFile::releasePackets((int)a2, *(_DWORD *)(result + 4));
        v4 = *v3;
        v5 = -1227133513 * (((signed int)v2 - *(_DWORD *)(v4 + 4)) >> 2);
        if ( v5 >= 0
             && v5 < *(_DWORD *)v4
                                && !*(_BYTE *)(*(_DWORD *)(v4 + 8) - 1227133513 * (((signed int)v2 - *(_DWORD *)(v4 + 4)) >> 2)) )
        {
            pthread_mutex_lock((pthread_mutex_t *)(v4 + 52));
            v6 = *(_DWORD *)(v4 + 8);
            v7 = *(unsigned __int8 *)(v6 + v5);
            if ( !*(_BYTE *)(v6 + v5) )
            {
                OneFile::reset(*(_DWORD *)(v4 + 4) + 28 * v5);
                v8 = *(_DWORD *)(v4 + 36);
                if ( v8 == *(_DWORD *)(v4 + 44) - 4 )
                {
                    if ( (unsigned int)(*(_DWORD *)(v4 + 16) - ((*(_DWORD *)(v4 + 48) - *(_DWORD *)(v4 + 12)) >> 2)) <= 1 )
                        std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)(v4 + 12), 1u, v7);
                    v11 = *(_DWORD *)(v4 + 48);
                    *(_DWORD *)(v11 + 4) = operator new(0x200u);
                    v12 = *(int **)(v4 + 36);
                    if ( v12 )
                        *v12 = v5;
                    v13 = *(_DWORD *)(v4 + 48);
                    *(_DWORD *)(v4 + 48) = v13 + 4;
                    v14 = *(_DWORD *)(v13 + 4);
                    *(_DWORD *)(v4 + 44) = v14 + 512;
                    *(_DWORD *)(v4 + 40) = v14;
                    *(_DWORD *)(v4 + 36) = v14;
                }
                else
                {
                    v9 = v8 == 0;
                    v10 = v8 + 4;
                    if ( !v9 )
                        *(_DWORD *)(v10 - 4) = v5;
                    *(_DWORD *)(v4 + 36) = v10;
                }
                *(_BYTE *)(*(_DWORD *)(v4 + 8) + v5) = 1;
            }
            result = pthread_mutex_unlock((pthread_mutex_t *)(v4 + 52));
        }
    }
    return result;
}

//----- (00029FEC) --------------------------------------------------------
int __fastcall LocalMemory::clearIncompletePendingFile(LocalMemory *this)
{
    pthread_mutex_t *v1; // r8
    int *v2; // r4
    char *v3; // r9
    int *v4; // r3
    int v5; // r6
    int v6; // r5
    int v7; // r6
    int v8; // r3
    int v10; // r3
    bool v11; // zf
    int v12; // r3
    int v13; // r3
    int *v14; // r3
    int v15; // r3
    int v16; // r3
    int v17; // [sp+4h] [bp-2Ch]

    v1 = (pthread_mutex_t *)((char *)this + 92);
    v2 = (int *)this;
    v3 = (char *)this + 12;
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 92));
    while ( 1 )
    {
        v4 = (int *)v2[5];
        if ( (int *)v2[9] == v4 )
            break;
        while ( 1 )
        {
            v5 = *v4;
            if ( v4 == (int *)(v2[7] - 4) )
                std::deque<OneFile *,std::allocator<OneFile *>>::_M_pop_front_aux((int)v3);
            else
                v2[5] = (int)(v4 + 1);
            OneFile::releasePackets(v5, v2[1]);
            v6 = *v2;
            v7 = -1227133513 * ((v5 - *(_DWORD *)(*v2 + 4)) >> 2);
            if ( v7 < 0 || v7 >= *(_DWORD *)v6 || *(_BYTE *)(*(_DWORD *)(v6 + 8) + v7) )
            break;
            pthread_mutex_lock((pthread_mutex_t *)(v6 + 52));
            v8 = *(_DWORD *)(v6 + 8);
            if ( !*(_BYTE *)(v8 + v7) )
            {
                v17 = *(unsigned __int8 *)(v8 + v7);
                OneFile::reset(*(_DWORD *)(v6 + 4) + 28 * v7);
                v10 = *(_DWORD *)(v6 + 36);
                if ( v10 == *(_DWORD *)(v6 + 44) - 4 )
                {
                    v13 = *(_DWORD *)(v6 + 48);
                    if ( (unsigned int)(*(_DWORD *)(v6 + 16) - ((v13 - *(_DWORD *)(v6 + 12)) >> 2)) <= 1 )
                    {
                        std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)(v6 + 12), 1u, v17);
                        v13 = *(_DWORD *)(v6 + 48);
                    }
                    *(_DWORD *)(v13 + 4) = operator new(0x200u);
                    v14 = *(int **)(v6 + 36);
                    if ( v14 )
                        *v14 = v7;
                    v15 = *(_DWORD *)(v6 + 48);
                    *(_DWORD *)(v6 + 48) = v15 + 4;
                    v16 = *(_DWORD *)(v15 + 4);
                    *(_DWORD *)(v6 + 44) = v16 + 512;
                    *(_DWORD *)(v6 + 40) = v16;
                    *(_DWORD *)(v6 + 36) = v16;
                }
                else
                {
                    v11 = v10 == 0;
                    v12 = v10 + 4;
                    if ( !v11 )
                        *(_DWORD *)(v12 - 4) = v7;
                    *(_DWORD *)(v6 + 36) = v12;
                }
                *(_BYTE *)(*(_DWORD *)(v6 + 8) + v7) = 1;
            }
            pthread_mutex_unlock((pthread_mutex_t *)(v6 + 52));
            v4 = (int *)v2[5];
            if ( (int *)v2[9] == v4 )
                return pthread_mutex_unlock(v1);
        }
    }
    return pthread_mutex_unlock(v1);
}

//----- (0002A18C) --------------------------------------------------------
LocalMemory *__fastcall LocalMemory::~LocalMemory(LocalMemory *this)
{
    LocalMemory *v1; // r4

    v1 = this;
    LocalMemory::clearPendingData(this);
    LocalMemory::clearIncompletePendingFile(v1);
    pthread_mutex_destroy((pthread_mutex_t *)((char *)v1 + 92));
    std::_Deque_base<OneData *,std::allocator<OneData *>>::~_Deque_base((void **)v1 + 13);
    std::_Deque_base<OneFile *,std::allocator<OneFile *>>::~_Deque_base((void **)v1 + 3);
    return v1;
}

//----- (0002A1E0) --------------------------------------------------------
void *__fastcall LocalMemory::addIncompletePendingFile(LocalMemory *this, OneFile *a2)
{
    LocalMemory *v2; // r4
    void *result; // r0
    OneFile **v4; // r3
    int v5; // r4
    int v6; // r2
    int v7; // r5
    int v8; // r3
    int v9; // r7
    int v10; // r3
    bool v11; // zf
    int v12; // r3
    int v13; // r8
    int *v14; // r3
    int v15; // r3
    int v16; // r3
    OneFile *v17; // [sp+4h] [bp-1Ch]

    v2 = this;
    v17 = a2;
    result = (void *)OneFile::getTotalSize(a2);
    if ( result )
    {
        v4 = (OneFile **)*((_DWORD *)v2 + 9);
        if ( v4 == (OneFile **)(*((_DWORD *)v2 + 11) - 4) )
        {
            result = std::deque<OneFile *,std::allocator<OneFile *>>::_M_push_back_aux((void **)v2 + 3, &v17);
        }
        else
        {
            if ( v4 )
            {
                *v4 = v17;
                v4 = (OneFile **)*((_DWORD *)v2 + 9);
            }
            *((_DWORD *)v2 + 9) = v4 + 1;
        }
    }
    else
    {
        result = (void *)OneFile::releasePackets((int)v17, *((_DWORD *)v2 + 1));
        v5 = *(_DWORD *)v2;
        v6 = *(_DWORD *)(v5 + 4);
        v7 = -1227133513 * (((signed int)v17 - v6) >> 2);
        if ( v7 >= 0 && v7 < *(_DWORD *)v5 && !*(_BYTE *)(*(_DWORD *)(v5 + 8) - 1227133513 * (((signed int)v17 - v6) >> 2)) )
        {
            pthread_mutex_lock((pthread_mutex_t *)(v5 + 52));
            v8 = *(_DWORD *)(v5 + 8);
            v9 = *(unsigned __int8 *)(v8 + v7);
            if ( !*(_BYTE *)(v8 + v7) )
            {
                OneFile::reset(*(_DWORD *)(v5 + 4) + 28 * v7);
                v10 = *(_DWORD *)(v5 + 36);
                if ( v10 == *(_DWORD *)(v5 + 44) - 4 )
                {
                    v13 = *(_DWORD *)(v5 + 48);
                    if ( (unsigned int)(*(_DWORD *)(v5 + 16) - ((v13 - *(_DWORD *)(v5 + 12)) >> 2)) <= 1 )
                    {
                        std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)(v5 + 12), 1u, v9);
                        v13 = *(_DWORD *)(v5 + 48);
                    }
                    *(_DWORD *)(v13 + 4) = operator new(0x200u);
                    v14 = *(int **)(v5 + 36);
                    if ( v14 )
                        *v14 = v7;
                    v15 = *(_DWORD *)(v5 + 48);
                    *(_DWORD *)(v5 + 48) = v15 + 4;
                    v16 = *(_DWORD *)(v15 + 4);
                    *(_DWORD *)(v5 + 44) = v16 + 512;
                    *(_DWORD *)(v5 + 40) = v16;
                    *(_DWORD *)(v5 + 36) = v16;
                }
                else
                {
                    v11 = v10 == 0;
                    v12 = v10 + 4;
                    if ( !v11 )
                        *(_DWORD *)(v12 - 4) = v7;
                    *(_DWORD *)(v5 + 36) = v12;
                }
                *(_BYTE *)(*(_DWORD *)(v5 + 8) + v7) = 1;
            }
            result = (void *)pthread_mutex_unlock((pthread_mutex_t *)(v5 + 52));
        }
    }
    return result;
}

//----- (0002A36C) --------------------------------------------------------
int __fastcall LocalMemory::addPendingFile(int result, OneFile *a2)
{
    OneFile *v2; // r5
    int *v3; // r4
    pthread_mutex_t *v4; // r6
    int v5; // r0
    OneData *v6; // r7
    _DWORD *v7; // r1
    int v8; // r12
    int v9; // r3
    int v10; // r1
    int v11; // r3
    unsigned int v12; // r2
    unsigned int v13; // r2
    int v14; // r12
    int v15; // r8
    _DWORD *v16; // r3
    int v17; // r2
    int v18; // r1
    int v19; // r12
    int v20; // r3
    int v21; // r1
    _DWORD *v22; // r3
    int v23; // r1
    int v24; // r12
    int v25; // r3
    int v26; // r1
    unsigned int v27; // r0
    void (__fastcall *v28)(int); // r3
    int v29; // r4
    int v30; // r5
    int v31; // r0
    unsigned int v32; // r0
    int v33; // r3
    int v34; // r8
    int v35; // r0
    int v36; // r3
    bool v37; // zf
    int v38; // r3
    int v39; // r9
    int *v40; // r3
    int v41; // r3
    int v42; // r3
    int v43; // [sp+4h] [bp-24h]

    v2 = a2;
    v3 = (int *)result;
    if ( !a2 )
        return result;
    v4 = (pthread_mutex_t *)(result + 92);
    pthread_mutex_lock((pthread_mutex_t *)(result + 92));
    v5 = OneFile::getFileId(v2);
    v6 = (OneData *)LocalMemory::locatePieceData((LocalMemory *)v3, v5, &v43);
    if ( v6 )
    {
        v7 = (_DWORD *)v3[25];
        v8 = v7[2];
        v9 = v7[3];
        v10 = v7[5];
        v11 = v43 + ((v8 - v9) >> 2);
        if ( (unsigned int)v11 <= 0x7F )
        {
            if ( *(_BYTE *)(*(_DWORD *)(v8 + 4 * v43) + 4) != 2 )
            {
                v14 = v8 + 4 * v43;
                goto LABEL_12;
            }
        }
        else
        {
            if ( v11 <= 0 )
                v12 = ~((unsigned int)~v11 >> 7);
            else
                v12 = v11 >> 7;
            if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v10 + 4 * v12) + 4 * (v11 - (v12 << 7))) + 4) != 2 )
            {
                if ( v11 <= 0 )
                    v13 = ~((unsigned int)~v11 >> 7);
                else
                    v13 = v11 >> 7;
                v14 = *(_DWORD *)(v10 + 4 * v13) + 4 * (v11 - (v13 << 7));
                LABEL_12:
                if ( *(_BYTE *)(*(_DWORD *)v14 + 4) == 3 )
                {
                    v35 = OneFile::getTotalSize(v2);
                    addP2PAndThirdDuplicateBytes(v35);
                }
                else
                {
                    v15 = OneFile::getTotalSize(v2);
                    LocalMemory::cacheFileDataToOneData((LocalMemory *)v3, v2, v6);
                    v16 = (_DWORD *)v3[25];
                    v17 = v43;
                    v18 = v16[2];
                    v19 = v16[5];
                    v20 = v43 + ((v18 - v16[3]) >> 2);
                    if ( (unsigned int)v20 > 0x7F )
                    {
                        if ( v20 <= 0 )
                            v32 = ~((unsigned int)~v20 >> 7);
                        else
                            v32 = v20 >> 7;
                        v21 = *(_DWORD *)(v19 + 4 * v32) + 4 * (v20 - (v32 << 7));
                    }
                    else
                    {
                        v21 = v18 + 4 * v43;
                    }
                    *(_BYTE *)(*(_DWORD *)v21 + 4) = 4;
                    v22 = (_DWORD *)v3[25];
                    v23 = v22[2];
                    v24 = v22[5];
                    v25 = v17 + ((v23 - v22[3]) >> 2);
                    if ( (unsigned int)v25 > 0x7F )
                    {
                        if ( v25 <= 0 )
                            v27 = ~((unsigned int)~v25 >> 7);
                        else
                            v27 = v25 >> 7;
                        v26 = *(_DWORD *)(v24 + 4 * v27) + 4 * (v25 - (v27 << 7));
                    }
                    else
                    {
                        v26 = v23 + 4 * v17;
                    }
                    v28 = (void (__fastcall *)(int))v3[24];
                    *(_DWORD *)(*(_DWORD *)v26 + 8) = v15;
                    v28(v17);
                    addCurrentPieceLength(v15);
                    addCurrentPieceNum(1);
                }
                goto LABEL_23;
            }
        }
        v31 = OneFile::getTotalSize(v2);
        addP2PAndCDNDuplicateBytes(v31);
    }
    LABEL_23:
    OneFile::releasePackets((int)v2, v3[1]);
    v29 = *v3;
    v30 = -1227133513 * (((signed int)v2 - *(_DWORD *)(v29 + 4)) >> 2);
    if ( v30 >= 0 && v30 < *(_DWORD *)v29 && !*(_BYTE *)(*(_DWORD *)(v29 + 8) + v30) )
    {
        pthread_mutex_lock((pthread_mutex_t *)(v29 + 52));
        v33 = *(_DWORD *)(v29 + 8);
        v34 = *(unsigned __int8 *)(v33 + v30);
        if ( !*(_BYTE *)(v33 + v30) )
        {
            OneFile::reset(*(_DWORD *)(v29 + 4) + 28 * v30);
            v36 = *(_DWORD *)(v29 + 36);
            if ( v36 == *(_DWORD *)(v29 + 44) - 4 )
            {
                v39 = *(_DWORD *)(v29 + 48);
                if ( (unsigned int)(*(_DWORD *)(v29 + 16) - ((v39 - *(_DWORD *)(v29 + 12)) >> 2)) <= 1 )
                {
                    std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)(v29 + 12), 1u, v34);
                    v39 = *(_DWORD *)(v29 + 48);
                }
                *(_DWORD *)(v39 + 4) = operator new(0x200u);
                v40 = *(int **)(v29 + 36);
                if ( v40 )
                    *v40 = v30;
                v41 = *(_DWORD *)(v29 + 48);
                *(_DWORD *)(v29 + 48) = v41 + 4;
                v42 = *(_DWORD *)(v41 + 4);
                *(_DWORD *)(v29 + 44) = v42 + 512;
                *(_DWORD *)(v29 + 40) = v42;
                *(_DWORD *)(v29 + 36) = v42;
            }
            else
            {
                v37 = v36 == 0;
                v38 = v36 + 4;
                if ( !v37 )
                    *(_DWORD *)(v38 - 4) = v30;
                *(_DWORD *)(v29 + 36) = v38;
            }
            *(_BYTE *)(*(_DWORD *)(v29 + 8) + v30) = 1;
        }
        pthread_mutex_unlock((pthread_mutex_t *)(v29 + 52));
    }
    return pthread_mutex_unlock(v4);
}

//----- (0002A67C) --------------------------------------------------------
int __fastcall LocalMemory::eraseIncompletePendingFileWithId(LocalMemory *this, unsigned int a2)
{
unsigned int v2; // r7
int v3; // r2
LocalMemory *v4; // r4
int v5; // r3
int v6; // r1
int v7; // r12
int result; // r0
unsigned int v9; // r6
unsigned int v10; // r5
OneFile *v11; // r8
OneFile **v12; // r0
int v13; // r3
unsigned int v14; // r1
int v15; // r2
int v16; // r3
int v17; // lr
int v18; // r12
int v19; // r5
int v20; // r6
unsigned int v21; // r6
int v22; // t1
int v23; // r4
int v24; // r5
int v25; // r3
int v26; // r7
int v27; // r3
bool v28; // zf
int v29; // r3
int v30; // r7
int *v31; // r3
int v32; // r3
int v33; // r3
int v34; // [sp+0h] [bp-38h]
int v35; // [sp+10h] [bp-28h]
int v36; // [sp+14h] [bp-24h]
int v37; // [sp+18h] [bp-20h]
int v38; // [sp+1Ch] [bp-1Ch]

v2 = a2;
v3 = *((_DWORD *)this + 8);
v4 = this;
v5 = *((_DWORD *)this + 5);
v6 = (*((_DWORD *)this + 12) - v3) >> 2;
v7 = (*((_DWORD *)this + 9) - *((_DWORD *)this + 10)) >> 2;
result = *((_DWORD *)this + 7) - v5;
if ( v7 + ((v6 - 1) << 7) + (result >> 2) )
{
v9 = 0;
v10 = 0;
while ( 1 )
{
v12 = (OneFile **)(v5 + 4 * v9);
v13 = v10 + ((v5 - *((_DWORD *)v4 + 6)) >> 2);
if ( (unsigned int)v13 > 0x7F )
{
v14 = v13 >> 7;
if ( v13 <= 0 )
v14 = ~((unsigned int)~v13 >> 7);
v12 = (OneFile **)(*(_DWORD *)(v3 + 4 * v14) + 4 * (v13 - (v14 << 7)));
}
v11 = *v12;
if ( OneFile::getFileId(*v12) == v2 )
break;
v3 = *((_DWORD *)v4 + 8);
v9 = ++v10;
v5 = *((_DWORD *)v4 + 5);
result = *((_DWORD *)v4 + 7) - v5;
if ( v10 >= ((*((_DWORD *)v4 + 9) - *((_DWORD *)v4 + 10)) >> 2)
+ ((((*((_DWORD *)v4 + 12) - v3) >> 2) - 1) << 7)
+ (result >> 2) )
return result;
}
v15 = *((_DWORD *)v4 + 5);
v16 = *((_DWORD *)v4 + 6);
v17 = *((_DWORD *)v4 + 7);
v18 = *((_DWORD *)v4 + 8);
v19 = v10 + ((v15 - v16) >> 2);
if ( (unsigned int)v19 > 0x7F )
{
if ( v19 <= 0 )
v21 = ~((unsigned int)~v19 >> 7);
else
v21 = v19 >> 7;
v22 = *(_DWORD *)(v18 + 4 * v21);
v18 += 4 * v21;
v16 = v22;
v20 = v22 + 4 * (v19 - (v21 << 7));
v17 = v22 + 512;
}
else
{
v20 = v15 + 4 * v9;
}
v36 = v16;
v37 = v17;
v38 = v18;
v35 = v20;
std::deque<OneFile *,std::allocator<OneFile *>>::erase(&v34, (_DWORD *)v4 + 3, &v35);
result = OneFile::releasePackets((int)v11, *((_DWORD *)v4 + 1));
v23 = *(_DWORD *)v4;
v24 = -1227133513 * (((signed int)v11 - *(_DWORD *)(v23 + 4)) >> 2);
if ( v24 >= 0
&& v24 < *(_DWORD *)v23
&& !*(_BYTE *)(*(_DWORD *)(v23 + 8) - 1227133513 * (((signed int)v11 - *(_DWORD *)(v23 + 4)) >> 2)) )
{
pthread_mutex_lock((pthread_mutex_t *)(v23 + 52));
v25 = *(_DWORD *)(v23 + 8);
v26 = *(unsigned __int8 *)(v25 + v24);
if ( !*(_BYTE *)(v25 + v24) )
{
OneFile::reset(*(_DWORD *)(v23 + 4) + 28 * v24);
v27 = *(_DWORD *)(v23 + 36);
if ( v27 == *(_DWORD *)(v23 + 44) - 4 )
{
if ( (unsigned int)(*(_DWORD *)(v23 + 16) - ((*(_DWORD *)(v23 + 48) - *(_DWORD *)(v23 + 12)) >> 2)) <= 1 )
std::deque<long,std::allocator<long>>::_M_reallocate_map((void **)(v23 + 12), 1u, v26);
v30 = *(_DWORD *)(v23 + 48);
*(_DWORD *)(v30 + 4) = operator new(0x200u);
v31 = *(int **)(v23 + 36);
if ( v31 )
*v31 = v24;
v32 = *(_DWORD *)(v23 + 48);
*(_DWORD *)(v23 + 48) = v32 + 4;
v33 = *(_DWORD *)(v32 + 4);
*(_DWORD *)(v23 + 44) = v33 + 512;
*(_DWORD *)(v23 + 40) = v33;
*(_DWORD *)(v23 + 36) = v33;
}
else
{
v28 = v27 == 0;
v29 = v27 + 4;
if ( !v28 )
*(_DWORD *)(v29 - 4) = v24;
*(_DWORD *)(v23 + 36) = v29;
}
*(_BYTE *)(*(_DWORD *)(v23 + 8) + v24) = 1;
}
result = pthread_mutex_unlock((pthread_mutex_t *)(v23 + 52));
}
}
return result;
}

//----- (0002A908) --------------------------------------------------------
int __fastcall LocalMemory::addPendingData(int a1, unsigned int *a2, int a3)
{
    unsigned int *v3; // r4
    int v4; // r6
    int v5; // r7
    int v6; // r5
    pthread_mutex_t *v8; // r8
    _DWORD *v9; // r5
    _DWORD *v10; // r3
    int v11; // r0
    int v12; // r2
    int v13; // r12
    int v14; // r3
    int v15; // r2
    unsigned int v16; // r1
    _DWORD *v17; // r3
    int v18; // r2
    int v19; // r12
    int v20; // r3
    int v21; // r2
    unsigned int v22; // r1
    void (*v23)(void); // r3
    _DWORD *v24; // r2
    int v25; // r1
    int v26; // r3
    int v27; // r2
    int v28; // r3
    int v29; // r1
    _DWORD *v30; // r2
    int v31; // r1
    int v32; // r3
    int v33; // r2
    int v34; // r3
    int v35; // r1
    unsigned int v36; // r1
    unsigned int v37; // r12
    unsigned int v38; // r1
    unsigned int v39; // r0
    int v40; // [sp+4h] [bp-1Ch]

    v3 = a2;
    v4 = a1;
    v5 = a3;
    if ( !a2 )
        return (int)a2;
    if ( (signed int)a2[1] > 0 )
        return LocalMemory::addIncompletePendingData((int *)a1, a2, a3);
    v8 = (pthread_mutex_t *)(a1 + 92);
    pthread_mutex_lock((pthread_mutex_t *)(a1 + 92));
    LocalMemory::eraseIncompletePendingFileWithId((LocalMemory *)v4, *v3);
    v9 = (_DWORD *)LocalMemory::locatePieceData((LocalMemory *)v4, *v3, &v40);
    if ( !v9 )
        goto LABEL_22;
    if ( v5 == 2 )
    {
        v24 = *(_DWORD **)(v4 + 100);
        v25 = v24[2];
        v26 = v24[3];
        v27 = v24[5];
        v28 = v40 + ((v25 - v26) >> 2);
        if ( (unsigned int)v28 > 0x7F )
        {
            if ( v28 <= 0 )
                v36 = ~((unsigned int)~v28 >> 7);
            else
                v36 = v28 >> 7;
            if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v27 + 4 * v36) + 4 * (v28 - (v36 << 7))) + 4) != 4 )
            {
                if ( v28 <= 0 )
                    v37 = ~((unsigned int)~v28 >> 7);
                else
                    v37 = v28 >> 7;
                v29 = *(_DWORD *)(v27 + 4 * v37) + 4 * (v28 - (v37 << 7));
                LABEL_29:
                if ( *(_BYTE *)(*(_DWORD *)v29 + 4) == 3 )
                {
                    v6 = 0;
                    addCdnAndThirdDuplicateBytes(v3[2]);
                    pthread_mutex_unlock(v8);
                    return v6;
                }
                goto LABEL_8;
            }
        }
        else if ( *(_BYTE *)(*(_DWORD *)(v25 + 4 * v40) + 4) != 4 )
        {
            v29 = v25 + 4 * v40;
            goto LABEL_29;
        }
        v6 = 0;
        addCdnAndP2PDuplicateBytes(v3[2]);
        pthread_mutex_unlock(v8);
        return v6;
    }
    if ( v5 == 3 )
    {
        v30 = *(_DWORD **)(v4 + 100);
        v31 = v30[2];
        v32 = v30[3];
        v33 = v30[5];
        v34 = v40 + ((v31 - v32) >> 2);
        if ( (unsigned int)v34 > 0x7F )
        {
            if ( v34 <= 0 )
                v38 = ~((unsigned int)~v34 >> 7);
            else
                v38 = v34 >> 7;
            if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(v33 + 4 * v38) + 4 * (v34 - (v38 << 7))) + 4) != 2 )
            {
                if ( v34 <= 0 )
                    v39 = ~((unsigned int)~v34 >> 7);
                else
                    v39 = v34 >> 7;
                v35 = *(_DWORD *)(v33 + 4 * v39) + 4 * (v34 - (v39 << 7));
                LABEL_35:
                if ( *(_BYTE *)(*(_DWORD *)v35 + 4) == 4 )
                {
                    v6 = 0;
                    addThirdAndP2PDuplicateBytes(v3[2]);
                    pthread_mutex_unlock(v8);
                    return v6;
                }
                goto LABEL_8;
            }
        }
        else if ( *(_BYTE *)(*(_DWORD *)(v31 + 4 * v40) + 4) != 2 )
        {
            v35 = v31 + 4 * v40;
            goto LABEL_35;
        }
        v6 = 0;
        addThirdAndCDNDuplicateBytes(v3[2]);
        pthread_mutex_unlock(v8);
        return v6;
    }
    LABEL_8:
    v9 = (_DWORD *)OneData::setDataInfo(v9, (int *)v3);
    if ( !v9 )
    {
        v10 = *(_DWORD **)(v4 + 100);
        v11 = v40;
        v12 = v10[2];
        v13 = v10[5];
        v14 = v40 + ((v12 - v10[3]) >> 2);
        if ( (unsigned int)v14 > 0x7F )
        {
            if ( v14 <= 0 )
                v16 = ~((unsigned int)~v14 >> 7);
            else
                v16 = v14 >> 7;
            v15 = *(_DWORD *)(v13 + 4 * v16) + 4 * (v14 - (v16 << 7));
        }
        else
        {
            v15 = v12 + 4 * v40;
        }
        *(_BYTE *)(*(_DWORD *)v15 + 4) = v5;
        v17 = *(_DWORD **)(v4 + 100);
        v18 = v17[2];
        v19 = v17[5];
        v20 = v11 + ((v18 - v17[3]) >> 2);
        if ( (unsigned int)v20 > 0x7F )
        {
            if ( v20 <= 0 )
                v22 = ~((unsigned int)~v20 >> 7);
            else
                v22 = v20 >> 7;
            v21 = *(_DWORD *)(v19 + 4 * v22) + 4 * (v20 - (v22 << 7));
        }
        else
        {
            v21 = v18 + 4 * v11;
        }
        v23 = *(void (**)(void))(v4 + 96);
        *(_DWORD *)(*(_DWORD *)v21 + 8) = v3[2];
        v23();
        addCurrentPieceLength(v3[2]);
        addCurrentPieceNum(1);
        LABEL_22:
        pthread_mutex_unlock(v8);
        return (int)v9;
    }
    (*(void (__fastcall **)(unsigned int))(v4 + 104))(*v3);
    pthread_mutex_unlock(v8);
    return 0;
}