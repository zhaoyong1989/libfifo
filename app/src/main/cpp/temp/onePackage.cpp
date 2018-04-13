//
// Created by 赵勇 on 2018/4/10.
//

//----- (0002B6E8) --------------------------------------------------------
void *__fastcall OnePacket::reset(OnePacket *this)
{
    OnePacket *v1; // r6

    v1 = this;
    *(_WORD *)this = 0;
    *((_WORD *)this + 36) = 0;
    *((_DWORD *)this + 1) = 0;
    *((_WORD *)this + 1) = 0;
    *((_QWORD *)this + 1) = 0LL;
    *((_QWORD *)this + 2) = 0LL;
    memset((char *)this + 24, 0, 0x30u);
    return memset((char *)v1 + 1232, 0, 0x10u);
}

//----- (0002B738) --------------------------------------------------------
OnePacket *__fastcall OnePacket::OnePacket(OnePacket *this)
{
    OnePacket *v1; // r4

    v1 = this;
    OnePacket::reset(this);
    return v1;
}

//----- (0002B74C) --------------------------------------------------------
signed int __fastcall OnePacket::setPacketData(OnePacket *this, const char *a2, int a3, sockaddr_in *a4)
{
sockaddr_in *v4; // r5
OnePacket *v5; // r4
in_addr_t v6; // r1
int v7; // r2
int v8; // r3
signed int result; // r0

v4 = a4;
v5 = this;
if ( !a2 || (unsigned int)a3 > 0x4D0 )
return -1;
memcpy((void *)this, a2, a3);
if ( v4 )
{
v6 = v4->sin_addr.s_addr;
v7 = *(_DWORD *)v4->sin_zero;
v8 = *(_DWORD *)&v4->sin_zero[4];
*((_DWORD *)v5 + 308) = *(_DWORD *)&v4->sin_family;
*((_DWORD *)v5 + 309) = v6;
*((_DWORD *)v5 + 310) = v7;
*((_DWORD *)v5 + 311) = v8;
}
if ( *(_WORD *)v5 == 2303 )
result = 0;
else
result = -2;
return result;
}

//----- (0002B7B4) --------------------------------------------------------
signed int __fastcall OnePacket::setPacketData(OnePacket *this, const char *a2, int a3, const char *s, unsigned int a5, unsigned __int16 a6, unsigned __int64 a7, unsigned __int64 a8)
{
size_t v8; // r6
const char *v9; // r8
OnePacket *v10; // r4
_BOOL4 v11; // r7
const char *v12; // r5
signed int result; // r0

v8 = a3;
v9 = a2;
v10 = this;
v11 = (unsigned int)a3 > 0x486;
if ( !a2 )
v11 = 1;
v12 = s;
if ( v11 || !s )
return -1;
if ( strlen(s) > 0x2F )
return -2;
*((_QWORD *)v10 + 1) = a7;
*((_QWORD *)v10 + 2) = a8;
*(_WORD *)v10 = 2303;
memcpy((char *)v10 + 74, v9, v8);
*((_WORD *)v10 + 36) = v8;
strcpy((char *)v10 + 24, v12);
*((_WORD *)v10 + 1) = a6;
result = 0;
*((_DWORD *)v10 + 1) = a5;
return result;
}

//----- (0002B860) --------------------------------------------------------
signed int __fastcall OnePacket::getPacketData(OnePacket *this, char **a2, sockaddr_in **a3)
{
    bool v3; // zf
    sockaddr_in *v4; // r3
    signed int result; // r0

    v3 = a3 == 0;
    if ( a3 )
        v3 = a2 == 0;
    if ( v3 )
        return -1;
    if ( !*((_WORD *)this + 36) )
    return -2;
    *a2 = (char *)this;
    v4 = (sockaddr_in *)((char *)this + 1232);
    result = 1232;
    *a3 = v4;
    return result;
}

//----- (0002B89C) --------------------------------------------------------
signed int __fastcall OnePacket::getPacketData(OnePacket *this, char **a2)
{
    if ( !a2 )
        return -1;
    if ( !*((_WORD *)this + 36) )
    return -2;
    *a2 = (char *)this;
    return 1232;
}

//----- (0002B8CC) --------------------------------------------------------
signed int __fastcall OnePacket::getPacketContentData(OnePacket *this, unsigned __int8 **a2, int a3, unsigned __int8 *a4)
{
signed int result; // r0

if ( a2 )
{
a4 = (unsigned __int8 *)this + 74;
result = *((unsigned __int16 *)this + 36);
}
else
{
result = -1;
}
if ( a2 )
*a2 = a4;
return result;
}

//----- (0002B8E4) --------------------------------------------------------
int __fastcall OnePacket::getPacketFileSize(OnePacket *this)
{
    return *((_DWORD *)this + 1);
}

//----- (0002B8EC) --------------------------------------------------------
int __fastcall OnePacket::getPacketSequence(OnePacket *this)
{
    return *((unsigned __int16 *)this + 1);
}

//----- (0002B8F4) --------------------------------------------------------
int __fastcall OnePacket::getPacketDataSize(OnePacket *this)
{
    return *((unsigned __int16 *)this + 36);
}

//----- (0002B8FC) --------------------------------------------------------
char *__fastcall OnePacket::getPacketFilePath(OnePacket *this)
{
    return (char *)this + 24;
}

//----- (0002B904) --------------------------------------------------------
signed int __fastcall OnePacket::setPacketAddr(OnePacket *this, sockaddr_in *a2)
{
    int v2; // r5
    OnePacket *v3; // r3
    signed int result; // r0
    in_addr_t v5; // r4
    int v6; // r12
    int v7; // r2

    v3 = this;
    if ( a2 )
    {
        result = 0;
        v2 = *(_DWORD *)&a2->sin_family;
    }
    else
    {
        result = -1;
    }
    if ( a2 )
    {
        v5 = a2->sin_addr.s_addr;
        v6 = *(_DWORD *)a2->sin_zero;
        v7 = *(_DWORD *)&a2->sin_zero[4];
        *((_DWORD *)v3 + 308) = v2;
        *((_DWORD *)v3 + 309) = v5;
        *((_DWORD *)v3 + 310) = v6;
        *((_DWORD *)v3 + 311) = v7;
    }
    return result;
}