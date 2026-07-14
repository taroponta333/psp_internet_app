/*
 * =========================================================
 * 3DS App Receiver v0.5.6
 * Network Header
 * Based on PSPSDK Official Samples
 * =========================================================
 */

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <pspkernel.h>

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
    Network
=========================================================*/

int Network_Init(void);

void Network_Shutdown(void);

void Network_PrintConnectionState(void);

int Network_GetIP(char *ip);

void Network_PrintIP(void);

#ifdef __cplusplus
}
#endif

#endif /* __NETWORK_H__ */
