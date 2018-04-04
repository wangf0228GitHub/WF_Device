#include "main.h"
#include "SimI2C.h"
#include "TypeDefine.h"
#include "SHT25.h"
uint16_t SHT25_T;//放大100倍后的温度
uint16_t SHT25_RH;//放大100倍后的湿度
uint8_t SHT25_bErrT;
uint8_t SHT25_bErrRH;
#ifdef SHT25_HOLDREAD
uint16_t SHT25_HoldRead(uint8_t cmd)
{
	uint SHT25_Data;
	uint8_t sum;
#ifdef SHT25_SimI2C
	SimI2C_Start();
	SimI2C_SendByte(SHT25_ADDR_W);//写
	if(SimI2C_RecAck())
		return 0;	
	SimI2C_SendByte(cmd);//写读写地址高字节
	if(SimI2C_RecAck())
		return 0;	
	SimI2C_Start();
	SimI2C_SendByte(SHT25_ADDR_R);//读
	if(SimI2C_RecAck())
		return 0;
	__delay_20ms(5);
	SHT25_Data.u8s[1]=SimI2C_ReadByte();
	SimI2C_Ack();
	SHT25_Data.u8s[0]=SimI2C_ReadByte();
	SimI2C_Ack();	
	sum=SimI2C_ReadByte();
	SimI2C_NoAck();
	SimI2C_Stop();
#endif	
	return SHT25_Data.u16;
}
#else
uint16_t SHT25_NoHoldRead(uint8_t cmd)
{
	uint SHT25_Data;
	//uint8_t sum;
#ifdef SHT25_SimI2C
	SimI2C_Start();
	SimI2C_SendByte(SHT25_ADDR_W);//写
	if(SimI2C_RecAck())
		return 0;	
	SimI2C_SendByte(cmd);//写读写地址高字节
	if(SimI2C_RecAck())
		return 0;	
	while(true)
	{
		SimI2C_Start();
		SimI2C_SendByte(SHT25_ADDR_R);//读
		if(SimI2C_RecAck())
			continue;
		break;
	}
	SHT25_Data.u8s[1]=SimI2C_ReadByte();
	SimI2C_Ack();
	SHT25_Data.u8s[0]=SimI2C_ReadByte();
	//SimI2C_Ack();	
	//sum=SimI2C_ReadByte();
	SimI2C_NoAck();
	SimI2C_Stop();
#endif	
	//if((uint8_t)(SHT25_Data.u8s[1],SHT25_Data.u8s[0])==sum)
		return SHT25_Data.u16;
	//else
	//	return FALSE;
}
#endif
uint8_t SHT25_GetUserReg(void)
{
	uint8_t x;
#ifdef SHT25_SimI2C
	SimI2C_Start();
	SimI2C_SendByte(SHT25_ADDR_W);//写
	if(SimI2C_RecAck())
		return 0;	
	SimI2C_SendByte(0xe7);//写读写地址高字节
	if(SimI2C_RecAck())
		return 0;	
	SimI2C_Start();
	SimI2C_SendByte(SHT25_ADDR_R);//读
	if(SimI2C_RecAck())
		return 0;	
	x=SimI2C_ReadByte();	
	SimI2C_NoAck();
	SimI2C_Stop();
#endif	
	if(x==0)
		x=1;
	return x;
}

void SHT25_GetT(void)
{
	uint16_t St;
	uint32_t t;
	SHT25_bErrT=0;
#ifdef SHT25_HOLDREAD
	St=SHT25_HoldRead(SHT25_HoldT);
#else
	St=SHT25_NoHoldRead(SHT25_NoHoldT);
#endif
	if(St==0)
	{
		SHT25_T=0;
		SHT25_bErrT=1;
		return;
	}	
	St=St&0xfffc;
	t=(uint32_t)St*17572;
	t=t>>16;
	t=t-4685;
	SHT25_T=(uint16_t)t;
}
void SHT25_GetRH(void)
{
	uint16_t Srh;
	uint32_t rh;
	SHT25_bErrRH=0;
#ifdef SHT25_HOLDREAD
	Srh=SHT25_HoldRead(SHT25_HoldRH);
#else
	Srh=SHT25_NoHoldRead(SHT25_NoHoldRH);
#endif
	if(Srh==0)
	{
		SHT25_RH=0;
		SHT25_bErrRH=0;
		return;
	}
	Srh=Srh&0xfffc;
	rh=(uint32_t)Srh*12500;
	rh=rh>>16;
	rh=rh-600;
	SHT25_RH=(uint16_t)rh;
}
uint8_t SHT25_Reset(void)
{
#ifdef SHT25_SimI2C
	SimI2C_Start();
	SimI2C_SendByte(SHT25_ADDR_W);//写
	if(SimI2C_RecAck())
		return 0;	
	SimI2C_SendByte(0xfe);//写读写地址高字节
	if(SimI2C_RecAck())
		return 0;	
	SimI2C_Stop();
#endif
	return 1;
}

