//
// Created by 赵勇 on 2018/4/10.
//

//----- (0002BD84) --------------------------------------------------------
signed int __fastcall P2PClient::checkPeerState(P2PClient *this, sockaddr_in *a2)
{
    int *v2; // r3
    int v3; // r5
    int v4; // r7
    int v5; // r12
    int v6; // r3
    int v7; // r2

    v2 = (int *)*((_DWORD *)this + 2756);
    v3 = *v2;
    v4 = (v2[1] - *v2) >> 2;
    if ( !v4 )
        return ConnectionManager::isAlreadyStacked(*((ConnectionManager **)this + 2743), a2);
    v5 = 0;
    v6 = 0;
    while ( 1 )
    {
        v7 = *(_DWORD *)(v3 + 4 * v5);
        v5 = ++v6;
        if ( *(_DWORD *)(v7 + 4) == a2->sin_addr.s_addr && *(unsigned __int16 *)(v7 + 2) == a2->sin_port )
        break;
        if ( v6 == v4 )
            return ConnectionManager::isAlreadyStacked(*((ConnectionManager **)this + 2743), a2);
    }
    return 1;
}

//----- (0002BDFC) --------------------------------------------------------
int __fastcall P2PClient::announceRoutine(P2PClient *this)
{
    P2PClient *v1; // r4
    _DWORD *v2; // r5
    _DWORD *v3; // r3
    _DWORD **v4; // r2
    _DWORD *v5; // r3
    bool v6; // zf
    bool v7; // nf
    int result; // r0

    v1 = this;
    v2 = operator new(0xA8u);
    memset(v2, 0, 0xA8u);
    v3 = (_DWORD *)*((_DWORD *)v1 + 2748);
    *(_WORD *)v2 = 511;
    v4 = (_DWORD **)v3[2];
    v5 = (_DWORD *)(((v3[6] - v3[7]) >> 2) + ((((v3[9] - v3[5]) >> 2) - 1) << 7) + ((v3[4] - (signed int)v4) >> 2));
    v6 = v5 == 0;
    v7 = (signed int)v5 < 0;
    if ( (signed int)v5 > 0 )
        v5 = *v4;
    if ( !v7 && !v6 )
        v2[1] = *v5;
    memcpy(v2 + 2, *((const void **)v1 + 2749), 0xA0u);
    ConnectionManager::announce(*((_DWORD *)v1 + 2743), v2);
    operator delete(v2);
    result = (*(int (__cdecl **)(_DWORD, _DWORD))(**((_DWORD **)v1 + 1026) + 8))(
            *((_DWORD *)v1 + 1026),
            *(_DWORD *)(**((_DWORD **)v1 + 1026) + 8));
    *((_DWORD *)v1 + 1025) = result;
    return result;
}

//----- (0002BEEC) --------------------------------------------------------
int __fastcall P2PClient::heartbeatRoutine(P2PClient *this)
{
    P2PClient *v1; // r5
    _WORD *v2; // r0
    const struct sockaddr *addr; // lr
    _WORD *v4; // r4
    int v5; // r0
    int result; // r0

    v1 = this;
    v2 = operator new(0x14u);
    addr = (const struct sockaddr *)*((_DWORD *)v1 + 2746);
    v4 = v2;
    v5 = *(_DWORD *)v1;
    v4[1] = 0;
    *v4 = -254;
    *((_DWORD *)v4 + 1) = 0;
    *((_DWORD *)v4 + 2) = 0;
    *((_DWORD *)v4 + 3) = 0;
    *((_DWORD *)v4 + 4) = 0;
    sendto(v5, v4, 0x14u, 0, addr, 0x10u);
    operator delete(v4);
    result = (*(int (__cdecl **)(_DWORD, _DWORD))(**((_DWORD **)v1 + 1026) + 8))(
            *((_DWORD *)v1 + 1026),
            *(_DWORD *)(**((_DWORD **)v1 + 1026) + 8));
    *((_DWORD *)v1 + 1025) = result;
    return result;
}

//----- (0002BF9C) --------------------------------------------------------
int __fastcall P2PClient::connectPeers(int a1, _DWORD *a2)
{
    _DWORD *v2; // r12
    int v3; // r7
    int v4; // r3
    unsigned int v5; // r2
    unsigned int v6; // r9
    int addr; // r8
    _DWORD *v8; // ST0C_4
    _WORD *v9; // r4
    _DWORD *v10; // r0
    int v11; // r2
    _DWORD *v12; // r6
    int v13; // r3
    int v14; // r1
    unsigned int v15; // r3
    int v16; // r0
    int v17; // r0
    int result; // r0

    v2 = a2;
    v3 = a1;
    if ( a2 && (v4 = *a2, (unsigned int)(a2[1] - *a2) >> 2) )
    {
        v5 = 0;
        v6 = 0;
        do
        {
            addr = *(_DWORD *)(v4 + 4 * v5);
            v8 = v2;
            v9 = operator new(0x14u);
            *v9 = 0;
            v9[1] = 0;
            *((_DWORD *)v9 + 1) = 0;
            *((_DWORD *)v9 + 2) = 0;
            *((_DWORD *)v9 + 3) = 0;
            *((_DWORD *)v9 + 4) = 0;
            v10 = operator new(0x14u);
            v11 = *(_DWORD *)(addr + 4);
            v12 = v10;
            v13 = *(_DWORD *)(v3 + 10988);
            *v9 = 1023;
            v14 = *(_DWORD *)(v13 + 4);
            v9[1] = 0;
            *((_DWORD *)v9 + 1) = 0;
            *((_DWORD *)v9 + 2) = 0;
            *((_DWORD *)v9 + 3) = 0;
            *((_DWORD *)v9 + 4) = 0;
            v15 = *(unsigned __int16 *)(v13 + 2);
            *(_WORD *)v10 = -252;
            *((_WORD *)v10 + 1) = 0;
            v10[1] = v14;
            v10[2] = v11;
            v10[3] = bswap32(v15);
            v16 = *(_DWORD *)v3;
            v12[4] = bswap32(*(unsigned __int16 *)(addr + 2));
            ++v6;
            sendto(v16, v9, 0x14u, 0, (const struct sockaddr *)addr, 0x10u);
            sendto(*(_DWORD *)v3, v12, 0x14u, 0, *(const struct sockaddr **)(v3 + 10984), 0x10u);
            sendto(*(_DWORD *)v3, v12, 0x14u, 0, *(const struct sockaddr **)(v3 + 10984), 0x10u);
            ++*(_DWORD *)(addr + 16);
            operator delete(v9);
            operator delete(v12);
            v2 = v8;
            v5 = v6;
            v4 = *v8;
        }
        while ( v6 < (v8[1] - *v8) >> 2 );
        v17 = *(_DWORD *)(v3 + 4104);
    }
    else
    {
        v17 = *(_DWORD *)(a1 + 4104);
    }
    result = (*(int (__cdecl **)(int, _DWORD))(*(_DWORD *)v17 + 8))(v17, *(_DWORD *)(*(_DWORD *)v17 + 8));
    *(_DWORD *)(v3 + 4100) = result;
    return result;
}

//----- (0002C160) --------------------------------------------------------
int __fastcall P2PClient::startToRock(P2PClient *this, sockaddr_in *a2, sockaddr_in *a3, int a4)
{
P2PClient *v4; // r4
void *v5; // r0
int v6; // r1

v4 = this;
*((_DWORD *)this + 2747) = a2;
*((_DWORD *)this + 2746) = a3;
ConnectionManager::setLocalAddress(*((ConnectionManager **)this + 2743), a2);
v5 = malloc(0x48u);
v6 = *(_DWORD *)v4;
*((_DWORD *)v4 + 1027) = v5;
sub_8B958((unsigned int)v5, v6, 18, (int)onRecvPointer, (int)v5);
sub_8AD50(*((_DWORD *)v4 + 1027), 0);
P2PClient::connectPeers((int)v4, *((_DWORD **)v4 + 2756));
P2PClient::announceRoutine(v4);
return P2PClient::heartbeatRoutine(v4);
}

//----- (0002C1E8) --------------------------------------------------------
ssize_t __fastcall P2PClient::onInvoke(int *a1, _DWORD *a2)
{
    int v2; // r2
    unsigned int v3; // r12
    int v4; // r5
    int v5; // r0
    struct sockaddr addr; // [sp+Ch] [bp-24h]

    v2 = a2[1];
    addr.sa_family = 2;
    v3 = a2[3];
    *(_DWORD *)&addr.sa_data[2] = v2;
    v4 = *a1;
    v5 = a2[1];
    *(_WORD *)a2 = 1535;
    *(_WORD *)addr.sa_data = __rev16(__rev16(bswap32(v3)));
    return sendto(v4, a2, 0x14u, 0, &addr, 0x10u);
}

//----- (0002C278) --------------------------------------------------------
int __fastcall P2PClient::onRequest(int a1, int a2, sockaddr_in *a3)
{
    int v3; // r7
    _DWORD *v4; // r3
    int v5; // r9
    int v6; // r8
    int v7; // r1
    int **v8; // r2
    signed __int64 v9; // r4
    int v10; // r0
    int v11; // r3
    unsigned int v12; // r0
    int v13; // r4
    int result; // r0
    _DWORD *v15; // r3
    int v16; // r1
    int v17; // r2
    signed int v18; // r3
    unsigned int **v19; // r2
    unsigned int *v20; // r11
    int v21; // r4
    _DWORD *v22; // r3
    int v23; // r2
    int v24; // r0
    int v25; // r3
    unsigned int v26; // r1
    _DWORD *v27; // r3
    int v28; // r2
    _BYTE *v29; // r1
    OnePacket *v30; // r10
    unsigned int v31; // r3
    unsigned int v32; // r6
    unsigned int v33; // r2
    unsigned int v34; // r1
    unsigned int v35; // r3
    unsigned __int16 addr_len; // ST04_2
    int v37; // r0
    _DWORD *v38; // r4
    int v39; // r0
    int v40; // r2
    int v41; // r3
    signed int v42; // t1
    size_t v43; // r0
    unsigned int v44; // r2
    unsigned int v45; // r0
    int v46; // r3
    int v47; // r1
    int v48; // r3
    int v49; // r3
    bool v50; // zf
    int v51; // r3
    char *v52; // r8
    int v53; // r2
    unsigned int v54; // r3
    _DWORD *v55; // r3
    int v56; // r3
    int v57; // r3
    char *v58; // r1
    int v59; // r9
    int v60; // r11
    unsigned int v61; // r6
    int v62; // r3
    char *v63; // r6
    int v64; // r3
    int v65; // r3
    int v66; // r3
    int v67; // r3
    unsigned int v68; // r8
    char *v69; // r0
    const void *v70; // r1
    int v71; // r2
    char *v72; // r10
    signed int v73; // [sp+18h] [bp-B8h]
    unsigned __int8 *v74; // [sp+1Ch] [bp-B4h]
    char *nptr; // [sp+20h] [bp-B0h]
    sockaddr_in *addr; // [sp+28h] [bp-A8h]
    int v77; // [sp+2Ch] [bp-A4h]
    int v78; // [sp+30h] [bp-A0h]
    void *src; // [sp+38h] [bp-98h]
    char v80; // [sp+3Ch] [bp-94h]
    int v81; // [sp+40h] [bp-90h]
    int v82; // [sp+44h] [bp-8Ch]
    int v83; // [sp+48h] [bp-88h]
    unsigned int v84[22]; // [sp+4Ch] [bp-84h]
    int v85; // [sp+A4h] [bp-2Ch]

    v4 = *(_DWORD **)(a1 + 10992);
    v5 = a1;
    v6 = a2;
    v7 = v4[5];
    addr = a3;
    v8 = (int **)v4[2];
    HIDWORD(v9) = &_stack_chk_guard;
    if ( !(((v4[6] - v4[7]) >> 2) + ((((v4[9] - v7) >> 2) - 1) << 7) + ((v4[4] - (signed int)v8) >> 2)) )
        sub_BFC08("deque::_M_range_check");
    v10 = (int)v8 - v4[3];
    v11 = v10 >> 2;
    if ( (unsigned int)(v10 >> 2) > 0x7F )
    {
        if ( v11 <= 0 )
            v12 = ~((unsigned int)~v11 >> 7);
        else
            v12 = v10 >> 9;
        v8 = (int **)(*(_DWORD *)(v7 + 4 * v12) + 4 * (v11 - (v12 << 7)));
    }
    nptr = (char *)(v6 + 824);
    v13 = **v8;
    result = atoi((const char *)(v6 + 824));
    LODWORD(v9) = result - v13;
    if ( (signed int)v9 >= 0 )
    {
        v15 = *(_DWORD **)(v5 + 10992);
        v16 = v15[5];
        v17 = v15[2];
        HIDWORD(v9) = (v15[6] - v15[7]) >> 2;
        result = HIDWORD(v9) + ((((v15[9] - v16) >> 2) - 1) << 7) + ((v15[4] - v17) >> 2);
        if ( (signed int)v9 < result )
        {
            v18 = v9 + ((v17 - v15[3]) >> 2);
            if ( (unsigned int)v18 > 0x7F )
            {
                v45 = v18 <= 0 ? ~((unsigned int)~v18 >> 7) : v18 >> 7;
                v19 = (unsigned int **)(*(_DWORD *)(v16 + 4 * v45) + 4 * (v18 - (v45 << 7)));
            }
            else
            {
                v19 = (unsigned int **)(v17 + 4 * v9);
            }
            v20 = *v19;
            HIDWORD(v9) = **v19;
            if ( HIDWORD(v9) == atoi(nptr) )
                goto LABEL_78;
            v21 = v9 - 1;
            v22 = *(_DWORD **)(v5 + 10992);
            v23 = v22[2];
            v24 = v22[5];
            v25 = v21 + ((v23 - v22[3]) >> 2);
            if ( (unsigned int)v25 > 0x7F )
            {
                if ( v25 <= 0 )
                    v26 = ~((unsigned int)~v25 >> 7);
                else
                    v26 = v25 >> 7;
                v23 = *(_DWORD *)(v24 + 4 * v26);
                v21 = v25 - (v26 << 7);
            }
            v20 = *(unsigned int **)(v23 + 4 * v21);
            LODWORD(v9) = *v20;
            result = atoi(nptr);
            if ( (_DWORD)v9 == result )
            {
                LABEL_78:
                LODWORD(v9) = *(_DWORD *)(v5 + 4120);
                pthread_mutex_lock((pthread_mutex_t *)(v9 + 52));
                v27 = *(_DWORD **)(v9 + 20);
                if ( *(_DWORD **)(v9 + 36) != v27
                     && (HIDWORD(v9) = *v27, v28 = *(_DWORD *)(v9 + 8), v29 = (_BYTE *)(v28 + *v27), *(_BYTE *)(v28 + *v27)) )
                {
                    if ( v27 == (_DWORD *)(*(_DWORD *)(v9 + 28) - 4) )
                    {
                        operator delete(*(void **)(v9 + 24));
                        v46 = *(_DWORD *)(v9 + 32);
                        v47 = *(_DWORD *)(v9 + 8);
                        *(_DWORD *)(v9 + 32) = v46 + 4;
                        v48 = *(_DWORD *)(v46 + 4);
                        v29 = (_BYTE *)(v47 + HIDWORD(v9));
                        *(_DWORD *)(v9 + 28) = v48 + 512;
                        *(_DWORD *)(v9 + 24) = v48;
                        *(_DWORD *)(v9 + 20) = v48;
                    }
                    else
                    {
                        *(_DWORD *)(v9 + 20) = v27 + 1;
                    }
                    *v29 = 0;
                    result = pthread_mutex_unlock((pthread_mutex_t *)(v9 + 52));
                    v30 = (OnePacket *)(*(_DWORD *)(v9 + 4) + 1256 * HIDWORD(v9));
                    if ( v30 )
                    {
                        v31 = v20[2];
                        v3 = v6 + 22;
                        v32 = 0;
                        v74 = (unsigned __int8 *)(v5 + 2052);
                        v33 = v31 / 0x486;
                        v73 = v31 / 0x486;
                        v34 = v31 % 0x486;
                        v35 = *(_DWORD *)(v6 + 4);
                        if ( v34 )
                            v73 = v33 + 1;
                        v78 = v34;
                        v77 = v73 - 1;
                        while ( v35 > 0x320 || v32 < v35 )
                        {
                            v42 = *(unsigned __int16 *)(v3 + 2);
                            v3 += 2;
                            v9 = __PAIR__(v73, v42);
                            if ( v73 > v42 )
                            {
                                v43 = *(_DWORD *)(v5 + 10976);
                                v44 = *v20;
                                if ( v77 == (_DWORD)v9 && (HIDWORD(v9) = v78) != 0 )
                                {
                                    LODWORD(v9) = v78;
                                    result = LocalMemory::readMemory(v43, v74, v44, v77, v78);
                                    if ( result < 0 )
                                        goto LABEL_9;
                                    v9 = *(_QWORD *)(v6 + 16);
                                    OnePacket::setPacketData(
                                            v30,
                                            (const char *)v74,
                                            (unsigned __int16)v78,
                                            nptr,
                                            v20[2],
                                            v73 - 1,
                                            *(_QWORD *)(v6 + 8),
                                            *(_QWORD *)(v6 + 16));
                                }
                                else
                                {
                                    result = LocalMemory::readMemory(v43, v74, v44, v9, 1158);
                                    if ( result < 0 )
                                        goto LABEL_9;
                                    addr_len = v9;
                                    v9 = *(_QWORD *)(v6 + 16);
                                    OnePacket::setPacketData(
                                            v30,
                                            (const char *)v74,
                                            1158,
                                            nptr,
                                            v20[2],
                                            addr_len,
                                            *(_QWORD *)(v6 + 8),
                                            *(_QWORD *)(v6 + 16));
                                }
                                result = OnePacket::getPacketData(v30, (char **)&src);
                                if ( result <= 0 )
                                    goto LABEL_9;
                                v37 = OnePacket::getPacketDataSize(v30);
                                addP2pUploadBytes(v37);
                                MD5Init(v84);
                                MD5Update(v84, (char *)src, 0x4D0u);
                                MD5Final(v84, (int)&v80);
                                v38 = operator new(0x4E0u);
                                memset(v38, 0, 0x4E0u);
                                memcpy(v38, src, 0x4D0u);
                                v39 = *(_DWORD *)&v80;
                                v40 = v82;
                                v41 = v83;
                                v38[309] = v81;
                                v38[310] = v40;
                                v38[311] = v41;
                                v38[308] = v39;
                                sendto(*(_DWORD *)v5, v38, 0x4E0u, 0, (const struct sockaddr *)addr, 0x10u);
                                operator delete(v38);
                                v35 = *(_DWORD *)(v6 + 4);
                            }
                            ++v32;
                        }
                        result = ConnectionManager::onUploadPacket(*(ConnectionManager **)(v5 + 10972), addr);
                        LODWORD(v9) = *(_DWORD *)(v5 + 4120);
                        HIDWORD(v9) = 738624949 * (((signed int)v30 - *(_DWORD *)(v9 + 4)) >> 3);
                        if ( v9 >= 0 && SHIDWORD(v9) < *(_DWORD *)v9 && !*(_BYTE *)(*(_DWORD *)(v9 + 8) + HIDWORD(v9)) )
                        {
                            v3 = v9 + 52;
                            pthread_mutex_lock((pthread_mutex_t *)(v9 + 52));
                            if ( !*(_BYTE *)(*(_DWORD *)(v9 + 8) + HIDWORD(v9)) )
                            {
                                OnePacket::reset((OnePacket *)(*(_DWORD *)(v9 + 4) + 1256 * HIDWORD(v9)));
                                v49 = *(_DWORD *)(v9 + 36);
                                if ( v49 == *(_DWORD *)(v9 + 44) - 4 )
                                    goto LABEL_58;
                                v50 = v49 == 0;
                                v51 = v49 + 4;
                                if ( !v50 )
                                    *(_DWORD *)(v51 - 4) = HIDWORD(v9);
                                *(_DWORD *)(v9 + 36) = v51;
                                goto LABEL_56;
                            }
                            goto LABEL_49;
                        }
                    }
                }
                else
                {
                    result = pthread_mutex_unlock((pthread_mutex_t *)(v9 + 52));
                }
            }
        }
    }
    LABEL_9:
    while ( v85 != _stack_chk_guard )
    {
        LABEL_58:
        v52 = *(char **)(v9 + 48);
        v53 = *(_DWORD *)(v9 + 12);
        v54 = *(_DWORD *)(v9 + 16);
        if ( v54 - ((signed int)&v52[-v53] >> 2) <= 1 )
        {
            v58 = *(char **)(v9 + 32);
            v59 = ((v52 - v58) >> 2) + 1;
            v60 = ((v52 - v58) >> 2) + 2;
            if ( v54 <= 2 * v60 )
            {
                if ( v54 )
                {
                    v68 = 2 * v54 + 2;
                    if ( v68 > 0x3FFFFFFF )
                        sub_BFA08();
                }
                else
                {
                    v68 = 3;
                }
                v69 = (char *)operator new(4 * v68);
                v70 = *(const void **)(v9 + 32);
                v71 = (*(_DWORD *)(v9 + 48) + 4 - (signed int)v70) >> 2;
                v72 = v69;
                v63 = &v69[4 * ((v68 - v60) >> 1)];
                if ( v71 )
                    memmove(&v69[4 * ((v68 - v60) >> 1)], v70, 4 * v71);
                operator delete(*(void **)(v9 + 12));
                *(_DWORD *)(v9 + 12) = v72;
                *(_DWORD *)(v9 + 16) = v68;
            }
            else
            {
                v61 = (v54 - v60) >> 1;
                v62 = (int)(v52 + 4);
                v63 = (char *)(v53 + 4 * v61);
                if ( v58 <= v63 )
                {
                    v67 = (v62 - (signed int)v58) >> 2;
                    if ( v67 )
                        memmove(&v63[4 * v59 + -4 * v67], v58, 4 * v67);
                }
                else
                {
                    v64 = v62 - (_DWORD)v58;
                    if ( v64 >> 2 )
                        memmove(v63, v58, 4 * (v64 >> 2));
                }
            }
            *(_DWORD *)(v9 + 32) = v63;
            v65 = *(_DWORD *)v63;
            v52 = &v63[4 * (v59 + 0x3FFFFFFF)];
            *(_DWORD *)(v9 + 48) = v52;
            *(_DWORD *)(v9 + 28) = v65 + 512;
            *(_DWORD *)(v9 + 24) = v65;
            v66 = *(_DWORD *)v52;
            *(_DWORD *)(v9 + 44) = *(_DWORD *)v52 + 512;
            *(_DWORD *)(v9 + 40) = v66;
        }
        *((_DWORD *)v52 + 1) = operator new(0x200u);
        v55 = *(_DWORD **)(v9 + 36);
        if ( v55 )
            *v55 = HIDWORD(v9);
        v56 = *(_DWORD *)(v9 + 48);
        *(_DWORD *)(v9 + 48) = v56 + 4;
        v57 = *(_DWORD *)(v56 + 4);
        *(_DWORD *)(v9 + 44) = v57 + 512;
        *(_DWORD *)(v9 + 40) = v57;
        *(_DWORD *)(v9 + 36) = v57;
        LABEL_56:
        *(_BYTE *)(*(_DWORD *)(v9 + 8) + HIDWORD(v9)) = 1;
        LABEL_49:
        result = pthread_mutex_unlock((pthread_mutex_t *)v3);
    }
    return result;
}

