#include "HardwareProfile.h"

void CH45x_Init(void)
{
	CH45x_DCLK_IO=0;
	CH45x_DIN_IO=0;
	CH45x_LOAD_IO=0;
	CH45x_DOUT_IO=1;
	CH45x_RST_IO=0;

	__delay_us(10);		
	CH45x_RST_W=1;
	__delay_us(10);
	CH45x_RST_W=0;
	__delay_us(20);
	CH45x_RST_W=1;
	__delay_us(10);
	CH45x_DIN_W=1;             //先低后高，选择4线输入由高变为低再变为高
	__delay_us(10);
	CH45x_DIN_W=0;             //先低后高，选择4线输入
	__delay_us(10);
	CH45x_DIN_W=1;

	CH45x_Write(CH45x_RESET);
	CH45x_Write(CH45x_SYSON2);
	CH45x_Write(CH45x_DSP);
	CH45x_Write(CH45x_BCD);
}
//向CH45x写命令/数据函数
void CH45x_Write(unsigned int command)
{
	unsigned char i;
	CH45x_CloseINT();
	CH45x_LOAD_W=0;                //命令开始       
	for(i=0;i<12;i++)			 //送入12位数据，低位在前
	{      
		if((command&0x01)==0x01)
			CH45x_DIN_W=1;
		else
			CH45x_DIN_W=0;
		NOP();     
		CH45x_DCLK_W=0;			 //低电平脉冲
		command>>=1;
		CH45x_DCLK_W=1;            //上升沿有效
	}
	CH45x_LOAD_W=1;                //加载数据
	CH45x_OpenINT();
}

//从CH45x读取一个字节函数
unsigned char CH45x_Read(void)
{
	unsigned char i;
	unsigned char command,keycode;     //定义命令字，和数据存储器
	CH45x_CloseINT();
	command=0x07;              		   //输入读451命令字 
	CH45x_LOAD_W=0;
	for(i=0;i<4;i++)
	{
		if((command&0x01)==0x01)
			CH45x_DIN_W=1;
		else
			CH45x_DIN_W=0;
		NOP();
		CH45x_DCLK_W=0;  		
		command>>=1;           //往右移一位
		CH45x_DCLK_W=1;          //产生时钟上升沿锁通知CH45x输入位数据
	}
	CH45x_LOAD_W=1;              //产生加载上升沿通知CH45x处理命令数据

	CH45x_DOUT_IO=1;          //外部中断输入线
	keycode=0;                 //清除keycode
	for(i=0;i<7;i++)
	{
		keycode<<=1;           //数据移入keycode,高位在前,低位在后
		CH45x_DCLK_W=1;
		NOP();    	
		CH45x_DCLK_W=0;          //产生时钟下升沿通知CH45x输出下一位
		keycode|=CH45x_DOUT_R;   //从高到低读入451的数据
		NOP();
		CH45x_DCLK_W=1;
	}
	CH45x_OpenINT();
	return keycode;      	 //返回键值
}
