//
// Created by 赵勇 on 2018/4/10.
//

//----- (0002B944) --------------------------------------------------------
signed int __fastcall OneRequest::reset(OneRequest *this)
{
    OneRequest *v1; // r6
    int v2; // r4
    char *v3; // r0
    signed int result; // r0

    v1 = this;
    v2 = 0;
    *(_WORD *)this = 0;
    *((_WORD *)this + 5) = 0;
    *((_DWORD *)this + 1) = 0;
    memset((char *)this + 6812, 0, 0x10u);
    do
    {
        v3 = (char *)v1 + v2 + 412;
        v2 += 16;
        memset(v3, 0, 0x10u);
    }
    while ( v2 != 6400 );
    result = 6848;
    *((_QWORD *)v1 + 854) = 0LL;
    *((_DWORD *)v1 + 1710) = 0;
    *((_DWORD *)v1 + 1711) = 0;
    *((_BYTE *)v1 + 6848) = 0;
    return result;
}

//----- (0002B9C0) --------------------------------------------------------
OneRequest *__fastcall OneRequest::OneRequest(OneRequest *this)
{
    OneRequest *v1; // r4

    v1 = this;
    OneRequest::reset(this);
    return v1;
}

//----- (0002B9D4) --------------------------------------------------------
signed int __fastcall OneRequest::setRequestData(OneRequest *this, const char *a2, int a3, sockaddr_in *a4)
{
sockaddr_in *v4; // r4
OneRequest *v5; // r6
_DWORD *v6; // r2
in_addr_t v7; // r12
int v8; // r0
int v9; // r1
signed int v10; // r4
signed int result; // r0

v4 = a4;
v5 = this;
if ( !a2 )
return -1;
if ( a3 != 6812 )
return -2;
memcpy((void *)this, a2, 0x1A9Cu);
if ( v4 )
{
v6 = (_DWORD *)((char *)v5 + 6784);
v7 = v4->sin_addr.s_addr;
v8 = *(_DWORD *)v4->sin_zero;
v9 = *(_DWORD *)&v4->sin_zero[4];
v6[7] = *(_DWORD *)&v4->sin_family;
v6[8] = v7;
v6[9] = v8;
v6[10] = v9;
}
v10 = 400;
do
{
memset((char *)v5 + 412, 0, 0x10u);
--v10;
}
while ( v10 );
if ( *(_WORD *)v5 != 2047 )
return -9;
result = 0;
*((_QWORD *)v5 + 854) = 0LL;
return result;
}

//----- (0002BA84) --------------------------------------------------------
unsigned __int64 __fastcall OneRequest::setBeginningTime(OneRequest *this)
{
OneRequest *v1; // r4
unsigned __int64 result; // r0
int v3; // [sp+0h] [bp-18h]
int v4; // [sp+4h] [bp-14h]

v1 = this;
gettimeofday((struct timeval *)&v3, 0);
result = 1000LL * v3 + v4 / 0x3E8uLL;
*((_QWORD *)v1 + 854) = result;
return result;
}

//----- (0002BACC) --------------------------------------------------------
signed int __fastcall OneRequest::getRequestData(int a1, _DWORD *a2, _DWORD *a3)
{
    int v3; // r3
    signed int result; // r0

    if ( !a2 )
        return -1;
    *a2 = a1;
    if ( !a3 )
        return 0;
    v3 = a1 + 6784;
    result = 0;
    *a3 = v3 + 28;
    return result;
}

//----- (0002BB04) --------------------------------------------------------
signed int __fastcall OneRequest::refreshRequestData(OneRequest *this, int a2, int a3)
{
int v3; // r3
signed int v4; // r3
char *v5; // r2
signed int result; // r0
int v7; // r3
signed int v8; // r3

if ( a2 <= 0 )
{
v7 = *((_DWORD *)this + 1711);
if ( v7 > 0 )
{
v8 = -9;
*((_WORD *)this + 5) = 401;
}
else
{
*((_DWORD *)this + 1711) = v7 + 1;
v8 = -101;
}
result = v8;
}
else
{
v3 = a2 / 0x486u;
if ( a2 % 0x486u )
++v3;
if ( (unsigned int)(v3 - 1) < 0x190 )
{
if ( (a3 > v3) | ((unsigned int)a3 >> 31) )
{
v4 = -2;
*((_WORD *)this + 5) = 401;
}
else
{
v5 = (char *)this + a3;
*((_WORD *)this + 5) = v3;
if ( (unsigned __int8)v5[12] == 255 )
++*((_DWORD *)this + 1710);
v4 = 0;
v5[12] = -1;
}
}
else
{
v4 = -1;
*((_WORD *)this + 5) = 401;
}
result = v4;
}
return result;
}

