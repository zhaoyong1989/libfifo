//
// Created by 赵勇 on 2018/4/10.
//

#include "sub.h"

//----- (00025C98) --------------------------------------------------------
signed int __fastcall sub_25C98(int a1)
{
    int v1; // r4
    int v2; // r5
    __int64 v3; // r2
    signed int result; // r0
    __int64 v5; // r2
    void *v6; // r0
    int v7; // r3

    v1 = a1 + 34048;
    v2 = a1;
    v3 = *(_QWORD *)(a1 + 472);
    *(_QWORD *)(a1 + 34192) = v3;
    if ( v3 || (result = *(_DWORD *)(a1 + 788)) != 0 )
    {
        if ( *(_BYTE *)(v1 + 137) )
            Curl_cfree(*(_DWORD *)(v1 + 140));
        v5 = *(_QWORD *)(v1 + 144);
        if ( v5 )
            v6 = curl_maprintf("%llu-", (unsigned int)v5 | HIDWORD(v5));
        else
            v6 = (void *)Curl_cstrdup(*(_DWORD *)(v2 + 788));
        *(_DWORD *)(v1 + 140) = v6;
        v7 = *(_DWORD *)(v1 + 140);
        *(_BYTE *)(v1 + 137) = v7 != 0;
        if ( v7 )
            result = 0;
        *(_BYTE *)(v1 + 136) = 1;
    }
    else
    {
        result = 27;
    }
}
else
{
*(_BYTE *)(v1 + 136) = 0;
}
return result;
}
// F3BEC: using guessed type int (__fastcall *Curl_cstrdup)(_DWORD);
// F3BF4: using guessed type int (__fastcall *Curl_cfree)(_DWORD);

//----- (00025D24) --------------------------------------------------------
int __fastcall sub_25D24(int a1)
{
    int v1; // r4
    int v2; // r0
    int result; // r0

    v1 = a1;
    v2 = *(_DWORD *)(a1 + 8);
    if ( !v2 || !Curl_multi_canPipeline(v2) || (*(_DWORD *)(v1 + 528) & 0xFFFFFFFB) != 1 )
        return 0;
    result = *(_DWORD *)(v1 + 532) - 1;
    if ( *(_DWORD *)(v1 + 532) != 1 )
        result = 1;
    return result;
}

//----- (00025D50) --------------------------------------------------------
int __fastcall sub_25D50(int a1, int a2)
{
    int v2; // r6
    _DWORD *v3; // r3
    int v4; // r5
    int v5; // r4
    int v6; // r1
    signed int v7; // r0

    v2 = a2;
    v3 = *(_DWORD **)(a1 + 1148);
    v4 = a1;
    v5 = 0;
    v6 = v3[1];
    while ( v5 < v6 )
    {
        if ( !*(_DWORD *)(*v3 + 4 * v5) )
            goto LABEL_9;
        ++v5;
    }
    if ( v5 == v6 )
    {
        v7 = sub_714BC(a1, v6);
        v5 = v7;
        if ( v7 == -1 )
            Curl_infof(v4, "This connection did not fit in the connection cache\n", 0);
        else
            Curl_infof(
                    v4,
                    "Connection (#%d) was killed to make room (holds %d)\n",
                    v7,
                    *(_DWORD *)(*(_DWORD *)(v4 + 1148) + 4));
    }
    LABEL_9:
    *(_BYTE *)(v2 + 40) = 1;
    *(_DWORD *)(v2 + 44) = v5;
    if ( v5 != -1 )
    {
        *(_DWORD *)(**(_DWORD **)(v4 + 1148) + 4 * v5) = v2;
        *(_DWORD *)v2 = v4;
    }
    return v5;
}

//----- (00025DC0) --------------------------------------------------------
void __fastcall __noreturn sub_25DC0(int a1)
{
    sub_9098C(
            -559030611,
            "%s: noting a del on a non-setup event %p (events: 0x%x, fd: %d, flags: 0x%x)",
            "event_del_internal",
            a1,
            *(signed __int16 *)(a1 + 48),
            *(_DWORD *)(a1 + 24),
            *(signed __int16 *)(a1 + 52));
}

//----- (00025E0C) --------------------------------------------------------
void __fastcall __noreturn sub_25E0C(int a1, int a2)
{
    sub_9098C(1, "%s: %p(fd %d) already on queue %x", "event_queue_insert", a1, *(_DWORD *)(a1 + 24), a2);
}

//----- (00025E48) --------------------------------------------------------
int __fastcall sub_25E48(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 40))();
}

//----- (00025E54) --------------------------------------------------------
int __fastcall sub_25E54(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 36))();
}