//----- (0002C958) --------------------------------------------------------
signed int __fastcall P2PClient::savePacketData(P2PClient *this, OnePacket *a2)
{
    pthread_mutex_t *v2; // r8
    P2PClient *v3; // r4
    OnePacket *v4; // r7
    int v5; // r3
    int v6; // r5
    OneRequest *v7; // r6
    char *v8; // r0
    int v9; // r0
    int v10; // r10
    int v11; // r3
    int v12; // r5
    OneFile *v13; // r6
    char *v14; // r0
    int v15; // r0
    unsigned int v17; // r5
    int v18; // r0

    v2 = (pthread_mutex_t *)((char *)this + 11004);
    v3 = this;
    v4 = a2;
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 11004));
    v5 = *((_DWORD *)v3 + 1034);
    if ( *((_DWORD *)v3 + 1035) - v5 <= 3 )
    {
        LABEL_7:
        v10 = 0;
    }
    else
    {
        v6 = 0;
        while ( 1 )
        {
            v7 = *(OneRequest **)(v5 + 4 * v6++);
            if ( v7 )
            {
                v8 = OnePacket::getPacketFilePath(v4);
                v9 = atoi(v8);
                if ( OneRequest::isTheSameRequest(v7, v9) )
                    break;
            }
            v5 = *((_DWORD *)v3 + 1034);
            if ( v6 >= (*((_DWORD *)v3 + 1035) - v5) >> 2 )
            goto LABEL_7;
        }
        v17 = OnePacket::getPacketFileSize(v4);
        v18 = OnePacket::getPacketSequence(v4);
        if ( OneRequest::refreshRequestData(v7, v17, v18) == -101 )
            goto LABEL_13;
        v10 = v17 / 0x486;
        if ( v17 % 0x486 )
            ++v10;
    }
    v11 = *((_DWORD *)v3 + 1031);
    if ( *((_DWORD *)v3 + 1032) - v11 <= 3 )
    goto LABEL_13;
    v12 = 0;
    while ( 1 )
    {
        v13 = *(OneFile **)(v11 + 4 * v12++);
        if ( v13 )
        {
            v14 = OnePacket::getPacketFilePath(v4);
            v15 = atoi(v14);
            if ( OneFile::isWithSameId(v13, v15) )
                break;
        }
        v11 = *((_DWORD *)v3 + 1031);
        if ( v12 >= (*((_DWORD *)v3 + 1032) - v11) >> 2 )
        goto LABEL_13;
    }
    if ( OneFile::addOnePacket(v13, v4, v10) )
    {
        LABEL_13:
        pthread_mutex_unlock(v2);
        return -1;
    }
    pthread_mutex_unlock(v2);
    return 0;
}

//----- (0002CACC) --------------------------------------------------------
int __fastcall P2PClient::onRecvedPacket(int a1, const char *a2, unsigned __int16 a3, sockaddr_in *a4)
{
    int v4; // r5
    int v5; // r7
    unsigned __int16 v6; // r8
    sockaddr_in *v7; // r6
    const char *v8; // r9
    int *v9; // r3
    int v10; // r4
    int v11; // r2
    _BYTE *v12; // r1
    int result; // r0
    OnePacket *v14; // r4
    unsigned __int64 v15; // r0
    ConnectionManager *v16; // r7
    double v17; // r0
    int v18; // r0
    int v19; // r5
    int v20; // r4
    pthread_mutex_t *v21; // r6
    OnePacket *v22; // r0
    int v23; // r3
    bool v24; // zf
    int v25; // r3
    int v26; // r3
    int v27; // r1
    int v28; // r3
    char *v29; // r8
    int v30; // r2
    unsigned int v31; // r3
    int *v32; // r3
    int v33; // r3
    int v34; // r3
    char *v35; // r1
    int v36; // r9
    int v37; // r10
    unsigned int v38; // r7
    int v39; // r3
    char *v40; // r7
    int v41; // r3
    int v42; // r3
    unsigned int v43; // r8
    char *v44; // r0
    const void *v45; // r1
    int v46; // r2
    char *v47; // r11
    int v48; // r3
    int v49; // [sp+0h] [bp-30h]
    int v50; // [sp+4h] [bp-2Ch]

    v4 = a1;
    v5 = *(_DWORD *)(a1 + 4120);
    v6 = a3;
    v7 = a4;
    v8 = a2;
    pthread_mutex_lock((pthread_mutex_t *)(v5 + 52));
    v9 = *(int **)(v5 + 20);
    if ( *(int **)(v5 + 36) == v9 )
        return pthread_mutex_unlock((pthread_mutex_t *)(v5 + 52));
    v10 = *v9;
    v11 = *(_DWORD *)(v5 + 8);
    v12 = (_BYTE *)(v11 + *v9);
    if ( !*(_BYTE *)(v11 + *v9) )
        return pthread_mutex_unlock((pthread_mutex_t *)(v5 + 52));
    if ( v9 == (int *)(*(_DWORD *)(v5 + 28) - 4) )
    {
        operator delete(*(void **)(v5 + 24));
        v26 = *(_DWORD *)(v5 + 32);
        v27 = *(_DWORD *)(v5 + 8);
        *(_DWORD *)(v5 + 32) = v26 + 4;
        v28 = *(_DWORD *)(v26 + 4);
        v12 = (_BYTE *)(v27 + v10);
        *(_DWORD *)(v5 + 28) = v28 + 512;
        *(_DWORD *)(v5 + 24) = v28;
        *(_DWORD *)(v5 + 20) = v28;
    }
    else
    {
        *(_DWORD *)(v5 + 20) = v9 + 1;
    }
    *v12 = 0;
    result = pthread_mutex_unlock((pthread_mutex_t *)(v5 + 52));
    v14 = (OnePacket *)(*(_DWORD *)(v5 + 4) + 1256 * v10);
    if ( v14 )
    {
        result = OnePacket::setPacketData(v14, v8, v6, v7);
        if ( result )
        {
            v19 = *(_DWORD *)(v4 + 4120);
            v20 = 738624949 * (((signed int)v14 - *(_DWORD *)(v19 + 4)) >> 3);
            if ( v20 >= 0 && v20 < *(_DWORD *)v19 && !*(_BYTE *)(*(_DWORD *)(v19 + 8) + v20) )
            {
                v21 = (pthread_mutex_t *)(v19 + 52);
                pthread_mutex_lock((pthread_mutex_t *)(v19 + 52));
                if ( !*(_BYTE *)(*(_DWORD *)(v19 + 8) + v20) )
                {
                    v22 = (OnePacket *)(*(_DWORD *)(v19 + 4) + 1256 * v20);
                    goto LABEL_23;
                }
                return pthread_mutex_unlock(v21);
            }
        }
        else
        {
            gettimeofday((struct timeval *)&v49, 0);
            v15 = 1000LL * v49 + v50 / 0x3E8uLL;
            if ( *((_QWORD *)v14 + 2) >= v15 )
            {
                v16 = *(ConnectionManager **)(v4 + 10972);
                LODWORD(v17) = _floatundidf(v15 - *((_QWORD *)v14 + 1));
                ConnectionManager::onPacketRecved(v16, v7, v17);
            }
            else
            {
                ConnectionManager::onPacketRecved(*(ConnectionManager **)(v4 + 10972), v7, 0.0);
            }
            v18 = OnePacket::getPacketDataSize(v14);
            addP2pDownloadBytes(v18);
            result = P2PClient::savePacketData((P2PClient *)v4, v14);
            if ( result )
            {
                v19 = *(_DWORD *)(v4 + 4120);
                v20 = 738624949 * (((signed int)v14 - *(_DWORD *)(v19 + 4)) >> 3);
                if ( v20 >= 0 && v20 < *(_DWORD *)v19 && !*(_BYTE *)(*(_DWORD *)(v19 + 8) + v20) )
                {
                    v21 = (pthread_mutex_t *)(v19 + 52);
                    pthread_mutex_lock((pthread_mutex_t *)(v19 + 52));
                    if ( !*(_BYTE *)(*(_DWORD *)(v19 + 8) + v20) )
                    {
                        v22 = (OnePacket *)(*(_DWORD *)(v19 + 4) + 1256 * v20);
                        LABEL_23:
                        OnePacket::reset(v22);
                        v23 = *(_DWORD *)(v19 + 36);
                        if ( v23 == *(_DWORD *)(v19 + 44) - 4 )
                        {
                            v29 = *(char **)(v19 + 48);
                            v30 = *(_DWORD *)(v19 + 12);
                            v31 = *(_DWORD *)(v19 + 16);
                            if ( v31 - ((signed int)&v29[-v30] >> 2) <= 1 )
                            {
                                v35 = *(char **)(v19 + 32);
                                v36 = ((v29 - v35) >> 2) + 1;
                                v37 = ((v29 - v35) >> 2) + 2;
                                if ( v31 <= 2 * v37 )
                                {
                                    if ( v31 )
                                    {
                                        v43 = 2 * v31 + 2;
                                        if ( v43 > 0x3FFFFFFF )
                                            sub_BFA08();
                                    }
                                    else
                                    {
                                        v43 = 3;
                                    }
                                    v44 = (char *)operator new(4 * v43);
                                    v45 = *(const void **)(v19 + 32);
                                    v46 = (*(_DWORD *)(v19 + 48) + 4 - (signed int)v45) >> 2;
                                    v47 = v44;
                                    v40 = &v44[4 * ((v43 - v37) >> 1)];
                                    if ( v46 )
                                        memmove(&v44[4 * ((v43 - v37) >> 1)], v45, 4 * v46);
                                    operator delete(*(void **)(v19 + 12));
                                    *(_DWORD *)(v19 + 12) = v47;
                                    *(_DWORD *)(v19 + 16) = v43;
                                }
                                else
                                {
                                    v38 = (v31 - v37) >> 1;
                                    v39 = v29 + 4 - v35;
                                    v40 = (char *)(v30 + 4 * v38);
                                    if ( v35 <= v40 )
                                    {
                                        v48 = v39 >> 2;
                                        if ( v48 )
                                            memmove(&v40[4 * v36 + -4 * v48], v35, 4 * v48);
                                    }
                                    else if ( v39 >> 2 )
                                    {
                                        memmove(v40, v35, 4 * (v39 >> 2));
                                    }
                                }
                                *(_DWORD *)(v19 + 32) = v40;
                                v41 = *(_DWORD *)v40;
                                v29 = &v40[4 * (v36 + 0x3FFFFFFF)];
                                *(_DWORD *)(v19 + 48) = v29;
                                *(_DWORD *)(v19 + 28) = v41 + 512;
                                *(_DWORD *)(v19 + 24) = v41;
                                v42 = *(_DWORD *)v29;
                                *(_DWORD *)(v19 + 44) = *(_DWORD *)v29 + 512;
                                *(_DWORD *)(v19 + 40) = v42;
                            }
                            *((_DWORD *)v29 + 1) = operator new(0x200u);
                            v32 = *(int **)(v19 + 36);
                            if ( v32 )
                                *v32 = v20;
                            v33 = *(_DWORD *)(v19 + 48);
                            *(_DWORD *)(v19 + 48) = v33 + 4;
                            v34 = *(_DWORD *)(v33 + 4);
                            *(_DWORD *)(v19 + 44) = v34 + 512;
                            *(_DWORD *)(v19 + 40) = v34;
                            *(_DWORD *)(v19 + 36) = v34;
                        }
                        else
                        {
                            v24 = v23 == 0;
                            v25 = v23 + 4;
                            if ( !v24 )
                                *(_DWORD *)(v25 - 4) = v20;
                            *(_DWORD *)(v19 + 36) = v25;
                        }
                        *(_BYTE *)(*(_DWORD *)(v19 + 8) + v20) = 1;
                        return pthread_mutex_unlock(v21);
                    }
                    return pthread_mutex_unlock(v21);
                }
            }
        }
    }
    return result;
}

//----- (0002CEE8) --------------------------------------------------------
int __fastcall P2PClient::onRecv(P2PClient *this, int a2, __int16 a3, void *a4)
{
P2PClient *v4; // r4
int v5; // r0
struct sockaddr *v6; // r2
unsigned int v7; // r3
int result; // r0
int v9; // r9
sockaddr_in *v10; // r1
ConnectionManager *v11; // r0
int v12; // r0
struct sockaddr *addr; // ST00_4
int addr_len; // [sp+8h] [bp-90h]
char v15; // [sp+Ch] [bp-8Ch]
unsigned int v16[22]; // [sp+1Ch] [bp-7Ch]

v4 = this;
v5 = *(_DWORD *)this;
if ( v5 <= 0 )
return -1;
v6 = (struct sockaddr *)*((_DWORD *)v4 + 2745);
addr_len = 16;
if ( recvfrom(v5, (char *)v4 + 4, 0x800u, 0, v6, (socklen_t *)&addr_len) <= 4 )
return -1;
v7 = *((unsigned __int16 *)v4 + 2);
if ( v7 == 1535 )
{
ConnectionManager::onConnectSuccess(*((_DWORD *)v4 + 2743), (int)v4 + 4);
result = 0;
}
else if ( v7 < 0x600 )
{
if ( v7 == 511 )
{
pthread_mutex_lock((pthread_mutex_t *)v4 + 459);
if ( *((_BYTE *)v4 + 11012) )
{
*((_BYTE *)v4 + 11012) = 0;
add_recvAnnoun();
}
pthread_mutex_unlock((pthread_mutex_t *)v4 + 459);
ConnectionManager::onAnnounce(*((_DWORD *)v4 + 2743), (int)v4 + 4, *((sockaddr_in **)v4 + 2745));
result = 0;
}
else
{
if ( v7 != 1023 )
return 0;
v9 = *((unsigned __int16 *)v4 + 3);
v10 = (sockaddr_in *)*((_DWORD *)v4 + 2745);
v11 = (ConnectionManager *)*((_DWORD *)v4 + 2743);
if ( *((_WORD *)v4 + 3) )
{
ConnectionManager::onConnectDirectly(v11, v10, 1);
result = 0;
}
else
{
ConnectionManager::onConnectDirectly(v11, v10, *((unsigned __int16 *)v4 + 3));
v12 = *(_DWORD *)v4;
addr = (struct sockaddr *)*((_DWORD *)v4 + 2745);
*((_WORD *)v4 + 3) = 1;
sendto(v12, (char *)v4 + 4, 0x14u, v9, addr, 0x10u);
result = v9;
}
}
}
else
{
switch ( v7 )
{
case 0x8FFu:
MD5Init(v16);
MD5Update(v16, (char *)v4 + 4, 0x4D0u);
MD5Final(v16, (int)&v15);
if ( !memcmp(&v15, (char *)v4 + 1236, 0x10u) )
P2PClient::onRecvedPacket((int)v4, (const char *)v4 + 4, 0x4D0u, *((sockaddr_in **)v4 + 2745));
return 0;
case 0xFF04u:
result = ConnectionManager::onConnect(*((_DWORD *)v4 + 2743), (int)v4 + 4);
if ( result )
{
P2PClient::onInvoke((int *)v4, (_DWORD *)v4 + 1);
result = 0;
}
break;
case 0x7FFu:
P2PClient::onRequest((int)v4, (int)v4 + 4, *((sockaddr_in **)v4 + 2745));
result = 0;
break;
default:
return 0;
}
}
return result;
}

//----- (0002D134) --------------------------------------------------------
int __fastcall onRecvPointer(int a1, __int16 a2, void *a3)
{
    return P2PClient::onRecv((P2PClient *)dword_F3D50, a1, a2, a3);
}
// F3D50: using guessed type int dword_F3D50;

