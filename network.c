/*
 * =========================================================
 * 3DS App Receiver v0.5.5
 * Network
 * PSPSDK Official Sample Based
 * =========================================================
 */

#include <pspkernel.h>
#include <pspdebug.h>

#include <pspsdk.h>

#include <pspnet.h>
#include <pspnet_apctl.h>
#include <pspnet_inet.h>
#include <pspnet_resolver.h>

#include <psputility.h>

#include <stdio.h>
#include <string.h>

#include "network.h"

/*=========================================================
    Network Initialize
=========================================================*/

int Network_Init(void)
{
    int ret;

    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf("=================================\n");
    pspDebugScreenPrintf(" Network Initialize\n");
    pspDebugScreenPrintf("=================================\n\n");

    /*-----------------------------------------
        COMMON Module
    -----------------------------------------*/

    pspDebugScreenPrintf(
        "Load COMMON Module...\n");

    ret = sceUtilityLoadNetModule(
        PSP_NET_MODULE_COMMON);

    if(ret < 0)
    {
        pspDebugScreenPrintf(
            "FAILED : 0x%08X\n",
            ret);

        return ret;
    }

    pspDebugScreenPrintf("OK\n");

    /*-----------------------------------------
        INET Module
    -----------------------------------------*/

    pspDebugScreenPrintf(
        "Load INET Module...\n");

    ret = sceUtilityLoadNetModule(
        PSP_NET_MODULE_INET);

    if(ret < 0)
    {
        pspDebugScreenPrintf(
            "FAILED : 0x%08X\n",
            ret);

        return ret;
    }

    pspDebugScreenPrintf("OK\n");

    /*-----------------------------------------
        Official SDK Initialize
    -----------------------------------------*/

    pspDebugScreenPrintf(
        "pspSdkInetInit()...\n");

    ret = pspSdkInetInit();

    if(ret < 0)
    {
        pspDebugScreenPrintf(
            "FAILED : 0x%08X\n",
            ret);

        return ret;
    }

    pspDebugScreenPrintf("OK\n");
    /*-----------------------------------------
        Official SDK Initialize
    -----------------------------------------*/

    pspDebugScreenPrintf("pspSdkInetInit()...\n");

    ret = pspSdkInetInit();

    if(ret < 0)
    {
        pspDebugScreenPrintf("FAILED : 0x%08X\n", ret);
        return ret;
    }

    pspDebugScreenPrintf("OK\n");

    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf("Connecting to Access Point...\n");

    /* 接続プロファイル1を使用 */

    ret = sceNetApctlConnect(1);

    if(ret != 0)
    {
        pspDebugScreenPrintf(
            "sceNetApctlConnect FAILED : 0x%08X\n",
            ret);

        return ret;
    }

    /* 接続待ち */

    {
        int state = 0;
        int lastState = -1;

        while(state != 4)
        {
            ret = sceNetApctlGetState(&state);

            if(ret < 0)
            {
                pspDebugScreenPrintf(
                    "sceNetApctlGetState FAILED : 0x%08X\n",
                    ret);

                return ret;
            }

            if(state != lastState)
            {
                pspDebugScreenPrintf(
                    "Connection State : %d / 4\n",
                    state);

                lastState = state;
            }

            sceKernelDelayThread(50 * 1000);
        }
    }

    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf("Connected!\n");

    return 0;
}

/*=========================================================
    Shutdown
=========================================================*/

void Network_Shutdown(void)
{
    pspSdkInetTerm();
}

/*=========================================================
    Connection State
=========================================================*/

void Network_PrintConnectionState(void)
{
    int state = 0;

    if(sceNetApctlGetState(&state) < 0)
    {
        pspDebugScreenPrintf("State : Unknown\n");
        return;
    }

    pspDebugScreenPrintf("State : %d\n", state);
}

/*=========================================================
    Get IP Address
=========================================================*/

int Network_GetIP(char *ip)
{
    union SceNetApctlInfo info;

    memset(&info, 0, sizeof(info));

    if(sceNetApctlGetInfo(PSP_NET_APCTL_INFO_IP, &info) != 0)
    {
        strcpy(ip, "Unknown");
        return -1;
    }

    strcpy(ip, info.ip);

    return 0;
}

/*=========================================================
    Print IP Address
=========================================================*/

void Network_PrintIP(void)
{
    char ip[16];

    if(Network_GetIP(ip) < 0)
    {
        pspDebugScreenPrintf("IP : Unknown\n");
        return;
    }

    pspDebugScreenPrintf("IP : %s\n", ip);
}
