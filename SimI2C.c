#include "HardwareProfile.h"
void SimI2C_Init( void )
{
	SimI2C_CLK_IO=0;
	SimI2C_DATA_IO=0;
#ifdef SimI2C_WP_W
	SimI2C_WP_IO=0;
#endif

#ifdef SimI2C_WP_W
	SimI2C_WP_W=1;
#endif
	SimI2C_CLK_W=1;
	SimI2C_DATA_W=1;
}

//数据线下降沿作为起始位
void SimI2C_Start(void)
{
	SimI2C_DATA_W=1;
	SimI2C_CLK_W=1;
	SimI2C_Delay();
	SimI2C_DATA_W=0;
	SimI2C_Delay();
	SimI2C_CLK_W=0;
}
//数据线上升沿作为起始位
void SimI2C_Stop(void)
{
	SimI2C_CLK_W=0;
	SimI2C_DATA_W=0;
    SimI2C_Delay();
	SimI2C_CLK_W=1;
	SimI2C_Delay();
	SimI2C_DATA_W=1;
}
//时钟线上升沿读取ACK
unsigned char SimI2C_RecAck(void)
{   
	unsigned char t;
	SimI2C_DATA_IO=1;
	SimI2C_CLK_W=0;
	SimI2C_Delay();
	SimI2C_CLK_W=1;
	SimI2C_Delay();
	t=SimI2C_DATA_R;
	SimI2C_CLK_W=0;
    SimI2C_DATA_IO=0;    
	return t;
}
//数据线低电平，发送Ack
void SimI2C_Ack(void)
{
	SimI2C_DATA_W=0;		
	SimI2C_Delay();
	SimI2C_CLK_W=1;
	SimI2C_Delay();
	SimI2C_CLK_W=0;
	SimI2C_Delay();
	SimI2C_DATA_W=1;
}
//数据线高电平，发送Ack
void SimI2C_NoAck(void)
{
	SimI2C_CLK_W=1;		
	SimI2C_DATA_W=1;
	SimI2C_Delay();
	SimI2C_CLK_W=0;
}
void SimI2C_SendByte(unsigned char data)//写数据
{   
	unsigned char i;
	unsigned char t;
	for(i=0;i<8;i++)
	{
		SimI2C_CLK_W=0;
		t=data&0x80;
		if(t==0x00)
			SimI2C_DATA_W=0;
		else 
			SimI2C_DATA_W=1;
		data<<=1;
		SimI2C_Delay();
		SimI2C_CLK_W=1;
		SimI2C_Delay();     
	}	
	SimI2C_CLK_W=0;
}
unsigned char SimI2C_ReadByte(void)                    //读数据
{
	unsigned char data,i;
	SimI2C_DATA_IO=1;
	SimI2C_Delay();
	SimI2C_CLK_W=0;
	data=0;
	for(i=0;i<8;i++)
	{   
		SimI2C_Delay();
		SimI2C_CLK_W=1;
		SimI2C_Delay();
		data=data<<1;
		if(SimI2C_DATA_R)
			data=data|0x01;
		SimI2C_Delay();
		SimI2C_CLK_W=0;
		SimI2C_Delay();
	}
	SimI2C_DATA_IO=0;
	SimI2C_Delay();
	return data;
}

#ifdef SimI2C_2
void SimI2C_Init_2( void )
{
	SimI2C_CLK_IO_2=0;
	SimI2C_DATA_IO_2=0;
#ifdef SimI2C_WP_W_2
	SimI2C_WP_IO_2=0;
#endif

#ifdef SimI2C_WP_W_2
	SimI2C_WP_W_2=1;
#endif
	SimI2C_CLK_W_2=1;
	SimI2C_DATA_W_2=1;
}