//----- (0002D160) --------------------------------------------------------
int __fastcall P2PClient::clearRequest(int result, OneRequest *a2)
{
    int v2; // r3
    _DWORD *v3; // r7
    OneRequest *v4; // r6
    int v5; // r4
    OneRequest *v6; // r5
    int v7; // r8
    int v8; // r5
    int v9; // r3
    int v10; // r12
    int v11; // r2
    int v12; // t1
    int v13; // r4
    int v14; // r5
    int v15; // r3
    bool v16; // zf
    int v17; // r3
    int v18; // r3
    int v19; // r0
    unsigned int v20; // r2
    char *v21; // r7
    int *v22; // r3
    int v23; // r3
    int v24; // r3
    char *v25; // r1
    int v26; // r8
    int v27; // r10
    int v28; // r3
    char *v29; // r6
    int v30; // r3
    int v31; // r3
    int v32; // r3
    int v33; // r3
    unsigned int v34; // r7
    char *v35; // r0
    const void *v36; // r1
    int v37; // r2
    char *v38; // r11
    int v39; // [sp+0h] [bp-30h]
    int v40; // [sp+4h] [bp-2Ch]

    v2 = *(_DWORD *)(result + 4136);
    v3 = (_DWORD *)result;
    v4 = a2;
    if ( *(_DWORD *)(result + 4140) - v2 > 3 )
    {
        v5 = 0;
        while ( 1 )
        {
            v6 = *(OneRequest **)(v2 + 4 * v5);
            v7 = OneRequest::getFileId(v4);
            result = OneRequest::getFileId(v6);
            if ( v7 == result )
                break;
            v2 = v3[1034];
            if ( ++v5 >= (v3[1035] - v2) >> 2 )
                return result;
        }
        if ( v6 )
        {
            v40 = 0;
            v39 = 0;
            OneRequest::getRequestData((int)v4, &v40, 0);
            result = OneRequest::getRequestData((int)v6, &v39, 0);
            v8 = *(unsigned __int16 *)(v40 + 10);
            if ( *(_WORD *)(v40 + 10) )
            {
                v9 = v39;
                v10 = v40 + 11;
                v11 = 0;
                do
                {
                    v12 = *(unsigned __int8 *)(v10++ + 1);
                    ++v11;
                    ++v9;
                    if ( v12 == 1 )
                        *(_BYTE *)(v9 + 11) = 0;
                }
                while ( v11 != v8 );
            }
            v13 = v3[1028];
            v14 = 1212814569 * (((signed int)v4 - *(_DWORD *)(v13 + 4)) >> 3);
            if ( v14 >= 0 && v14 < *(_DWORD *)v13 && !*(_BYTE *)(*(_DWORD *)(v13 + 8) + v14) )
            {
                pthread_mutex_lock((pthread_mutex_t *)(v13 + 52));
                if ( !*(_BYTE *)(*(_DWORD *)(v13 + 8) + v14) )
                {
                    OneRequest::reset((OneRequest *)(*(_DWORD *)(v13 + 4) + 6856 * v14));
                    v15 = *(_DWORD *)(v13 + 36);
                    if ( v15 == *(_DWORD *)(v13 + 44) - 4 )
                    {
                        v18 = *(_DWORD *)(v13 + 48);
                        v19 = *(_DWORD *)(v13 + 12);
                        v20 = *(_DWORD *)(v13 + 16);
                        if ( v20 - ((v18 - v19) >> 2) <= 1 )
                        {
                            v25 = *(char **)(v13 + 32);
                            v26 = ((v18 - (signed int)v25) >> 2) + 1;
                            v27 = ((v18 - (signed int)v25) >> 2) + 2;
                            if ( v20 <= 2 * v27 )
                            {
                                if ( v20 )
                                {
                                    v34 = 2 * v20 + 2;
                                    if ( v34 > 0x3FFFFFFF )
                                        sub_BFA08();
                                }
                                else
                                {
                                    v34 = 3;
                                }
                                v35 = (char *)operator new(4 * v34);
                                v36 = *(const void **)(v13 + 32);
                                v37 = (*(_DWORD *)(v13 + 48) + 4 - (signed int)v36) >> 2;
                                v38 = v35;
                                v29 = &v35[4 * ((v34 - v27) >> 1)];
                                if ( v37 )
                                    memmove(&v35[4 * ((v34 - v27) >> 1)], v36, 4 * v37);
                                operator delete(*(void **)(v13 + 12));
                                *(_DWORD *)(v13 + 12) = v38;
                                *(_DWORD *)(v13 + 16) = v34;
                            }
                            else
                            {
                                v28 = v18 + 4;
                                v29 = (char *)(v19 + 4 * ((v20 - v27) >> 1));
                                if ( v25 <= v29 )
                                {
                                    v33 = (v28 - (signed int)v25) >> 2;
                                    if ( v33 )
                                        memmove(&v29[4 * v26 + -4 * v33], v25, 4 * v33);
                                }
                                else
                                {
                                    v30 = v28 - (_DWORD)v25;
                                    if ( v30 >> 2 )
                                        memmove(v29, v25, 4 * (v30 >> 2));
                                }
                            }
                            *(_DWORD *)(v13 + 32) = v29;
                            v31 = *(_DWORD *)v29;
                            v21 = &v29[4 * (v26 + 0x3FFFFFFF)];
                            *(_DWORD *)(v13 + 48) = v21;
                            *(_DWORD *)(v13 + 28) = v31 + 512;
                            *(_DWORD *)(v13 + 24) = v31;
                            v32 = *(_DWORD *)v21;
                            *(_DWORD *)(v13 + 44) = *(_DWORD *)v21 + 512;
                            *(_DWORD *)(v13 + 40) = v32;
                        }
                        else
                        {
                            v21 = *(char **)(v13 + 48);
                        }
                        *((_DWORD *)v21 + 1) = operator new(0x200u);
                        v22 = *(int **)(v13 + 36);
                        if ( v22 )
                            *v22 = v14;
                        v23 = *(_DWORD *)(v13 + 48);
                        *(_DWORD *)(v13 + 48) = v23 + 4;
                        v24 = *(_DWORD *)(v23 + 4);
                        *(_DWORD *)(v13 + 44) = v24 + 512;
                        *(_DWORD *)(v13 + 40) = v24;
                        *(_DWORD *)(v13 + 36) = v24;
                    }
                    else
                    {
                        v16 = v15 == 0;
                        v17 = v15 + 4;
                        if ( !v16 )
                            *(_DWORD *)(v17 - 4) = v14;
                        *(_DWORD *)(v13 + 36) = v17;
                    }
                    *(_BYTE *)(*(_DWORD *)(v13 + 8) + v14) = 1;
                }
                result = pthread_mutex_unlock((pthread_mutex_t *)(v13 + 52));
            }
        }
    }
    return result;
}

//----- (0002D468) --------------------------------------------------------
void __fastcall P2PClient::sendRequest(P2PClient *this, OneRequest *a2)
{
    int v2; // r5
    int v3; // r4
    int v4; // r4
    int v5; // r6
    int v6; // r3
    int v7; // r4
    int v8; // r5
    int v9; // r0
    int v10; // r2
    int v11; // r3
    int v12; // t1
    char *v13; // r1
    int v14; // r9
    ConnectionManager *v15; // r4
    int v16; // r0
    int v17; // r0
    int addr; // r4
    int v19; // r7
    char *v20; // r0
    char *v21; // r6
    __int64 v22; // d6
    unsigned __int64 v23; // r10
    __int64 v24; // r0
    int v25; // r0
    int v26; // r2
    char *v27; // r2
    int v28; // t1
    int v29; // r12
    _DWORD *v30; // r1
    signed int v31; // r0
    int v32; // lr
    int v33; // r12
    int v34; // r0
    int v35; // r1
    char *v36; // r8
    int v37; // t1
    int v38; // r3
    bool v39; // zf
    int v40; // r3
    int v41; // r3
    int v42; // r0
    unsigned int v43; // r2
    int *v44; // r7
    int *v45; // r3
    int v46; // r3
    int v47; // r3
    char *v48; // r1
    int v49; // r8
    int v50; // r10
    int v51; // r3
    char *v52; // r5
    int v53; // r3
    int v54; // r3
    int v55; // r3
    int v56; // r3
    unsigned int v57; // r7
    char *v58; // r0
    const void *v59; // r1
    int v60; // r2
    char *v61; // r11
    OneRequest *v62; // [sp+10h] [bp-370h]
    int *v63; // [sp+14h] [bp-36Ch]
    int v64; // [sp+18h] [bp-368h]
    int v65; // [sp+1Ch] [bp-364h]
    struct timeval tv; // [sp+20h] [bp-360h]
    char v67[800]; // [sp+28h] [bp-358h]
    char v68; // [sp+348h] [bp-38h]

    v62 = a2;
    v63 = (int *)this;
    if ( a2 )
    {
        if ( *((_DWORD *)this + 1035) - *((_DWORD *)this + 1034) > 3 )
        {
            v2 = 0;
            while ( 1 )
            {
                while ( 1 )
                {
                    v3 = OneRequest::getFileId(v62);
                    if ( v3 == OneRequest::getFileId(*(OneRequest **)(v63[1034] + 4 * v2)) )
                        break;
                    if ( ++v2 >= (v63[1035] - v63[1034]) >> 2 )
                        goto LABEL_6;
                }
                v6 = v63[1034];
                v7 = *(_DWORD *)(v6 + 4 * v2++);
                if ( v2 >= (v63[1035] - v6) >> 2 )
                    break;
                if ( v7 )
                    goto LABEL_12;
            }
            if ( !v7 )
                goto LABEL_6;
            LABEL_12:
            v8 = 0;
            v65 = 0;
            v64 = 0;
            OneRequest::getRequestData((int)v62, &v65, 0);
            OneRequest::getRequestData(v7, &v64, 0);
            memset(v67, 0, 0x320u);
            v9 = *(unsigned __int16 *)(v65 + 10);
            if ( *(_WORD *)(v65 + 10) )
            {
                v10 = v65 + 11;
                v11 = 0;
                do
                {
                    v12 = *(unsigned __int8 *)(v10++ + 1);
                    if ( v12 == 1 )
                    {
                        v13 = &v68 + 2 * v8++;
                        *((_WORD *)v13 - 400) = v11;
                    }
                    ++v11;
                }
                while ( v11 != v9 );
                if ( v8 )
                {
                    v14 = 0;
                    while ( 1 )
                    {
                        v15 = (ConnectionManager *)v63[2743];
                        v16 = OneRequest::getFileId(v62);
                        v17 = ConnectionManager::selectPeer(v15, v16);
                        addr = v17;
                        if ( !v17 )
                            break;
                        v19 = *(_DWORD *)(v17 + 64) - *(_DWORD *)(v17 + 32);
                        v20 = (char *)operator new(0x368u);
                        if ( v19 >= v8 )
                            v19 = v8;
                        v21 = v20;
                        memset(v20, 0, 0x368u);
                        *(_WORD *)v21 = 2047;
                        gettimeofday(&tv, 0);
                        *(double *)&v22 = *(double *)(addr + 40) / 1000.0;
                        v23 = 1000LL * tv.tv_sec + tv.tv_usec / 0x3E8uLL;
                        *((_QWORD *)v21 + 1) = v23;
                        LODWORD(v24) = _fixunsdfdi(v22);
                        *((_QWORD *)v21 + 2) = v23 + v24;
                        v25 = OneRequest::getFileId(v62);
                        sprintf(v21 + 824, "%u", v25);
                        memcpy(v21 + 24, &v67[2 * v14], 2 * v19);
                        *((_DWORD *)v21 + 1) = v19;
                        if ( v19 > 0 )
                        {
                            v26 = v14 - 1;
                            v14 += v19;
                            v27 = &v67[2 * v26];
                            do
                            {
                                v28 = *((unsigned __int16 *)v27 + 1);
                                v27 += 2;
                                v29 = v64 + v28;
                                v30 = (_DWORD *)(v64 + 16 * v28);
                                v31 = (signed int)(*(double *)(addr + 40) / 50000.0);
                                if ( v31 <= 19 )
                                    LOBYTE(v31) = 20;
                                *(_BYTE *)(v29 + 12) = v31;
                                v32 = *(_DWORD *)(addr + 4);
                                v33 = *(_DWORD *)(addr + 8);
                                v34 = *(_DWORD *)(addr + 12);
                                v30[103] = *(_DWORD *)addr;
                                v30[104] = v32;
                                v30[105] = v33;
                                v30[106] = v34;
                            }
                            while ( v27 != (char *)&tv.tv_usec + 2 * v14 + 2 );
                        }
                        else
                        {
                            v14 += v19;
                        }
                        v8 -= v19;
                        sendto(*v63, v21, 0x368u, 0, (const struct sockaddr *)addr, 0x10u);
                        operator delete(v21);
                        *(_DWORD *)(addr + 32) += v19;
                        if ( v8 <= 0 )
                            goto LABEL_6;
                    }
                    v35 = v64;
                    v36 = &v67[2 * (v14 - 1)];
                    do
                    {
                        v37 = *((unsigned __int16 *)v36 + 1);
                        v36 += 2;
                        ++addr;
                        *(_BYTE *)(v35 + v37 + 12) = v17;
                    }
                    while ( addr < v8 );
                }
            }
        }
        LABEL_6:
        v4 = v63[1028];
        v5 = 1212814569 * (((signed int)v62 - *(_DWORD *)(v4 + 4)) >> 3);
        if ( v5 >= 0 && v5 < *(_DWORD *)v4 && !*(_BYTE *)(*(_DWORD *)(v4 + 8) + v5) )
        {
            pthread_mutex_lock((pthread_mutex_t *)(v4 + 52));
            if ( *(_BYTE *)(*(_DWORD *)(v4 + 8) + v5) )
            {
                pthread_mutex_unlock((pthread_mutex_t *)(v4 + 52));
            }
            else
            {
                OneRequest::reset((OneRequest *)(*(_DWORD *)(v4 + 4) + 6856 * v5));
                v38 = *(_DWORD *)(v4 + 36);
                if ( v38 == *(_DWORD *)(v4 + 44) - 4 )
                {
                    v41 = *(_DWORD *)(v4 + 48);
                    v42 = *(_DWORD *)(v4 + 12);
                    v43 = *(_DWORD *)(v4 + 16);
                    if ( v43 - ((v41 - v42) >> 2) <= 1 )
                    {
                        v48 = *(char **)(v4 + 32);
                        v49 = ((v41 - (signed int)v48) >> 2) + 1;
                        v50 = ((v41 - (signed int)v48) >> 2) + 2;
                        if ( v43 <= 2 * v50 )
                        {
                            if ( v43 )
                            {
                                v57 = 2 * v43 + 2;
                                if ( v57 > 0x3FFFFFFF )
                                    sub_BFA08();
                            }
                            else
                            {
                                v57 = 3;
                            }
                            v58 = (char *)operator new(4 * v57);
                            v59 = *(const void **)(v4 + 32);
                            v60 = (*(_DWORD *)(v4 + 48) + 4 - (signed int)v59) >> 2;
                            v61 = v58;
                            v52 = &v58[4 * ((v57 - v50) >> 1)];
                            if ( v60 )
                                memmove(&v58[4 * ((v57 - v50) >> 1)], v59, 4 * v60);
                            operator delete(*(void **)(v4 + 12));
                            *(_DWORD *)(v4 + 12) = v61;
                            *(_DWORD *)(v4 + 16) = v57;
                        }
                        else
                        {
                            v51 = v41 + 4;
                            v52 = (char *)(v42 + 4 * ((v43 - v50) >> 1));
                            if ( v48 <= v52 )
                            {
                                v56 = (v51 - (signed int)v48) >> 2;
                                if ( v56 )
                                    memmove(&v52[4 * v49 + -4 * v56], v48, 4 * v56);
                            }
                            else
                            {
                                v53 = v51 - (_DWORD)v48;
                                if ( v53 >> 2 )
                                    memmove(v52, v48, 4 * (v53 >> 2));
                            }
                        }
                        *(_DWORD *)(v4 + 32) = v52;
                        v54 = *(_DWORD *)v52;
                        v44 = (int *)&v52[4 * (v49 + 0x3FFFFFFF)];
                        *(_DWORD *)(v4 + 48) = v44;
                        *(_DWORD *)(v4 + 28) = v54 + 512;
                        *(_DWORD *)(v4 + 24) = v54;
                        v55 = *v44;
                        *(_DWORD *)(v4 + 44) = *v44 + 512;
                        *(_DWORD *)(v4 + 40) = v55;
                    }
                    else
                    {
                        v44 = *(int **)(v4 + 48);
                    }
                    v44[1] = (int)operator new(0x200u);
                    v45 = *(int **)(v4 + 36);
                    if ( v45 )
                        *v45 = v5;
                    v46 = *(_DWORD *)(v4 + 48);
                    *(_DWORD *)(v4 + 48) = v46 + 4;
                    v47 = *(_DWORD *)(v46 + 4);
                    *(_DWORD *)(v4 + 44) = v47 + 512;
                    *(_DWORD *)(v4 + 40) = v47;
                    *(_DWORD *)(v4 + 36) = v47;
                }
                else
                {
                    v39 = v38 == 0;
                    v40 = v38 + 4;
                    if ( !v39 )
                        *(_DWORD *)(v40 - 4) = v5;
                    *(_DWORD *)(v4 + 36) = v40;
                }
                *(_BYTE *)(*(_DWORD *)(v4 + 8) + v5) = 1;
                pthread_mutex_unlock((pthread_mutex_t *)(v4 + 52));
            }
        }
    }
}
// 2D468: using guessed type char var_358[800];

//----- (0002D9D8) --------------------------------------------------------
int __fastcall P2PClient::setOneFileFinished(int result, unsigned int a2)
{
    int v2; // r3
    int v3; // r5
    unsigned int v4; // r7
    int v5; // r4
    OneFile *v6; // r6

    v2 = *(_DWORD *)(result + 4124);
    v3 = result;
    v4 = a2;
    if ( *(_DWORD *)(result + 4128) - v2 > 3 )
    {
        v5 = 0;
        while ( 1 )
        {
            v6 = *(OneFile **)(v2 + 4 * v5++);
            result = OneFile::isWithSameId(v6, v4);
            if ( result )
                break;
            v2 = *(_DWORD *)(v3 + 4124);
            if ( v5 >= (*(_DWORD *)(v3 + 4128) - v2) >> 2 )
                return result;
        }
        result = OneFile::setFinished((int)v6);
    }
    return result;
}

//----- (0002DA48) --------------------------------------------------------
int __fastcall P2PClient::informValidOtherUrlSeqNum(int result, int a2, __int64 a3)
{
    int v3; // r4
    unsigned __int64 v4; // r2

    if ( !((a2 <= 0) | (HIDWORD(a3) >> 31)) )
    {
        v3 = a2 * HIDWORD(a3) + a3 * (a2 >> 31);
        *(_DWORD *)(result + 11036) = a2;
        v4 = (unsigned int)a2 * (unsigned __int64)(unsigned int)a3;
        HIDWORD(v4) += v3;
        *(_QWORD *)(result + 11040) = v4;
    }
    return result;
}

//----- (0002DA8C) --------------------------------------------------------
signed int __fastcall P2PClient::isDownloading(P2PClient *this, unsigned int a2)
{
pthread_mutex_t *v2; // r7
P2PClient *v3; // r6
unsigned int v4; // r8
int v5; // r3
int v6; // r4
signed int v7; // r5
_BOOL4 v9; // r0
signed int v10; // r2

v2 = (pthread_mutex_t *)((char *)this + 11004);
v3 = this;
v4 = a2;
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 11004));
v5 = *((_DWORD *)v3 + 1031);
if ( *((_DWORD *)v3 + 1032) - v5 <= 3 )
{
v7 = 0;
}
else
{
v6 = 0;
do
{
while ( 1 )
{
v9 = OneFile::isWithSameId(*(OneFile **)(v5 + 4 * v6), v4);
v5 = *((_DWORD *)v3 + 1031);
v7 = v9;
if ( !v9 )
break;
v10 = *(_DWORD *)(v5 + 4 * v6++);
if ( v6 >= (*((_DWORD *)v3 + 1032) - v5) >> 2 )
goto LABEL_8;
if ( v10 )
goto LABEL_4;
}
++v6;
}
while ( v6 < (*((_DWORD *)v3 + 1032) - v5) >> 2 );
v10 = 0;
LABEL_8:
        v7 = v10;
if ( v10 )
v7 = 1;
}
LABEL_4:
        pthread_mutex_unlock(v2);
return v7;
}

