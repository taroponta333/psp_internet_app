#include <pspkernel.h>
#include <pspdebug.h>

#include "receiver.h"

/*=========================================================
    Receiver 初期化
=========================================================*/

int Receiver_Init(void)
{
    pspDebugScreenPrintf("Receiver Initialized\n");

    return 0;
}

/*=========================================================
    Receiver 更新
=========================================================*/

void Receiver_Update(void)
{
    /*
        v0.6

        ・Socket作成
        ・接続待機
        ・データ受信

        をここへ追加
    */
}

/*=========================================================
    Receiver 終了
=========================================================*/

void Receiver_Shutdown(void)
{
    pspDebugScreenPrintf("Receiver Shutdown\n");
}
