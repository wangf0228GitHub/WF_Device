#ifndef __SS5060_h__
#define __SS5060_h__

#ifndef SS5060_RetryCount
#define SS5060_RetryCount 2
#endif

#ifndef SS5060_Addr
#define SS5060_Addr 0b01000110
#endif

uint SS5060_RegReadResualt;

void SS5060_Init(void);
unsigned char SS5060_ReadReg(void);
unsigned char SS5060_Setting(unsigned char x);
unsigned char SS5060_GetResult(unsigned char x);
#endif