//----- (0002DB3C) --------------------------------------------------------
int __fastcall P2PClient::clearPendingMissions(P2PClient *this)
{
    P2PClient *v1; // r4
    int v2; // r2
    int v3; // r5
    int v4; // r7
    int v5; // r6
    int v6; // r7
    int v7; // r3
    int v8; // r1
    int v9; // r5
    int v10; // r6
    int v11; // r7
    int v13; // r3
    bool v14; // zf
    int v15; // r3
    int v16; // r3
    int v17; // r3
    char *v18; // r2
    int v19; // r12
    unsigned int v20; // r0
    int *v21; // r3
    int v22; // r3
    int v23; // r3
    char *v24; // r2
    int v25; // r12
    unsigned int v26; // r0
    int *v27; // r3
    int v28; // r3
    int v29; // r3
    _BYTE *v30; // r1
    int v31; // r3
    int v32; // r2
    _DWORD *v33; // r3
    int v34; // r2
    int v35; // r0
    int v36; // r3
    _BYTE *v37; // r1
    int v38; // r3
    int v39; // r2
    _DWORD *v40; // r3
    int v41; // r2
    int v42; // r0
    int v43; // r3
    unsigned int v44; // r12
    char *v45; // r0
    unsigned int v46; // r12
    const void *v47; // r1
    int v48; // r2
    unsigned int v49; // r3
    void *v50; // r0
    _DWORD *v51; // ST08_4
    unsigned int v52; // ST04_4
    unsigned int v53; // r12
    char *v54; // r0
    unsigned int v55; // r12
    const void *v56; // r1
    int v57; // r2
    unsigned int v58; // r3
    void *v59; // r0
    _DWORD *v60; // ST08_4
    unsigned int v61; // ST04_4
    int v62; // r2
    _DWORD *v63; // ST08_4
    int v64; // r2
    _DWORD *v65; // ST08_4
    unsigned int v66; // [sp+4h] [bp-3Ch]
    unsigned int v67; // [sp+4h] [bp-3Ch]
    int v68; // [sp+8h] [bp-38h]
    int v69; // [sp+8h] [bp-38h]
    pthread_mutex_t *mutex; // [sp+Ch] [bp-34h]
    int v71; // [sp+10h] [bp-30h]
    int v72; // [sp+10h] [bp-30h]
    char *v73; // [sp+14h] [bp-2Ch]
    char *v74; // [sp+14h] [bp-2Ch]

    v1 = this;
    mutex = (pthread_mutex_t *)((char *)this + 11004);
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 11004));
    v2 = *((_DWORD *)v1 + 1031);
    if ( *((_DWORD *)v1 + 1032) - v2 > 3 )
    {
        v3 = 0;
        do
        {
            v4 = *(_DWORD *)(v2 + 4 * v3);
            OneFile::releasePackets(*(_DWORD *)(v2 + 4 * v3), *((_DWORD *)v1 + 1030));
            v5 = *((_DWORD *)v1 + 1029);
            v6 = -1227133513 * ((v4 - *(_DWORD *)(v5 + 4)) >> 2);
            if ( v6 >= 0 && v6 < *(_DWORD *)v5 && !*(_BYTE *)(*(_DWORD *)(v5 + 8) + v6) )
            {
                pthread_mutex_lock((pthread_mutex_t *)(v5 + 52));
                if ( !*(_BYTE *)(*(_DWORD *)(v5 + 8) + v6) )
                {
                    OneFile::reset(*(_DWORD *)(v5 + 4) + 28 * v6);
                    v13 = *(_DWORD *)(v5 + 36);
                    if ( v13 == *(_DWORD *)(v5 + 44) - 4 )
                    {
                        v18 = *(char **)(v5 + 48);
                        v19 = *(_DWORD *)(v5 + 12);
                        v20 = *(_DWORD *)(v5 + 16);
                        if ( v20 - ((signed int)&v18[-v19] >> 2) <= 1 )
                        {
                            v30 = *(_BYTE **)(v5 + 32);
                            v71 = ((v18 - v30) >> 2) + 1;
                            v31 = ((v18 - v30) >> 2) + 2;
                            if ( v20 <= 2 * v31 )
                            {
                                if ( v20 )
                                {
                                    v53 = 2 * v20 + 2;
                                    if ( v53 > 0x3FFFFFFF )
                                        LABEL_62:
                                        sub_BFA08();
                                }
                                else
                                {
                                    v53 = 3;
                                }
                                v69 = ((v18 - v30) >> 2) + 2;
                                v67 = v53;
                                v54 = (char *)operator new(4 * v53);
                                v55 = v67;
                                v56 = *(const void **)(v5 + 32);
                                v57 = (*(_DWORD *)(v5 + 48) + 4 - (signed int)v56) >> 2;
                                v74 = v54;
                                v58 = (unsigned int)&v54[4 * ((v67 - v69) >> 1)];
                                if ( v57 )
                                {
                                    v59 = memmove(&v54[4 * ((v67 - v69) >> 1)], v56, 4 * v57);
                                    v55 = v67;
                                    v58 = (unsigned int)v59;
                                }
                                v60 = (_DWORD *)v58;
                                v61 = v55;
                                operator delete(*(void **)(v5 + 12));
                                v33 = v60;
                                *(_DWORD *)(v5 + 12) = v74;
                                *(_DWORD *)(v5 + 16) = v61;
                            }
                            else
                            {
                                v32 = v18 + 4 - v30;
                                v33 = (_DWORD *)(v19 + 4 * ((v20 - v31) >> 1));
                                if ( v30 <= (_BYTE *)v33 )
                                {
                                    v64 = v32 >> 2;
                                    if ( v64 )
                                    {
                                        v65 = v33;
                                        memmove(&v33[v71 - v64], v30, 4 * v64);
                                        v33 = v65;
                                    }
                                }
                                else
                                {
                                    v34 = v32 >> 2;
                                    if ( v34 )
                                        v33 = memmove(v33, v30, 4 * v34);
                                }
                            }
                            *(_DWORD *)(v5 + 32) = v33;
                            v35 = *v33;
                            v18 = (char *)&v33[v71 + 0x3FFFFFFF];
                            *(_DWORD *)(v5 + 28) = *v33 + 512;
                            *(_DWORD *)(v5 + 48) = v18;
                            *(_DWORD *)(v5 + 24) = v35;
                            v36 = *(_DWORD *)v18;
                            *(_DWORD *)(v5 + 44) = *(_DWORD *)v18 + 512;
                            *(_DWORD *)(v5 + 40) = v36;
                        }
                        *((_DWORD *)v18 + 1) = operator new(0x200u);
                        v21 = *(int **)(v5 + 36);
                        if ( v21 )
                            *v21 = v6;
                        v22 = *(_DWORD *)(v5 + 48);
                        *(_DWORD *)(v5 + 48) = v22 + 4;
                        v23 = *(_DWORD *)(v22 + 4);
                        *(_DWORD *)(v5 + 44) = v23 + 512;
                        *(_DWORD *)(v5 + 40) = v23;
                        *(_DWORD *)(v5 + 36) = v23;
                    }
                    else
                    {
                        v14 = v13 == 0;
                        v15 = v13 + 4;
                        if ( !v14 )
                            *(_DWORD *)(v15 - 4) = v6;
                        *(_DWORD *)(v5 + 36) = v15;
                    }
                    *(_BYTE *)(*(_DWORD *)(v5 + 8) + v6) = 1;
                }
                pthread_mutex_unlock((pthread_mutex_t *)(v5 + 52));
            }
            v2 = *((_DWORD *)v1 + 1031);
            ++v3;
        }
        while ( v3 < (*((_DWORD *)v1 + 1032) - v2) >> 2 );
    }
    v7 = *((_DWORD *)v1 + 1034);
    v8 = *((_DWORD *)v1 + 1035);
    *((_DWORD *)v1 + 1032) = v2;
    if ( v8 - v7 > 3 )
    {
        v9 = 0;
        do
        {
            v10 = *((_DWORD *)v1 + 1028);
            v11 = 1212814569 * ((*(_DWORD *)(v7 + 4 * v9) - *(_DWORD *)(v10 + 4)) >> 3);
            if ( v11 >= 0 && v11 < *(_DWORD *)v10 && !*(_BYTE *)(*(_DWORD *)(v10 + 8) + v11) )
            {
                pthread_mutex_lock((pthread_mutex_t *)(v10 + 52));
                if ( !*(_BYTE *)(*(_DWORD *)(v10 + 8) + v11) )
                {
                    OneRequest::reset((OneRequest *)(*(_DWORD *)(v10 + 4) + 6856 * v11));
                    v16 = *(_DWORD *)(v10 + 36);
                    if ( v16 == *(_DWORD *)(v10 + 44) - 4 )
                    {
                        v24 = *(char **)(v10 + 48);
                        v25 = *(_DWORD *)(v10 + 12);
                        v26 = *(_DWORD *)(v10 + 16);
                        if ( v26 - ((signed int)&v24[-v25] >> 2) <= 1 )
                        {
                            v37 = *(_BYTE **)(v10 + 32);
                            v72 = ((v24 - v37) >> 2) + 1;
                            v38 = ((v24 - v37) >> 2) + 2;
                            if ( v26 <= 2 * v38 )
                            {
                                if ( v26 )
                                {
                                    v44 = 2 * v26 + 2;
                                    if ( v44 > 0x3FFFFFFF )
                                        goto LABEL_62;
                                }
                                else
                                {
                                    v44 = 3;
                                }
                                v68 = ((v24 - v37) >> 2) + 2;
                                v66 = v44;
                                v45 = (char *)operator new(4 * v44);
                                v46 = v66;
                                v47 = *(const void **)(v10 + 32);
                                v48 = (*(_DWORD *)(v10 + 48) + 4 - (signed int)v47) >> 2;
                                v73 = v45;
                                v49 = (unsigned int)&v45[4 * ((v66 - v68) >> 1)];
                                if ( v48 )
                                {
                                    v50 = memmove(&v45[4 * ((v66 - v68) >> 1)], v47, 4 * v48);
                                    v46 = v66;
                                    v49 = (unsigned int)v50;
                                }
                                v51 = (_DWORD *)v49;
                                v52 = v46;
                                operator delete(*(void **)(v10 + 12));
                                v40 = v51;
                                *(_DWORD *)(v10 + 12) = v73;
                                *(_DWORD *)(v10 + 16) = v52;
                            }
                            else
                            {
                                v39 = v24 + 4 - v37;
                                v40 = (_DWORD *)(v25 + 4 * ((v26 - v38) >> 1));
                                if ( v37 <= (_BYTE *)v40 )
                                {
                                    v62 = v39 >> 2;
                                    if ( v62 )
                                    {
                                        v63 = v40;
                                        memmove(&v40[v72 - v62], v37, 4 * v62);
                                        v40 = v63;
                                    }
                                }
                                else
                                {
                                    v41 = v39 >> 2;
                                    if ( v41 )
                                        v40 = memmove(v40, v37, 4 * v41);
                                }
                            }
                            *(_DWORD *)(v10 + 32) = v40;
                            v42 = *v40;
                            v24 = (char *)&v40[v72 + 0x3FFFFFFF];
                            *(_DWORD *)(v10 + 28) = *v40 + 512;
                            *(_DWORD *)(v10 + 48) = v24;
                            *(_DWORD *)(v10 + 24) = v42;
                            v43 = *(_DWORD *)v24;
                            *(_DWORD *)(v10 + 44) = *(_DWORD *)v24 + 512;
                            *(_DWORD *)(v10 + 40) = v43;
                        }
                        *((_DWORD *)v24 + 1) = operator new(0x200u);
                        v27 = *(int **)(v10 + 36);
                        if ( v27 )
                            *v27 = v11;
                        v28 = *(_DWORD *)(v10 + 48);
                        *(_DWORD *)(v10 + 48) = v28 + 4;
                        v29 = *(_DWORD *)(v28 + 4);
                        *(_DWORD *)(v10 + 44) = v29 + 512;
                        *(_DWORD *)(v10 + 40) = v29;
                        *(_DWORD *)(v10 + 36) = v29;
                    }
                    else
                    {
                        v14 = v16 == 0;
                        v17 = v16 + 4;
                        if ( !v14 )
                            *(_DWORD *)(v17 - 4) = v11;
                        *(_DWORD *)(v10 + 36) = v17;
                    }
                    *(_BYTE *)(*(_DWORD *)(v10 + 8) + v11) = 1;
                }
                pthread_mutex_unlock((pthread_mutex_t *)(v10 + 52));
            }
            v7 = *((_DWORD *)v1 + 1034);
            ++v9;
        }
        while ( v9 < (*((_DWORD *)v1 + 1035) - v7) >> 2 );
    }
    *((_DWORD *)v1 + 1035) = v7;
    return pthread_mutex_unlock(mutex);
}

//----- (0002E0E0) --------------------------------------------------------
P2PClient *__fastcall P2PClient::~P2PClient(P2PClient *this)
{
    void *v1; // r4
    P2PClient *v2; // r5
    unsigned int v3; // r0
    void *v4; // r0
    int *v5; // r3
    int v6; // r2
    unsigned int v7; // r1
    unsigned int v8; // r4
    void **v9; // r4
    void *v10; // r0
    void *v11; // r0

    v1 = (void *)*((_DWORD *)this + 2743);
    v2 = this;
    if ( v1 )
    {
        ConnectionManager::~ConnectionManager(*((ConnectionManager **)this + 2743));
        operator delete(v1);
        *((_DWORD *)v2 + 2743) = 0;
    }
    P2PClient::clearPendingMissions(v2);
    v3 = *((_DWORD *)v2 + 1027);
    if ( v3 )
    {
        sub_88C24(v3);
        free(*((void **)v2 + 1027));
    }
    pthread_mutex_destroy((pthread_mutex_t *)v2 + 459);
    v4 = (void *)*((_DWORD *)v2 + 2745);
    if ( v4 )
    {
        free(v4);
        *((_DWORD *)v2 + 2745) = 0;
    }
    v5 = (int *)*((_DWORD *)v2 + 2756);
    if ( v5 )
    {
        v6 = *v5;
        if ( (unsigned int)(v5[1] - *v5) >> 2 )
        {
            v7 = 0;
            v8 = 0;
            do
            {
                ++v8;
                operator delete(*(void **)(v6 + 4 * v7));
                v5 = (int *)*((_DWORD *)v2 + 2756);
                v7 = v8;
                v6 = *v5;
            }
            while ( v8 < (v5[1] - *v5) >> 2 );
        }
        v5[1] = v6;
        v9 = (void **)*((_DWORD *)v2 + 2756);
        if ( v9 )
        {
            if ( *v9 )
                operator delete(*v9);
            operator delete(v9);
        }
        *((_DWORD *)v2 + 2756) = 0;
    }
    pthread_mutex_destroy((pthread_mutex_t *)((char *)v2 + 11008));
    pthread_mutex_destroy((pthread_mutex_t *)((char *)v2 + 11004));
    v10 = (void *)*((_DWORD *)v2 + 1034);
    if ( v10 )
        operator delete(v10);
    v11 = (void *)*((_DWORD *)v2 + 1031);
    if ( v11 )
        operator delete(v11);
    return v2;
}

//----- (0002E280) --------------------------------------------------------
int __fastcall P2PClient::checkCDNMargin(int result, int a2)
{
    int v2; // r3
    int v3; // r5
    unsigned int v4; // r7
    unsigned int v5; // r2
    unsigned int v6; // r4
    int v7; // r6

    v2 = *(_DWORD *)(result + 4136);
    v3 = result;
    v4 = a2;
    if ( (unsigned int)(*(_DWORD *)(result + 4140) - v2) >> 2 )
    {
        v5 = 0;
        v6 = 0;
        do
        {
            v7 = *(_DWORD *)(v2 + 4 * v5);
            ++v6;
            result = OneRequest::getFileId(*(OneRequest **)(v2 + 4 * v5));
            if ( result <= v4 )
                result = OneRequest::setTimeout(v7);
            v2 = *(_DWORD *)(v3 + 4136);
            v5 = v6;
        }
        while ( v6 < (*(_DWORD *)(v3 + 4140) - v2) >> 2 );
    }
    return result;
}

//----- (0002E2F4) --------------------------------------------------------
void *__fastcall std::vector<PEERSTATE *,std::allocator<PEERSTATE *>>::erase(int a1, _BYTE *a2)
{
int v2; // r4
_BYTE *v3; // r0
void *v4; // r3
_BYTE *v5; // r1
int v6; // r1
void *result; // r0

v2 = a1;
v3 = *(_BYTE **)(a1 + 4);
v4 = a2;
v5 = a2 + 4;
if ( v5 == v3 )
{
v3 = v5;
}
else if ( (v3 - v5) >> 2 )
{
v4 = memmove(v4, v5, 4 * ((v3 - v5) >> 2));
v3 = *(_BYTE **)(v2 + 4);
}
v6 = (int)(v3 - 4);
result = v4;
*(_DWORD *)(v2 + 4) = v6;
return result;
}

//----- (0002E348) --------------------------------------------------------
int __fastcall P2PClient::reConnectPeers(P2PClient *this)
{
    P2PClient *v1; // r6
    int *v2; // r2
    int v3; // r3
    int v4; // r2
    int v5; // r7
    _WORD *v6; // r5
    _DWORD *v7; // r0
    int v8; // r2
    _DWORD *v9; // r11
    int v10; // r3
    int v11; // r1
    unsigned int v12; // r3
    int v13; // r0
    int *v14; // r2
    int v15; // r2
    int addr; // r8
    int v17; // r5
    int v18; // r4
    int v19; // r0
    int v20; // r0
    int result; // r0
    int v22; // r2
    int v23; // [sp+8h] [bp-30h]

    v1 = this;
    v23 = 64 - ConnectionManager::getCurrentConnection(*((ConnectionManager **)this + 2743));
    if ( v23 <= 0 )
    {
        v20 = *((_DWORD *)v1 + 1026);
    }
    else
    {
        pthread_mutex_lock((pthread_mutex_t *)((char *)v1 + 11008));
        v2 = (int *)*((_DWORD *)v1 + 2756);
        v3 = *v2;
        v4 = (v2[1] - *v2) >> 2;
        if ( v4 >= v23 )
            v4 = v23;
        if ( v4 > 0 )
        {
            v5 = 0;
            do
            {
                addr = *(_DWORD *)(v3 + 4 * v5);
                v17 = 4 * v5;
                v18 = ConnectionManager::isAlreadyStacked(*((ConnectionManager **)v1 + 2743), *(sockaddr_in **)(v3 + 4 * v5));
                if ( v18 || *(_DWORD *)(addr + 16) == 2 )
                {
                    --v5;
                    operator delete((void *)addr);
                    std::vector<PEERSTATE *,std::allocator<PEERSTATE *>>::erase(
                            *((_DWORD *)v1 + 2756),
                    (_BYTE *)(**((_DWORD **)v1 + 2756) + v17));
                }
                else
                {
                    v6 = operator new(0x14u);
                    *v6 = v18;
                    v6[1] = v18;
                    *((_DWORD *)v6 + 1) = v18;
                    *((_DWORD *)v6 + 2) = v18;
                    *((_DWORD *)v6 + 3) = v18;
                    *((_DWORD *)v6 + 4) = v18;
                    v7 = operator new(0x14u);
                    v8 = *(_DWORD *)(addr + 4);
                    v9 = v7;
                    v10 = *((_DWORD *)v1 + 2747);
                    *v6 = 1023;
                    v11 = *(_DWORD *)(v10 + 4);
                    v6[1] = v18;
                    *((_DWORD *)v6 + 1) = v18;
                    *((_DWORD *)v6 + 2) = v18;
                    *((_DWORD *)v6 + 3) = v18;
                    *((_DWORD *)v6 + 4) = v18;
                    v12 = *(unsigned __int16 *)(v10 + 2);
                    *(_WORD *)v7 = -252;
                    *((_WORD *)v7 + 1) = v18;
                    v7[1] = v11;
                    v7[2] = v8;
                    v7[3] = bswap32(v12);
                    v13 = *(_DWORD *)v1;
                    v9[4] = bswap32(*(unsigned __int16 *)(addr + 2));
                    sendto(v13, v6, 0x14u, v18, (const struct sockaddr *)addr, 0x10u);
                    sendto(*(_DWORD *)v1, v9, 0x14u, v18, *((const struct sockaddr **)v1 + 2746), 0x10u);
                    sendto(*(_DWORD *)v1, v9, 0x14u, v18, *((const struct sockaddr **)v1 + 2746), 0x10u);
                    ++*(_DWORD *)(addr + 16);
                    operator delete(v6);
                    operator delete(v9);
                }
                v14 = (int *)*((_DWORD *)v1 + 2756);
                ++v5;
                v3 = *v14;
                v15 = (v14[1] - *v14) >> 2;
                if ( v15 >= v23 )
                    v15 = v23;
            }
            while ( v15 > v5 );
        }
        v19 = pthread_mutex_unlock((pthread_mutex_t *)((char *)v1 + 11008));
        if ( v23 > (unsigned int)((*(_DWORD *)(*((_DWORD *)v1 + 2756) + 4) - **((_DWORD **)v1 + 2756)) >> 2)
        && *((_BYTE *)v1 + 11028) )
        {
            v22 = *((_DWORD *)v1 + 2758) + 1;
            *((_DWORD *)v1 + 2758) = v22;
            if ( v22 <= 9 )
                (*((void (__fastcall **)(int))v1 + 2742))(v19);
            else
                *((_BYTE *)v1 + 11028) = 0;
        }
        else
        {
            *((_DWORD *)v1 + 2758) = 0;
        }
        v20 = *((_DWORD *)v1 + 1026);
    }
    result = (*(int (__cdecl **)(int, _DWORD))(*(_DWORD *)v20 + 8))(v20, *(_DWORD *)(*(_DWORD *)v20 + 8));
    *((_DWORD *)v1 + 1025) = result;
    return result;
}

