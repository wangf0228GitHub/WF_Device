#ifndef __DS1302_H__
#define __DS1302_H__

// #define DS1302_DATA_DIR	TRISA1
// #define DS1302_CLK_DIR	TRISA2
// #define DS1302_CE_DIR	TRISA0
// 
// #define DS1302_DATA	RA1
// #define DS1302_CLK	RA2	
// #define DS1302_CE		RA0
typedef union
{	
	unsigned char Times[7];
	struct
	{
		unsigned char Second;
		unsigned char Minute;
		unsigned char Hour;
		unsigned char Day;
		unsigned char Month;
		unsigned char Week;
		unsigned char Year;
		//unsigned char WP;
	};	
}DS1302_TIME;


extern DS1302_TIME DS1302_Time;//秒;分;时;日;月;星期;年;

void DS1302_Init(void);
//时钟开关切换
void DS1302_Switch(unsigned char bStart);
//设置时间函数
void DS1302_SetTime(void);
void DS1302_SetHour24(unsigned char b24);
//---------------------------------------------
//读取时间函数
//秒;分;时;日;月;星期;年;
void DS1302_GetTime(void);
void DS1302_ReadTime(DS1302_TIME* t);

unsigned char DS1302_GetDay( void );
unsigned char DS1302_GetMonth( void );
unsigned char DS1302_GetHour24( void );
unsigned char DS1302_GetMinute( void );
unsigned char DS1302_GetSecond( void );
unsigned char DS1302_GetNum(unsigned char x);
void DS1302_Convert2Char(void);
#endif
