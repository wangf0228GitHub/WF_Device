#ifndef __TM1650_h__
#define __TM1650_h__

#ifndef TM1650_RetryCount
#define TM1650_RetryCount 2
#endif

extern uint8_t TM1650_Result;
#ifndef TM1650_LEDNumCode
const uint8_t TM1650_LEDNumCode[]=
{
	//DP G F E D C B A
	0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x40,0x00//0-9,A-F,-
};
#endif
uint8_t TM1650_Read(void);
void TM1650_Init(void);
//送6位地址+TM1650_DATALENGTH位数据
uint8_t TM1650_WriteData(uint8_t Com,uint8_t Data);

#ifdef TM1650_2
#ifndef TM1650_2_RetryCount
#define TM1650_2_RetryCount 2
#endif

extern uint8_t TM1650_2_Result;
uint8_t TM1650_2_Read(void);
void TM1650_2_Init(void);
//送6位地址+TM1650_DATALENGTH位数据
uint8_t TM1650_2_WriteData(uint8_t Com,uint8_t Data);
#endif

#ifdef TM1650_3
#ifndef TM1650_3_RetryCount
#define TM1650_3_RetryCount 2
#endif

extern uint8_t TM1650_3_Result;
uint8_t TM1650_3_Read(void);
void TM1650_3_Init(void);
//送6位地址+TM1650_DATALENGTH位数据
uint8_t TM1650_3_WriteData(uint8_t Com,uint8_t Data);
#endif

#ifdef TM1650_4
#ifndef TM1650_4_RetryCount
#define TM1650_4_RetryCount 2
#endif

extern uint8_t TM1650_4_Result;
uint8_t TM1650_4_Read(void);
void TM1650_4_Init(void);
//送6位地址+TM1650_DATALENGTH位数据
uint8_t TM1650_4_WriteData(uint8_t Com, uint8_t Data);
#endif


#endif
