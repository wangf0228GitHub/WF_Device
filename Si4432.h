#ifndef __Si4432_h__
#define __Si4432_h__


#define Si4432_TxPacketLength 0x3e
#define Si4432_RxPacketLength 0x4b
#define Si4432_RxBuffer 0x7f
#define Si4432_TxBuffer 0x7f

void Si4432_Init(void);
unsigned char Si4432_ReadRegister(unsigned char reg);
void Si4432_WriteRegister(unsigned char reg,unsigned char value);
void Si4432_WriteRegisters(unsigned char reg,unsigned char Count,const unsigned char *p);
void Si4432_ReadRegisters(unsigned char reg,unsigned char Count,unsigned char *p);

#endif // __Si4432_h__
