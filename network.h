/*
 * =========================================================
 * 3DS App Receiver v0.5.6
 * Network Header
 * Based on PSPSDK Official Sample
 * =========================================================
 */

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <pspkernel.h>

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
    Network Initialize / Shutdown
=========================================================*/

/* ネットワークライブラリ初期化 */
int Network_Init(void);

/* ネットワーク終了処理 */
void Network_Shutdown(void);

/*=========================================================
    Connection Information
=========================================================*/

/* 接続状態表示 */
void Network_PrintConnectionState(void);

/* IPアドレス取得 */
int Network_GetIP(char *ip);

/* IPアドレス表示 */
void Network_PrintIP(void);

/* 接続済みか判定
   1 = Connected
   0 = Not Connected
*/
int Network_IsConnected(void);

#ifdef __cplusplus
}
#endif

#endif /* __NETWORK_H__ */