//----- (0002BBD0) --------------------------------------------------------
bool __fastcall OneRequest::isTheSameRequest(OneRequest *this, unsigned int a2)
{
return *((_DWORD *)this + 1) - a2 <= 0;
}

//----- (0002BBE4) --------------------------------------------------------
int __fastcall OneRequest::getFileId(OneRequest *this)
{
    return *((_DWORD *)this + 1);
}

//----- (0002BBEC) --------------------------------------------------------
int __fastcall OneRequest::isTimeout(OneRequest *this)
{
    return *((unsigned __int8 *)this + 6848);
}

//----- (0002BBF8) --------------------------------------------------------
int __fastcall OneRequest::setTimeout(int result)
{
    *(_BYTE *)(result + 6848) = 1;
    return result;
}

//----- (0002BC08) --------------------------------------------------------
bool __fastcall OneRequest::isValid(OneRequest *this)
{
    return *((unsigned __int16 *)this + 5) <= 0x190u;
}

//----- (0002BC1C) --------------------------------------------------------
int __fastcall OneRequest::getDuration(OneRequest *this)
{
    OneRequest *v1; // r5
    int v3; // [sp+0h] [bp-18h]
    int v4; // [sp+4h] [bp-14h]

    v1 = this;
    if ( !*((_QWORD *)this + 854) )
    return 0;
    gettimeofday((struct timeval *)&v3, 0);
    return 1000 * v3 + v4 / 0x3E8uLL - *((unsigned __int64 *)v1 + 854);
}

//----- (0002BC80) --------------------------------------------------------
int __fastcall OneRequest::getTotalPacketNumb(OneRequest *this)
{
    return *((unsigned __int16 *)this + 5);
}

//----- (0002BC88) --------------------------------------------------------
signed int __fastcall OneRequest::getDownloadedNumb(OneRequest *this, int *a2, int *a3, int *a4)
{
    bool v4; // zf
    int v5; // r5
    char *v6; // r4
    int v7; // r0
    bool v8; // zf
    int v9; // r12
    int v10; // r12
    int v11; // r12
    int v12; // t1

    v4 = a2 == 0;
    if ( a2 )
        v4 = a3 == 0;
    if ( v4 || !a4 )
        return -1;
    v5 = *((unsigned __int16 *)this + 5);
    if ( *((_WORD *)this + 5) )
    {
        v6 = (char *)this + 11;
        v7 = 0;
        do
        {
            while ( 1 )
            {
                v12 = (unsigned __int8)(v6++)[1];
                v11 = v12;
                if ( v12 != 255 )
                    break;
                ++v7;
                ++*a2;
                if ( v7 == v5 )
                    return 0;
            }
            v8 = v11 == 0;
            ++v7;
            if ( v11 )
                v9 = *a3;
            else
                v9 = *a4;
            v10 = v9 + 1;
            if ( v8 )
                *a4 = v10;
            else
                *a3 = v10;
        }
        while ( v7 != v5 );
    }
    return 0;
}

//----- (0002BD20) --------------------------------------------------------
int __fastcall OneRequest::getDuplicateCount(OneRequest *this)
{
    return *((_DWORD *)this + 1710);
}

//----- (0002BD2C) --------------------------------------------------------
_DWORD *__fastcall OneRequest::operator=(_QWORD *a1, int a2)
{
    _DWORD *v2; // r7
    int v3; // r6
    int v4; // r5
    int v5; // r4
    int v6; // r3
    _DWORD *result; // r0

    v2 = a1 + 848;
    v3 = a2;
    a1[854] = *(_QWORD *)(a2 + 6832);
    v4 = *(_DWORD *)(a2 + 6816);
    v5 = *(_DWORD *)(a2 + 6820);
    v6 = *(_DWORD *)(a2 + 6824);
    v2[7] = *(_DWORD *)(a2 + 6812);
    v2[8] = v4;
    v2[10] = v6;
    v2[9] = v5;
    result = memcpy(a1, (const void *)a2, 0x1A9Cu);
    result[1711] = *(_DWORD *)(v3 + 6844);
    return result;
}