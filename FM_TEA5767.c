#include "HardwareProfile.h"
#include "FM_TEA5767.h"
#ifdef SimI2C
#include "SimI2C.h"
#endif
//#define FM_TEA5767_DATA_W LATC1   
//#define FM_TEA5767_WR_W  LATC2   
//#define FM_TEA5767_CS_W 	 LATC3	
//
//#define FM_TEA5767_DIN_DIR RC1    
//#define FM_TEA5767_WR_DIR  RC2    
//#define FM_TEA5767_CS_DIR 	 RC3

#ifdef SimI2C
void FM_TEA5767_Init(void)
{
	SimI2C_Init();
	FM_TEA5767_WriteData[0]=0x2b;
	FM_TEA5767_WriteData[1]=0x3d;
	FM_TEA5767_WriteData[2]=0xC1;
	FM_TEA5767_WriteData[3]=0x11;
	FM_TEA5767_WriteData[4]=0x40;
	FM_TEA5767_Write();
}
unsigned char FM_TEA5767_Read(void)
{
	unsigned char ErrTimes=FM_TEA5767_RetryCount;
	unsigned char bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();
		SimI2C_SendByte(0xc1);          //TEA5767读地址
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 表示接收数据正确，否则是出错
			continue;
		FM_TEA5767_ReadData[0]=SimI2C_ReadByte();
		SimI2C_Ack(); 
		FM_TEA5767_ReadData[1]=SimI2C_ReadByte(); 
		SimI2C_Ack(); 
		FM_TEA5767_ReadData[2]=SimI2C_ReadByte();
		SimI2C_Ack(); 
		FM_TEA5767_ReadData[3]=SimI2C_ReadByte(); 
		SimI2C_Ack(); 
		FM_TEA5767_ReadData[4]=SimI2C_ReadByte(); 
		bRight=1;
		break;
	}
	SimI2C_NoAck();
	SimI2C_Stop();
	return bRight;
}
unsigned char FM_TEA5767_Write(void)
{
	unsigned char ErrTimes=FM_TEA5767_RetryCount;
	unsigned char bRight=0;	
	while(ErrTimes--)
	{
		SimI2C_Start();
		SimI2C_SendByte(0xC0);         //TEA5767写地址
		if(SimI2C_RecAck()) //i2c_TestAck())   //ack=0 表示接收数据正确，否则是出错
			continue;
		SimI2C_SendByte(FM_TEA5767_WriteData[0]);
		SimI2C_Ack();
		SimI2C_SendByte(FM_TEA5767_WriteData[1]);
		SimI2C_Ack();
		SimI2C_SendByte(FM_TEA5767_WriteData[2]);
		SimI2C_Ack();
		SimI2C_SendByte(FM_TEA5767_WriteData[3]);
		SimI2C_Ack();
		SimI2C_SendByte(FM_TEA5767_WriteData[4]);
		bRight=1;
		break;
	}
	SimI2C_NoAck();
	SimI2C_Stop();
	__delay_us(5);
	return bRight;
}
//手动设置频率,mode=1,+0.1MHz; mode=0:-0.1MHz ,不用考虑TEA5767用于搜台的相关位:SM,SUD

void FM_TEA5767_NextChannel(void)
{
	unsigned char temp_l,temp_h;
	unsigned int Pll;

	FM_TEA5767_Read();
	Pll=MAKE_INT(FM_TEA5767_ReadData[0],FM_TEA5767_ReadData[1]);
	Pll&=0x3fff;
	if(FM_TEA5767_Flags.bAddPLL)
	{
		Pll+=FM_TEA5767_PerStep;
		if(Pll>FM_TEA5767_MaxPLL)
		{
			Pll=FM_TEA5767_MinPLL;
		}
	}
	else
	{
		Pll-=FM_TEA5767_PerStep;
		if(Pll<FM_TEA5767_MinPLL)
		{
			Pll=FM_TEA5767_MaxPLL;
		}
	}
	FM_TEA5767_WriteData[0]=HIGH_BYTE(Pll);    //PLL高位
	FM_TEA5767_WriteData[0] &=0xbf;    //sm=0
	FM_TEA5767_WriteData[0] |=0x80;    //静音 mute=1
	FM_TEA5767_WriteData[1]=LOW_BYTE(Pll);			//PLL低位
	FM_TEA5767_WriteData[2]=0xE9;		//11000001  增加搜索频率 SLL1 SLL2为10  即ADC设置为7 （中）
	FM_TEA5767_WriteData[3]=0x11;
	FM_TEA5767_WriteData[4]=0x40;
	FM_TEA5767_Write();
	FM_SearchTick=SystemTick;
	FM_TEA5767_Flags.bSearch=1;
}
#endif
