/*
 * =========================================================
 * 3DS App Receiver v0.5.5
 * Main Program
 * Based on PSPSDK Official Network Sample
 * =========================================================
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

#include <pspsdk.h>
#include <psputility.h>

#include "network.h"
#include "receiver.h"

/*=========================================================
    Module Information
=========================================================*/

PSP_MODULE_INFO("3DS App Receiver", 0, 5, 5);

PSP_HEAP_THRESHOLD_SIZE_KB(1024);
PSP_HEAP_SIZE_KB(-2048);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);
PSP_MAIN_THREAD_STACK_SIZE_KB(1024);

/*=========================================================
    Exit Callback
=========================================================*/

int exit_callback(int arg1, int arg2, void *common)
{
    Network_Shutdown();
    sceKernelExitGame();
    return 0;
}

/*=========================================================
    Callback Thread
=========================================================*/

int CallbackThread(SceSize args, void *argp)
{
    int cbid;

    cbid = sceKernelCreateCallback(
        "Exit Callback",
        exit_callback,
        NULL);

    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();

    return 0;
}

/*=========================================================
    Setup Callback
=========================================================*/

int SetupCallbacks(void)
{
    int thid;

    thid = sceKernelCreateThread(
        "update_thread",
        CallbackThread,
        0x11,
        0xFA0,
        PSP_THREAD_ATTR_USER,
        NULL);

    if(thid >= 0)
    {
        sceKernelStartThread(thid, 0, NULL);
    }

    return thid;
}

/*=========================================================
    Network Thread
=========================================================*/

int NetworkThread(SceSize args, void *argp)
{
    int ret;

    pspDebugScreenInit();

    pspDebugScreenPrintf("=================================\n");
    pspDebugScreenPrintf("      3DS App Receiver\n");
    pspDebugScreenPrintf("            v0.5.5\n");
    pspDebugScreenPrintf("=================================\n\n");

    /*
     * Official Sample Style
     * Network initialization is handled by Network_Init().
     */

    ret = Network_Init();

    if(ret < 0)
    {
        pspDebugScreenPrintf("\n");
        pspDebugScreenPrintf("Network Init Failed!\n");
        pspDebugScreenPrintf("Error : 0x%08X\n", ret);

        while(1)
        {
            sceDisplayWaitVblankStart();
        }
    }

    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf("[OK] Network Initialized\n\n");
    Network_PrintConnectionState();
    Network_PrintIP();

    /*=====================================================
        Receiver Initialize
    =====================================================*/

    Receiver_Init();

    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf("---------------------------------\n");
    pspDebugScreenPrintf("Waiting for 3DS...\n");
    pspDebugScreenPrintf("---------------------------------\n\n");

    pspDebugScreenPrintf("HOME : Exit\n\n");

    /*=====================================================
        Main Loop
    =====================================================*/

    while(1)
    {
        Receiver_Update();

        sceDisplayWaitVblankStart();
    }

    /* Normally never reaches here */

    Receiver_Shutdown();
    Network_Shutdown();

    sceKernelExitDeleteThread(0);

    return 0;
}

/*=========================================================
    Main
=========================================================*/

int main(int argc, char *argv[])
{
    SceUID thid;

    /* HOME Button Callback */

    SetupCallbacks();

    /* Debug Screen */

    pspDebugScreenInit();

    /*=====================================================
        Create Official Style Network Thread
    =====================================================*/

    thid = sceKernelCreateThread(
        "network_thread",
        NetworkThread,
        0x11,
        256 * 1024,
        PSP_THREAD_ATTR_USER,
        NULL);

    if(thid < 0)
    {
        pspDebugScreenPrintf(
            "Failed to create network thread.\n");

        sceKernelSleepThread();

        return 0;
    }

    sceKernelStartThread(
        thid,
        0,
        NULL);

    /*=====================================================
        End Main Thread
    =====================================================*/

    sceKernelExitDeleteThread(0);

    return 0;
}