//----- (0002E610) --------------------------------------------------------
void *__fastcall std::vector<OneFile *,std::allocator<OneFile *>>::erase(int a1, _BYTE *a2)
{
int v2; // r4
_BYTE *v3; // r0
void *v4; // r3
_BYTE *v5; // r1
int v6; // r1
void *result; // r0

v2 = a1;
v3 = *(_BYTE **)(a1 + 4);
v4 = a2;
v5 = a2 + 4;
if ( v5 == v3 )
{
v3 = v5;
}
else if ( (v3 - v5) >> 2 )
{
v4 = memmove(v4, v5, 4 * ((v3 - v5) >> 2));
v3 = *(_BYTE **)(v2 + 4);
}
v6 = (int)(v3 - 4);
result = v4;
*(_DWORD *)(v2 + 4) = v6;
return result;
}

//----- (0002E664) --------------------------------------------------------
int __fastcall P2PClient::handleTimeoutOneFile(int result, unsigned int a2)
{
    int v2; // r3
    int v3; // r5
    unsigned int v4; // r7
    int v5; // r4
    OneFile *v6; // r6
    int v7; // r10
    int v8; // r0
    int v9; // r0

    v2 = *(_DWORD *)(result + 4124);
    v3 = result;
    v4 = a2;
    if ( *(_DWORD *)(result + 4128) - v2 > 3 )
    {
        v5 = 0;
        while ( 1 )
        {
            v6 = *(OneFile **)(v2 + 4 * v5);
            v7 = 4 * v5++;
            result = OneFile::isWithSameId(v6, v4);
            if ( result )
                break;
            v2 = *(_DWORD *)(v3 + 4124);
            if ( v5 >= (*(_DWORD *)(v3 + 4128) - v2) >> 2 )
                return result;
        }
        v8 = OneFile::getTotalAvailableSize(v6);
        addIncompleteP2PBytes(v8);
        OneFile::handleIncompleteFile(v6, *(_DWORD *)(v3 + 4120));
        v9 = OneFile::getTotalAvailableSize(v6);
        addIncompleteP2PBeginContinuousBytes(v9);
        (*(void (__fastcall **)(OneFile *))(v3 + 10960))(v6);
        result = (int)std::vector<OneFile *,std::allocator<OneFile *>>::erase(
                v3 + 4124,
                (_BYTE *)(*(_DWORD *)(v3 + 4124) + v7));
    }
    return result;
}

//----- (0002E720) --------------------------------------------------------
int __fastcall P2PClient::notifyFinishedFiles(P2PClient *this)
{
    P2PClient *v1; // r5
    int v2; // r3
    int v3; // r4
    int v4; // r10
    int v5; // r7
    void (__fastcall *v6)(int); // r3
    int v8; // r9
    int v9; // r10
    int v10; // r2
    bool v11; // zf
    int v12; // r2
    int v13; // r0
    int v14; // lr
    unsigned int v15; // r12
    int *v16; // r2
    int *v17; // r2
    int v18; // r2
    int v19; // r2
    _DWORD *v20; // r1
    int v21; // r2
    unsigned int v22; // r12
    int v23; // r2
    _DWORD *v24; // r12
    int v25; // r2
    int v26; // lr
    int v27; // r1
    int v28; // r2
    _DWORD *v29; // ST04_4
    unsigned int v30; // r3
    char *v31; // r0
    unsigned int v32; // r3
    const void *v33; // r1
    unsigned int v34; // r12
    int v35; // r2
    void *v36; // r0
    unsigned int v37; // ST00_4
    _DWORD *v38; // ST04_4
    unsigned int v39; // [sp+0h] [bp-40h]
    int v40; // [sp+4h] [bp-3Ch]
    pthread_mutex_t *mutex; // [sp+8h] [bp-38h]
    int v42; // [sp+10h] [bp-30h]
    char *v43; // [sp+14h] [bp-2Ch]

    v1 = this;
    mutex = (pthread_mutex_t *)((char *)this + 11004);
    pthread_mutex_lock((pthread_mutex_t *)((char *)this + 11004));
    v2 = *((_DWORD *)v1 + 1031);
    if ( *((_DWORD *)v1 + 1032) - v2 > 3 )
    {
        v3 = 0;
        do
        {
            v4 = *(_DWORD *)(v2 + 4 * v3);
            v5 = 4 * v3;
            if ( v4 && OneFile::isFinished(*(OneFile **)(v2 + 4 * v3)) )
            {
                v6 = (void (__fastcall *)(int))*((_DWORD *)v1 + 2740);
                if ( v6 )
                {
                    v6(v4);
                }
                else
                {
                    OneFile::releasePackets(v4, *((_DWORD *)v1 + 1030));
                    v8 = *((_DWORD *)v1 + 1029);
                    v9 = -1227133513 * ((v4 - *(_DWORD *)(v8 + 4)) >> 2);
                    if ( v9 >= 0 && v9 < *(_DWORD *)v8 && !*(_BYTE *)(*(_DWORD *)(v8 + 8) + v9) )
                    {
                        pthread_mutex_lock((pthread_mutex_t *)(v8 + 52));
                        if ( !*(_BYTE *)(*(_DWORD *)(v8 + 8) + v9) )
                        {
                            OneFile::reset(*(_DWORD *)(v8 + 4) + 28 * v9);
                            v10 = *(_DWORD *)(v8 + 36);
                            if ( v10 == *(_DWORD *)(v8 + 44) - 4 )
                            {
                                v13 = *(_DWORD *)(v8 + 48);
                                v14 = *(_DWORD *)(v8 + 12);
                                v15 = *(_DWORD *)(v8 + 16);
                                if ( v15 - ((v13 - v14) >> 2) <= 1 )
                                {
                                    v20 = *(_DWORD **)(v8 + 32);
                                    v42 = ((v13 - (signed int)v20) >> 2) + 1;
                                    v21 = ((v13 - (signed int)v20) >> 2) + 2;
                                    if ( v15 <= 2 * v21 )
                                    {
                                        if ( v15 )
                                        {
                                            v30 = 2 * v15 + 2;
                                            if ( v30 > 0x3FFFFFFF )
                                                sub_BFA08();
                                        }
                                        else
                                        {
                                            v30 = 3;
                                        }
                                        v40 = ((v13 - (signed int)v20) >> 2) + 2;
                                        v39 = v30;
                                        v31 = (char *)operator new(4 * v30);
                                        v32 = v39;
                                        v33 = *(const void **)(v8 + 32);
                                        v43 = v31;
                                        v34 = (unsigned int)&v31[4 * ((v39 - v40) >> 1)];
                                        v35 = (*(_DWORD *)(v8 + 48) + 4 - (signed int)v33) >> 2;
                                        if ( v35 )
                                        {
                                            v36 = memmove(&v31[4 * ((v39 - v40) >> 1)], v33, 4 * v35);
                                            v32 = v39;
                                            v34 = (unsigned int)v36;
                                        }
                                        v37 = v32;
                                        v38 = (_DWORD *)v34;
                                        operator delete(*(void **)(v8 + 12));
                                        v24 = v38;
                                        *(_DWORD *)(v8 + 12) = v43;
                                        *(_DWORD *)(v8 + 16) = v37;
                                    }
                                    else
                                    {
                                        v22 = v15 - v21;
                                        v23 = v13 + 4;
                                        v24 = (_DWORD *)(v14 + 4 * (v22 >> 1));
                                        if ( v20 <= v24 )
                                        {
                                            v28 = (v23 - (signed int)v20) >> 2;
                                            if ( v28 )
                                            {
                                                v29 = v24;
                                                memmove(&v24[v42 - v28], v20, 4 * v28);
                                                v24 = v29;
                                            }
                                        }
                                        else
                                        {
                                            v25 = (v23 - (signed int)v20) >> 2;
                                            if ( v25 )
                                                v24 = memmove(v24, v20, 4 * v25);
                                        }
                                    }
                                    *(_DWORD *)(v8 + 32) = v24;
                                    v26 = *v24 + 512;
                                    v16 = &v24[v42 + 0x3FFFFFFF];
                                    *(_DWORD *)(v8 + 24) = *v24;
                                    *(_DWORD *)(v8 + 48) = v16;
                                    *(_DWORD *)(v8 + 28) = v26;
                                    v27 = *v16;
                                    *(_DWORD *)(v8 + 44) = *v16 + 512;
                                    *(_DWORD *)(v8 + 40) = v27;
                                }
                                else
                                {
                                    v16 = *(int **)(v8 + 48);
                                }
                                v16[1] = (int)operator new(0x200u);
                                v17 = *(int **)(v8 + 36);
                                if ( v17 )
                                    *v17 = v9;
                                v18 = *(_DWORD *)(v8 + 48);
                                *(_DWORD *)(v8 + 48) = v18 + 4;
                                v19 = *(_DWORD *)(v18 + 4);
                                *(_DWORD *)(v8 + 44) = v19 + 512;
                                *(_DWORD *)(v8 + 40) = v19;
                                *(_DWORD *)(v8 + 36) = v19;
                            }
                            else
                            {
                                v11 = v10 == 0;
                                v12 = v10 + 4;
                                if ( !v11 )
                                    *(_DWORD *)(v12 - 4) = v9;
                                *(_DWORD *)(v8 + 36) = v12;
                            }
                            *(_BYTE *)(*(_DWORD *)(v8 + 8) + v9) = 1;
                        }
                        pthread_mutex_unlock((pthread_mutex_t *)(v8 + 52));
                    }
                }
                --v3;
                std::vector<OneFile *,std::allocator<OneFile *>>::erase((int)v1 + 4124, (_BYTE *)(*((_DWORD *)v1 + 1031) + v5));
            }
            v2 = *((_DWORD *)v1 + 1031);
            ++v3;
        }
        while ( v3 < (*((_DWORD *)v1 + 1032) - v2) >> 2 );
    }
    return pthread_mutex_unlock(mutex);
}

//----- (0002EA60) --------------------------------------------------------
void *__fastcall std::vector<OneRequest *,std::allocator<OneRequest *>>::erase(int a1, _BYTE *a2)
{
int v2; // r4
_BYTE *v3; // r0
void *v4; // r3
_BYTE *v5; // r1
int v6; // r1
void *result; // r0

v2 = a1;
v3 = *(_BYTE **)(a1 + 4);
v4 = a2;
v5 = a2 + 4;
if ( v5 == v3 )
{
v3 = v5;
}
else if ( (v3 - v5) >> 2 )
{
v4 = memmove(v4, v5, 4 * ((v3 - v5) >> 2));
v3 = *(_BYTE **)(v2 + 4);
}
v6 = (int)(v3 - 4);
result = v4;
*(_DWORD *)(v2 + 4) = v6;
return result;
}

//----- (0002EAB4) --------------------------------------------------------
int __fastcall P2PClient::eraseMission(P2PClient *this, unsigned int a2)
{
pthread_mutex_t *v2; // r8
P2PClient *v3; // r5
unsigned int v4; // r6
int v5; // r3
int v6; // r4
int v7; // r7
int v8; // r4
int v9; // r7
int v10; // r3
int v11; // r4
int v12; // r7
int v13; // r4
int v14; // r5
int v16; // r3
bool v17; // zf
int v18; // r3
int v19; // r3
int v20; // r3
int v21; // r2
int v22; // r12
unsigned int v23; // r0
int *v24; // r11
int *v25; // r3
int v26; // r3
int v27; // r3
int v28; // r3
int v29; // r0
unsigned int v30; // r2
char *v31; // r9
int *v32; // r3
int v33; // r3
int v34; // r3
_DWORD *v35; // r1
int v36; // r10
int v37; // r3
int v38; // r2
_DWORD *v39; // r3
int v40; // r2
int v41; // r2
int v42; // r3
char *v43; // r1
int v44; // r10
int v45; // r7
int v46; // r3
char *v47; // r7
int v48; // r3
int v49; // r3
int v50; // r3
int v51; // r3
unsigned int v52; // r9
char *v53; // r0
const void *v54; // r1
int v55; // r2
char *v56; // r11
int v57; // r2
_DWORD *v58; // ST00_4
unsigned int v59; // r11
char *v60; // r0
const void *v61; // r1
int v62; // r2
char *v63; // r3
char *v64; // ST00_4
int v65; // [sp+0h] [bp-30h]
char *v66; // [sp+4h] [bp-2Ch]

v2 = (pthread_mutex_t *)((char *)this + 11004);
v3 = this;
v4 = a2;
pthread_mutex_lock((pthread_mutex_t *)((char *)this + 11004));
v5 = *((_DWORD *)v3 + 1031);
if ( *((_DWORD *)v3 + 1032) - v5 > 3 )
{
v6 = 0;
while ( 1 )
{
v7 = *(_DWORD *)(v5 + 4 * v6);
if ( OneFile::isWithSameId(*(OneFile **)(v5 + 4 * v6), v4) )
break;
v5 = *((_DWORD *)v3 + 1031);
if ( ++v6 >= (*((_DWORD *)v3 + 1032) - v5) >> 2 )
goto LABEL_8;
}
std::vector<OneFile *,std::allocator<OneFile *>>::erase((int)v3 + 4124, (_BYTE *)(*((_DWORD *)v3 + 1031) + 4 * v6));
OneFile::releasePackets(v7, *((_DWORD *)v3 + 1030));
v8 = *((_DWORD *)v3 + 1029);
v9 = -1227133513 * ((v7 - *(_DWORD *)(v8 + 4)) >> 2);
if ( v9 >= 0 && v9 < *(_DWORD *)v8 && !*(_BYTE *)(*(_DWORD *)(v8 + 8) + v9) )
{
pthread_mutex_lock((pthread_mutex_t *)(v8 + 52));
if ( !*(_BYTE *)(*(_DWORD *)(v8 + 8) + v9) )
{
OneFile::reset(*(_DWORD *)(v8 + 4) + 28 * v9);
v16 = *(_DWORD *)(v8 + 36);
if ( v16 == *(_DWORD *)(v8 + 44) - 4 )
{
v21 = *(_DWORD *)(v8 + 48);
v22 = *(_DWORD *)(v8 + 12);
v23 = *(_DWORD *)(v8 + 16);
if ( v23 - ((v21 - v22) >> 2) <= 1 )
{
v35 = *(_DWORD **)(v8 + 32);
v36 = ((v21 - (signed int)v35) >> 2) + 1;
v37 = ((v21 - (signed int)v35) >> 2) + 2;
if ( v23 <= 2 * v37 )
{
if ( v23 )
{
v59 = 2 * v23 + 2;
if ( v59 > 0x3FFFFFFF )
goto LABEL_60;
}
else
{
v59 = 3;
}
v65 = ((v21 - (signed int)v35) >> 2) + 2;
v60 = (char *)operator new(4 * v59);
v61 = *(const void **)(v8 + 32);
v62 = (*(_DWORD *)(v8 + 48) + 4 - (signed int)v61) >> 2;
v66 = v60;
v63 = &v60[4 * ((v59 - v65) >> 1)];
if ( v62 )
v63 = (char *)memmove(&v60[4 * ((v59 - v65) >> 1)], v61, 4 * v62);
v64 = v63;
operator delete(*(void **)(v8 + 12));
*(_DWORD *)(v8 + 16) = v59;
v39 = v64;
*(_DWORD *)(v8 + 12) = v66;
}
else
{
v38 = v21 + 4;
v39 = (_DWORD *)(v22 + 4 * ((v23 - v37) >> 1));
if ( v35 <= v39 )
{
v57 = (v38 - (signed int)v35) >> 2;
if ( v57 )
{
v58 = v39;
memmove(&v39[v36 - v57], v35, 4 * v57);
v39 = v58;
}
}
else
{
v40 = (v38 - (signed int)v35) >> 2;
if ( v40 )
v39 = memmove(v39, v35, 4 * v40);
}
}
*(_DWORD *)(v8 + 32) = v39;
v41 = *v39;
v24 = &v39[v36 + 0x3FFFFFFF];
*(_DWORD *)(v8 + 48) = v24;
*(_DWORD *)(v8 + 28) = v41 + 512;
*(_DWORD *)(v8 + 24) = v41;
v42 = *v24;
*(_DWORD *)(v8 + 44) = *v24 + 512;
*(_DWORD *)(v8 + 40) = v42;
}
else
{
v24 = *(int **)(v8 + 48);
}
v24[1] = (int)operator new(0x200u);
v25 = *(int **)(v8 + 36);
if ( v25 )
*v25 = v9;
v26 = *(_DWORD *)(v8 + 48);
*(_DWORD *)(v8 + 48) = v26 + 4;
v27 = *(_DWORD *)(v26 + 4);
*(_DWORD *)(v8 + 44) = v27 + 512;
*(_DWORD *)(v8 + 40) = v27;
*(_DWORD *)(v8 + 36) = v27;
}
else
{
v17 = v16 == 0;
v18 = v16 + 4;
if ( !v17 )
*(_DWORD *)(v18 - 4) = v9;
*(_DWORD *)(v8 + 36) = v18;
}
*(_BYTE *)(*(_DWORD *)(v8 + 8) + v9) = 1;
}
pthread_mutex_unlock((pthread_mutex_t *)(v8 + 52));
}
}
LABEL_8:
        v10 = *((_DWORD *)v3 + 1034);
if ( *((_DWORD *)v3 + 1035) - v10 > 3 )
{
v11 = 0;
while ( 1 )
{
v12 = *(_DWORD *)(v10 + 4 * v11);
if ( OneRequest::isTheSameRequest(*(OneRequest **)(v10 + 4 * v11), v4) )
break;
v10 = *((_DWORD *)v3 + 1034);
if ( ++v11 >= (*((_DWORD *)v3 + 1035) - v10) >> 2 )
goto LABEL_16;
}
std::vector<OneRequest *,std::allocator<OneRequest *>>::erase(
(int)v3 + 4136,
(_BYTE *)(*((_DWORD *)v3 + 1034) + 4 * v11));
v13 = *((_DWORD *)v3 + 1028);
v14 = 1212814569 * ((v12 - *(_DWORD *)(v13 + 4)) >> 3);
if ( v14 >= 0 && v14 < *(_DWORD *)v13 && !*(_BYTE *)(*(_DWORD *)(v13 + 8) + v14) )
{
pthread_mutex_lock((pthread_mutex_t *)(v13 + 52));
if ( *(_BYTE *)(*(_DWORD *)(v13 + 8) + v14) )
{
LABEL_20:
        pthread_mutex_unlock((pthread_mutex_t *)(v13 + 52));
goto LABEL_16;
}
OneRequest::reset((OneRequest *)(*(_DWORD *)(v13 + 4) + 6856 * v14));
v19 = *(_DWORD *)(v13 + 36);
if ( v19 != *(_DWORD *)(v13 + 44) - 4 )
{
v17 = v19 == 0;
v20 = v19 + 4;
if ( !v17 )
*(_DWORD *)(v20 - 4) = v14;
*(_DWORD *)(v13 + 36) = v20;
LABEL_30:
*(_BYTE *)(*(_DWORD *)(v13 + 8) + v14) = 1;
goto LABEL_20;
}
v28 = *(_DWORD *)(v13 + 48);
v29 = *(_DWORD *)(v13 + 12);
v30 = *(_DWORD *)(v13 + 16);
if ( v30 - ((v28 - v29) >> 2) > 1 )
{
v31 = *(char **)(v13 + 48);
LABEL_40:
*((_DWORD *)v31 + 1) = operator new(0x200u);
v32 = *(int **)(v13 + 36);
if ( v32 )
*v32 = v14;
v33 = *(_DWORD *)(v13 + 48);
*(_DWORD *)(v13 + 48) = v33 + 4;
v34 = *(_DWORD *)(v33 + 4);
*(_DWORD *)(v13 + 44) = v34 + 512;
*(_DWORD *)(v13 + 40) = v34;
*(_DWORD *)(v13 + 36) = v34;
goto LABEL_30;
}
v43 = *(char **)(v13 + 32);
v44 = ((v28 - (signed int)v43) >> 2) + 1;
v45 = ((v28 - (signed int)v43) >> 2) + 2;
if ( v30 > 2 * v45 )
{
v46 = v28 + 4;
v47 = (char *)(v29 + 4 * ((v30 - v45) >> 1));
if ( v43 <= v47 )
{
v51 = (v46 - (signed int)v43) >> 2;
if ( v51 )
memmove(&v47[4 * v44 + -4 * v51], v43, 4 * v51);
}
else
{
v48 = v46 - (_DWORD)v43;
if ( v48 >> 2 )
memmove(v47, v43, 4 * (v48 >> 2));
}
LABEL_52:
*(_DWORD *)(v13 + 32) = v47;
v49 = *(_DWORD *)v47;
v31 = &v47[4 * (v44 + 0x3FFFFFFF)];
*(_DWORD *)(v13 + 48) = v31;
*(_DWORD *)(v13 + 28) = v49 + 512;
*(_DWORD *)(v13 + 24) = v49;
v50 = *(_DWORD *)v31;
*(_DWORD *)(v13 + 44) = *(_DWORD *)v31 + 512;
*(_DWORD *)(v13 + 40) = v50;
goto LABEL_40;
}
if ( !v30 )
{
v52 = 3;
goto LABEL_57;
}
v52 = 2 * v30 + 2;
if ( v52 <= 0x3FFFFFFF )
{
LABEL_57:
        v53 = (char *)operator new(4 * v52);
v54 = *(const void **)(v13 + 32);
v55 = (*(_DWORD *)(v13 + 48) + 4 - (signed int)v54) >> 2;
v56 = v53;
v47 = &v53[4 * ((v52 - v45) >> 1)];
if ( v55 )
memmove(v47, v54, 4 * v55);
operator delete(*(void **)(v13 + 12));
*(_DWORD *)(v13 + 12) = v56;
*(_DWORD *)(v13 + 16) = v52;
goto LABEL_52;
}
LABEL_60:
        sub_BFA08();
}
}
LABEL_16:
        pthread_mutex_unlock(v2);
return 0;
}

