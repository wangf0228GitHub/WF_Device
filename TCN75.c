#include "HardwareProfile.h"
#include "TCN75.h"
#ifdef SimI2C
#include "SimI2C.h"
#endif
//#define TCN75_DATA_W LATC1   
//#define TCN75_WR_W  LATC2   
//#define TCN75_CS_W 	 LATC3	
//
//#define TCN75_DIN_DIR RC1    
//#define TCN75_WR_DIR  RC2    
//#define TCN75_CS_DIR 	 RC3

#ifdef SimI2C
void TCN75_Init(void)
{
	SimI2C_Init();
}
unsigned char TCN75_ReadReg(unsigned char RegPoint)
{
	unsigned char ErrTimes=TCN75_RetryCount;
	unsigned char bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr&0xfe);          //写地址
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;
		SimI2C_SendByte(RegPoint);
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr|0x01);          //读地址
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;
		TCN75_RegReadResualt.u8H=SimI2C_ReadByte();
		SimI2C_Ack();
		TCN75_RegReadResualt.u8L=SimI2C_ReadByte();
		SimI2C_NoAck();
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
unsigned char TCN75_SetConfig(void)
{
	unsigned char ErrTimes=TCN75_RetryCount;
	unsigned char bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr&0xfe);          //写地址
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;		
		SimI2C_SendByte(0x01);
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;
		SimI2C_SendByte(TCN75_Config.AllFlag);          //读地址
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;		
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
unsigned char TCN75_ReadConfig(void)
{
	unsigned char ErrTimes=TCN75_RetryCount;
	unsigned char bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr&0xfe);          //写地址
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;		
		SimI2C_SendByte(0x01);
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr|0x01);          //读地址		
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;	
		TCN75_Config.AllFlag=SimI2C_ReadByte();
		SimI2C_NoAck();
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
#endif
