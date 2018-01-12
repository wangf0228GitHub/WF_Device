#include "HardwareProfile.h"
#ifdef SimI2C
#include "SimI2C.h"
#endif
//#define SS5060_DATA_W LATC1   
//#define SS5060_WR_W  LATC2   
//#define SS5060_CS_W 	 LATC3	
//
//#define SS5060_DIN_DIR RC1    
//#define SS5060_WR_DIR  RC2    
//#define SS5060_CS_DIR 	 RC3

#ifdef SimI2C
void SS5060_Init(void)
{
	SimI2C_Init();
}
unsigned char SS5060_GetResult(unsigned char x)
{
	if(SS5060_Setting(x)==0)
		return 0;
	__delay_20ms(10);
	if(SS5060_ReadReg()==0)
		return 0;
	return 1;
}
unsigned char SS5060_ReadReg(void)
{
	unsigned char ErrTimes=SS5060_RetryCount;
	unsigned char bRight=0;
	while(ErrTimes--)
	{		
		SimI2C_Start();
		SimI2C_SendByte(SS5060_Addr|0x01);          //读地址
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;
		SS5060_RegReadResualt.u8H=SimI2C_ReadByte();
		SimI2C_Ack();
		SS5060_RegReadResualt.u8L=SimI2C_ReadByte();
		SimI2C_NoAck();
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
unsigned char SS5060_Setting(unsigned char x)
{
	unsigned char ErrTimes=SS5060_RetryCount;
	unsigned char bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();
		SimI2C_SendByte(SS5060_Addr&0xfe);          //写地址
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;
		SimI2C_SendByte(x);
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
#endif
