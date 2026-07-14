/*
 * =========================================================
 * 3DS App Receiver v0.5.6
 * Dialog Header
 * Based on PSPSDK Official Samples
 * =========================================================
 */

#ifndef __DIALOG_H__
#define __DIALOG_H__

#include <pspkernel.h>
#include <psputility.h>
#include <psputility_netconf.h>

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
    Dialog Result
=========================================================*/

#define DIALOG_RESULT_RUNNING     1
#define DIALOG_RESULT_OK          0
#define DIALOG_RESULT_CANCEL     -1
#define DIALOG_RESULT_ERROR      -2

/*=========================================================
    Network Configuration Dialog
=========================================================*/

/* 初期化 */
int Dialog_Init(void);

/* 更新 */
int Dialog_Update(void);

/* 終了処理 */
void Dialog_Shutdown(void);

/* 完了確認 */
int Dialog_Finished(void);

/* ネットワーク設定ダイアログ表示 */
int Dialog_ShowNetConfig(void);

#ifdef __cplusplus
}
#endif

#endif /* __DIALOG_H__ */
