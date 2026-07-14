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

/*=========================================================
    Network Configuration Dialog
=========================================================*/

/* 初期化 */
int Dialog_InitNetConfig(void);

/* 更新 */
int Dialog_UpdateNetConfig(void);

/* 描画 */
void Dialog_Draw(void);

/* ダイアログ表示 */
int Dialog_ShowNetConfig(void);

/* 終了処理 */
void Dialog_Shutdown(void);

#endif /* __DIALOG_H__ */
