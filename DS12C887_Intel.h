
#ifndef __DS12C887_Intel_H_
#define __DS12C887_Intel_H_

#ifndef DS12C887_DM
#define DS12C887_DM 1	//¶þ½øÖÆ
#endif

#define DS12C887_SECOND 0x00
#define DS12C887_SECOND_ALARM 0x01
#define DS12C887_MINUTE 0x02 
#define DS12C887_MINUTE_ALARM 0x03
#define DS12C887_HOUR 0x04
#define DS12C887_HOUR_ALARM 0x05
#define DS12C887_DayOfWeek 0x06
#define DS12C887_DayOfMonth 0x07
#define DS12C887_MONTH 0x08
#define DS12C887_YEAR 0x09
#define DS12C887_REGA 0x0a
#define DS12C887_REGB 0x0b
#define DS12C887_REGC 0x0c
#define DS12C887_REGD 0x0d

typedef union
{	
	uint8_t Times[10];
	struct
	{
		uint8_t Second;
		uint8_t SecondAlarm;
		uint8_t Minute;
		uint8_t MinuteAlarm;
		uint8_t Hour;
		uint8_t HourAlarm;
		uint8_t Week;
		uint8_t Day;
		uint8_t Month;
		uint8_t Year;
	};	
}DS12C887_TIME;
extern DS12C887_TIME DS12C887_Time;
void DS12C887_Init(void); 
uint8_t DS12C887_ReadByte(uint8_t reg);
void DS12C887_WriteByte(uint8_t reg,uint8_t c);
void DS12C887_GetTime(void);
void DS12C887_SetTime(void);
void DS12C887_GetAlarm(void);
void DS12C887_SetAlarm(void);
void DS12C887_SetTimeEx(DS12C887_TIME exTime);
#endif

/////////////   SUNROUTINE DECLARE   /////////////
       // 12C887 data write routine

/////////////////// SUBROUTINE ///////////////////

