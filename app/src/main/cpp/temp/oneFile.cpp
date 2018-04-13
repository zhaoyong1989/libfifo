//
// Created by 赵勇 on 2018/4/10.
//

//----- (0002ADB8) --------------------------------------------------------
OneFile *__fastcall OneFile::~OneFile(OneFile *this)
{
    OneFile *v1; // r4
    void *v2; // r0

    v1 = this;
    v2 = (void *)*((_DWORD *)this + 1);
    if ( v2 )
        operator delete(v2);
    return v1;
}

//----- (0002ADD8) --------------------------------------------------------
int __fastcall OneFile::reset(int result)
{
    *(_BYTE *)(result + 16) = 0;
    return result;
}

//----- (0002ADE4) --------------------------------------------------------
OneFile *__fastcall OneFile::OneFile(OneFile *this)
{
    OneFile *v1; // r4

    *((_DWORD *)this + 1) = 0;
    v1 = this;
    *((_DWORD *)this + 2) = 0;
    *((_DWORD *)this + 3) = 0;
    OneFile::reset((int)this);
    return v1;
}

//----- (0002AE1C) --------------------------------------------------------
int __fastcall OneFile::setFileId(int result, unsigned int a2)
{
    *(_DWORD *)result = a2;
    *(_BYTE *)(result + 16) = 0;
    return result;
}

//----- (0002AE2C) --------------------------------------------------------
int __fastcall OneFile::getFileId(OneFile *this)
{
    return *(_DWORD *)this;
}

//----- (0002AE34) --------------------------------------------------------
signed int __fastcall OneFile::getOnePacket(int a1, void *a2, int a3)
{
    int v3; // r3

    if ( !a2 )
        return -1;
    v3 = *(_DWORD *)(a1 + 4);
    if ( a3 >= (*(_DWORD *)(a1 + 8) - v3) >> 2 )
        return -2;
    memcpy(a2, *(const void **)(v3 + 4 * a3), 0x4E8u);
    return 0;
}

//----- (0002AE78) --------------------------------------------------------
signed int __fastcall OneFile::getPacketContent(OneFile *this, unsigned __int8 **a2, int a3)
{
unsigned __int8 *v3; // r3
OnePacket *v4; // r0
signed int result; // r0

if ( !a2 )
return -1;
v3 = (unsigned __int8 *)*((_DWORD *)this + 1);
if ( a3 < (*((_DWORD *)this + 2) - (signed int)v3) >> 2 && (v4 = *(OnePacket **)&v3[4 * a3]) != 0 )
result = OnePacket::getPacketContentData(v4, a2, a3, v3);
else
result = -2;
return result;
}

//----- (0002AEB4) --------------------------------------------------------
int __fastcall OneFile::getPacketNumb(OneFile *this)
{
    return (*((_DWORD *)this + 2) - *((_DWORD *)this + 1)) >> 2;
}

//----- (0002AEC8) --------------------------------------------------------
int __fastcall OneFile::getCurrentPacketNumb(OneFile *this)
{
    return *((_DWORD *)this + 5);
}

//----- (0002AED0) --------------------------------------------------------
int __fastcall OneFile::setCurrentPacketNumb(int result, int a2)
{
    *(_DWORD *)(result + 20) = a2;
    return result;
}

//----- (0002AED8) --------------------------------------------------------
int __fastcall OneFile::isFinished(OneFile *this)
{
    return *((unsigned __int8 *)this + 16);
}

//----- (0002AEE0) --------------------------------------------------------
int __fastcall OneFile::setFinished(int result)
{
    *(_BYTE *)(result + 16) = 1;
    return result;
}

//----- (0002AEEC) --------------------------------------------------------
bool __fastcall OneFile::isWithSameId(OneFile *this, unsigned int a2)
{
return *(_DWORD *)this - a2 <= 0;
}

//----- (0002AF00) --------------------------------------------------------
int __fastcall OneFile::getTotalSize(OneFile *this)
{
    int v1; // r3
    int result; // r0
    int v3; // r4

    v1 = *((_DWORD *)this + 1);
    result = (*((_DWORD *)this + 2) - v1) >> 2;
    if ( result )
    {
        v3 = result - 1;
        result = *(_DWORD *)(v1 + 4 * (result - 1));
        if ( result )
            result = OnePacket::getPacketDataSize((OnePacket *)result) + 1158 * v3;
    }
    return result;
}

//----- (0002AF38) --------------------------------------------------------
int __fastcall OneFile::getTotalAvailableSize(OneFile *this)
{
    OneFile *v1; // r6
    int v2; // r3
    int v3; // r7
    int v4; // r4
    int v5; // r5
    OnePacket *v6; // r0

    v1 = this;
    v2 = *((_DWORD *)this + 1);
    v3 = (*((_DWORD *)this + 2) - v2) >> 2;
    if ( v3 <= 0 )
        return 0;
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
        v6 = *(OnePacket **)(v2 + 4 * v4++);
        if ( v6 )
            v5 += OnePacket::getPacketDataSize(v6);
        if ( v4 == v3 )
            break;
        v2 = *((_DWORD *)v1 + 1);
    }
    return v5;
}

