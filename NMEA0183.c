#include "HardwareProfile.h"
#include "NMEA0183.h"
#include "afx.h"
_NMEA0183_Flags NMEA0183_Flags;
unsigned char NMEA0183_RxCount;
char NMEA0183_RxBuf[NMEA0183_RxBufSize];
void NMEA0183_Init(void)
{
	NMEA0183_RxCount=0;
	NMEA0183_Flags.bRx=0;
}
void NMEA0183_RxProc(unsigned char rx)
{
	if(NMEA0183_Flags.bRx)
		return;
	NMEA0183_RxBuf[NMEA0183_RxCount++]=rx;
	if(NMEA0183_RxCount==1)
	{
 		if(NMEA0183_RxBuf[0]!='$')
 			NMEA0183_RxCount=0;
	}
	else
	{
		if(rx=='\n')
		{
			NMEA0183_Flags.bRx=1;
		}
		else if(NMEA0183_RxCount>=NMEA0183_RxBufSize)
		{
			NMEA0183_RxCount=0;
		}
	}
}
unsigned char NMEA0183_Verify(void)
{
	unsigned char i;
	unsigned char ver;
	ver=NMEA0183_RxBuf[1];
	for(i=2;;i++)
	{
		if(NMEA0183_RxBuf[i]=='*')
			break;
		if(i>=NMEA0183_RxBufSize)
			return 0;
		ver ^=NMEA0183_RxBuf[i];
	}
	i=ASCII2Byte_Capital(NMEA0183_RxBuf[NMEA0183_RxCount-4],NMEA0183_RxBuf[NMEA0183_RxCount-3]);
	if(i!=ver)
		return 0;
	return 1;
}