//----- (00025E60) --------------------------------------------------------
int __fastcall sub_25E60(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 40))();
}

//----- (00025E6C) --------------------------------------------------------
int __fastcall sub_25E6C(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 36))();
}

//----- (00025E78) --------------------------------------------------------
int __fastcall sub_25E78(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 36))();
}

//----- (00025E84) --------------------------------------------------------
int __fastcall sub_25E84(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 40))();
}

//----- (00025E90) --------------------------------------------------------
int __fastcall sub_25E90(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 36))();
}

//----- (00025E9C) --------------------------------------------------------
int __fastcall sub_25E9C(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 40))();
}

//----- (00025EA8) --------------------------------------------------------
int __fastcall sub_25EA8(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 52))();
}

//----- (00025EB4) --------------------------------------------------------
int __fastcall sub_25EB4(int a1)
{
    return (*(int (**)(void))(*(_DWORD *)a1 + 52))();
}

//----- (00025EC0) --------------------------------------------------------
_DWORD *__fastcall sub_25EC0(_DWORD *result, int a2)
{
    *result = a2;
    result[2] = 0;
    result[a2 + 3] = 0;
    return result;
}

//----- (00025ED0) --------------------------------------------------------
void __fastcall sub_25ED0(unsigned int *a1)
{
    unsigned int *v1; // r3
    signed int v2; // r2

    v1 = a1 + 2;
    __dmb(0xFu);
    do
        v2 = __ldrex(v1);
    while ( __strex(v2 - 1, v1) );
    __dmb(0xFu);
    if ( v2 <= 0 )
        operator delete(a1);
}

//----- (00025EFC) --------------------------------------------------------
void __fastcall sub_25EFC(unsigned int *a1)
{
    unsigned int *v1; // r3
    signed int v2; // r2

    v1 = a1 + 2;
    __dmb(0xFu);
    do
        v2 = __ldrex(v1);
    while ( __strex(v2 - 1, v1) );
    __dmb(0xFu);
    if ( v2 <= 0 )
        operator delete(a1);
}

//----- (00025F28) --------------------------------------------------------
int sub_25F28()
{
    return _cxa_finalize(&unk_F3000);
}
// 253DC: using guessed type int __fastcall _cxa_finalize(_DWORD);

//----- (00025F38) --------------------------------------------------------
int sub_25F38()
{
    sub_93764((int)&unk_F3D38);
    return sub_D0FE4();
}

//----- (00025F74) --------------------------------------------------------
int sub_25F74()
{
    sub_93764((int)&unk_F3D3C);
    return sub_D0FE4();
}

//----- (00025FB0) --------------------------------------------------------
int sub_25FB0()
{
    sub_93764((int)&unk_F3D40);
    return sub_D0FE4();
}

//----- (00025FEC) --------------------------------------------------------
int sub_25FEC()
{
    sub_93764((int)&unk_F3D44);
    return sub_D0FE4();
}

//----- (00026028) --------------------------------------------------------
int sub_26028()
{
    sub_93764((int)&unk_F3D48);
    return sub_D0FE4();
}

//----- (00026064) --------------------------------------------------------
int sub_26064()
{
    sub_93764((int)&unk_F3D4C);
    return sub_D0FE4();
}

//----- (000260A0) --------------------------------------------------------
int sub_260A0()
{
    sub_93764((int)algn_F3D54);
    return sub_D0FE4();
}

//----- (000260E0) --------------------------------------------------------
int sub_260E0()
{
    sub_93764((int)algn_F3D64);
    return sub_D0FE4();
}

//----- (00026120) --------------------------------------------------------
int sub_26120()
{
    sub_93764((int)algn_F3D7C);
    return sub_D0FE4();
}

//----- (00026160) --------------------------------------------------------
int sub_26160()
{
    sub_93764((int)&unk_F3DB8);
    return sub_D0FE4();
}

//----- (0002619C) --------------------------------------------------------
int sub_2619C()
{
    sub_93764((int)algn_F40E4);
    return sub_D0FE4();
}

//----- (000261DC) --------------------------------------------------------
int sub_261DC()
{
    sub_93764((int)&unk_F40F8);
    return sub_D0FE4();
}

//----- (00026218) --------------------------------------------------------
int sub_26218()
{
    sub_93764((int)&unk_F40FC);
    return sub_D0FE4();
}

//----- (00026254) --------------------------------------------------------
int sub_26254()
{
    sub_93764((int)&unk_F4134);
    return sub_D0FE4();
}

//----- (00026290) --------------------------------------------------------
int sub_26290()
{
    sub_93764((int)&unk_F413C);
    return sub_D0FE4();
}

