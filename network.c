/*
 * =========================================================
 * 3DS App Receiver v0.5.6
 * Network
 * Based on PSPSDK Official Sample
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
        Load COMMON Module
    -----------------------------------------*/

    pspDebugScreenPrintf("Load COMMON Module...\n");

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
        Load INET Module
    -----------------------------------------*/

    pspDebugScreenPrintf("Load INET Module...\n");

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
        Initialize Network Library
    -----------------------------------------*/

    pspDebugScreenPrintf("pspSdkInetInit()...\n");

    ret = pspSdkInetInit();

    if(ret < 0)
    {
        pspDebugScreenPrintf(
            "FAILED : 0x%08X\n",
            ret);

        return ret;
    }

    pspDebugScreenPrintf("OK\n");

    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf(
        "Network Library Ready.\n\n");

    return 0;
}
/*=========================================================
    Shutdown
=========================================================*/

void Network_Shutdown(void)
{
    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf("Network Shutdown...\n");

    /*-----------------------------------------
        Terminate Network
    -----------------------------------------*/

    pspSdkInetTerm();

    /*-----------------------------------------
        Unload Modules
    -----------------------------------------*/

    sceUtilityUnloadNetModule(
        PSP_NET_MODULE_INET);

    sceUtilityUnloadNetModule(
        PSP_NET_MODULE_COMMON);

    pspDebugScreenPrintf("Done.\n");
}

/*=========================================================
    Print Connection State
=========================================================*/

void Network_PrintConnectionState(void)
{
    int state = 0;

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
                "Connection State : Disconnected\n");
            break;

        case 1:
            pspDebugScreenPrintf(
                "Connection State : Scanning\n");
            break;

        case 2:
            pspDebugScreenPrintf(
                "Connection State : Connecting\n");
            break;

        case 3:
            pspDebugScreenPrintf(
                "Connection State : Getting IP\n");
            break;

        case 4:
            pspDebugScreenPrintf(
                "Connection State : Connected\n");
            break;

        default:
            pspDebugScreenPrintf(
                "Connection State : %d\n",
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
            "IP Address : Unknown\n");
        return;
    }

    pspDebugScreenPrintf(
        "IP Address : %s\n",
        ip);
}

/*=========================================================
    Is Connected
=========================================================*/

int Network_IsConnected(void)
{
    int state;

    if(sceNetApctlGetState(&state) < 0)
        return 0;

    return (state == 4);
}
