#include "ADS8689.h"
#include "ADS8689_Conf.h"
#include "wfDefine.h"


// uint32_t ADS8689_ReadResult(void)
// {
// 	uint32_t ret;
// 	while(1)
// 	{
// 		if(ADS8689_RVS_Read()==1)//rvs拉高后继续
// 			break;
// 	}
// 	ADS8689_CS_Low();
// 	while(1)
// 	{
// 		if(ADS8689_RVS_Read()==0)//rvs拉低后继续
// 			break;
// 	}	
// 	ret.u16H.u8H=ADS8689_SPIProc(0);
// 	ret.u16H.u8L=ADS8689_SPIProc(0);
// 	ret.u16L.u8H=ADS8689_SPIProc(0);
// 	ret.u16L.u8L=ADS8689_SPIProc(0);
// 	ADS8689_CS_High();
// 	return ret;
// }


void  ADS8689_Setting(uint8_t reg,uint16_t data)
{
	while(1)
	{
		if(ADS8689_RVS_Read()==1)//rvs拉高后继续
			break;
	}
	ADS8689_CS_Low();
	while(1)
	{
		if(ADS8689_RVS_Read()==0)//rvs拉低后继续
			break;
	}
// 	if((reg&0x80)==0)
// 	{
 		ADS8689_SPIProc(0xd0);//11010 00 0
// 	}
// 	else
// 	{
// 		ADS8689_SPIProc(0xd1);
// 	}
	//reg=reg<<1;
	ADS8689_SPIProc(reg);
	ADS8689_SPIProc(HIGH_BYTE(data));
	ADS8689_SPIProc(LOW_BYTE(data));
	ADS8689_CS_High();
}

u16_wf ADS8689_ReadReg(uint8_t reg)
{
	u16_wf ret;
	while(1)
	{
		if(ADS8689_RVS_Read()==1)//rvs拉高后继续
			break;
	}
	ADS8689_CS_Low();
	while(1)
	{
		if(ADS8689_RVS_Read()==0)//rvs拉低后继续
			break;
	}
	if((reg&0x80)==0)
	{
		ADS8689_SPIProc(0xc8);//11001 00 0
	}
	else
	{
		ADS8689_SPIProc(0xc9);
	}
	reg=reg<<1;
	ADS8689_SPIProc(reg);
	ADS8689_SPIProc(0);
	ADS8689_SPIProc(0);
	ADS8689_CS_High();
	while(1)
	{
		if(ADS8689_RVS_Read()==1)//rvs拉高后继续
			break;
	}
	ADS8689_CS_Low();
	while(1)
	{
		if(ADS8689_RVS_Read()==0)//rvs拉低后继续
			break;
	}
	ret.u8H=ADS8689_SPIProc(0);
	ret.u8L=ADS8689_SPIProc(0);
	ADS8689_SPIProc(0);
	ADS8689_SPIProc(0);
	ADS8689_CS_High();
	return ret;
}