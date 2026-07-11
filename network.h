#ifndef NETWORK_H
#define NETWORK_H

/*=========================================================
    Network
=========================================================*/

/* 初期化 */
int Network_Init(void);

/* 終了 */
void Network_Shutdown(void);

/* 接続状態 */
int Network_IsConnected(void);

/* 状態表示 */
void Network_PrintConnectionState(void);

/* IP取得 */
int Network_GetIP(char *ip);

/* IP表示 */
void Network_PrintIP(void);

#endif
