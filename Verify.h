#ifndef __VERIFY_H__
#define __VERUFY_H__
unsigned char GetVerify_Sum(unsigned char* pBuff,unsigned int Count);
unsigned char GetVerify_CRC8(unsigned char* pBuff, unsigned int Count);

#ifdef Verify_CRC16

uint GetVerify_CRC16(unsigned char *puchMsg,unsigned int usDataLen);

#ifndef Verify_CRC16_Init
#define Verify_CRC16_Init 0xffff
#endif

#endif


unsigned char GetVerify_byteXOR(unsigned char* pBuff, unsigned int Count);
unsigned char GetVerify_byteXOR_WithOrigV(unsigned char origV,unsigned char* pBuff, unsigned int Count);
#define VERIFYSUM(x,y) ((unsigned char)(x+y))
extern const unsigned char auchCRCHi[];
extern const unsigned char auchCRCLo[];
#define VERIFYCRC16(x) uIndex = crc.u8H ^ x ;	\
						crc.u8H = crc.u8L ^ auchCRCHi[uIndex] ;	\
						crc.u8L = auchCRCLo[uIndex] ;
#define VERIFYXOR(x,y) ((unsigned char)(x^y))
#endif
