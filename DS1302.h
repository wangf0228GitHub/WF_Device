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
	uint8_t Times[7];
	struct
	{
		uint8_t Second;
		uint8_t Minute;
		uint8_t Hour;
		uint8_t Day;
		uint8_t Month;
		uint8_t Week;
		uint8_t Year;
		//uint8_t WP;
	};	
}DS1302_TIME;


extern DS1302_TIME DS1302_Time;//秒;分;时;日;月;星期;年;

void DS1302_Init(void);
//时钟开关切换
void DS1302_Switch(uint8_t bStart);
//设置时间函数
void DS1302_SetTime(void);
void DS1302_SetHour24(uint8_t b24);
//---------------------------------------------
//读取时间函数
//秒;分;时;日;月;星期;年;
void DS1302_GetTime(void);
void DS1302_ReadTime(DS1302_TIME* t);

uint8_t DS1302_GetDay( void );
uint8_t DS1302_GetMonth( void );
uint8_t DS1302_GetHour24( void );
uint8_t DS1302_GetMinute( void );
uint8_t DS1302_GetSecond( void );
uint8_t DS1302_GetNum(uint8_t x);
void DS1302_Convert2Char(void);
#endif
