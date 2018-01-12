#include "HardwareProfile.h"
#include "DS12C887_Intel.h"

DS12C887_TIME DS12C887_Time;

void DS12C887_Wait(void);
void DS12C887_Init(void)
{
#ifdef DS12C887_RST_DIR
	DS12C887_RST_DIR=0;
	DS12C887_RST_W=0;
	__delay_20ms(20);
	DS12C887_RST_W=1;
#endif	
#ifdef DS12C887_PORT_DIR
	DS12C887_PORT_DIR=0x00;//Êä³ö
#else
	DS12C887_SetPortWrite();
#endif	
	DS12C887_RD_DIR=0;
	DS12C887_WR_DIR=0;
	DS12C887_ALE_DIR=0;
	DS12C887_CS_DIR=0;
	DS12C887_CS_W=1;
	DS12C887_WR_W=1;
	DS12C887_RD_W=1;
	DS12C887_ALE_W=1;
	DS12C887_WriteByte(DS12C887_REGA,0b00100000); //Æô¶¯
	if(DS12C887_DM==1)
		DS12C887_WriteByte(DS12C887_REGB,0b00000110); //24xiao shi zhi,binary mode 
	else
		DS12C887_WriteByte(DS12C887_REGB,0b00000010); //24xiao shi zhi,BCD
	DS12C887_WriteByte(DS12C887_REGC,0b00000000);
}

void DS12C887_GetTime(void)
{
	DS12C887_Wait();
	DS12C887_Time.Second=DS12C887_ReadByte(DS12C887_SECOND)&0x7f;
	DS12C887_Time.Minute=DS12C887_ReadByte(DS12C887_MINUTE)&0x7f;
	DS12C887_Time.Hour=DS12C887_ReadByte(DS12C887_HOUR)&0x7f;
	DS12C887_Time.Day=DS12C887_ReadByte(DS12C887_DayOfMonth)&0x3f;
	DS12C887_Time.Month=DS12C887_ReadByte(DS12C887_MONTH)&0x1f;
	DS12C887_Time.Year=DS12C887_ReadByte(DS12C887_YEAR);
#ifdef DS12C887_OPWeek
	DS12C887_Time.Week=DS12C887_ReadByte(DS12C887_DayOfWeek)&0x07;
#endif	
}
void DS12C887_SetTime(void)
{
	DS12C887_WriteByte(DS12C887_SECOND,DS12C887_Time.Second);
	DS12C887_WriteByte(DS12C887_MINUTE,DS12C887_Time.Minute);
	DS12C887_WriteByte(DS12C887_HOUR,DS12C887_Time.Hour);
	DS12C887_WriteByte(DS12C887_DayOfMonth,DS12C887_Time.Day);
	DS12C887_WriteByte(DS12C887_MONTH,DS12C887_Time.Month);
	DS12C887_WriteByte(DS12C887_YEAR,DS12C887_Time.Year);
#ifdef DS12C887_OPWeek
	DS12C887_WriteByte(DS12C887_DayOfWeek,DS12C887_Time.Week);
#endif	
}
void DS12C887_SetTimeEx(DS12C887_TIME exTime)
{
	DS12C887_WriteByte(DS12C887_SECOND,exTime.Second);
	DS12C887_WriteByte(DS12C887_MINUTE,exTime.Minute);
	DS12C887_WriteByte(DS12C887_HOUR,exTime.Hour);
	DS12C887_WriteByte(DS12C887_DayOfMonth,exTime.Day);
	DS12C887_WriteByte(DS12C887_MONTH,exTime.Month);
	DS12C887_WriteByte(DS12C887_YEAR,exTime.Year);
#ifdef DS12C887_OPWeek
	DS12C887_WriteByte(DS12C887_DayOfWeek,exTime.Week);
#endif	
}
void DS12C887_GetAlarm(void)
{
	DS12C887_Time.SecondAlarm=DS12C887_ReadByte(DS12C887_SECOND_ALARM);
	DS12C887_Time.MinuteAlarm=DS12C887_ReadByte(DS12C887_MINUTE_ALARM);
	DS12C887_Time.HourAlarm=DS12C887_ReadByte(DS12C887_HOUR_ALARM);	
}
void DS12C887_SetAlarm(void)
{
	DS12C887_WriteByte(DS12C887_SECOND_ALARM,DS12C887_Time.SecondAlarm);
	DS12C887_WriteByte(DS12C887_MINUTE_ALARM,DS12C887_Time.MinuteAlarm);
	DS12C887_WriteByte(DS12C887_HOUR_ALARM,DS12C887_Time.HourAlarm);	
}
void DS12C887_SetAlarmEx(DS12C887_TIME exTime)
{
	DS12C887_WriteByte(DS12C887_SECOND_ALARM,exTime.SecondAlarm);
	DS12C887_WriteByte(DS12C887_MINUTE_ALARM,exTime.MinuteAlarm);
	DS12C887_WriteByte(DS12C887_HOUR_ALARM,exTime.HourAlarm);	
}
void DS12C887_WriteByte(unsigned char reg,unsigned char c)
{
	DS12C887_CS_W=0;
	__delay_us(1);
#ifdef DS12C887_PORT_DIR
	DS12C887_PORT_W=reg;
#else
	DS12C887_SetPortData(reg);
#endif	
	__delay_us(1);
	DS12C887_ALE_W=0;
	__delay_us(1);
#ifdef DS12C887_PORT_DIR
	DS12C887_PORT_W=c;
#else
	DS12C887_SetPortData(c);
#endif
	__delay_us(1);
	DS12C887_WR_W=0;
	__delay_us(1);
	DS12C887_WR_W=1;
	DS12C887_ALE_W=1;
	DS12C887_CS_W=1;
}
unsigned char DS12C887_ReadByte(unsigned char reg)
{	
	unsigned char x;
	DS12C887_CS_W=0;
	__delay_us(1);
#ifdef DS12C887_PORT_DIR
	DS12C887_PORT_W=reg;
#else
	DS12C887_SetPortData(reg);
#endif
	__delay_us(1);
	DS12C887_ALE_W=0;
	__delay_us(1);
#ifdef DS12C887_PORT_DIR
	DS12C887_PORT_DIR=0xff;	
#else
	DS12C887_SetPortRead();
#endif
	
	DS12C887_RD_W=0;
	__delay_us(1);
#ifdef DS12C887_PORT_DIR
	x=DS12C887_PORT_R;
#else
	x=DS12C887_GetPortData();
#endif	
	DS12C887_RD_W=1;
	DS12C887_ALE_W=1;
	DS12C887_CS_W=1;
#ifdef DS12C887_PORT_DIR
	DS12C887_PORT_DIR=0x00;
#else
	DS12C887_SetPortWrite();
#endif		
	return x;
}
void DS12C887_Wait( void )
{
	unsigned char x;
	while(1)
	{
		x=DS12C887_ReadByte(DS12C887_REGA);
		x=x&0x80;
		if(x==0x00)
			return;
	}
}