//----- (0002F038) --------------------------------------------------------
void __fastcall std::vector<PEERSTATE *,std::allocator<PEERSTATE *>>::_M_insert_aux(const void **a1, _DWORD *a2, _DWORD *a3)
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

//----- (0002F188) --------------------------------------------------------
int __fastcall P2PClient::addPeers(int result, int a2, int *a3)
{
    int *v3; // r10
    P2PClient *v4; // r6
    pthread_mutex_t *v5; // r8
    int v6; // r3
    unsigned int v7; // r2
    unsigned int v8; // r4
    int *v9; // r11
    _WORD *v10; // r0
    signed int v11; // r3
    _WORD *v12; // r12
    int v13; // r1
    int v14; // r2
    int v15; // lr
    int v16; // r0
    int v17; // r2
    int *v18; // r1
    int *v19; // r12
    _DWORD *v20; // [sp+Ch] [bp-2Ch]

    v3 = a3;
    v4 = (P2PClient *)result;
    if ( (unsigned int)(a3[1] - *a3) >> 2
         && (unsigned int)(*(_DWORD *)(*(_DWORD *)(result + 11024) + 4) - **(_DWORD **)(result + 11024)) < 0x104 )
    {
        v5 = (pthread_mutex_t *)(result + 11008);
        pthread_mutex_lock((pthread_mutex_t *)(result + 11008));
        v6 = *v3;
        if ( (unsigned int)(v3[1] - *v3) >> 2 )
        {
            v7 = 0;
            v8 = 0;
            do
            {
                v9 = *(int **)(v6 + 4 * v7);
                if ( !P2PClient::checkPeerState(v4, *(sockaddr_in **)(v6 + 4 * v7)) )
                {
                    v10 = operator new(0x14u);
                    v11 = 7;
                    v12 = v10;
                    *v10 = 0;
                    v10[1] = 0;
                    *((_DWORD *)v10 + 1) = 0;
                    *((_BYTE *)v10 + 8) = 0;
                    do
                    {
                        --v11;
                        *((_BYTE *)v12 + 9) = 0;
                        v12 = (_WORD *)((char *)v12 + 1);
                    }
                    while ( v11 );
                    *((_DWORD *)v10 + 4) = 0;
                    v20 = v10;
                    v13 = v9[2];
                    v14 = v9[3];
                    v15 = *v9;
                    *((_DWORD *)v10 + 1) = v9[1];
                    *((_DWORD *)v10 + 2) = v13;
                    *(_DWORD *)v10 = v15;
                    *((_DWORD *)v10 + 3) = v14;
                    v16 = *((_DWORD *)v4 + 2756);
                    v17 = (int)v20;
                    v18 = *(int **)(v16 + 4);
                    v19 = *(int **)(v16 + 8);
                    v20[4] = 0;
                    if ( v18 == v19 )
                    {
                        std::vector<PEERSTATE *,std::allocator<PEERSTATE *>>::_M_insert_aux((const void **)v16, v18, &v20);
                    }
                    else
                    {
                        if ( v18 )
                        {
                            *v18 = v17;
                            v11 = *(_DWORD *)(v16 + 4);
                        }
                        *(_DWORD *)(v16 + 4) = v11 + 4;
                    }
                }
                v6 = *v3;
                v7 = ++v8;
            }
            while ( v8 < (v3[1] - *v3) >> 2 );
        }
        result = pthread_mutex_unlock(v5);
    }
    return result;
}

//----- (0002F2D8) --------------------------------------------------------
void __fastcall std::vector<OneFile *,std::allocator<OneFile *>>::_M_insert_aux(const void **a1, _DWORD *a2, _DWORD *a3)
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

//----- (0002F428) --------------------------------------------------------
void __fastcall std::vector<OneRequest *,std::allocator<OneRequest *>>::_M_insert_aux(const void **a1, _DWORD *a2, _DWORD *a3)
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

//----- (0002F578) --------------------------------------------------------
signed int __fastcall P2PClient::addMission(P2PClient *this, unsigned int a2)
{
char *v2; // r4
int v3; // r5
pthread_mutex_t *v4; // r10
P2PClient *v5; // r6
int v6; // r9
int *v7; // r3
int v8; // r2
_BYTE *v9; // r1
int v10; // r0
int v11; // r4
int *v12; // r3
int v13; // r8
int v14; // r2
_BYTE *v15; // r1
OneRequest *v16; // r11
_DWORD *v17; // r1
OneRequest **v18; // r1
signed int result; // r0
int v20; // r2
int v21; // r3
int v22; // r1
int v23; // r3
int v24; // r3
int v25; // r1
int v26; // r3
int v27; // r3
bool v28; // zf
int v29; // r3
char *v30; // r8
int v31; // r2
unsigned int v32; // r3
int *v33; // r3
int v34; // r3
int v35; // r3
char *v36; // r1
int v37; // r9
int v38; // r6
unsigned int v39; // r6
int v40; // r3
char *v41; // r6
int v42; // r3
int v43; // r3
int v44; // r3
int v45; // r3
unsigned int v46; // r8
char *v47; // r0
const void *v48; // r1
int v49; // r2
char *v50; // r11
int v51; // [sp+0h] [bp-1AE0h]
OneRequest *v52; // [sp+4h] [bp-1ADCh]
int v53; // [sp+8h] [bp-1AD8h]
int v54; // [sp+Ch] [bp-1AD4h]
int v55; // [sp+10h] [bp-1AD0h]
int v56; // [sp+14h] [bp-1ACCh]
int v57; // [sp+18h] [bp-1AC8h]
int v58; // [sp+1Ch] [bp-1AC4h]
__int16 v59; // [sp+22h] [bp-1ABEh]
char v60; // [sp+38h] [bp-1AA8h]
int v61; // [sp+1AB4h] [bp-2Ch]
int v62; // [sp+1AB8h] [bp-28h]

v5 = this;
v6 = a2;
if ( P2PClient::isDownloading(this, a2) )
{
result = -2;
goto LABEL_21;
}
v2 = (char *)*((_DWORD *)v5 + 1029);
pthread_mutex_lock((pthread_mutex_t *)(v2 + 52));
v7 = (int *)*((_DWORD *)v2 + 5);
if ( *((int **)v2 + 9) == v7 || (v3 = *v7, v8 = *((_DWORD *)v2 + 2), v9 = (_BYTE *)(v8 + *v7), !*(_BYTE *)(v8 + *v7)) )
{
pthread_mutex_unlock((pthread_mutex_t *)(v2 + 52));
result = -3;
goto LABEL_21;
}
if ( v7 == (int *)(*((_DWORD *)v2 + 7) - 4) )
{
operator delete(*((void **)v2 + 6));
v21 = *((_DWORD *)v2 + 8);
v22 = *((_DWORD *)v2 + 2);
*((_DWORD *)v2 + 8) = v21 + 4;
v23 = *(_DWORD *)(v21 + 4);
v9 = (_BYTE *)(v22 + v3);
*((_DWORD *)v2 + 7) = v23 + 512;
*((_DWORD *)v2 + 6) = v23;
*((_DWORD *)v2 + 5) = v23;
}
else
{
*((_DWORD *)v2 + 5) = v7 + 1;
}
*v9 = 0;
pthread_mutex_unlock((pthread_mutex_t *)(v2 + 52));
v10 = *((_DWORD *)v2 + 1) + 28 * v3;
v3 = (int)&v62;
v51 = v10;
if ( !v10 )
{
result = -3;
goto LABEL_21;
}
OneFile::setFileId(v10, v6);
v11 = *((_DWORD *)v5 + 1028);
pthread_mutex_lock((pthread_mutex_t *)(v11 + 52));
v12 = *(int **)(v11 + 20);
if ( *(int **)(v11 + 36) != v12
        && (v13 = *v12, v14 = *(_DWORD *)(v11 + 8), v15 = (_BYTE *)(v14 + *v12), *(_BYTE *)(v14 + *v12)) )
{
if ( v12 == (int *)(*(_DWORD *)(v11 + 28) - 4) )
{
operator delete(*(void **)(v11 + 24));
v24 = *(_DWORD *)(v11 + 32);
v25 = *(_DWORD *)(v11 + 8);
*(_DWORD *)(v11 + 32) = v24 + 4;
v26 = *(_DWORD *)(v24 + 4);
v15 = (_BYTE *)(v25 + v13);
*(_DWORD *)(v11 + 28) = v26 + 512;
*(_DWORD *)(v11 + 24) = v26;
*(_DWORD *)(v11 + 20) = v26;
}
else
{
*(_DWORD *)(v11 + 20) = v12 + 1;
}
*v15 = 0;
pthread_mutex_unlock((pthread_mutex_t *)(v11 + 52));
v16 = (OneRequest *)(*(_DWORD *)(v11 + 4) + 6856 * v13);
v52 = v16;
if ( v16 )
{
v2 = &v60;
v4 = (pthread_mutex_t *)&v57;
memset(&v57, 0, 0x1A9Cu);
v53 = 0;
v54 = 0;
v55 = 0;
v56 = 0;
v3 = (int)&v62;
v58 = v6;
LOWORD(v57) = 2047;
v59 = 6;
OneRequest::setRequestData(v16, (const char *)&v57, 6812, (sockaddr_in *)&v53);
pthread_mutex_lock((pthread_mutex_t *)((char *)v5 + 11004));
v17 = (_DWORD *)*((_DWORD *)v5 + 1032);
if ( v17 == *((_DWORD **)v5 + 1033) )
{
std::vector<OneFile *,std::allocator<OneFile *>>::_M_insert_aux((const void **)v5 + 1031, v17, &v51);
}
else
{
if ( v17 )
{
*v17 = v51;
v17 = (_DWORD *)*((_DWORD *)v5 + 1032);
}
*((_DWORD *)v5 + 1032) = v17 + 1;
}
v18 = (OneRequest **)*((_DWORD *)v5 + 1035);
if ( v18 == *((OneRequest ***)v5 + 1036) )
{
std::vector<OneRequest *,std::allocator<OneRequest *>>::_M_insert_aux((const void **)v5 + 1034, v18, &v52);
}
else
{
if ( v18 )
{
v3 = (int)&v62;
*v18 = v52;
v18 = (OneRequest **)*((_DWORD *)v5 + 1035);
}
*((_DWORD *)v5 + 1035) = v18 + 1;
}
pthread_mutex_unlock((pthread_mutex_t *)((char *)v5 + 11004));
result = 0;
goto LABEL_21;
}
}
else
{
pthread_mutex_unlock((pthread_mutex_t *)(v11 + 52));
v52 = 0;
}
OneFile::releasePackets(v51, *((_DWORD *)v5 + 1030));
v2 = (char *)*((_DWORD *)v5 + 1029);
v20 = *((_DWORD *)v2 + 1);
v3 = -1227133513 * ((v51 - v20) >> 2);
if ( v3 >= 0 && v3 < *(_DWORD *)v2 && !*(_BYTE *)(*((_DWORD *)v2 + 2) - 1227133513 * ((v51 - v20) >> 2)) )
{
v4 = (pthread_mutex_t *)(v2 + 52);
pthread_mutex_lock((pthread_mutex_t *)(v2 + 52));
if ( !*(_BYTE *)(*((_DWORD *)v2 + 2) + v3) )
goto LABEL_36;
goto LABEL_35;
}
result = -5;
LABEL_21:
while ( v61 != _stack_chk_guard )
{
LABEL_36:
        OneFile::reset(*((_DWORD *)v2 + 1) + 28 * v3);
v27 = *((_DWORD *)v2 + 9);
if ( v27 == *((_DWORD *)v2 + 11) - 4 )
{
v30 = (char *)*((_DWORD *)v2 + 12);
v31 = *((_DWORD *)v2 + 3);
v32 = *((_DWORD *)v2 + 4);
if ( v32 - ((signed int)&v30[-v31] >> 2) <= 1 )
{
v36 = (char *)*((_DWORD *)v2 + 8);
v37 = ((v30 - v36) >> 2) + 1;
v38 = ((v30 - v36) >> 2) + 2;
if ( v32 <= 2 * v38 )
{
if ( v32 )
{
v46 = 2 * v32 + 2;
if ( v46 > 0x3FFFFFFF )
sub_BFA08();
}
else
{
v46 = 3;
}
v47 = (char *)operator new(4 * v46);
v48 = (const void *)*((_DWORD *)v2 + 8);
v49 = (*((_DWORD *)v2 + 12) + 4 - (signed int)v48) >> 2;
v50 = v47;
v41 = &v47[4 * ((v46 - v38) >> 1)];
if ( v49 )
memmove(v41, v48, 4 * v49);
operator delete(*((void **)v2 + 3));
*((_DWORD *)v2 + 3) = v50;
*((_DWORD *)v2 + 4) = v46;
}
else
{
v39 = v32 - v38;
v40 = (int)(v30 + 4);
v41 = (char *)(v31 + 4 * (v39 >> 1));
if ( v36 <= v41 )
{
v45 = (v40 - (signed int)v36) >> 2;
if ( v45 )
memmove(&v41[4 * v37 + -4 * v45], v36, 4 * v45);
}
else
{
v42 = v40 - (_DWORD)v36;
if ( v42 >> 2 )
memmove(v41, v36, 4 * (v42 >> 2));
}
}
*((_DWORD *)v2 + 8) = v41;
v43 = *(_DWORD *)v41;
v30 = &v41[4 * (v37 + 0x3FFFFFFF)];
*((_DWORD *)v2 + 12) = v30;
*((_DWORD *)v2 + 7) = v43 + 512;
*((_DWORD *)v2 + 6) = v43;
v44 = *(_DWORD *)v30;
*((_DWORD *)v2 + 11) = *(_DWORD *)v30 + 512;
*((_DWORD *)v2 + 10) = v44;
}
*((_DWORD *)v30 + 1) = operator new(0x200u);
v33 = (int *)*((_DWORD *)v2 + 9);
if ( v33 )
*v33 = v3;
v34 = *((_DWORD *)v2 + 12);
*((_DWORD *)v2 + 12) = v34 + 4;
v35 = *(_DWORD *)(v34 + 4);
*((_DWORD *)v2 + 11) = v35 + 512;
*((_DWORD *)v2 + 10) = v35;
*((_DWORD *)v2 + 9) = v35;
}
else
{
v28 = v27 == 0;
v29 = v27 + 4;
if ( !v28 )
*(_DWORD *)(v29 - 4) = v3;
*((_DWORD *)v2 + 9) = v29;
}
*(_BYTE *)(*((_DWORD *)v2 + 2) + v3) = 1;
LABEL_35:
        pthread_mutex_unlock(v4);
result = -5;
}
return result;
}

//----- (0002FB0C) --------------------------------------------------------
void **__fastcall std::_Deque_base<OneRequest *,std::allocator<OneRequest *>>::~_Deque_base(void **a1)
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

//----- (0002FB54) --------------------------------------------------------
char *__fastcall std::_Deque_base<OneRequest *,std::allocator<OneRequest *>>::_M_initialize_map(_DWORD *a1, unsigned int a2)
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

//----- (0002FC4C) --------------------------------------------------------
_DWORD *__fastcall std::deque<OneRequest *,std::allocator<OneRequest *>>::deque(_DWORD *a1, _DWORD *a2)
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
std::_Deque_base<OneRequest *,std::allocator<OneRequest *>>::_M_initialize_map(
        a1,
(v5 >> 2) + ((v6 - 1) << 7) + ((v4 - v7) >> 2));
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

