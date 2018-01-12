#include "HardwareProfile.h"
#include "GPS_GPRMC.h"
#include <string.h>
     
_GPS_GPRMC GPS_GPRMC;
unsigned char GPS_GPRMC_DataProc( char* data )
{
	unsigned char dotIndex[12];
	unsigned char dotCount=0;
	unsigned char i,j;
	if(data[0]!='$')
		return 0;
	if(data[1]!='G')
		return 0;
	if(data[2]!='P')
		return 0;
	if(data[3]!='R')
		return 0;
	if(data[4]!='M')
		return 0;
	if(data[5]!='C')
		return 0;
	for(i=0;;i++)
	{
		if(data[i]=='*')
			break;
		if(data[i]==',')
		{
			dotIndex[dotCount++]=i;
			if(dotCount>11)
				return 0;
		}		
	}
	if(dotCount!=11 && dotCount!=12)
		return 0;
	//$GPRMC,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>*hh
	//$GPRMC
	for(i=0;i<dotIndex[0];i++)
	{
		GPS_GPRMC.Header[i]=data[i];
	}
	//<1> UTC时间，hhmmss.sss(时分秒.毫秒)格式
	for(j=0;j<10;j++)
	{
		GPS_GPRMC.UTCTime[j]=0;
	}
	for(i=dotIndex[0]+1,j=0;i<dotIndex[1];i++,j++)
	{
		GPS_GPRMC.UTCTime[j]=data[i];
	}
	//<2> 定位状态，A=有效定位，V=无效定位
	for(i=dotIndex[1]+1,j=0;i<dotIndex[2];i++,j++)
	{
		GPS_GPRMC.AV=data[i];
	}
	//<3> 纬度ddmm.mmmm(度分)格式(前面的0也将被传输)
	for(i=dotIndex[2]+1,j=0;i<dotIndex[3];i++,j++)
	{
		GPS_GPRMC.Latitude[j]=data[i];
	}
	//<4> 纬度半球N(北半球)或S(南半球)
	for(i=dotIndex[3]+1,j=0;i<dotIndex[4];i++,j++)
	{
		GPS_GPRMC.NS=data[i];
	}
	//<5> 经度dddmm.mmmm(度分)格式(前面的0也将被传输)
	for(i=dotIndex[4]+1,j=0;i<dotIndex[5];i++,j++)
	{
		GPS_GPRMC.Longitude[j]=data[i];
	}
	//<6> 经度半球E(东经)或W(西经)
	for(i=dotIndex[5]+1,j=0;i<dotIndex[6];i++,j++)
	{
		GPS_GPRMC.EW=data[i];
	}
	//<7> 地面速率(000.0~999.9节，前面的0也将被传输)
	for(i=dotIndex[6]+1,j=0;i<dotIndex[7];i++,j++)
	{
		GPS_GPRMC.GPSSpeed[j]=data[i];
	}
	//<8> 地面航向(000.0~359.9度，以正北为参考基准，前面的0也将被传输)
	for(i=dotIndex[7]+1,j=0;i<dotIndex[8];i++,j++)
	{
		GPS_GPRMC.Course[j]=data[i];
	}
	//<9> UTC日期，ddmmyy(日月年)格式
	for(i=dotIndex[8]+1,j=0;i<dotIndex[9];i++,j++)
	{
		GPS_GPRMC.UTCDate[j]=data[i];
	}
	//<10> 磁偏角(000.0~180.0度，前面的0也将被传输)
	for(i=dotIndex[9]+1,j=0;i<dotIndex[10];i++,j++)
	{
		GPS_GPRMC.CPJ[j]=data[i];
	}
	if(dotCount==12)
	{
		//<11> 磁偏角方向，E(东)或W(西)
		for(i=dotIndex[10]+1,j=0;i<dotIndex[11];i++,j++)
		{
			GPS_GPRMC.CPJFX=data[i];
		}
		//<12> 模式指示(仅NMEA0183 3.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效)
		for(i=dotIndex[11]+1,j=0;;i++,j++)
		{
			if(data[i]=='*')
				break;
			GPS_GPRMC.UTCTime[j]=data[i];
		}
	}
	else
	{
		//<11> 磁偏角方向，E(东)或W(西)
		for(i=dotIndex[10]+1,j=0;;i++,j++)
		{
			if(data[i]=='*')
				break;
			GPS_GPRMC.CPJFX=data[i];
		}		
	}
	return 1;
}
