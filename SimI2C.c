#include "main.h"
#include "SimI2C_Conf.h"
#include "SimI2C.h"
void SimI2C_Init( void )
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = SimI2C_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SimI2C_SDA_GPIO_Port, &GPIO_InitStruct);	
	SIMI2C_SCL_High();
	SIMI2C_SDA_High();
}

//数据线下降沿作为起始位
void SimI2C_Start(void)
{
	SIMI2C_SDA_High();
	SIMI2C_SCL_High();
	SimI2C_Delay();
	SIMI2C_SDA_Low();
	SimI2C_Delay();
	SIMI2C_SCL_Low();
}
//数据线上升沿作为起始位
void SimI2C_Stop(void)
{
	SIMI2C_SCL_Low();
	SIMI2C_SDA_Low();
    SimI2C_Delay();
	SIMI2C_SCL_High();
	SimI2C_Delay();
	SIMI2C_SDA_High();
}
//时钟线上升沿读取ACK
unsigned char SimI2C_RecAck(void)
{   
	unsigned char t;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = SimI2C_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(SimI2C_SDA_GPIO_Port, &GPIO_InitStruct);

	SIMI2C_SCL_Low();
	SimI2C_Delay();
	SIMI2C_SCL_High();
	SimI2C_Delay();
	t=SIMI2C_SDA_Read();
	SIMI2C_SCL_Low();
	GPIO_InitStruct.Pin = SimI2C_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SimI2C_SDA_GPIO_Port, &GPIO_InitStruct);   
	return t;
}
//数据线低电平，发送Ack
void SimI2C_Ack(void)
{
	SIMI2C_SDA_Low();		
	SimI2C_Delay();
	SIMI2C_SCL_High();
	SimI2C_Delay();
	SIMI2C_SCL_Low();
	SimI2C_Delay();
	SIMI2C_SDA_High();
}
//数据线高电平，发送Ack
void SimI2C_NoAck(void)
{
	SIMI2C_SCL_High();		
	SIMI2C_SDA_High();
	SimI2C_Delay();
	SIMI2C_SCL_Low();
}
void SimI2C_SendByte(unsigned char data)//写数据
{   
	unsigned char i;
	unsigned char t;
	for(i=0;i<8;i++)
	{
		SIMI2C_SCL_Low();
		t=data&0x80;
		if(t==0x00)
			SIMI2C_SDA_Low();
		else 
			SIMI2C_SDA_High();
		data<<=1;
		SimI2C_Delay();
		SIMI2C_SCL_High();
		SimI2C_Delay();     
	}	
	SIMI2C_SCL_Low();
}
unsigned char SimI2C_ReadByte(void)                    //读数据
{
	unsigned char data,i;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = SimI2C_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(SimI2C_SDA_GPIO_Port, &GPIO_InitStruct);
	SimI2C_Delay();
	SIMI2C_SCL_Low();
	data=0;
	for(i=0;i<8;i++)
	{   
		SimI2C_Delay();
		SIMI2C_SCL_High();
		SimI2C_Delay();
		data=data<<1;
		if(SIMI2C_SDA_Read())
			data=data|0x01;
		SimI2C_Delay();
		SIMI2C_SCL_Low();
		SimI2C_Delay();
	}
	GPIO_InitStruct.Pin = SimI2C_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SimI2C_SDA_GPIO_Port, &GPIO_InitStruct);
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

