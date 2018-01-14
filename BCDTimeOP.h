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
}_SystemBCDTime;
uint8_t GetMonthDay_BCD(uint8_t Y,uint8_t M);
uint8_t GetMonthDay(uint8_t Y,uint8_t M);

void BCDDateTimeAdd1M(_SystemBCDTime* dt);

void BCDDateTimeAddMinutes(_SystemBCDTime* dt,uint16_t MS);

uint16_t GetMinutesGap_BCD(_SystemBCDTime dts,_SystemBCDTime dte);

//获得整小时的时间间隔
uint16_t GetHourGap_BCD(_SystemBCDTime dts,_SystemBCDTime dte);

//获得整天的时间间隔
uint16_t GetDayGap_BCD(_SystemBCDTime dts,_SystemBCDTime dte);

#endif // TimeOP_h__
