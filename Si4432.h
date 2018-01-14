#ifndef __Si4432_h__
#define __Si4432_h__


#define Si4432_TxPacketLength 0x3e
#define Si4432_RxPacketLength 0x4b
#define Si4432_RxBuffer 0x7f
#define Si4432_TxBuffer 0x7f

void Si4432_Init(void);
uint8_t Si4432_ReadRegister(uint8_t reg);
void Si4432_WriteRegister(uint8_t reg,uint8_t value);
void Si4432_WriteRegisters(uint8_t reg,uint8_t Count,const uint8_t *p);
void Si4432_ReadRegisters(uint8_t reg,uint8_t Count,uint8_t *p);

#endif // __Si4432_h__