//数据线下降沿作为起始位
void SimI2C_Start_2(void)
{
	SimI2C_DATA_W_2=1;
	SimI2C_CLK_W_2=1;
	SimI2C_Delay_2();
	SimI2C_DATA_W_2=0;
	SimI2C_Delay_2();
	SimI2C_CLK_W_2=0;
}
//数据线上升沿作为起始位
void SimI2C_Stop_2(void)
{
	SimI2C_CLK_W_2=0;
	SimI2C_DATA_W_2=0;
	SimI2C_Delay_2();
	SimI2C_CLK_W_2=1;
	SimI2C_Delay_2();
	SimI2C_DATA_W_2=1;
}
//时钟线上升沿读取ACK
unsigned char SimI2C_RecAck_2(void)
{   
	unsigned char t;
	SimI2C_DATA_IO_2=1;
	SimI2C_CLK_W_2=0;
	SimI2C_Delay_2();
	SimI2C_CLK_W_2=1;
	SimI2C_Delay_2();
	t=SimI2C_DATA_R_2;
	SimI2C_CLK_W_2=0;
	SimI2C_DATA_IO_2=0;    
	return t;
}
//数据线低电平，发送Ack
void SimI2C_Ack_2(void)
{
	SimI2C_DATA_W_2=0;		
	SimI2C_Delay_2();
	SimI2C_CLK_W_2=1;
	SimI2C_Delay_2();
	SimI2C_CLK_W_2=0;
	SimI2C_Delay_2();
	SimI2C_DATA_W_2=1;
}
//数据线高电平，发送Ack
void SimI2C_NoAck_2(void)
{
	SimI2C_CLK_W_2=1;		
	SimI2C_DATA_W_2=1;
	SimI2C_Delay_2();
	SimI2C_CLK_W_2=0;
}
void SimI2C_SendByte_2(unsigned char data)//写数据
{   
	unsigned char i;
	unsigned char t;
	for(i=0;i<8;i++)
	{
		SimI2C_CLK_W_2=0;
		t=data&0x80;
		if(t==0x00)
			SimI2C_DATA_W_2=0;
		else 
			SimI2C_DATA_W_2=1;
		data<<=1;
		SimI2C_Delay_2();
		SimI2C_CLK_W_2=1;
		SimI2C_Delay_2();     
	}	
	SimI2C_CLK_W_2=0;
}
unsigned char SimI2C_ReadByte_2(void)                    //读数据
{
	unsigned char data,i;
	SimI2C_DATA_IO_2=1;
	SimI2C_Delay_2();
	SimI2C_CLK_W_2=0;
	data=0;
	for(i=0;i<8;i++)
	{   
		SimI2C_Delay_2();
		SimI2C_CLK_W_2=1;
		SimI2C_Delay_2();
		data=data<<1;
		if(SimI2C_DATA_R_2)
			data=data|0x01;
		SimI2C_Delay_2();
		SimI2C_CLK_W_2=0;
		SimI2C_Delay_2();
	}
	SimI2C_DATA_IO_2=0;
	SimI2C_Delay_2();
	return data;
}
#endif

#ifdef SimI2C_3
void SimI2C_Init_3( void )
{
	SimI2C_CLK_IO_3=0;
	SimI2C_DATA_IO_3=0;
#ifdef SimI2C_WP_W_3
	SimI2C_WP_IO_3=0;
#endif

#ifdef SimI2C_WP_W_3
	SimI2C_WP_W_3=1;
#endif
	SimI2C_CLK_W_3=1;
	SimI2C_DATA_W_3=1;
}

//数据线下降沿作为起始位
void SimI2C_Start_3(void)
{
	SimI2C_DATA_W_3=1;
	SimI2C_CLK_W_3=1;
	SimI2C_Delay_3();
	SimI2C_DATA_W_3=0;
	SimI2C_Delay_3();
	SimI2C_CLK_W_3=0;
}
//数据线上升沿作为起始位
void SimI2C_Stop_3(void)
{
	SimI2C_CLK_W_3=0;
	SimI2C_DATA_W_3=0;
	SimI2C_Delay_3();
	SimI2C_CLK_W_3=1;
	SimI2C_Delay_3();
	SimI2C_DATA_W_3=1;
}
//时钟线上升沿读取ACK
unsigned char SimI2C_RecAck_3(void)
{   
	unsigned char t;
	SimI2C_DATA_IO_3=1;
	SimI2C_CLK_W_3=0;
	SimI2C_Delay_3();
	SimI2C_CLK_W_3=1;
	SimI2C_Delay_3();
	t=SimI2C_DATA_R_3;
	SimI2C_CLK_W_3=0;
	SimI2C_DATA_IO_3=0;    
	return t;
}
//数据线低电平，发送Ack
void SimI2C_Ack_3(void)
{
	SimI2C_DATA_W_3=0;		
	SimI2C_Delay_3();
	SimI2C_CLK_W_3=1;
	SimI2C_Delay_3();
	SimI2C_CLK_W_3=0;
	SimI2C_Delay_3();
	SimI2C_DATA_W_3=1;
}
//数据线高电平，发送Ack
void SimI2C_NoAck_3(void)
{
	SimI2C_CLK_W_3=1;		
	SimI2C_DATA_W_3=1;
	SimI2C_Delay_3();
	SimI2C_CLK_W_3=0;
}
void SimI2C_SendByte_3(unsigned char data)//写数据
{   
	unsigned char i;
	unsigned char t;
	for(i=0;i<8;i++)
	{
		SimI2C_CLK_W_3=0;
		t=data&0x80;
		if(t==0x00)
			SimI2C_DATA_W_3=0;
		else 
			SimI2C_DATA_W_3=1;
		data<<=1;
		SimI2C_Delay_3();
		SimI2C_CLK_W_3=1;
		SimI2C_Delay_3();     
	}	
	SimI2C_CLK_W_3=0;
}
unsigned char SimI2C_ReadByte_3(void)                    //读数据
{
	unsigned char data,i;
	SimI2C_DATA_IO_3=1;
	SimI2C_Delay_3();
	SimI2C_CLK_W_3=0;
	data=0;
	for(i=0;i<8;i++)
	{   
		SimI2C_Delay_3();
		SimI2C_CLK_W_3=1;
		SimI2C_Delay_3();
		data=data<<1;
		if(SimI2C_DATA_R_3)
			data=data|0x01;
		SimI2C_Delay_3();
		SimI2C_CLK_W_3=0;
		SimI2C_Delay_3();
	}
	SimI2C_DATA_IO_3=0;
	SimI2C_Delay_3();
	return data;
}
#endif