//----- (0002AF94) --------------------------------------------------------
int __fastcall OneFile::getFileSize(OneFile *this)
{
    OnePacket **v1; // r2
    int v2; // r1
    OnePacket *v3; // r0
    int v4; // r3
    OnePacket *v5; // t1

    v1 = (OnePacket **)*((_DWORD *)this + 1);
    v2 = (*((_DWORD *)this + 2) - (signed int)v1) >> 2;
    if ( v2 <= 0 )
        return 0;
    v3 = *v1;
    if ( !*v1 )
    {
        v4 = 0;
        while ( ++v4 != v2 )
        {
            v5 = v1[1];
            ++v1;
            v3 = v5;
            if ( v5 )
                return OnePacket::getPacketFileSize(v3);
        }
        return 0;
    }
    return OnePacket::getPacketFileSize(v3);
}

//----- (0002AFE4) --------------------------------------------------------
void __fastcall std::vector<OnePacket *,std::allocator<OnePacket *>>::_M_insert_aux(const void **a1, _DWORD *a2, _DWORD *a3)
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

//----- (0002B134) --------------------------------------------------------
signed int __fastcall OneFile::addOnePacket(OneFile *this, OnePacket *a2, int a3)
{
OnePacket *v3; // r6
OneFile *v4; // r4
unsigned int v5; // r7
_DWORD *v6; // r1
int v7; // r3
const void **v8; // r9
_DWORD *v9; // r2
int v10; // r0
int v11; // r3
_DWORD *v12; // r1
int v13; // r5
int v14; // r8
int v15; // r5
_DWORD *v16; // r3
signed int result; // r0
int v18; // [sp+4h] [bp-24h]

v3 = a2;
v4 = this;
v5 = a3;
if ( !a2 )
return -1;
v6 = (_DWORD *)*((_DWORD *)this + 2);
v7 = *((_DWORD *)this + 1);
if ( a3 > (unsigned int)(((signed int)v6 - v7) >> 2) )
{
v8 = (const void **)((char *)this + 4);
do
{
v9 = (_DWORD *)*((_DWORD *)v4 + 3);
v18 = 0;
if ( v6 == v9 )
{
std::vector<OnePacket *,std::allocator<OnePacket *>>::_M_insert_aux(v8, v6, &v18);
v6 = (_DWORD *)*((_DWORD *)v4 + 2);
v7 = *((_DWORD *)v4 + 1);
}
else
{
if ( v6 )
*v6 = 0;
if ( v6 )
v7 = *((_DWORD *)v4 + 1);
v6 = (_DWORD *)(*((_DWORD *)v4 + 2) + 4);
*((_DWORD *)v4 + 2) = v6;
}
}
while ( v5 > ((signed int)v6 - v7) >> 2 );
}
v10 = OnePacket::getPacketSequence(v3);
v11 = *((_DWORD *)v4 + 1);
v12 = (_DWORD *)*((_DWORD *)v4 + 2);
v13 = ((signed int)v12 - v11) >> 2;
v14 = v10;
if ( v10 >= v13 )
{
v15 = 1 - v13 + v10;
if ( v15 > 0 )
{
while ( 1 )
{
v16 = (_DWORD *)*((_DWORD *)v4 + 3);
v18 = 0;
if ( v16 == v12 )
{
std::vector<OnePacket *,std::allocator<OnePacket *>>::_M_insert_aux((const void **)v4 + 1, v12, &v18);
}
else
{
if ( v12 )
{
*v12 = 0;
v12 = (_DWORD *)*((_DWORD *)v4 + 2);
}
*((_DWORD *)v4 + 2) = v12 + 1;
}
if ( !--v15 )
break;
v12 = (_DWORD *)*((_DWORD *)v4 + 2);
}
v11 = *((_DWORD *)v4 + 1);
}
}
result = *(_DWORD *)(v11 + 4 * v14);
if ( result )
return -2;
*(_DWORD *)(v11 + 4 * v14) = v3;
return result;
}

//----- (0002B26C) --------------------------------------------------------
void *__fastcall std::deque<long,std::allocator<long>>::_M_push_back_aux(void **a1, _DWORD *a2)
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

