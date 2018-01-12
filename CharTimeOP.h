#ifndef TimeOP_h__
#define TimeOP_h__

typedef union
{	
	unsigned char Times[8];
	struct
	{
		unsigned char Year;
		unsigned char Month;
		unsigned char Day;
		unsigned char Hour;
		unsigned char Minute;
		unsigned char Second;
		unsigned char Week;
	};	
}_SystemCharTime;
unsigned char GetMonthDay(unsigned char Y,unsigned char M);

void DateTimeAdd1M(_SystemCharTime* dt);

void DateTimeAddMinutes(_SystemCharTime* dt,unsigned int MS);

unsigned int GetMinutesGap(_SystemCharTime dts,_SystemCharTime dte);

//获得整小时的时间间隔
unsigned int GetHourGap(_SystemCharTime dts,_SystemCharTime dte);

//获得整天的时间间隔
unsigned int GetDayGap(_SystemCharTime dts,_SystemCharTime dte);

#endif // TimeOP_h__
