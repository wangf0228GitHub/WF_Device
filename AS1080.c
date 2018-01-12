#include "HardwareProfile.h"

#ifdef SimI2C
void AS1080_Init(void)
{
	SimI2C_Init();
	unsigned char i;
	AS1080_SendByte(0x0F, 0x80);     	// Write Enable. The WR_EN register in bit 7 needs to be set to “1” before writing to any of the RW registers.
	__delay_ms(2);
	AS1080_SendByte(0x0C, 0x1F);        //set Register 0Ch = 1Fh (default is 09h) and 0Dh = 7Fh (default is 29h).  工作在快速检测状态
	__delay_ms(2);
	AS1080_SendByte(0x0D, 0x7F);
	__delay_ms(2);

	for(i=0x10;i<0x1c;i++)
	{
		AS1080_SendByte(i, 0x19);          // adjusts the detection threshold for each individual key. 调节每个按键的灵敏度
		__delay_ms(2);
	}
	AS1080_SendByte(0x0F, 0x00);     		// Write disable. The WR_EN register in bit 7 needs to be set to “1” before writing to any of the RW registers.
	__delay_ms(20);
}

void AS1080_SendByte(unsigned char addr,unsigned char dat)
{
	while(1)
	{
		SimI2C_Start();
		SimI2C_SendByte(AS1080Addr);
		if(SimI2C_RecAck())
			continue;//无应答返回到循环,表示出错
		SimI2C_SendByte(addr);
		if(SimI2C_RecAck())
			continue;//无应答返回到循环,表示出错
		SimI2C_SendByte(dat);
		if(SimI2C_RecAck())
			continue;//无应答返回到循环,表示出错
		SimI2C_Stop();
		break;
	}
}

unsigned char AS1080_ReadByte(unsigned char addr)
{
	unsigned char dat;
	while(1)
	{
		SimI2C_Start();
		SimI2C_SendByte(AS1080Addr);
		if(SimI2C_RecAck())
			continue;//无应答返回到循环,表示出错
		SimI2C_SendByte(addr);
		if(SimI2C_RecAck())
			continue;//无应答返回到循环,表示出错
		SimI2C_Start();
		dat=AS1080Addr|0x01;
		SimI2C_SendByte(dat);
		if(SimI2C_RecAck())
			continue;//无应答返回到循环,表示出错
		dat = SimI2C_ReadByte();
		SimI2C_NoAck();
		SimI2C_Stop();
		break;
	}
	return dat;
}
#endif