//----- (000262CC) --------------------------------------------------------
int sub_262CC()
{
    sub_93764((int)&unk_F4140);
    return sub_D0FE4();
}

//----- (00026308) --------------------------------------------------------
int sub_26308()
{
    sub_93764((int)&unk_F4144);
    return sub_D0FE4();
}

//----- (00026344) --------------------------------------------------------
int sub_26344()
{
    sub_93764((int)&unk_F4148);
    return sub_936DC();
}

//----- (00026370) --------------------------------------------------------
int sub_26370()
{
    sub_93764((int)&unk_F414C);
    sub_936DC();
    sub_C1C58((void **)VideoDefinitionString, "LD");
    sub_C1C58((void **)&unk_F4154, "SD");
    sub_C1C58((void **)&unk_F4158, "HD");
    sub_C1C58((void **)&unk_F415C, "UHD");
    return sub_936DC();
}

//----- (00026430) --------------------------------------------------------
int sub_26430()
{
    sub_93764((int)&unk_F4190);
    return sub_936DC();
}

//----- (0002645C) --------------------------------------------------------
int sub_2645C()
{
    sub_93764((int)&unk_F4191);
    return sub_936DC();
}

//----- (00026488) --------------------------------------------------------
_DWORD *sub_26488()
{
    char *v0; // r4
    _DWORD *result; // r0

    sub_93764((int)&unk_F4198);
    sub_936DC();
    RegularInfo::resetRegularStatistic((RegularInfo *)&currentChannelInfo);
    sub_936DC();
    v0 = (char *)operator new(8u);
    pthread_mutex_init((pthread_mutex_t *)(v0 + 4), 0);
    result = operator new(0x20u);
    *(_DWORD *)v0 = result;
    *result = 0;
    *(_DWORD *)(*(_DWORD *)v0 + 4) = 0;
    *(_DWORD *)(*(_DWORD *)v0 + 8) = 0;
    *(_DWORD *)(*(_DWORD *)v0 + 12) = 0;
    *(_DWORD *)(*(_DWORD *)v0 + 24) = 0;
    invalidSource = (int)v0;
    return result;
}
// F41D8: using guessed type int invalidSource;

//----- (00026518) --------------------------------------------------------
int sub_26518()
{
    sub_93764((int)&unk_F5730);
    return sub_936DC();
}

//----- (00026544) --------------------------------------------------------
int sub_26544()
{
    sub_93764((int)&unk_F5738);
    return sub_936DC();
}

//----- (00026570) --------------------------------------------------------
int sub_26570()
{
    sub_93764((int)&unk_F5748);
    return sub_936DC();
}

//----- (0002659C) --------------------------------------------------------
int sub_2659C()
{
    sub_93764((int)&unk_F5B50);
    return sub_936DC();
}

//----- (000265C8) --------------------------------------------------------
int sub_265C8()
{
    sub_93764((int)&unk_F6052);
    return sub_936DC();
}

//----- (000265F4) --------------------------------------------------------
int sub_265F4()
{
    sub_93764((int)&unk_F6053);
    return sub_936DC();
}

//----- (00026620) --------------------------------------------------------
int sub_26620()
{
    sub_93764((int)&unk_F6054);
    return sub_936DC();
}

//----- (0002664C) --------------------------------------------------------
int sub_2664C()
{
    sub_93764((int)&unk_2F6060);
    return sub_936DC();
}

//----- (00026678) --------------------------------------------------------
int **sub_26678()
{
    sub_93764((int)&unk_2F6070);
    sub_936DC();
    Json::Value::Value((int)&Json::Value::null, 0);
    sub_936DC();
    return sub_539CC();
}

//----- (000266D0) --------------------------------------------------------
int sub_266D0()
{
    sub_93764((int)&unk_2F6088);
    return sub_936DC();
}

//----- (000266FC) --------------------------------------------------------
int sub_266FC()
{
    sub_93764((int)&unk_2F6090);
    sub_936DC();
    RegularInfo::resetRegularStatistic((RegularInfo *)&lastChannelInfo);
    sub_936DC();
    RegularInfo::resetRegularStatistic((RegularInfo *)&lastSecondInfo);
    sub_936DC();
    RegularInfo::resetRegularStatistic((RegularInfo *)&currentSecondInfo);
    return sub_936DC();
}

//----- (00026780) --------------------------------------------------------
int sub_26780()
{
    sub_93764((int)&unk_2F83F8);
    return sub_D0FE4();
}

