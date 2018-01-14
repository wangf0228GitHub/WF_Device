#include "HardwareProfile.h"
#include "BCDTimeOP.h"
#include "afx.h"
const uint8_t MonthDaymax[] =
//jan feb mar apr may jun jul aug sep oct nov dec
{  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
uint8_t GetMonthDay(uint8_t Y,uint8_t M)
{
	if(M>12 || M==0)
		return 0;
	if(M==2)
	{		
		if((Y%4) == 0)
			return 29;
		else
			return 28;
	}
	else
		return MonthDaymax[M-1];
}
void DateTimeAdd1M(_SystemCharTime* dt)
{
	uint8_t x,md;
	x=(*dt).Minute;
	x++;
	if(x<60)
		(*dt).Minute=x;
	else//跨小时
	{
		(*dt).Minute=0;
		x=(*dt).Hour;
		x++;
		if(x<24)
			(*dt).Hour=x;
		else//跨天
		{
			(*dt).Hour=0;			
			md=GetMonthDay((*dt).Year,(*dt).Month);
			x=(*dt).Day;
			x++;
			if(x<=md)
				(*dt).Day=x;
			else//跨月
			{
				(*dt).Day=1;
				x=(*dt).Month;
				x++;
				if(x<=12)
					(*dt).Month=x;
				else//跨年
				{
					(*dt).Month=1;
					x=(*dt).Year;
					x++;
					if(x>99)
						x=0;
					(*dt).Year=x;
				}
			}
		}
	}		
}
void DateTimeAddMinutes(_SystemCharTime* dt,uint16_t MS)
{
	uint8_t addM,addH,addD;
	uint8_t x,md,y;
	addM=MS%60;
	MS=MS/60;
	addH=MS%24;
	addD=MS/24;
	/************************************************************************/
	/* 分钟                                                                 */
	/************************************************************************/
	x=(*dt).Minute;
	x=x+addM;
	if(x>=60)
	{
		x=x-60;
		addH++;
	}
	(*dt).Minute=x;
	/************************************************************************/
	/* 小时                                                                 */
	/************************************************************************/
	x=(*dt).Hour;
	x=x+addH;
	while(x>=24)
	{
		x=x-24;
		addD++;
	}
	(*dt).Hour=x;
	/************************************************************************/
	/* 天                                                                   */
	/************************************************************************/
	x=(*dt).Day;
	x=x+addD;
	while(1)
	{
		md=GetMonthDay((*dt).Year,(*dt).Month);;
		if(x>md)
		{
			x=x-md;
			md=(*dt).Month;
			md++;
			if(md<=12)
				(*dt).Month=md;
			else//跨年
			{
				(*dt).Month=1;
				y=(*dt).Year;
				y++;
				if(y>99)
					y=0;
				(*dt).Year=y;
			}
		}
		else
			break;
	}
	(*dt).Day=CHAR2BCD(x);	
}
uint16_t GetMinutesGap(_SystemCharTime dts,_SystemCharTime dte)
{
	uint16_t ret=0,dh;
	uint8_t x1,x2;
	dh=GetHourGap(dts,dte);
	if(dh>1092)
		return 0xffff;
	if(dte.Minute<dts.Minute)
	{
		if(dh==0)
			return 0xffff;
		x1=dts.Minute;
		x2=dte.Minute;
		x2+=60;
		ret=x2-x1;
		dh--;
		ret+=dh*60;
	}
	else
	{
		x1=dts.Minute;
		x2=dte.Minute;
		ret=x2-x1;
		ret+=dh*60;
	}
	return ret;
}
//获得整小时的时间间隔
uint16_t GetHourGap(_SystemCharTime dts,_SystemCharTime dte)
{
	uint16_t ret=0,ds;
	uint8_t x1,x2;
	ds=GetDayGap(dts,dte);
	if(ds>2730)
		return 0xffff;
	if(dte.Hour<dts.Hour)
	{
		if(ds==0)
			return 0xffff;
		x1=dts.Hour;
		x2=dte.Hour;
		x2+=24;
		ret=x2-x1;
		ds--;
		ret+=ds*24;
	}
	else
	{
		x1=dts.Hour;
		x2=dte.Hour;
		ret=x2-x1;
		ret+=ds*24;
	}
	return ret;
}
//获得整天的时间间隔
uint16_t GetDayGap(_SystemCharTime dts,_SystemCharTime dte)
{
	uint16_t ret=0;
	uint8_t i,x,x1,x2,md;
	if(dts.Year!=dte.Year)//年不相等
	{
		if(dts.Year>dts.Year)
			return 0xffff;
		x1=dts.Year;
		x2=dte.Year;
		x=x2-x1;
		for(i=0;i<(x-1);i++)
		{
			if(((dts.Year+1+i)%4)==0)
				ret+=366;
			else
				ret+=365;
		}
		md=GetMonthDay(dts.Year,dts.Month);
		ret+=md-dts.Day;
		ret+=dte.Day;
		x1=dts.Month;
		x1++;
		x2=dts.Year;
		while(x1<=12)
		{
			md=GetMonthDay(x2,x1);
			ret+=md;
			x1++;
		}
		x1=dte.Month;
		x1--;
		x2=dte.Year;
		while(x1!=0)
		{
			md=GetMonthDay(x2,x1);
			ret+=md;
			x1--;
		}		
	}
	else//年相同
	{
		if(dts.Month!=dte.Month)//月不相同
		{
			if(dts.Month>dte.Month)
				return 0xffff;
			x1=dts.Month;
			x2=dte.Month;
			x1++;
			x=dte.Year;
			while(x1!=x2)
			{
				ret+=GetMonthDay(x,x1);
				x1++;
			}
			md=GetMonthDay(dts.Year,dts.Month);
			ret+=md-dts.Day;
			ret+=dte.Day;
		}
		else//月相同
		{
			if(dts.Day!=dte.Day)//日不相同
			{
				ret=dte.Day-dts.Day;
			}
			else
				ret=0;
		}
	}
	return ret;
}
