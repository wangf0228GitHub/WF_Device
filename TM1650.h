#ifndef __TM1650_h__
#define __TM1650_h__

#ifndef TM1650_RetryCount
#define TM1650_RetryCount 2
#endif

extern unsigned char TM1650_Result;
#ifndef TM1650_LEDNumCode
const unsigned char TM1650_LEDNumCode[]=
{
	//DP G F E D C B A
	0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x40,0x00//0-9,A-F,-
};
#endif
unsigned char TM1650_Read(void);
void TM1650_Init(void);
//送6位地址+TM1650_DATALENGTH位数据
unsigned char TM1650_WriteData(unsigned char Com,unsigned char Data);

#ifdef TM1650_2
#ifndef TM1650_RetryCount_2
#define TM1650_RetryCount_2 2
#endif

extern unsigned char TM1650_Result_2;
unsigned char TM1650_Read_2(void);
void TM1650_Init_2(void);
//送6位地址+TM1650_DATALENGTH位数据
unsigned char TM1650_WriteData_2(unsigned char Com,unsigned char Data);
#endif

#ifdef TM1650_3
#ifndef TM1650_RetryCount_3
#define TM1650_RetryCount_3 2
#endif

extern unsigned char TM1650_Result_3;
unsigned char TM1650_Read_3(void);
void TM1650_Init_3(void);
//送6位地址+TM1650_DATALENGTH位数据
unsigned char TM1650_WriteData_3(unsigned char Com,unsigned char Data);
#endif

#endif
