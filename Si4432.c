#include "HardwareProfile.h"
#include "Si4432.h"

//#define Si4432_NSEL_DIR	TRISA1
//#define Si4432_SCL_DIR	TRISA1
//#define Si4432_SDI_DIR	TRISA2
//#define Si4432_SDO_DIR	TRISA0
//
//#define Si4432_NSEL	RA1
//#define Si4432_SCL	RA1
//#define Si4432_SDI	RA0 //芯片的输入
//#define Si4432_SDO	RA2	//芯片的输出
void Si4432_Init(void)
{	
	Si4432_NSEL_DIR=0;
	Si4432_SCL_DIR=0;
	Si4432_SDO_DIR=1;
	Si4432_SDI_DIR=0;
	Si4432_NSEL_W=1;
	Si4432_SCL_W=1;	//拉低时钟信号
}

void Si4432_WriteRegister(uint8_t reg,uint8_t value)
{
	uint8_t i;
	Si4432_NSEL_W=0;
	Si4432_SCL_W=0;	//拉高时钟信号
	reg=reg|0x80;//写
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if((reg&0x80)==0x80)	//判断待发送的数据位是0或1
		{
			Si4432_SDI_W=1;	//待发送数据位是1
		}
		NOP();
		Si4432_SCL_W=1;
		reg=reg<<1;	//判断待发送的数据位是0或1
		Si4432_SCL_W=0;	//拉高时钟信号
	}
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if((value&0x80)==0x80)	//判断待发送的数据位是0或1
		{
			Si4432_SDI_W=1;	//待发送数据位是1
		}
		NOP();
		Si4432_SCL_W=1;
		value=value<<1;	//判断待发送的数据位是0或1
		Si4432_SCL_W=0;	//拉高时钟信号
	}
	Si4432_NSEL_W=1;
}
uint8_t Si4432_ReadRegister(uint8_t reg)
{
	uint8_t i,value;
	Si4432_NSEL_W=0;
	Si4432_SCL_W=0;	//拉高时钟信号
	value=reg&0x7f;//写
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if((value&0x80)==0x80)	//判断待发送的数据位是0或1
		{
			Si4432_SDI_W=1;	//待发送数据位是1
		}
		NOP();
		Si4432_SCL_W=1;
		value=value<<1;	//判断待发送的数据位是0或1
		Si4432_SCL_W=0;	//拉高时钟信号
	}	
#ifdef SI4463
	while(1)
	{
		value=0;
		for(i=0;i<8;i++)
		{

			value=value<<1;
			if(Si4432_SDO_R==1)
				value=value|0x01;
			Si4432_SCL_W=1;
			NOP();		
			Si4432_SCL_W=0;	//拉高时钟信号
		}
		Si4432_NSEL_W=1;
		if(value==0xff)
			break;
	}
	value=0;
	for(i=0;i<8;i++)
	{

		value=value<<1;
		if(Si4432_SDO_R==1)
			value=value|0x01;
		Si4432_SCL_W=1;
		NOP();		
		Si4432_SCL_W=0;	//拉高时钟信号
	}
	Si4432_NSEL_W=1;
#else
	value=0;
	for(i=0;i<8;i++)
	{

		value=value<<1;
		if(Si4432_SDO_R==1)
			value=value|0x01;
		Si4432_SCL_W=1;
		NOP();		
		Si4432_SCL_W=0;	//拉高时钟信号
	}
	Si4432_NSEL_W=1;
#endif
	
	return value;
}
void Si4432_WriteRegisters(uint8_t reg,uint8_t Count,const uint8_t *p)
{
	uint8_t i,j,v;
	Si4432_NSEL_W=0;
	Si4432_SCL_W=0;	//拉高时钟信号
	reg=reg|0x80;//写
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if(reg&0x80==0x80)	//判断待发送的数据位是0或1
		{
			Si4432_SDI_W=1;	//待发送数据位是1
		}
		NOP();
		Si4432_SCL_W=1;
		reg=reg<<1;	//判断待发送的数据位是0或1
		Si4432_SCL_W=0;	//拉高时钟信号
	}
	for(j=0;j<Count;j++)
	{
		v=p[j];
		for(i=0;i<8;i++)
		{
			Si4432_SDI_W=0;
			if(v&0x80==0x80)	//判断待发送的数据位是0或1
			{
				Si4432_SDI_W=1;	//待发送数据位是1
			}
			NOP();
			Si4432_SCL_W=1;
			v=v<<1;	//判断待发送的数据位是0或1
			Si4432_SCL_W=0;	//拉高时钟信号
		}
	}
}
void Si4432_ReadRegisters(uint8_t reg,uint8_t Count,uint8_t *p)
{
	uint8_t i,j,value;
	Si4432_NSEL_W=0;
	Si4432_SCL_W=0;	//拉高时钟信号
	reg=reg&0x7f;//写
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if(reg&0x80==0x80)	//判断待发送的数据位是0或1
		{
			Si4432_SDI_W=1;	//待发送数据位是1
		}
		NOP();
		Si4432_SCL_W=1;
		reg=reg<<1;	//判断待发送的数据位是0或1
		Si4432_SCL_W=0;	//拉高时钟信号
	}
	for(j=0;j<Count;j++)
	{
		value=0;
		for(i=0;i<8;i++)
		{
			Si4432_SCL_W=1;
			value=value<<1;
			if(Si4432_SDO_R==1)
				value=value|0x01;	
			Si4432_SCL_W=0;	//拉高时钟信号
		}
		p[j]=value;
	}
}
