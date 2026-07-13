/*
 * =========================================================
 * 3DS App Receiver v0.5.5
 * Network
 * Based on PSPSDK Official Network Sample
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
    int stateLast = -1;

    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf("=================================\n");
    pspDebugScreenPrintf(" Network Initialize\n");
    pspDebugScreenPrintf("=================================\n\n");

    /*-----------------------------------------
        Load COMMON Module
    -----------------------------------------*/

    pspDebugScreenPrintf("Load COMMON Module...\n");

    ret = sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);

    pspDebugScreenPrintf("Return : 0x%08X\n", ret);

    /*-----------------------------------------
        Load INET Module
    -----------------------------------------*/

    pspDebugScreenPrintf("Load INET Module...\n");

    ret = sceUtilityLoadNetModule(PSP_NET_MODULE_INET);

    pspDebugScreenPrintf("Return : 0x%08X\n", ret);

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

    pspDebugScreenPrintf("OK\n\n");

    /*-----------------------------------------
        Connect to Access Point
    -----------------------------------------*/

    pspDebugScreenPrintf("Connecting...\n");

    ret = sceNetApctlConnect(1);

    if(ret != 0)
    {
        pspDebugScreenPrintf(
            "sceNetApctlConnect : 0x%08X\n",
            ret);

        return ret;
    }

    while(1)
    {
        int state;

        ret = sceNetApctlGetState(&state);

        if(ret != 0)
        {
            pspDebugScreenPrintf(
                "sceNetApctlGetState : 0x%08X\n",
                ret);

            return ret;
        }

        if(state > stateLast)
        {
            pspDebugScreenPrintf(
                "Connection State : %d / 4\n",
                state);

            stateLast = state;
        }

        if(state == 4)
            break;

        sceKernelDelayThread(50 * 1000);
    }

    pspDebugScreenPrintf("Connected!\n\n");

    return 0;
}
/*=========================================================
    Network Shutdown
=========================================================*/

void Network_Shutdown(void)
{
    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf("Network Shutdown...\n");

    pspSdkInetTerm();

    /* Utility Modules */

    sceUtilityUnloadNetModule(
        PSP_NET_MODULE_INET);

    sceUtilityUnloadNetModule(
        PSP_NET_MODULE_COMMON);

    pspDebugScreenPrintf("Done.\n");
}

/*=========================================================
    Connection State
=========================================================*/

void Network_PrintConnectionState(void)
{
    int state;

    if(sceNetApctlGetState(&state) < 0)
    {
        pspDebugScreenPrintf(
            "Connection State : Unknown\n");

        return;
    }

    switch(state)
    {
        case 0:
            pspDebugScreenPrintf(
                "Connection : Disconnected\n");
            break;

        case 1:
            pspDebugScreenPrintf(
                "Connection : Scanning\n");
            break;

        case 2:
            pspDebugScreenPrintf(
                "Connection : Connecting\n");
            break;

        case 3:
            pspDebugScreenPrintf(
                "Connection : Getting IP\n");
            break;

        case 4:
            pspDebugScreenPrintf(
                "Connection : Connected\n");
            break;

        default:
            pspDebugScreenPrintf(
                "Connection : Unknown (%d)\n",
                state);
            break;
    }
}

/*=========================================================
    Get IP Address
=========================================================*/

int Network_GetIP(char *ip)
{
    union SceNetApctlInfo info;

    memset(&info, 0, sizeof(info));

    if(sceNetApctlGetInfo(
        PSP_NET_APCTL_INFO_IP,
        &info) != 0)
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
        pspDebugScreenPrintf(
            "IP : Unknown\n");

        return;
    }

    pspDebugScreenPrintf(
        "IP : %s\n",
        ip);
}
