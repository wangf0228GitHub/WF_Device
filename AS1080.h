#ifndef __AS1080_h__
#define __AS1080_h__

void AS1080_Init(void);

#ifndef AS1080Addr
#define AS1080Addr 0x2e
#endif

void AS1080_SendByte(uint8_t addr,uint8_t dat);
uint8_t AS1080_ReadByte(uint8_t addr);
#endif // __Key_h__
