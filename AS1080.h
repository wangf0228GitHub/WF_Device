#ifndef __AS1080_h__
#define __AS1080_h__

void AS1080_Init(void);

#ifndef AS1080Addr
#define AS1080Addr 0x2e
#endif

void AS1080_SendByte(unsigned char addr,unsigned char dat);
unsigned char AS1080_ReadByte(unsigned char addr);
#endif // __Key_h__
