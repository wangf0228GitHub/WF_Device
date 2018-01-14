#include "HardwareProfile.h"

ulong TM1638_KeyValue;
void TM1638_Init(void)
{
	TM1638_STB_IO=0; 
	TM1638_CLK_IO=0;
	TM1638_DIO_IO=0;

	TM1638_STB=1;
	TM1638_CLK=0;
	TM1638_DIO=0;
}
void TM1638_WriteByte(uint8_t d)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		TM1638_CLK=0;
		if(d&0x01==0x01)
			TM1638_DIO=1;
		else
			TM1638_DIO=0;
		d>>=1;
		__delay_us(1);
		TM1638_CLK=1;
	}
}
void TM1638_WriteCommand(uint8_t c)
{
	TM1638_STB=0;
	__delay_us(1);
	TM1638_WriteByte(c);
	TM1638_STB=1;
}
void TM1638_WriteData(uint8_t addr,uint8_t d)
{
	TM1638_WriteCommand(0x44);//固定地址写显示寄存器
	TM1638_STB=0;
	__delay_us(1);
	TM1638_WriteByte(0xc0|addr);
	TM1638_WriteByte(d);
	TM1638_STB=1;
}
void TM1638_WriteDatas(uint8_t addr,uint8_t* d,uint8_t count)
{
	uint8_t i;
	TM1638_WriteCommand(0x40);//增加地址写显示寄存器
	TM1638_STB=0;
	__delay_us(1);
	TM1638_WriteByte(0xc0|addr);
	for(i=0;i<count;i++)
		TM1638_WriteByte(d[i]);
	TM1638_STB=1;
}
uint8_t TM1638_ReadByte(void)					//读数据函数
{
	uint8_t i;
	uint8_t temp=0;
	TM1638_DIO=1;	//设置为输入
	for(i=0;i<8;i++)
	{
		temp>>=1;
		TM1638_CLK=0;
		if(TM1638_DIO)
			temp|=0x80;
		__delay_us(1);
		TM1638_CLK=1;
	}
	return temp;
}
void TM1638_ReadKey(void)
{
	TM1638_STB=0;
	__delay_us(1);
	TM1638_WriteByte(0x42);
	TM1638_KeyValue.u8s[0]=TM1638_ReadByte();
	TM1638_KeyValue.u8s[1]=TM1638_ReadByte();
	TM1638_KeyValue.u8s[2]=TM1638_ReadByte();
	TM1638_KeyValue.u8s[3]=TM1638_ReadByte();	
	TM1638_STB=1;					//4个字节数据合成一个字节	
}