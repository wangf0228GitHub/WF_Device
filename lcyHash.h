#ifndef __lcyHash_H__
#define __lcyHash_H__

#include <stdint.h>
extern uint8_t lcyHashIn[0x08];
extern uint8_t lcyHashOut[0x08];
void lcyHashOnce(void);
void lcyHashCalc(uint8_t n);
void lcyHashRead(uint8_t* pBuf);
void lcyHashInit(uint8_t* pBuf);
void GetlcyHashN(uint8_t* pIn,uint8_t* pOut,uint8_t n);
void GetlcyHashOnce(uint8_t* pIn,uint8_t* pOut);
#endif
