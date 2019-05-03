#ifndef __lcyIRDecode_H__
#define __lcyIRDecode_H__

#include <stdint.h>
extern uint8_t lcyIRDecodeIn[0x08];
extern uint8_t lcyIRDecodeOut[0x08];
void lcyIRDecode(void);
void GetlcyIRDecode(uint8_t* pIn,uint8_t* pOut);
void lcyIRDecodeRead(uint8_t* pBuf);
void lcyIRDecodeInit(uint8_t* pBuf);
#endif