//----- (0002FD4C) --------------------------------------------------------
void **__fastcall P2PClient::checkAllRequests(P2PClient *this)
{
    signed int v1; // r4
    P2PClient *v2; // r6
    int v3; // r1
    int v4; // r3
    int v5; // r11
    unsigned int v6; // r0
    int v7; // r7
    signed int v8; // r9
    unsigned int v9; // r10
    int v10; // r0
    OneRequest *v11; // r8
    int v12; // r4
    int *v13; // r3
    int v14; // r5
    int v15; // r2
    _BYTE *v16; // r1
    int v17; // r0
    int v18; // r2
    int v19; // r3
    int v20; // r1
    OneRequest **v21; // r3
    int v22; // r4
    int v23; // r5
    int v24; // r0
    int v25; // r3
    __int16 v26; // r1
    int v27; // r4
    int v28; // r5
    int v29; // r9
    int v30; // r2
    int v31; // r2
    int v32; // r1
    int v33; // r2
    int v34; // r2
    OneRequest **v35; // r3
    int v36; // r4
    int v37; // r5
    int v38; // r3
    int v39; // r1
    int v40; // r3
    int v41; // r4
    int v42; // r8
    int v43; // r4
    int v44; // r8
    OneRequest **v45; // r3
    OneRequest *v46; // r4
    void **v48; // r4
    _DWORD *v49; // r3
    void **v50; // r4
    _DWORD *v51; // r3
    int v52; // r3
    bool v53; // zf
    int v54; // r3
    int v55; // r7
    int v56; // r5
    int v57; // r3
    void **v58; // r5
    int v59; // r7
    char *v60; // r3
    int v61; // r3
    int v62; // r7
    int v63; // r5
    int v64; // r3
    void **v65; // r5
    int v66; // r7
    char *v67; // r3
    int v68; // r3
    int v69; // r3
    int v70; // r3
    unsigned int v71; // r4
    char *v72; // r9
    int v73; // r2
    unsigned int v74; // r4
    char *v75; // r9
    int v76; // r2
    void *v77; // r3
    int v78; // r3
    int v79; // r3
    int v80; // r3
    int v81; // r3
    int v82; // r3
    int v83; // r3
    char *v84; // r7
    int v85; // r2
    unsigned int v86; // r3
    int *v87; // r3
    int v88; // r3
    int v89; // r3
    char *v90; // r5
    int v91; // r2
    unsigned int v92; // r3
    int *v93; // r3
    int v94; // r3
    int v95; // r3
    char *v96; // r1
    int v97; // r9
    int v98; // r7
    unsigned int v99; // r7
    int v100; // r3
    char *v101; // r7
    int v102; // r3
    int v103; // r3
    int v104; // r3
    int v105; // r3
    unsigned int v106; // r5
    char *v107; // r0
    const void *v108; // r1
    int v109; // r2
    char *v110; // r5
    int v111; // r2
    unsigned int v112; // r3
    int *v113; // r3
    int v114; // r3
    int v115; // r3
    char *v116; // r7
    int v117; // r2
    unsigned int v118; // r3
    int *v119; // r3
    int v120; // r3
    int v121; // r3
    int *v122; // r1
    int v123; // r8
    unsigned int v124; // r8
    int v125; // r3
    int *v126; // r8
    int v127; // r3
    int v128; // r3
    int v129; // r3
    int v130; // r3
    unsigned int v131; // r7
    OneRequest *v132; // r0
    const void *v133; // r1
    int v134; // r2
    int *v135; // r1
    int v136; // r9
    int v137; // r7
    unsigned int v138; // r7
    int v139; // r3
    int *v140; // r7
    int v141; // r3
    int v142; // r3
    int v143; // r3
    int v144; // r3
    unsigned int v145; // r5
    OneRequest *v146; // r0
    const void *v147; // r1
    int v148; // r2
    int *v149; // r1
    int v150; // r8
    unsigned int v151; // r8
    int v152; // r3
    int *v153; // r8
    int v154; // r3
    int v155; // r3
    int v156; // r3
    int v157; // r3
    unsigned int v158; // r7
    OneRequest *v159; // r0
    const void *v160; // r1
    int v161; // r2
    signed __int64 v162; // [sp+0h] [bp-D0h]
    int v163; // [sp+0h] [bp-D0h]
    pthread_mutex_t *v164; // [sp+8h] [bp-C8h]
    pthread_mutex_t *v165; // [sp+8h] [bp-C8h]
    pthread_mutex_t *v166; // [sp+8h] [bp-C8h]
    OneRequest *v167; // [sp+Ch] [bp-C4h]
    OneRequest *v168; // [sp+Ch] [bp-C4h]
    OneRequest *v169; // [sp+Ch] [bp-C4h]
    OneRequest *v170; // [sp+Ch] [bp-C4h]
    signed __int64 v171; // [sp+10h] [bp-C0h]
    void *s; // [sp+18h] [bp-B8h]
    int v173; // [sp+1Ch] [bp-B4h]
    signed int v174; // [sp+2Ch] [bp-A4h]
    char *v175; // [sp+2Ch] [bp-A4h]
    __int64 v176; // [sp+30h] [bp-A0h]
    __int64 v177; // [sp+38h] [bp-98h]
    int v178; // [sp+48h] [bp-88h]
    sockaddr_in *v179; // [sp+4Ch] [bp-84h]
    int v180; // [sp+50h] [bp-80h]
    int v181; // [sp+54h] [bp-7Ch]
    void *v182; // [sp+58h] [bp-78h]
    unsigned int v183; // [sp+5Ch] [bp-74h]
    OneRequest **v184; // [sp+60h] [bp-70h]
    void *v185; // [sp+64h] [bp-6Ch]
    char *v186; // [sp+68h] [bp-68h]
    void *src; // [sp+6Ch] [bp-64h]
    OneRequest **v188; // [sp+70h] [bp-60h]
    _DWORD *v189; // [sp+74h] [bp-5Ch]
    char *v190; // [sp+78h] [bp-58h]
    void **v191; // [sp+7Ch] [bp-54h]
    int v192; // [sp+80h] [bp-50h]
    int v193; // [sp+84h] [bp-4Ch]
    int v194; // [sp+88h] [bp-48h]
    int v195; // [sp+8Ch] [bp-44h]
    int v196; // [sp+90h] [bp-40h]
    int v197; // [sp+94h] [bp-3Ch]
    int v198; // [sp+98h] [bp-38h]
    int v199; // [sp+9Ch] [bp-34h]
    int v200; // [sp+A0h] [bp-30h]
    int v201; // [sp+A4h] [bp-2Ch]

    v2 = this;
    v192 = 0;
    v193 = 0;
    v194 = 0;
    v195 = 0;
    v196 = 0;
    v197 = 0;
    v198 = 0;
    v199 = 0;
    v200 = 0;
    v201 = 0;
    std::_Deque_base<OneRequest *,std::allocator<OneRequest *>>::_M_initialize_map(&v192, 0);
    std::deque<OneRequest *,std::allocator<OneRequest *>>::deque(&v182, &v192);
    std::_Deque_base<OneRequest *,std::allocator<OneRequest *>>::~_Deque_base((void **)&v192);
    v3 = *((_DWORD *)v2 + 2759);
    v178 = 0;
    v179 = 0;
    if ( v3 > 0 )
        v1 = *((_DWORD *)v2 + 2759);
    if ( v3 <= 0 )
        v1 = 1;
    v176 = *((_QWORD *)v2 + 1380);
    pthread_mutex_lock((pthread_mutex_t *)((char *)v2 + 11004));
    v4 = *((_DWORD *)v2 + 1034);
    if ( *((_DWORD *)v2 + 1035) - v4 <= 3 )
    {
        v174 = 0;
    }
    else
    {
        v5 = 0;
        s = (char *)v2 + 4148;
        v174 = 0;
        v177 = v1;
        do
        {
            v6 = OneRequest::getFileId(*(OneRequest **)(v4 + 4 * v5));
            v171 = v6;
            v7 = 4 * v5 + 4;
            if ( HIDWORD(v176) + (v6 < (unsigned int)v176) > 0 )
                v8 = 1;
            else
                v8 = v177;
            if ( HIDWORD(v176) + (v6 < (unsigned int)v176) > 0 )
                v9 = 0;
            else
                v9 = HIDWORD(v177);
            v162 = v6 / (signed __int64)__PAIR__(v9, v8);
            while ( 1 )
            {
                v4 = *((_DWORD *)v2 + 1034);
                if ( v5 + 1 >= (*((_DWORD *)v2 + 1035) - v4) >> 2 )
                break;
                v10 = OneRequest::getFileId(*(OneRequest **)(v4 + v7));
                v7 += 4;
                if ( (unsigned int)v10 / (signed __int64)__PAIR__(v9, v8) != v162 )
                {
                    v4 = *((_DWORD *)v2 + 1034);
                    if ( v5 < 0 )
                        goto LABEL_93;
                    goto LABEL_18;
                }
                ++v5;
            }
            if ( v5 < 0 )
            {
                LABEL_93:
                ++v5;
                continue;
            }
            LABEL_18:
            v173 = v5;
            v163 = 4 * v5;
            while ( 1 )
            {
                v11 = *(OneRequest **)(v4 + v163);
                v164 = (pthread_mutex_t *)OneRequest::getFileId(*(OneRequest **)(v4 + v163));
                if ( (unsigned int)v164 < v171 )
                    break;
                v12 = *((_DWORD *)v2 + 1028);
                pthread_mutex_lock((pthread_mutex_t *)(v12 + 52));
                v13 = *(int **)(v12 + 20);
                if ( *(int **)(v12 + 36) == v13
                     || (v14 = *v13, v15 = *(_DWORD *)(v12 + 8), v16 = (_BYTE *)(v15 + *v13), !*(_BYTE *)(v15 + *v13)) )
                {
                    pthread_mutex_unlock((pthread_mutex_t *)(v12 + 52));
                    goto LABEL_38;
                }
                if ( v13 == (int *)(*(_DWORD *)(v12 + 28) - 4) )
                {
                    operator delete(*(void **)(v12 + 24));
                    v38 = *(_DWORD *)(v12 + 32);
                    v39 = *(_DWORD *)(v12 + 8);
                    *(_DWORD *)(v12 + 32) = v38 + 4;
                    v40 = *(_DWORD *)(v38 + 4);
                    v16 = (_BYTE *)(v39 + v14);
                    *(_DWORD *)(v12 + 28) = v40 + 512;
                    *(_DWORD *)(v12 + 24) = v40;
                    *(_DWORD *)(v12 + 20) = v40;
                }
                else
                {
                    *(_DWORD *)(v12 + 20) = v13 + 1;
                }
                *v16 = 0;
                pthread_mutex_unlock((pthread_mutex_t *)(v12 + 52));
                v167 = (OneRequest *)(*(_DWORD *)(v12 + 4) + 6856 * v14);
                if ( v167 )
                {
                    OneRequest::getRequestData((int)v11, &v178, &v179);
                    if ( !*(_WORD *)(v178 + 10) )
                    {
                        memset(s, *(unsigned __int16 *)(v178 + 10), 0x1A9Cu);
                        *((_WORD *)v2 + 2074) = 2047;
                        v17 = OneRequest::getFileId(v11);
                        v18 = v178;
                        *((_DWORD *)v2 + 1038) = v17;
                        *((_WORD *)v2 + 2078) = 0;
                        v19 = 0;
                        *((_WORD *)v2 + 2079) = 6;
                        do
                        {
                            v20 = (int)v2 + v19++;
                            ++v18;
                            *(_BYTE *)(v20 + 4160) = 1;
                            *(_BYTE *)(v18 + 11) = 0;
                        }
                        while ( v19 != 6 );
                        OneRequest::setRequestData(v167, (const char *)s, 6812, v179);
                        v21 = v188;
                        if ( v188 == (OneRequest **)(v190 - 4) )
                        {
                            v48 = v191;
                            if ( v183 - (((char *)v191 - (_BYTE *)v182) >> 2) <= 1 )
                            {
                                v55 = (((char *)v191 - (_BYTE *)src) >> 2) + 1;
                                v56 = (((char *)v191 - (_BYTE *)src) >> 2) + 2;
                                if ( v183 <= 2 * v56 )
                                {
                                    if ( v183 )
                                    {
                                        v71 = 2 * v183 + 2;
                                        if ( v71 > 0x3FFFFFFF )
                                            sub_BFA08();
                                    }
                                    else
                                    {
                                        v71 = 3;
                                    }
                                    v72 = (char *)operator new(4 * v71);
                                    v58 = (void **)&v72[4 * ((v71 - v56) >> 1)];
                                    v73 = ((char *)(v191 + 1) - (_BYTE *)src) >> 2;
                                    if ( v73 )
                                        memmove(v58, src, 4 * v73);
                                    operator delete(v182);
                                    v182 = v72;
                                    v183 = v71;
                                }
                                else
                                {
                                    v57 = (char *)(v191 + 1) - (_BYTE *)src;
                                    v58 = (void **)((char *)v182 + 4 * ((v183 - v56) >> 1));
                                    if ( src <= v58 )
                                    {
                                        v78 = v57 >> 2;
                                        if ( v78 )
                                            memmove(&v58[v55] - v78, src, 4 * v78);
                                    }
                                    else if ( v57 >> 2 )
                                    {
                                        memmove(v58, src, 4 * (v57 >> 2));
                                    }
                                }
                                src = v58;
                                v59 = v55 + 0x3FFFFFFF;
                                v60 = (char *)*v58;
                                v48 = &v58[v59];
                                v191 = &v58[v59];
                                v186 = v60 + 512;
                                v185 = v60;
                                v61 = (int)v58[v59];
                                v190 = (char *)(v61 + 512);
                                v189 = (_DWORD *)v61;
                            }
                            v48[1] = operator new(0x200u);
                            if ( v188 )
                                *v188 = v167;
                            ++v191;
                            v49 = *v191;
                            v190 = (char *)*v191 + 512;
                            v189 = v49;
                            v188 = (OneRequest **)v49;
                        }
                        else
                        {
                            if ( v188 )
                            {
                                *v188 = v167;
                                v21 = v188;
                            }
                            v188 = v21 + 1;
                        }
                        *(_WORD *)(v178 + 10) = 6;
                        OneRequest::setBeginningTime(v11);
                        goto LABEL_33;
                    }
                    memset(s, 0, 0x1A9Cu);
                    *((_WORD *)v2 + 2074) = 2047;
                    v24 = OneRequest::getFileId(v11);
                    v25 = v178;
                    *((_DWORD *)v2 + 1038) = v24;
                    v26 = *(_WORD *)(v25 + 10);
                    *((_WORD *)v2 + 2078) = 0;
                    *((_WORD *)v2 + 2079) = v26;
                    if ( !*(_WORD *)(v25 + 10) )
                        goto LABEL_65;
                    v27 = 0;
                    v28 = 0;
                    v29 = 0;
                    while ( 2 )
                    {
                        while ( 1 )
                        {
                            v32 = v25 + v27;
                            v33 = *(unsigned __int8 *)(v25 + v27 + 12);
                            if ( v33 == 255 )
                                break;
                            if ( *(_BYTE *)(v25 + v27 + 12) )
                            {
                                v30 = (unsigned __int8)(v33 - 1);
                                *(_BYTE *)(v25 + v27 + 12) = v30;
                                if ( v30 )
                                    goto LABEL_43;
                                ConnectionManager::onRequestTimeout(
                                        *((ConnectionManager **)v2 + 2743),
                                (sockaddr_in *)(v25 + 16 * v27 + 412));
                                v25 = v178;
                                v32 = v178 + v27;
                                if ( *(_BYTE *)(v178 + v27 + 12) )
                                    goto LABEL_43;
                            }
                            v34 = (int)v2 + v27++;
                            ++v28;
                            *(_BYTE *)(v34 + 4160) = 1;
                            v31 = *(unsigned __int16 *)(v25 + 10);
                            *(_BYTE *)(v32 + 12) = 1;
                            if ( v31 <= v27 )
                            {
                                LABEL_48:
                                if ( v29 != v31 )
                                {
                                    if ( v28 )
                                    {
                                        OneRequest::setRequestData(v167, (const char *)s, 6812, v179);
                                        v35 = v188;
                                        if ( v188 == (OneRequest **)(v190 - 4) )
                                        {
                                            v50 = v191;
                                            if ( v183 - (((char *)v191 - (_BYTE *)v182) >> 2) <= 1 )
                                            {
                                                v62 = (((char *)v191 - (_BYTE *)src) >> 2) + 1;
                                                v63 = (((char *)v191 - (_BYTE *)src) >> 2) + 2;
                                                if ( v183 <= 2 * v63 )
                                                {
                                                    if ( v183 )
                                                    {
                                                        v74 = 2 * v183 + 2;
                                                        if ( v74 > 0x3FFFFFFF )
                                                            sub_BFA08();
                                                    }
                                                    else
                                                    {
                                                        v74 = 3;
                                                    }
                                                    v75 = (char *)operator new(4 * v74);
                                                    v65 = (void **)&v75[4 * ((v74 - v63) >> 1)];
                                                    v76 = ((char *)(v191 + 1) - (_BYTE *)src) >> 2;
                                                    if ( v76 )
                                                        memmove(v65, src, 4 * v76);
                                                    operator delete(v182);
                                                    v182 = v75;
                                                    v183 = v74;
                                                }
                                                else
                                                {
                                                    v64 = (char *)(v191 + 1) - (_BYTE *)src;
                                                    v65 = (void **)((char *)v182 + 4 * ((v183 - v63) >> 1));
                                                    if ( src <= v65 )
                                                    {
                                                        v83 = v64 >> 2;
                                                        if ( v83 )
                                                            memmove(&v65[v62] - v83, src, 4 * v83);
                                                    }
                                                    else if ( v64 >> 2 )
                                                    {
                                                        memmove(v65, src, 4 * (v64 >> 2));
                                                    }
                                                }
                                                src = v65;
                                                v66 = v62 + 0x3FFFFFFF;
                                                v67 = (char *)*v65;
                                                v50 = &v65[v66];
                                                v191 = &v65[v66];
                                                v186 = v67 + 512;
                                                v185 = v67;
                                                v68 = (int)v65[v66];
                                                v190 = (char *)(v68 + 512);
                                                v189 = (_DWORD *)v68;
                                            }
                                            v50[1] = operator new(0x200u);
                                            if ( v188 )
                                                *v188 = v167;
                                            ++v191;
                                            v51 = *v191;
                                            v190 = (char *)*v191 + 512;
                                            v189 = v51;
                                            v188 = (OneRequest **)v51;
                                        }
                                        else
                                        {
                                            if ( v188 )
                                            {
                                                *v188 = v167;
                                                v35 = v188;
                                            }
                                            v188 = v35 + 1;
                                        }
                                        LABEL_33:
                                        if ( OneRequest::isTimeout(v11) || !OneRequest::isValid(v11) )
                                        {
                                            OneRequest::getTotalPacketNumb(v11);
                                            v180 = 0;
                                            v181 = 0;
                                            v192 = 0;
                                            OneRequest::getDownloadedNumb(v11, &v180, &v181, &v192);
                                            OneRequest::isTimeout(v11);
                                            P2PClient::handleTimeoutOneFile((int)v2, (unsigned int)v164);
                                            v22 = *((_DWORD *)v2 + 1028);
                                            v23 = 1212814569 * (((signed int)v11 - *(_DWORD *)(v22 + 4)) >> 3);
                                            if ( v23 >= 0 && v23 < *(_DWORD *)v22 && !*(_BYTE *)(*(_DWORD *)(v22 + 8) + v23) )
                                            {
                                                pthread_mutex_lock((pthread_mutex_t *)(v22 + 52));
                                                if ( !*(_BYTE *)(*(_DWORD *)(v22 + 8) + v23) )
                                                {
                                                    OneRequest::reset((OneRequest *)(*(_DWORD *)(v22 + 4) + 6856 * v23));
                                                    v52 = *(_DWORD *)(v22 + 36);
                                                    if ( v52 == *(_DWORD *)(v22 + 44) - 4 )
                                                    {
                                                        v84 = *(char **)(v22 + 48);
                                                        v85 = *(_DWORD *)(v22 + 12);
                                                        v86 = *(_DWORD *)(v22 + 16);
                                                        if ( v86 - ((signed int)&v84[-v85] >> 2) <= 1 )
                                                        {
                                                            v122 = *(int **)(v22 + 32);
                                                            v165 = (pthread_mutex_t *)(((v84 - (char *)v122) >> 2) + 1);
                                                            v123 = ((v84 - (char *)v122) >> 2) + 2;
                                                            if ( v86 <= 2 * v123 )
                                                            {
                                                                if ( v86 )
                                                                {
                                                                    v131 = 2 * v86 + 2;
                                                                    if ( v131 > 0x3FFFFFFF )
                                                                        sub_BFA08();
                                                                }
                                                                else
                                                                {
                                                                    v131 = 3;
                                                                }
                                                                v132 = (OneRequest *)operator new(4 * v131);
                                                                v133 = *(const void **)(v22 + 32);
                                                                v168 = v132;
                                                                v126 = (int *)((char *)v132 + 4 * ((v131 - v123) >> 1));
                                                                v134 = (*(_DWORD *)(v22 + 48) + 4 - (signed int)v133) >> 2;
                                                                if ( v134 )
                                                                    memmove(v126, v133, 4 * v134);
                                                                operator delete(*(void **)(v22 + 12));
                                                                *(_DWORD *)(v22 + 16) = v131;
                                                                *(_DWORD *)(v22 + 12) = v168;
                                                            }
                                                            else
                                                            {
                                                                v124 = v86 - v123;
                                                                v125 = (int)(v84 + 4);
                                                                v126 = (int *)(v85 + 4 * (v124 >> 1));
                                                                if ( v122 <= v126 )
                                                                {
                                                                    v130 = (v125 - (signed int)v122) >> 2;
                                                                    if ( v130 )
                                                                        memmove(&v126[(_DWORD)v165 - v130], v122, 4 * v130);
                                                                }
                                                                else
                                                                {
                                                                    v127 = v125 - (_DWORD)v122;
                                                                    if ( v127 >> 2 )
                                                                        memmove(v126, v122, 4 * (v127 >> 2));
                                                                }
                                                            }
                                                            *(_DWORD *)(v22 + 32) = v126;
                                                            v128 = *v126;
                                                            v84 = (char *)&v126[(_DWORD)v165 + 0x3FFFFFFF];
                                                            *(_DWORD *)(v22 + 28) = *v126 + 512;
                                                            *(_DWORD *)(v22 + 48) = v84;
                                                            *(_DWORD *)(v22 + 24) = v128;
                                                            v129 = *(_DWORD *)v84;
                                                            *(_DWORD *)(v22 + 44) = *(_DWORD *)v84 + 512;
                                                            *(_DWORD *)(v22 + 40) = v129;
                                                        }
                                                        *((_DWORD *)v84 + 1) = operator new(0x200u);
                                                        v87 = *(int **)(v22 + 36);
                                                        if ( v87 )
                                                            *v87 = v23;
                                                        v88 = *(_DWORD *)(v22 + 48);
                                                        *(_DWORD *)(v22 + 48) = v88 + 4;
                                                        v89 = *(_DWORD *)(v88 + 4);
                                                        *(_DWORD *)(v22 + 44) = v89 + 512;
                                                        *(_DWORD *)(v22 + 40) = v89;
                                                        *(_DWORD *)(v22 + 36) = v89;
                                                    }
                                                    else
                                                    {
                                                        v53 = v52 == 0;
                                                        v54 = v52 + 4;
                                                        if ( !v53 )
                                                            *(_DWORD *)(v54 - 4) = v23;
                                                        *(_DWORD *)(v22 + 36) = v54;
                                                    }
                                                    *(_BYTE *)(*(_DWORD *)(v22 + 8) + v23) = 1;
                                                }
                                                pthread_mutex_unlock((pthread_mutex_t *)(v22 + 52));
                                            }
                                            --v173;
                                            std::vector<OneRequest *,std::allocator<OneRequest *>>::erase(
                                                    (int)v2 + 4136,
                                                    (_BYTE *)(*((_DWORD *)v2 + 1034) + v163));
                                        }
                                    }
                                    else
                                    {
                                        v36 = *((_DWORD *)v2 + 1028);
                                        v37 = 1212814569 * (((signed int)v167 - *(_DWORD *)(v36 + 4)) >> 3);
                                        if ( v37 >= 0 && v37 < *(_DWORD *)v36 && !*(_BYTE *)(*(_DWORD *)(v36 + 8) + v37) )
                                        {
                                            pthread_mutex_lock((pthread_mutex_t *)(v36 + 52));
                                            if ( !*(_BYTE *)(*(_DWORD *)(v36 + 8) + v37) )
                                            {
                                                OneRequest::reset((OneRequest *)(*(_DWORD *)(v36 + 4) + 6856 * v37));
                                                v69 = *(_DWORD *)(v36 + 36);
                                                if ( v69 == *(_DWORD *)(v36 + 44) - 4 )
                                                {
                                                    v116 = *(char **)(v36 + 48);
                                                    v117 = *(_DWORD *)(v36 + 12);
                                                    v118 = *(_DWORD *)(v36 + 16);
                                                    if ( v118 - ((signed int)&v116[-v117] >> 2) <= 1 )
                                                    {
                                                        v149 = *(int **)(v36 + 32);
                                                        v166 = (pthread_mutex_t *)(((v116 - (char *)v149) >> 2) + 1);
                                                        v150 = ((v116 - (char *)v149) >> 2) + 2;
                                                        if ( v118 <= 2 * v150 )
                                                        {
                                                            if ( v118 )
                                                            {
                                                                v158 = 2 * v118 + 2;
                                                                if ( v158 > 0x3FFFFFFF )
                                                                    sub_BFA08();
                                                            }
                                                            else
                                                            {
                                                                v158 = 3;
                                                            }
                                                            v159 = (OneRequest *)operator new(4 * v158);
                                                            v160 = *(const void **)(v36 + 32);
                                                            v170 = v159;
                                                            v153 = (int *)((char *)v159 + 4 * ((v158 - v150) >> 1));
                                                            v161 = (*(_DWORD *)(v36 + 48) + 4 - (signed int)v160) >> 2;
                                                            if ( v161 )
                                                                memmove(v153, v160, 4 * v161);
                                                            operator delete(*(void **)(v36 + 12));
                                                            *(_DWORD *)(v36 + 16) = v158;
                                                            *(_DWORD *)(v36 + 12) = v170;
                                                        }
                                                        else
                                                        {
                                                            v151 = v118 - v150;
                                                            v152 = (int)(v116 + 4);
                                                            v153 = (int *)(v117 + 4 * (v151 >> 1));
                                                            if ( v149 <= v153 )
                                                            {
                                                                v157 = (v152 - (signed int)v149) >> 2;
                                                                if ( v157 )
                                                                    memmove(&v153[(_DWORD)v166 - v157], v149, 4 * v157);
                                                            }
                                                            else
                                                            {
                                                                v154 = v152 - (_DWORD)v149;
                                                                if ( v154 >> 2 )
                                                                    memmove(v153, v149, 4 * (v154 >> 2));
                                                            }
                                                        }
                                                        *(_DWORD *)(v36 + 32) = v153;
                                                        v155 = *v153;
                                                        v116 = (char *)&v153[(_DWORD)v166 + 0x3FFFFFFF];
                                                        *(_DWORD *)(v36 + 28) = *v153 + 512;
                                                        *(_DWORD *)(v36 + 48) = v116;
                                                        *(_DWORD *)(v36 + 24) = v155;
                                                        v156 = *(_DWORD *)v116;
                                                        *(_DWORD *)(v36 + 44) = *(_DWORD *)v116 + 512;
                                                        *(_DWORD *)(v36 + 40) = v156;
                                                    }
                                                    *((_DWORD *)v116 + 1) = operator new(0x200u);
                                                    v119 = *(int **)(v36 + 36);
                                                    if ( v119 )
                                                        *v119 = v37;
                                                    v120 = *(_DWORD *)(v36 + 48);
                                                    *(_DWORD *)(v36 + 48) = v120 + 4;
                                                    v121 = *(_DWORD *)(v120 + 4);
                                                    *(_DWORD *)(v36 + 44) = v121 + 512;
                                                    *(_DWORD *)(v36 + 40) = v121;
                                                    *(_DWORD *)(v36 + 36) = v121;
                                                }
                                                else
                                                {
                                                    v53 = v69 == 0;
                                                    v70 = v69 + 4;
                                                    if ( !v53 )
                                                        *(_DWORD *)(v70 - 4) = v37;
                                                    *(_DWORD *)(v36 + 36) = v70;
                                                }
                                                *(_BYTE *)(*(_DWORD *)(v36 + 8) + v37) = 1;
                                            }
                                            pthread_mutex_unlock((pthread_mutex_t *)(v36 + 52));
                                        }
                                    }
                                    goto LABEL_38;
                                }
                                LABEL_65:
                                P2PClient::setOneFileFinished((int)v2, (unsigned int)v164);
                                v41 = *((_DWORD *)v2 + 1028);
                                v42 = 1212814569 * (((signed int)v11 - *(_DWORD *)(v41 + 4)) >> 3);
                                if ( v42 >= 0 && v42 < *(_DWORD *)v41 && !*(_BYTE *)(*(_DWORD *)(v41 + 8) + v42) )
                                {
                                    pthread_mutex_lock((pthread_mutex_t *)(v41 + 52));
                                    if ( !*(_BYTE *)(*(_DWORD *)(v41 + 8) + v42) )
                                    {
                                        OneRequest::reset((OneRequest *)(*(_DWORD *)(v41 + 4) + 6856 * v42));
                                        v79 = *(_DWORD *)(v41 + 36);
                                        if ( v79 == *(_DWORD *)(v41 + 44) - 4 )
                                        {
                                            v90 = *(char **)(v41 + 48);
                                            v91 = *(_DWORD *)(v41 + 12);
                                            v92 = *(_DWORD *)(v41 + 16);
                                            if ( v92 - ((signed int)&v90[-v91] >> 2) <= 1 )
                                            {
                                                v96 = *(char **)(v41 + 32);
                                                v97 = ((v90 - v96) >> 2) + 1;
                                                v98 = ((v90 - v96) >> 2) + 2;
                                                if ( v92 <= 2 * v98 )
                                                {
                                                    if ( v92 )
                                                    {
                                                        v106 = 2 * v92 + 2;
                                                        if ( v106 > 0x3FFFFFFF )
                                                            sub_BFA08();
                                                    }
                                                    else
                                                    {
                                                        v106 = 3;
                                                    }
                                                    v107 = (char *)operator new(4 * v106);
                                                    v108 = *(const void **)(v41 + 32);
                                                    v175 = v107;
                                                    v101 = &v107[4 * ((v106 - v98) >> 1)];
                                                    v109 = (*(_DWORD *)(v41 + 48) + 4 - (signed int)v108) >> 2;
                                                    if ( v109 )
                                                        memmove(v101, v108, 4 * v109);
                                                    operator delete(*(void **)(v41 + 12));
                                                    *(_DWORD *)(v41 + 16) = v106;
                                                    *(_DWORD *)(v41 + 12) = v175;
                                                }
                                                else
                                                {
                                                    v99 = v92 - v98;
                                                    v100 = (int)(v90 + 4);
                                                    v101 = (char *)(v91 + 4 * (v99 >> 1));
                                                    if ( v96 <= v101 )
                                                    {
                                                        v105 = (v100 - (signed int)v96) >> 2;
                                                        if ( v105 )
                                                            memmove(&v101[4 * v97 + -4 * v105], v96, 4 * v105);
                                                    }
                                                    else
                                                    {
                                                        v102 = v100 - (_DWORD)v96;
                                                        if ( v102 >> 2 )
                                                            memmove(v101, v96, 4 * (v102 >> 2));
                                                    }
                                                }
                                                *(_DWORD *)(v41 + 32) = v101;
                                                v103 = *(_DWORD *)v101;
                                                v90 = &v101[4 * (v97 + 0x3FFFFFFF)];
                                                *(_DWORD *)(v41 + 48) = v90;
                                                *(_DWORD *)(v41 + 28) = v103 + 512;
                                                *(_DWORD *)(v41 + 24) = v103;
                                                v104 = *(_DWORD *)v90;
                                                *(_DWORD *)(v41 + 44) = *(_DWORD *)v90 + 512;
                                                *(_DWORD *)(v41 + 40) = v104;
                                            }
                                            *((_DWORD *)v90 + 1) = operator new(0x200u);
                                            v93 = *(int **)(v41 + 36);
                                            if ( v93 )
                                                *v93 = v42;
                                            v94 = *(_DWORD *)(v41 + 48);
                                            *(_DWORD *)(v41 + 48) = v94 + 4;
                                            v95 = *(_DWORD *)(v94 + 4);
                                            *(_DWORD *)(v41 + 44) = v95 + 512;
                                            *(_DWORD *)(v41 + 40) = v95;
                                            *(_DWORD *)(v41 + 36) = v95;
                                        }
                                        else
                                        {
                                            v53 = v79 == 0;
                                            v80 = v79 + 4;
                                            if ( !v53 )
                                                *(_DWORD *)(v80 - 4) = v42;
                                            *(_DWORD *)(v41 + 36) = v80;
                                        }
                                        *(_BYTE *)(*(_DWORD *)(v41 + 8) + v42) = 1;
                                    }
                                    pthread_mutex_unlock((pthread_mutex_t *)(v41 + 52));
                                }
                                --v173;
                                std::vector<OneRequest *,std::allocator<OneRequest *>>::erase(
                                        (int)v2 + 4136,
                                        (_BYTE *)(*((_DWORD *)v2 + 1034) + v163));
                                v43 = *((_DWORD *)v2 + 1028);
                                v44 = 1212814569 * (((signed int)v167 - *(_DWORD *)(v43 + 4)) >> 3);
                                if ( v44 >= 0 )
                                {
                                    if ( v44 >= *(_DWORD *)v43 )
                                    {
                                        v174 = 1;
                                        goto LABEL_38;
                                    }
                                    if ( *(_BYTE *)(*(_DWORD *)(v43 + 8) + v44) )
                                    {
                                        v174 = 1;
                                        goto LABEL_38;
                                    }
                                    pthread_mutex_lock((pthread_mutex_t *)(v43 + 52));
                                    if ( !*(_BYTE *)(*(_DWORD *)(v43 + 8) + v44) )
                                    {
                                        OneRequest::reset((OneRequest *)(*(_DWORD *)(v43 + 4) + 6856 * v44));
                                        v81 = *(_DWORD *)(v43 + 36);
                                        if ( v81 == *(_DWORD *)(v43 + 44) - 4 )
                                        {
                                            v110 = *(char **)(v43 + 48);
                                            v111 = *(_DWORD *)(v43 + 12);
                                            v112 = *(_DWORD *)(v43 + 16);
                                            if ( v112 - ((signed int)&v110[-v111] >> 2) <= 1 )
                                            {
                                                v135 = *(int **)(v43 + 32);
                                                v136 = ((v110 - (char *)v135) >> 2) + 1;
                                                v137 = ((v110 - (char *)v135) >> 2) + 2;
                                                if ( v112 <= 2 * v137 )
                                                {
                                                    if ( v112 )
                                                    {
                                                        v145 = 2 * v112 + 2;
                                                        if ( v145 > 0x3FFFFFFF )
                                                            sub_BFA08();
                                                    }
                                                    else
                                                    {
                                                        v145 = 3;
                                                    }
                                                    v146 = (OneRequest *)operator new(4 * v145);
                                                    v147 = *(const void **)(v43 + 32);
                                                    v169 = v146;
                                                    v140 = (int *)((char *)v146 + 4 * ((v145 - v137) >> 1));
                                                    v148 = (*(_DWORD *)(v43 + 48) + 4 - (signed int)v147) >> 2;
                                                    if ( v148 )
                                                        memmove(v140, v147, 4 * v148);
                                                    operator delete(*(void **)(v43 + 12));
                                                    *(_DWORD *)(v43 + 16) = v145;
                                                    *(_DWORD *)(v43 + 12) = v169;
                                                }
                                                else
                                                {
                                                    v138 = v112 - v137;
                                                    v139 = (int)(v110 + 4);
                                                    v140 = (int *)(v111 + 4 * (v138 >> 1));
                                                    if ( v135 <= v140 )
                                                    {
                                                        v144 = (v139 - (signed int)v135) >> 2;
                                                        if ( v144 )
                                                            memmove(&v140[v136 - v144], v135, 4 * v144);
                                                    }
                                                    else
                                                    {
                                                        v141 = v139 - (_DWORD)v135;
                                                        if ( v141 >> 2 )
                                                            memmove(v140, v135, 4 * (v141 >> 2));
                                                    }
                                                }
                                                *(_DWORD *)(v43 + 32) = v140;
                                                v142 = *v140;
                                                v110 = (char *)&v140[v136 + 0x3FFFFFFF];
                                                *(_DWORD *)(v43 + 48) = v110;
                                                *(_DWORD *)(v43 + 28) = v142 + 512;
                                                *(_DWORD *)(v43 + 24) = v142;
                                                v143 = *(_DWORD *)v110;
                                                *(_DWORD *)(v43 + 44) = *(_DWORD *)v110 + 512;
                                                *(_DWORD *)(v43 + 40) = v143;
                                            }
                                            *((_DWORD *)v110 + 1) = operator new(0x200u);
                                            v113 = *(int **)(v43 + 36);
                                            if ( v113 )
                                                *v113 = v44;
                                            v114 = *(_DWORD *)(v43 + 48);
                                            *(_DWORD *)(v43 + 48) = v114 + 4;
                                            v115 = *(_DWORD *)(v114 + 4);
                                            *(_DWORD *)(v43 + 44) = v115 + 512;
                                            *(_DWORD *)(v43 + 40) = v115;
                                            *(_DWORD *)(v43 + 36) = v115;
                                        }
                                        else
                                        {
                                            v53 = v81 == 0;
                                            v82 = v81 + 4;
                                            if ( !v53 )
                                                *(_DWORD *)(v82 - 4) = v44;
                                            *(_DWORD *)(v43 + 36) = v82;
                                        }
                                        *(_BYTE *)(*(_DWORD *)(v43 + 8) + v44) = 1;
                                    }
                                    pthread_mutex_unlock((pthread_mutex_t *)(v43 + 52));
                                }
                                v174 = 1;
                                goto LABEL_38;
                            }
                        }
                        ++v29;
                        LABEL_43:
                        v31 = *(unsigned __int16 *)(v25 + 10);
                        if ( v31 <= ++v27 )
                            goto LABEL_48;
                        continue;
                    }
                }
                LABEL_38:
                --v5;
                v163 -= 4;
                if ( v5 == -1 )
                    break;
                v4 = *((_DWORD *)v2 + 1034);
            }
            v4 = *((_DWORD *)v2 + 1034);
            v5 = v173 + 1;
        }
        while ( v5 < (*((_DWORD *)v2 + 1035) - v4) >> 2 );
    }
    pthread_mutex_unlock((pthread_mutex_t *)((char *)v2 + 11004));
    while ( 1 )
    {
        v45 = v184;
        if ( v188 == v184 )
            break;
        while ( 1 )
        {
            v46 = *v45;
            if ( v45 == (OneRequest **)(v186 - 4) )
            {
                operator delete(v185);
                src = (char *)src + 4;
                v77 = *(void **)src;
                v186 = (char *)(*(_DWORD *)src + 512);
                v185 = v77;
                v184 = (OneRequest **)v77;
            }
            else
            {
                v184 = v45 + 1;
            }
            if ( *(_DWORD *)v2 <= 0 )
            break;
            P2PClient::sendRequest(v2, v46);
            v45 = v184;
            if ( v188 == v184 )
                goto LABEL_83;
        }
        P2PClient::clearRequest((int)v2, v46);
    }
    LABEL_83:
    if ( v174 )
        P2PClient::notifyFinishedFiles(v2);
    return std::_Deque_base<OneRequest *,std::allocator<OneRequest *>>::~_Deque_base(&v182);
}

