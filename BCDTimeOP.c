#include "HardwareProfile.h"
#include "BCDTimeOP.h"
#include "afx.h"
const unsigned char MonthDaymax[] =
//jan feb mar apr may jun jul aug sep oct nov dec
{  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
unsigned char GetMonthDay_BCD(unsigned char Y,unsigned char M)
{
	unsigned char y,m;	
	m=BCD2CHAR(M);
	if(m>12 || m==0)
		return 0;
	if(m==2)
	{
		y=BCD2CHAR(Y);
		if((y%4) == 0)
			return 29;
		else
			return 28;
	}
	else
		return MonthDaymax[m-1];
}
void BCDDateTimeAdd1M(_SystemBCDTime* dt)
{
	unsigned char x,md;
	x=BCD2CHAR((*dt).Minute);
	x++;
	if(x<60)
		(*dt).Minute=CHAR2BCD(x);
	else//跨小时
	{
		(*dt).Minute=0;
		x=BCD2CHAR((*dt).Hour);
		x++;
		if(x<24)
			(*dt).Hour=CHAR2BCD(x);
		else//跨天
		{
			(*dt).Hour=0;			
			md=GetMonthDay_BCD((*dt).Year,(*dt).Month);
			x=BCD2CHAR((*dt).Day);
			x++;
			if(x<=md)
				(*dt).Day=CHAR2BCD(x);
			else//跨月
			{
				(*dt).Day=1;
				x=BCD2CHAR((*dt).Month);
				x++;
				if(x<=12)
					(*dt).Month=CHAR2BCD(x);
				else//跨年
				{
					(*dt).Month=1;
					x=BCD2CHAR((*dt).Year);
					x++;
					if(x>99)
						x=0;
					(*dt).Year=CHAR2BCD(x);
				}
			}
		}
	}		
}
void BCDDateTimeAddMinutes(_SystemBCDTime* dt,unsigned int MS)
{
	unsigned char addM,addH,addD;
	unsigned char x,md,y;
	addM=MS%60;
	MS=MS/60;
	addH=MS%24;
	addD=MS/24;
	/************************************************************************/
	/* 分钟                                                                 */
	/************************************************************************/
	x=BCD2CHAR((*dt).Minute);
	x=x+addM;
	if(x>=60)
	{
		x=x-60;
		addH++;
	}
	(*dt).Minute=CHAR2BCD(x);
	/************************************************************************/
	/* 小时                                                                 */
	/************************************************************************/
	x=BCD2CHAR((*dt).Hour);
	x=x+addH;
	while(x>=24)
	{
		x=x-24;
		addD++;
	}
	(*dt).Hour=CHAR2BCD(x);
	/************************************************************************/
	/* 天                                                                   */
	/************************************************************************/
	x=BCD2CHAR((*dt).Day);
	x=x+addD;
	while(1)
	{
		md=GetMonthDay_BCD((*dt).Year,(*dt).Month);;
		if(x>md)
		{
			x=x-md;
			md=BCD2CHAR((*dt).Month);
			md++;
			if(md<=12)
				(*dt).Month=CHAR2BCD(md);
			else//跨年
			{
				(*dt).Month=1;
				y=BCD2CHAR((*dt).Year);
				y++;
				if(y>99)
					y=0;
				(*dt).Year=CHAR2BCD(y);
			}
		}
		else
			break;
	}
	(*dt).Day=CHAR2BCD(x);	
}
unsigned int GetMinutesGap_BCD(_SystemBCDTime dts,_SystemBCDTime dte)
{
	unsigned int ret=0,dh;
	unsigned char x1,x2;
	dh=GetHourGap_BCD(dts,dte);
	if(dh>1092)
		return 0xffff;
	if(dte.Minute<dts.Minute)
	{
		if(dh==0)
			return 0xffff;
		x1=BCD2CHAR(dts.Minute);
		x2=BCD2CHAR(dte.Minute);
		x2+=60;
		ret=x2-x1;
		dh--;
		ret+=dh*60;
	}
	else
	{
		x1=BCD2CHAR(dts.Minute);
		x2=BCD2CHAR(dte.Minute);
		ret=x2-x1;
		ret+=dh*60;
	}
	return ret;
}
//获得整小时的时间间隔
unsigned int GetHourGap_BCD(_SystemBCDTime dts,_SystemBCDTime dte)
{
	unsigned int ret=0,ds;
	unsigned char x1,x2;
	ds=GetDayGap_BCD(dts,dte);
	if(ds>2730)
		return 0xffff;
	if(dte.Hour<dts.Hour)
	{
		if(ds==0)
			return 0xffff;
		x1=BCD2CHAR(dts.Hour);
		x2=BCD2CHAR(dte.Hour);
		x2+=24;
		ret=x2-x1;
		ds--;
		ret+=ds*24;
	}
	else
	{
		x1=BCD2CHAR(dts.Hour);
		x2=BCD2CHAR(dte.Hour);
		ret=x2-x1;
		ret+=ds*24;
	}
	return ret;
}
//获得整天的时间间隔
unsigned int GetDayGap_BCD(_SystemBCDTime dts,_SystemBCDTime dte)
{
	unsigned int ret=0;
	unsigned char i,x,x1,x2,md;
	if(dts.Year!=dte.Year)//年不相等
	{
		if(dts.Year>dts.Year)
			return 0xffff;
		x1=BCD2CHAR(dts.Year);
		x2=BCD2CHAR(dte.Year);
		x=x2-x1;
		for(i=0;i<(x-1);i++)
		{
			if(((dts.Year+1+i)%4)==0)
				ret+=366;
			else
				ret+=365;
		}
		md=GetMonthDay_BCD(dts.Year,dts.Month);
		ret+=md-BCD2CHAR(dts.Day);
		ret+=BCD2CHAR(dte.Day);
		x1=BCD2CHAR(dts.Month);
		x1++;
		x2=BCD2CHAR(dts.Year);
		while(x1<=12)
		{
			md=GetMonthDay(x2,x1);
			ret+=md;
			x1++;
		}
		x1=BCD2CHAR(dte.Month);
		x1--;
		x2=BCD2CHAR(dte.Year);
		while(x!=0)
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
			x1=BCD2CHAR(dts.Month);
			x2=BCD2CHAR(dte.Month);
			x1++;
			x=BCD2CHAR(dte.Year);
			while(x1!=x2)
			{
				ret+=GetMonthDay(x,x1);
				x1++;
			}
			md=GetMonthDay_BCD(dts.Year,dts.Month);
			ret+=md-BCD2CHAR(dts.Day);
			ret+=BCD2CHAR(dte.Day);
		}
		else//月相同
		{
			if(dts.Day!=dte.Day)//日不相同
			{
				x1=BCD2CHAR(dts.Day);
				x2=BCD2CHAR(dte.Day);
				ret=x2-x1;
			}
			else
				ret=0;
		}
	}
	return ret;
}
