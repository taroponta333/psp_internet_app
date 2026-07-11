#include <pspkernel.h>
#include <pspdebug.h>

#include <pspnet.h>
#include <pspnet_apctl.h>
#include <pspnet_inet.h>
#include <pspnet_resolver.h>

#include <stdio.h>
#include <string.h>

#include "network.h"

/*=========================================================
    ネットワーク初期化
=========================================================*/

int Network_Init(void)
{
    int ret;

    ret = sceNetInit(
        128 * 1024,
        42,
        4 * 1024,
        42,
        4 * 1024);

    if (ret < 0)
        return ret;

    ret = sceNetInetInit();

    if (ret < 0)
        return ret;

    ret = sceNetResolverInit();

    if (ret < 0)
        return ret;

    ret = sceNetApctlInit(
        0x1800,
        48);

    if (ret < 0)
        return ret;

    return 0;
}

/*=========================================================
    ネットワーク終了
=========================================================*/

void Network_Shutdown(void)
{
    sceNetApctlTerm();
    sceNetResolverTerm();
    sceNetInetTerm();
    sceNetTerm();
}

/*=========================================================
    接続状態
=========================================================*/

int Network_IsConnected(void)
{
    int state;

    if (sceNetApctlGetState(&state) < 0)
        return 0;

    return (state == 4);
}

/*=========================================================
    接続状態表示
=========================================================*/

void Network_PrintConnectionState(void)
{
    int state = 0;

    if (sceNetApctlGetState(&state) < 0)
    {
        pspDebugScreenPrintf("Network State : Unknown\n");
        return;
    }

    pspDebugScreenPrintf("\n");

    switch (state)
    {
        case 0:
            pspDebugScreenPrintf("Disconnected\n");
            break;

        case 1:
            pspDebugScreenPrintf("Scanning...\n");
            break;

        case 2:
            pspDebugScreenPrintf("Connecting...\n");
            break;

        case 3:
            pspDebugScreenPrintf("Getting IP...\n");
            break;

        case 4:
            pspDebugScreenPrintf("Connected!\n");
            break;

        default:
            pspDebugScreenPrintf("Unknown State : %d\n", state);
            break;
    }
}

/*=========================================================
    IP取得
=========================================================*/

int Network_GetIP(char *ip)
{
    union SceNetApctlInfo info;

    memset(&info, 0, sizeof(info));

    if (sceNetApctlGetInfo(PSP_NET_APCTL_INFO_IP, &info) < 0)
        return -1;

    strcpy(ip, info.ip);

    return 0;
}

/*=========================================================
    IP表示
=========================================================*/

void Network_PrintIP(void)
{
    char ip[16];

    if (Network_GetIP(ip) < 0)
    {
        pspDebugScreenPrintf("IP : Unknown\n");
        return;
    }

    pspDebugScreenPrintf("IP : %s\n", ip);
}