//----- (00030F80) --------------------------------------------------------
void **__fastcall P2PClient::p2pClientRoutine(P2PClient *this)
{
    P2PClient *v1; // r4

    v1 = this;
    *((_DWORD *)this + 1025) = (*(int (__cdecl **)(_DWORD, _DWORD))(**((_DWORD **)this + 1026) + 8))(
            *((_DWORD *)this + 1026),
    *(_DWORD *)(**((_DWORD **)this + 1026) + 8));
    return P2PClient::checkAllRequests(v1);
}

//----- (00030FD8) --------------------------------------------------------
int __fastcall P2PClient::P2PClient(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12)
{
    int v12; // r4
    int v13; // lr
    int v14; // r5
    void *v15; // r7
    _DWORD *v16; // r0
    int result; // r0
    int v18; // [sp+0h] [bp-30h]
    int v19; // [sp+4h] [bp-2Ch]

    v12 = a1;
    v13 = a1 + 4096;
    v14 = a1 + 4124;
    *(_DWORD *)a1 = a12;
    *(_DWORD *)(a1 + 4104) = a2;
    *(_DWORD *)(a1 + 4108) = 0;
    *(_DWORD *)(a1 + 4112) = a3;
    *(_DWORD *)(a1 + 4116) = a4;
    *(_DWORD *)(a1 + 4120) = a5;
    *(_DWORD *)(a1 + 4124) = 0;
    *(_DWORD *)(v14 + 4) = 0;
    *(_DWORD *)(v14 + 8) = 0;
    *(_DWORD *)(a1 + 4136) = 0;
    *(_DWORD *)(v13 + 44) = 0;
    *(_DWORD *)(v13 + 48) = 0;
    *(_DWORD *)(a1 + 10976) = a8;
    *(_DWORD *)(a1 + 10992) = a10;
    *(_DWORD *)(a1 + 10996) = a9;
    *(_DWORD *)(a1 + 11000) = 0;
    pthread_mutex_init((pthread_mutex_t *)(a1 + 11004), 0);
    pthread_mutex_init((pthread_mutex_t *)(v12 + 11008), 0);
    *(_DWORD *)(v12 + 11032) = 0;
    *(_BYTE *)(v12 + 11028) = 1;
    gettimeofday((struct timeval *)&v18, 0);
    srand48(v19 / 0x3E8uLL + 1000 * v18);
    *(_DWORD *)(v12 + 10960) = a6;
    *(_DWORD *)(v12 + 10964) = a7;
    *(_DWORD *)(v12 + 10968) = a11;
    *(_DWORD *)(v12 + 10972) = 0;
    *(_DWORD *)(v12 + 10980) = malloc(0x10u);
    v15 = operator new(0x2Cu);
    ConnectionManager::ConnectionManager((int)v15, *(_DWORD *)(v12 + 4104), *(_DWORD *)v12, 64);
    *(_DWORD *)(v12 + 10972) = v15;
    *(_BYTE *)(v12 + 11012) = 1;
    pthread_mutex_init((pthread_mutex_t *)(v12 + 11016), 0);
    *(_DWORD *)(v12 + 11020) = 0;
    v16 = operator new(0xCu);
    *v16 = 0;
    v16[1] = 0;
    v16[2] = 0;
    *(_DWORD *)(v12 + 11024) = v16;
    P2PClient::p2pClientRoutine((P2PClient *)v12);
    *(_DWORD *)(v12 + 11036) = 1;
    dword_F3D50 = v12;
    result = v12;
    *(_QWORD *)(v12 + 11040) = 4294967288LL;
    return result;
}
// F3D50: using guessed type int dword_F3D50;