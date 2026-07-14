/*
 * =========================================================
 * 3DS App Receiver v0.5.6
 * Network Configuration Dialog
 * Based on PSPSDK Official Samples
 * =========================================================
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>

#include <psputility.h>
#include <psputility_netconf.h>
#include <psputility_sysparam.h>

#include <string.h>

#include "dialog.h"

/*=========================================================
    Parameter
=========================================================*/

static pspUtilityNetconfData netData;

/*=========================================================
    Initialize
=========================================================*/

int Dialog_InitNetConfig(void)
{
    memset(&netData, 0, sizeof(netData));

    netData.base.size = sizeof(netData);

    netData.base.language =
        PSP_SYSTEMPARAM_LANGUAGE_JAPANESE;

    netData.base.buttonSwap =
        PSP_UTILITY_ACCEPT_CROSS;

    netData.base.graphicsThread = 17;
    netData.base.accessThread   = 19;
    netData.base.fontThread     = 18;
    netData.base.soundThread    = 16;

    netData.action =
        PSP_NETCONF_ACTION_CONNECTAP;

    return sceUtilityNetconfInitStart(
        &netData);
}

/*=========================================================
    Update
=========================================================*/

int Dialog_UpdateNetConfig(void)
{
    switch(sceUtilityNetconfGetStatus())
    {
        case PSP_UTILITY_DIALOG_VISIBLE:

            sceUtilityNetconfUpdate(1);

            break;

        case PSP_UTILITY_DIALOG_QUIT:

            sceUtilityNetconfShutdownStart();

            break;

        case PSP_UTILITY_DIALOG_NONE:

            return 1;

        default:

            break;
    }

    return 0;
}

/*=========================================================
    Draw
=========================================================*/

void Dialog_Draw(void)
{
    sceDisplayWaitVblankStart();
}

/*=========================================================
    Run Network Config Dialog
=========================================================*/

int Dialog_ShowNetConfig(void)
{
    int ret;

    ret = Dialog_InitNetConfig();

    if(ret < 0)
    {
        pspDebugScreenPrintf(
            "NetConf Init Failed : 0x%08X\n",
            ret);

        return ret;
    }

    while(1)
    {
        if(Dialog_UpdateNetConfig())
            break;

        Dialog_Draw();
    }

    pspDebugScreenPrintf(
        "NetConf Finished.\n");

    return 0;
}

/*=========================================================
    Shutdown
=========================================================*/

void Dialog_Shutdown(void)
{
    while(sceUtilityNetconfGetStatus()
        != PSP_UTILITY_DIALOG_NONE)
    {
        if(sceUtilityNetconfGetStatus()
            == PSP_UTILITY_DIALOG_QUIT)
        {
            sceUtilityNetconfShutdownStart();
        }

        sceUtilityNetconfUpdate(1);

        sceDisplayWaitVblankStart();
    }
}
