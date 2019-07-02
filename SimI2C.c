#include "SimI2C.h"

void SimI2C_Init( void )
{
	SIMI2C_SCL_High();
	SIMI2C_SDA_High();
	SIMI2C_SDA_OUT();	
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
uint8_t SimI2C_RecAck(void)
{   
	uint8_t t;
	SIMI2C_SDA_IN();
	SIMI2C_SCL_Low();
	SimI2C_Delay();
	SIMI2C_SCL_High();
	SimI2C_Delay();
	t=SIMI2C_SDA_Read();
	SIMI2C_SCL_Low();
	SIMI2C_SDA_OUT();  
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
void SimI2C_SendByte(uint8_t data)//写数据
{   
	uint8_t i;
	uint8_t t;
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
uint8_t SimI2C_ReadByte(void)                    //读数据
{
	uint8_t data,i;
	SIMI2C_SDA_IN();
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
	SIMI2C_SDA_OUT();
	SimI2C_Delay();
	return data;
}

#ifdef SimI2C_2
void SimI2C_2_Init( void )
{
	SimI2C_2_SCL_High();
	SimI2C_2_SDA_High();
	SimI2C_2_SDA_OUT();	
}

//数据线下降沿作为起始位
void SimI2C_2_Start(void)
{
	SimI2C_2_SDA_High();
	SimI2C_2_SCL_High();
	SimI2C_2_Delay();
	SimI2C_2_SDA_Low();
	SimI2C_2_Delay();
	SimI2C_2_SCL_Low();
}
//数据线上升沿作为起始位
void SimI2C_2_Stop(void)
{
	SimI2C_2_SCL_Low();
	SimI2C_2_SDA_Low();
	SimI2C_2_Delay();
	SimI2C_2_SCL_High();
	SimI2C_2_Delay();
	SimI2C_2_SDA_High();
}
//时钟线上升沿读取ACK
uint8_t SimI2C_2_RecAck(void)
{   
	uint8_t t;
	SimI2C_2_SDA_IN();
	SimI2C_2_SCL_Low();
	SimI2C_2_Delay();
	SimI2C_2_SCL_High();
	SimI2C_2_Delay();
	t=SimI2C_2_SDA_Read();
	SimI2C_2_SCL_Low();
	SimI2C_2_SDA_OUT();  
	return t;
}
//数据线低电平，发送Ack
void SimI2C_2_Ack(void)
{
	SimI2C_2_SDA_Low();		
	SimI2C_2_Delay();
	SimI2C_2_SCL_High();
	SimI2C_2_Delay();
	SimI2C_2_SCL_Low();
	SimI2C_2_Delay();
	SimI2C_2_SDA_High();
}
//数据线高电平，发送Ack
void SimI2C_2_NoAck(void)
{
	SimI2C_2_SCL_High();		
	SimI2C_2_SDA_High();
	SimI2C_2_Delay();
	SimI2C_2_SCL_Low();
}
void SimI2C_2_SendByte(uint8_t data)//写数据
{   
	uint8_t i;
	uint8_t t;
	for(i=0;i<8;i++)
	{
		SimI2C_2_SCL_Low();
		t=data&0x80;
		if(t==0x00)
			SimI2C_2_SDA_Low();
		else 
			SimI2C_2_SDA_High();
		data<<=1;
		SimI2C_2_Delay();
		SimI2C_2_SCL_High();
		SimI2C_2_Delay();     
	}	
	SimI2C_2_SCL_Low();
}
uint8_t SimI2C_2_ReadByte(void)                    //读数据
{
	uint8_t data,i;
	SimI2C_2_SDA_IN();
	SimI2C_2_Delay();
	SimI2C_2_SCL_Low();
	data=0;
	for(i=0;i<8;i++)
	{   
		SimI2C_2_Delay();
		SimI2C_2_SCL_High();
		SimI2C_2_Delay();
		data=data<<1;
		if(SimI2C_2_SDA_Read())
			data=data|0x01;
		SimI2C_2_Delay();
		SimI2C_2_SCL_Low();
		SimI2C_2_Delay();
	}
	SimI2C_2_SDA_OUT();
	SimI2C_2_Delay();
	return data;
}
#endif

#ifdef SimI2C_3
void SimI2C_3_Init( void )
{
	SimI2C_3_SCL_High();
	SimI2C_3_SDA_High();
	SimI2C_3_SDA_OUT();	
}

//数据线下降沿作为起始位
void SimI2C_3_Start(void)
{
	SimI2C_3_SDA_High();
	SimI2C_3_SCL_High();
	SimI2C_3_Delay();
	SimI2C_3_SDA_Low();
	SimI2C_3_Delay();
	SimI2C_3_SCL_Low();
}
//数据线上升沿作为起始位
void SimI2C_3_Stop(void)
{
	SimI2C_3_SCL_Low();
	SimI2C_3_SDA_Low();
	SimI2C_3_Delay();
	SimI2C_3_SCL_High();
	SimI2C_3_Delay();
	SimI2C_3_SDA_High();
}
//时钟线上升沿读取ACK
uint8_t SimI2C_3_RecAck(void)
{   
	uint8_t t;
	SimI2C_3_SDA_IN();
	SimI2C_3_SCL_Low();
	SimI2C_3_Delay();
	SimI2C_3_SCL_High();
	SimI2C_3_Delay();
	t=SimI2C_3_SDA_Read();
	SimI2C_3_SCL_Low();
	SimI2C_3_SDA_OUT();  
	return t;
}
//数据线低电平，发送Ack
void SimI2C_3_Ack(void)
{
	SimI2C_3_SDA_Low();		
	SimI2C_3_Delay();
	SimI2C_3_SCL_High();
	SimI2C_3_Delay();
	SimI2C_3_SCL_Low();
	SimI2C_3_Delay();
	SimI2C_3_SDA_High();
}
//数据线高电平，发送Ack
void SimI2C_3_NoAck(void)
{
	SimI2C_3_SCL_High();		
	SimI2C_3_SDA_High();
	SimI2C_3_Delay();
	SimI2C_3_SCL_Low();
}
void SimI2C_3_SendByte(uint8_t data)//写数据
{   
	uint8_t i;
	uint8_t t;
	for(i=0;i<8;i++)
	{
		SimI2C_3_SCL_Low();
		t=data&0x80;
		if(t==0x00)
			SimI2C_3_SDA_Low();
		else 
			SimI2C_3_SDA_High();
		data<<=1;
		SimI2C_3_Delay();
		SimI2C_3_SCL_High();
		SimI2C_3_Delay();     
	}	
	SimI2C_3_SCL_Low();
}
uint8_t SimI2C_3_ReadByte(void)                    //读数据
{
	uint8_t data,i;
	SimI2C_3_SDA_IN();
	SimI2C_3_Delay();
	SimI2C_3_SCL_Low();
	data=0;
	for(i=0;i<8;i++)
	{   
		SimI2C_3_Delay();
		SimI2C_3_SCL_High();
		SimI2C_3_Delay();
		data=data<<1;
		if(SimI2C_3_SDA_Read())
			data=data|0x01;
		SimI2C_3_Delay();
		SimI2C_3_SCL_Low();
		SimI2C_3_Delay();
	}
	SimI2C_3_SDA_OUT();
	SimI2C_3_Delay();
	return data;
}
#endif

