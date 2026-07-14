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
#include <pspnet_apctl.h>
#include <psputility.h>
#include <psputility_netconf.h>
#include <psputility_sysparam.h>

#include <string.h>

#include "dialog.h"

/*=========================================================
    Dialog Result
=========================================================*/

#define DIALOG_RESULT_RUNNING     1
#define DIALOG_RESULT_OK          0
#define DIALOG_RESULT_CANCEL     -1
#define DIALOG_RESULT_ERROR      -2

/*=========================================================
    NetConf Data
=========================================================*/

static pspUtilityNetconfData g_NetConf;

/*=========================================================
    Dialog Initialize
=========================================================*/

int Dialog_Init(void)
{
    memset(&g_NetConf, 0, sizeof(g_NetConf));

    g_NetConf.base.size = sizeof(g_NetConf);

    g_NetConf.base.language =
        PSP_SYSTEMPARAM_LANGUAGE_JAPANESE;

    g_NetConf.base.buttonSwap =
        PSP_UTILITY_ACCEPT_CROSS;

    g_NetConf.base.graphicsThread = 17;
    g_NetConf.base.accessThread   = 19;
    g_NetConf.base.fontThread     = 18;
    g_NetConf.base.soundThread    = 16;

    g_NetConf.action =
        PSP_NETCONF_ACTION_CONNECTAP;

    pspDebugScreenPrintf(
        "Starting Network Config Dialog...\n");

    if(sceUtilityNetconfInitStart(&g_NetConf) < 0)
    {
        pspDebugScreenPrintf(
            "sceUtilityNetconfInitStart FAILED\n");

        return DIALOG_RESULT_ERROR;
    }

    return DIALOG_RESULT_RUNNING;
}
/*=========================================================
    Dialog Update
=========================================================*/

int Dialog_Update(void)
{
    int status;

    status = sceUtilityNetconfGetStatus();

    switch(status)
    {
        /*-----------------------------------------
            Visible
        -----------------------------------------*/

        case PSP_UTILITY_DIALOG_VISIBLE:

            sceUtilityNetconfUpdate(1);

            return DIALOG_RESULT_RUNNING;

        /*-----------------------------------------
            Quit
        -----------------------------------------*/

        case PSP_UTILITY_DIALOG_QUIT:

            sceUtilityNetconfShutdownStart();

            return DIALOG_RESULT_RUNNING;

        /*-----------------------------------------
            None
        -----------------------------------------*/

        case PSP_UTILITY_DIALOG_NONE:

            return DIALOG_RESULT_OK;

        /*-----------------------------------------
            Init
        -----------------------------------------*/

        case PSP_UTILITY_DIALOG_INIT:

            return DIALOG_RESULT_RUNNING;

        /*-----------------------------------------
            Unknown
        -----------------------------------------*/

        default:

            pspDebugScreenPrintf(
                "Dialog Status : %d\n",
                status);

            return DIALOG_RESULT_RUNNING;
    }
}
/*=========================================================
    Dialog Shutdown
=========================================================*/

void Dialog_Shutdown(void)
{
    while(1)
    {
        int status;

        status = sceUtilityNetconfGetStatus();

        if(status == PSP_UTILITY_DIALOG_NONE)
        {
            break;
        }

        if(status == PSP_UTILITY_DIALOG_QUIT)
        {
            sceUtilityNetconfShutdownStart();
        }

        switch(status)
{
    case PSP_UTILITY_DIALOG_VISIBLE:
        sceUtilityNetconfUpdate(1);
        break;

    case PSP_UTILITY_DIALOG_QUIT:
        sceUtilityNetconfShutdownStart();
        break;

    case PSP_UTILITY_DIALOG_NONE:
        return;
}

        sceDisplayWaitVblankStart();
    }
}

/*=========================================================
    Dialog Finished
=========================================================*/

int Dialog_Finished(void)
{
    if(sceUtilityNetconfGetStatus() ==
        PSP_UTILITY_DIALOG_NONE)
    {
        return 1;
    }

    return 0;
}
/*=========================================================
    Show Network Config Dialog
=========================================================*/

int Dialog_ShowNetConfig(void)
{
    int ret;

    /*-----------------------------------------
        Initialize
    -----------------------------------------*/

    ret = Dialog_Init();

    if(ret != DIALOG_RESULT_RUNNING)
    {
        return DIALOG_RESULT_ERROR;
    }

    /*-----------------------------------------
        Main Loop
    -----------------------------------------*/

    while(1)
    {
        ret = Dialog_Update();

        if(ret == DIALOG_RESULT_OK)
        {
            break;
        }

        if(ret == DIALOG_RESULT_ERROR)
        {
            Dialog_Shutdown();

            return DIALOG_RESULT_ERROR;
        }

        sceDisplayWaitVblankStart();
    }

    /*-----------------------------------------
        Shutdown
    -----------------------------------------*/

    Dialog_Shutdown();

    /*-----------------------------------------
        Connection Check
    -----------------------------------------*/

    {
        int state = 0;

        if(sceNetApctlGetState(&state) < 0)
        {
            return DIALOG_RESULT_ERROR;
        }

pspDebugScreenPrintf("APCTL State : %d\n", state);

if(state != 4)
{
    return DIALOG_RESULT_CANCEL;
}

return DIALOG_RESULT_OK;