//----- (0002B3E4) --------------------------------------------------------
int __fastcall OneFile::handleIncompleteFile(OneFile *this, int a2)
{
OneFile *v2; // r4
_DWORD *v3; // lr
int v4; // r5
int v5; // r0
int v6; // r0
_DWORD *v7; // r2
unsigned int v8; // r3
int v9; // t1
unsigned int v10; // r8
int v11; // r11
int v12; // r3
_DWORD *v13; // r1
int v14; // r3
int v15; // r3
int v16; // r3
int v18; // r3
bool v19; // zf
int v20; // r3
int v21; // [sp+Ch] [bp-2Ch]

v2 = this;
v3 = (_DWORD *)*((_DWORD *)this + 1);
v4 = a2;
v5 = *((_DWORD *)this + 2) - (_DWORD)v3;
if ( v5 <= 3 )
{
v6 = v5 >> 2;
goto LABEL_27;
}
v6 = v5 >> 2;
if ( !*v3 )
{
LABEL_27:
        v10 = 0;
goto LABEL_7;
}
v7 = v3;
v8 = 0;
do
{
if ( (signed int)++v8 >= v6 )
break;
v9 = v7[1];
++v7;
}
while ( v9 );
v10 = v8;
LABEL_7:
if ( v6 > v10 )
{
v11 = v10;
do
{
v15 = v3[v11];
if ( v15 )
{
v16 = 738624949 * ((v15 - *(_DWORD *)(v4 + 4)) >> 3);
v21 = v16;
if ( v16 >= 0 && v16 < *(_DWORD *)v4 && !*(_BYTE *)(*(_DWORD *)(v4 + 8) + v16) )
{
pthread_mutex_lock((pthread_mutex_t *)(v4 + 52));
if ( !*(_BYTE *)(*(_DWORD *)(v4 + 8) + v21) )
{
OnePacket::reset((OnePacket *)(*(_DWORD *)(v4 + 4) + 1256 * v21));
v18 = *(_DWORD *)(v4 + 36);
if ( v18 == *(_DWORD *)(v4 + 44) - 4 )
{
std::deque<long,std::allocator<long>>::_M_push_back_aux((void **)(v4 + 12), &v21);
}
else
{
v19 = v18 == 0;
v20 = v18 + 4;
if ( !v19 )
*(_DWORD *)(v20 - 4) = v21;
*(_DWORD *)(v4 + 36) = v20;
}
*(_BYTE *)(*(_DWORD *)(v4 + 8) + v21) = 1;
}
pthread_mutex_unlock((pthread_mutex_t *)(v4 + 52));
}
}
v3 = (_DWORD *)*((_DWORD *)v2 + 1);
v12 = *((_DWORD *)v2 + 2);
v13 = &v3[v11 + 1];
if ( v13 == (_DWORD *)v12 )
{
v12 = (int)&v3[v11 + 1];
}
else if ( (v12 - (signed int)v13) >> 2 )
{
memmove(&v3[v11], v13, 4 * ((v12 - (signed int)v13) >> 2));
v3 = (_DWORD *)*((_DWORD *)v2 + 1);
v12 = *((_DWORD *)v2 + 2);
}
v14 = v12 - 4;
*((_DWORD *)v2 + 2) = v14;
}
while ( v10 < (v14 - (signed int)v3) >> 2 );
}
*((_BYTE *)v2 + 16) = 0;
return OneFile::getTotalSize(v2);
}

//----- (0002B5A0) --------------------------------------------------------
int __fastcall OneFile::releasePackets(int a1, int a2)
{
    int v2; // r9
    int v3; // r10
    int v4; // r1
    int result; // r0
    int v6; // r4
    int v7; // r3
    int v8; // r3
    int v9; // r3
    bool v10; // zf
    int v11; // r3
    int v12; // [sp+Ch] [bp-2Ch]

    v2 = a1;
    v3 = a2;
    v4 = *(_DWORD *)(a1 + 4);
    result = *(_DWORD *)(a1 + 8);
    if ( result - v4 > 3 )
    {
        v6 = 0;
        do
        {
            while ( 1 )
            {
                v7 = *(_DWORD *)(v4 + 4 * v6);
                if ( v7 )
                {
                    v8 = 738624949 * ((v7 - *(_DWORD *)(v3 + 4)) >> 3);
                    v12 = v8;
                    if ( v8 >= 0 && v8 < *(_DWORD *)v3 && !*(_BYTE *)(*(_DWORD *)(v3 + 8) + v8) )
                    break;
                }
                if ( ++v6 >= (result - v4) >> 2 )
                    goto LABEL_10;
            }
            pthread_mutex_lock((pthread_mutex_t *)(v3 + 52));
            if ( !*(_BYTE *)(*(_DWORD *)(v3 + 8) + v12) )
            {
                OnePacket::reset((OnePacket *)(*(_DWORD *)(v3 + 4) + 1256 * v12));
                v9 = *(_DWORD *)(v3 + 36);
                if ( v9 == *(_DWORD *)(v3 + 44) - 4 )
                {
                    std::deque<long,std::allocator<long>>::_M_push_back_aux((void **)(v3 + 12), &v12);
                }
                else
                {
                    v10 = v9 == 0;
                    v11 = v9 + 4;
                    if ( !v10 )
                        *(_DWORD *)(v11 - 4) = v12;
                    *(_DWORD *)(v3 + 36) = v11;
                }
                *(_BYTE *)(*(_DWORD *)(v3 + 8) + v12) = 1;
            }
            ++v6;
            pthread_mutex_unlock((pthread_mutex_t *)(v3 + 52));
            v4 = *(_DWORD *)(v2 + 4);
            result = *(_DWORD *)(v2 + 8);
        }
        while ( v6 < (result - v4) >> 2 );
    }
    LABEL_10:
    *(_DWORD *)(v2 + 8) = v4;
    *(_BYTE *)(v2 + 16) = 0;
    return result;
}