//----- (000267BC) --------------------------------------------------------
int sub_267BC()
{
    byte_2F895C = 0;
    byte_2F895C = pthread_key_create((pthread_key_t *)&dword_2F8958, (void (*)(void *))sub_92D14) == 0;
    return sub_936DC();
}
// 2F8958: using guessed type int dword_2F8958;
// 2F895C: using guessed type char byte_2F895C;

//----- (000267FC) --------------------------------------------------------
void sub_267FC()
{
    dword_2F9870 = 0;
}
// 2F9870: using guessed type int dword_2F9870;

//----- (0002680C) --------------------------------------------------------
int sub_2680C()
{
    int result; // r0

    if ( !(dword_2FE094 & 1) )
        dword_2FE094 = 1;
    if ( !(dword_2FE090 & 1) )
        dword_2FE090 = 1;
    if ( !(dword_2FE08C & 1) )
        dword_2FE08C = 1;
    if ( !(dword_2FE088 & 1) )
        dword_2FE088 = 1;
    if ( !(dword_2FE084 & 1) )
        dword_2FE084 = 1;
    if ( !(dword_2FE080 & 1) )
        dword_2FE080 = 1;
    if ( !(dword_2FE07C & 1) )
        dword_2FE07C = 1;
    if ( !(dword_2FE078 & 1) )
        dword_2FE078 = 1;
    if ( !(dword_2FE074 & 1) )
        dword_2FE074 = 1;
    result = dword_2FE070 << 31;
    if ( !(dword_2FE070 & 1) )
        dword_2FE070 = 1;
    if ( !(dword_2FE06C & 1) )
        dword_2FE06C = 1;
    if ( !(dword_2FE068 & 1) )
        dword_2FE068 = 1;
    return result;
}
// 2FE068: using guessed type int dword_2FE068;
// 2FE06C: using guessed type int dword_2FE06C;
// 2FE070: using guessed type int dword_2FE070;
// 2FE074: using guessed type int dword_2FE074;
// 2FE078: using guessed type int dword_2FE078;
// 2FE07C: using guessed type int dword_2FE07C;
// 2FE080: using guessed type int dword_2FE080;
// 2FE084: using guessed type int dword_2FE084;
// 2FE088: using guessed type int dword_2FE088;
// 2FE08C: using guessed type int dword_2FE08C;
// 2FE090: using guessed type int dword_2FE090;
// 2FE094: using guessed type int dword_2FE094;

//----- (000268E8) --------------------------------------------------------
int sub_268E8()
{
    int result; // r0

    if ( !(dword_2FEEF0 & 1) )
        dword_2FEEF0 = 1;
    if ( !(dword_2FEEEC & 1) )
        dword_2FEEEC = 1;
    if ( !(dword_2FEEE8 & 1) )
        dword_2FEEE8 = 1;
    if ( !(dword_2FEEE4 & 1) )
        dword_2FEEE4 = 1;
    if ( !(dword_2FEEE0 & 1) )
        dword_2FEEE0 = 1;
    if ( !(dword_2FEEDC & 1) )
        dword_2FEEDC = 1;
    if ( !(dword_2FEED8 & 1) )
        dword_2FEED8 = 1;
    if ( !(dword_2FEED4 & 1) )
        dword_2FEED4 = 1;
    if ( !(dword_2FEED0 & 1) )
        dword_2FEED0 = 1;
    result = dword_2FEECC << 31;
    if ( !(dword_2FEECC & 1) )
        dword_2FEECC = 1;
    if ( !(dword_2FEEC8 & 1) )
        dword_2FEEC8 = 1;
    if ( !(dword_2FEEC4 & 1) )
        dword_2FEEC4 = 1;
    return result;
}
// 2FEEC4: using guessed type int dword_2FEEC4;
// 2FEEC8: using guessed type int dword_2FEEC8;
// 2FEECC: using guessed type int dword_2FEECC;
// 2FEED0: using guessed type int dword_2FEED0;
// 2FEED4: using guessed type int dword_2FEED4;
// 2FEED8: using guessed type int dword_2FEED8;
// 2FEEDC: using guessed type int dword_2FEEDC;
// 2FEEE0: using guessed type int dword_2FEEE0;
// 2FEEE4: using guessed type int dword_2FEEE4;
// 2FEEE8: using guessed type int dword_2FEEE8;
// 2FEEEC: using guessed type int dword_2FEEEC;
// 2FEEF0: using guessed type int dword_2FEEF0;

//----- (000269C4) --------------------------------------------------------
int sub_269C4()
{
    dword_2FEF50 = (int)&off_F24E0;
    sub_936DC();
    dword_2FEF4C = (int)&off_F2520;
    return sub_936DC();
}