#include "HardwareProfile.h"
#include "TM1650.h"
#ifdef SimI2C
#include "SimI2C.h"
#endif
//#define TM1650_DATA_W LATC1   
//#define TM1650_WR_W  LATC2   
//#define TM1650_CS_W 	 LATC3	
//
//#define TM1650_DIN_DIR RC1    
//#define TM1650_WR_DIR  RC2    
//#define TM1650_CS_DIR 	 RC3
uint8_t TM1650_Result;
#ifdef SimI2C
void TM1650_Init(void)
{
	SimI2C_Init();
}
uint8_t TM1650_Read(void)
{
	uint8_t ErrTimes=TM1650_RetryCount;
	uint8_t bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();		
		SimI2C_SendByte(0x49);//读
		if(SimI2C_RecAck())
			continue;
		TM1650_Result=SimI2C_ReadByte();
		SimI2C_Ack();		
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
uint8_t TM1650_WriteData(uint8_t Com,uint8_t Data)
{
	uint8_t ErrTimes=TM1650_RetryCount;
	uint8_t bRight=0;	
	while(ErrTimes--)
	{
		SimI2C_Start();		
		SimI2C_SendByte(Com);//写
		if(SimI2C_RecAck())
			continue;//无应答返回到循环
		SimI2C_SendByte(Data);
		if(SimI2C_RecAck())
			continue;
		bRight=1;	
		break;	
	}
	SimI2C_Stop();
	__delay_us(5);
	return bRight;
}
#endif

#ifdef TM1650_2
uint8_t TM1650_2_Result;
#ifdef SimI2C_2
void TM1650_2_Init(void)
{
	SimI2C_2_Init();
}
uint8_t TM1650_2_Read(void)
{
	uint8_t ErrTimes=TM1650_2_RetryCount;	
	uint8_t bRight=0;
	while(ErrTimes--)
	{
		SimI2C_2_Start();		
		SimI2C_2_SendByte(0x49);//读
		if(SimI2C_2_RecAck())
			continue;
		TM1650_2_Result=SimI2C_ReadByte();
		SimI2C_2_Ack();		
		bRight=1;
		break;
	}
	SimI2C_2_Stop();
	return bRight;
}
uint8_t TM1650_2_WriteData(uint8_t Com,uint8_t Data)
{
	uint8_t ErrTimes=TM1650_2_RetryCount;
	uint8_t bRight=0;	
	while(ErrTimes--)
	{
		SimI2C_2_Start();		
		SimI2C_2_SendByte(Com);//写
		if(SimI2C_2_RecAck())
			continue;//无应答返回到循环
		SimI2C_2_SendByte(Data);
		if(SimI2C_2_RecAck())
			continue;
		bRight=1;				
		break;		
	}
	SimI2C_2_Stop();
	__delay_us(5);
	return bRight;
}
#endif
#endif
#ifdef TM1650_3
uint8_t TM1650_3_Result;
#ifdef SimI2C_3
void TM1650_3_Init(void)
{
	SimI2C_3_Init();
}
uint8_t TM1650_3_Read(void)
{
	uint8_t ErrTimes=TM1650_3_RetryCount;
	uint8_t bRight=0;
	while(ErrTimes--)
	{
		SimI2C_3_Start();
		SimI2C_3_SendByte(0x49);//读
		if(SimI2C_3_RecAck())
			continue;
		TM1650_3_Result=SimI2C_ReadByte();
		SimI2C_3_Ack();
		bRight=1;
		break;
	}
	SimI2C_3_Stop();
	return bRight;
}
uint8_t TM1650_3_WriteData(uint8_t Com,uint8_t Data)
{
	uint8_t ErrTimes=TM1650_3_RetryCount;
	uint8_t bRight=0;	
	while(ErrTimes--)
	{
		SimI2C_3_Start();
		SimI2C_3_SendByte(Com);//写
		if(SimI2C_3_RecAck())
			continue;//无应答返回到循环
		SimI2C_3_SendByte(Data);
		if(SimI2C_3_RecAck())
			continue;
		bRight = 1;
		break;		
	}
	SimI2C_3_Stop();
	__delay_us(5);
	return bRight;
}
#endif
#endif

#ifdef TM1650_4
uint8_t TM1650_4_Result;
#ifdef SimI2C_4
void TM1650_4_Init(void)
{
	SimI2C_4_Init();
}
uint8_t TM1650_4_Read(void)
{
	uint8_t ErrTimes = TM1650_4_RetryCount;
	uint8_t bRight = 0;
	while (ErrTimes--)
	{
		SimI2C_4_Start();
		SimI2C_4_SendByte(0x49);//读
		if (SimI2C_4_RecAck())
			continue;
		TM1650_4_Result = SimI2C_4_ReadByte();
		SimI2C_4_Ack();
		bRight = 1;
		break;
	}
	SimI2C_4_Stop();
	return bRight;
}
uint8_t TM1650_4_WriteData(uint8_t Com, uint8_t Data)
{
	uint8_t ErrTimes = TM1650_4_RetryCount;
	uint8_t bRight = 0;
	while (ErrTimes--)
	{
		SimI2C_4_Start();
		SimI2C_4_SendByte(Com);//写
		if (SimI2C_4_RecAck())
			continue;//无应答返回到循环
		SimI2C_4_SendByte(Data);
		if (SimI2C_4_RecAck())
			continue;
		bRight = 1;
		break;
	}
	SimI2C_4_Stop();
	__delay_us(5);
	return bRight;
}
#endif
#endif

