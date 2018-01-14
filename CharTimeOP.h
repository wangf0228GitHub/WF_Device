#ifndef TimeOP_h__
#define TimeOP_h__

typedef union
{	
	uint8_t Times[8];
	struct
	{
		uint8_t Year;
		uint8_t Month;
		uint8_t Day;
		uint8_t Hour;
		uint8_t Minute;
		uint8_t Second;
		uint8_t Week;
	};	
}_SystemCharTime;
uint8_t GetMonthDay(uint8_t Y,uint8_t M);

void DateTimeAdd1M(_SystemCharTime* dt);

void DateTimeAddMinutes(_SystemCharTime* dt,uint16_t MS);

uint16_t GetMinutesGap(_SystemCharTime dts,_SystemCharTime dte);

//获得整小时的时间间隔
uint16_t GetHourGap(_SystemCharTime dts,_SystemCharTime dte);

//获得整天的时间间隔
uint16_t GetDayGap(_SystemCharTime dts,_SystemCharTime dte);

#endif // TimeOP_h__
