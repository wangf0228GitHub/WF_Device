#ifndef __VERIFY_H__
#define __VERIFY_H__

#include "HardwareProfile.h"


#define VERIFYSUM(x,y) ((uint8_t)(x+y))
#define VERIFYXOR(x,y) ((uint8_t)(x^y))


#ifdef Verify_Sum
#ifdef MCU32
	uint8_t GetVerify_Sum(uint8_t* pBuff,uint32_t Count);
#else
    uint8_t GetVerify_Sum(uint8_t* pBuff,uint8_t Count);
#endif

#endif

#ifdef Verify_CRC8
#ifdef MCU32
	uint8_t GetVerify_CRC8(uint8_t* pBuff, uint32_t Count);
#else
    uint8_t GetVerify_CRC8(uint8_t* pBuff, uint8_t Count);
#endif

#endif


#ifdef Verify_CRC16
#include "TypeDefine.h"
#define VERIFYCRC16(x) uIndex = crc.u8H ^ x ;	\
	crc.u8H = crc.u8L ^ auchCRCHi[uIndex] ;	\
	crc.u8L = auchCRCLo[uIndex] ;
extern const uint8_t auchCRCHi[];
extern const uint8_t auchCRCLo[];
#ifdef MCU32
	u16_wf GetVerify_CRC16(uint8_t *puchMsg,uint32_t usDataLen);
#else
    u16_wf GetVerify_CRC16(uint8_t *puchMsg,uint8_t usDataLen);
#endif


#ifndef Verify_CRC16_Init
#define Verify_CRC16_Init 0xffff
#endif

#endif

#ifdef Verify_byteXOR
#ifdef MCU32
	uint8_t GetVerify_byteXOR(uint8_t* pBuff, uint32_t Count);
uint8_t GetVerify_byteXOR_WithOrigV(uint8_t origV,uint8_t* pBuff, uint32_t Count);
#else
    uint8_t GetVerify_byteXOR(uint8_t* pBuff, uint8_t Count);
uint8_t GetVerify_byteXOR_WithOrigV(uint8_t origV,uint8_t* pBuff, uint8_t Count);
#endif

#endif

#endif
