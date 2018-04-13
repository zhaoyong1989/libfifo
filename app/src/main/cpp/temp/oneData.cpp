//
// Created by 赵勇 on 2018/4/10.
//

//----- (0002AC3C) --------------------------------------------------------
int __fastcall OneData::OneData(int result)
{
    *(_DWORD *)(result + 12) = 0;
    *(_DWORD *)(result + 8) = -1;
    *(_DWORD *)result = 0;
    *(_DWORD *)(result + 4) = 0;
    *(_DWORD *)(result + 16) = 0;
    return result;
}

//----- (0002AC5C) --------------------------------------------------------
OneData *__fastcall OneData::~OneData(OneData *this)
{
    OneData *v1; // r4
    void *v2; // r0

    v1 = this;
    v2 = (void *)*((_DWORD *)this + 3);
    if ( v2 )
    {
        free(v2);
        *((_DWORD *)v1 + 3) = 0;
    }
    return v1;
}

//----- (0002AC84) --------------------------------------------------------
void __fastcall OneData::reset(OneData *this)
{
    OneData *v1; // r4
    void *v2; // r0

    v1 = this;
    v2 = (void *)*((_DWORD *)this + 3);
    if ( v2 )
    {
        free(v2);
        *((_DWORD *)v1 + 3) = 0;
    }
    *(_DWORD *)v1 = 0;
    *((_DWORD *)v1 + 1) = 0;
    *((_DWORD *)v1 + 4) = 0;
    *((_DWORD *)v1 + 2) = -1;
}

//----- (0002ACC0) --------------------------------------------------------
signed int __fastcall OneData::setDataInfo(_DWORD *a1, int *a2)
{
    int *v2; // r5
    _DWORD *v3; // r4
    signed int v4; // r6
    void *v5; // r0
    int v6; // r1
    int v7; // r2
    signed int result; // r0

    v2 = a2;
    v3 = a1;
    if ( !a2 )
        return -1;
    v4 = a2[2];
    if ( v4 < 0 )
        return -2;
    v5 = malloc(a2[2]);
    v3[3] = v5;
    memcpy(v5, (const void *)v2[3], v4);
    v6 = *v2;
    v7 = v2[2];
    result = 0;
    v3[4] = 0;
    *v3 = v6;
    v3[1] = 0;
    v3[2] = v7;
    return result;
}

//----- (0002AD24) --------------------------------------------------------
int __fastcall OneData::getDataLength(OneData *this)
{
    return *((_DWORD *)this + 2);
}

//----- (0002AD2C) --------------------------------------------------------
int __fastcall OneData::setDataLength(int result, int a2)
{
    *(_DWORD *)(result + 8) = a2;
    return result;
}

//----- (0002AD34) --------------------------------------------------------
void *__fastcall OneData::cacheData(OneData *this, unsigned __int8 *a2, size_t n, int a4, size_t size)
{
OneData *v5; // r4
size_t v6; // r5
char *v7; // r12
void *result; // r0
unsigned __int8 *v9; // ST04_4
char *v10; // r0

v5 = this;
v6 = n;
if ( a4 )
{
v7 = (char *)*((_DWORD *)this + 3);
}
else
{
v9 = a2;
v10 = (char *)malloc(size);
a2 = v9;
v7 = v10;
*((_DWORD *)v5 + 3) = v10;
}
result = memcpy(&v7[*((_DWORD *)v5 + 4)], a2, v6);
*((_DWORD *)v5 + 4) += v6;
return result;
}

//----- (0002AD90) --------------------------------------------------------
signed int __fastcall OneData::getOneData(OneData *this, unsigned __int8 **a2, int a3, unsigned __int8 *a4)
{
signed int result; // r0

if ( a2 )
{
a4 = (unsigned __int8 *)*((_DWORD *)this + 3);
result = *((_DWORD *)this + 2);
}
else
{
result = -1;
}
if ( a2 )
*a2 = a4;
return result;
}

//----- (0002ADA8) --------------------------------------------------------
int __fastcall OneData::getDataId(OneData *this)
{
    return *(_DWORD *)this;
}

//----- (0002ADB0) --------------------------------------------------------
int __fastcall OneData::setDataId(int result, unsigned int a2)
{
    *(_DWORD *)result = a2;
    return result;
}