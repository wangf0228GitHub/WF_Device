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
uint8_t TM1650_Result_2;
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
		TM1650_Result_2=SimI2C_ReadByte();
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
uint8_t TM1650_Result_3;
#ifdef SimI2C_3
void TM1650_Init_3(void)
{
	SimI2C_Init_3();
}
uint8_t TM1650_Read_3(void)
{
	uint8_t ErrTimes=TM1650_RetryCount_3;	
	uint8_t bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start_3();		
		SimI2C_SendByte_3(0x49);//读
		if(SimI2C_RecAck_3())
			continue;
		TM1650_Result_3=SimI2C_ReadByte_3();
		SimI2C_Ack_3();		
		bRight=1;
		break;
	}
	SimI2C_Stop_3();
	return bRight;
}
uint8_t TM1650_WriteData_3(uint8_t Com,uint8_t Data)
{
	uint8_t ErrTimes=TM1650_RetryCount_3;
	uint8_t bRight=0;	
	while(ErrTimes--)
	{
		SimI2C_Start_3();		
		SimI2C_SendByte_3(Com);//写
		if(SimI2C_RecAck_3())
			continue;//无应答返回到循环
		SimI2C_SendByte_3(Data);
		if(SimI2C_RecAck_3())
			continue;
		break;		
	}
	SimI2C_Stop_3();
	__delay_us(5);
	return bRight;
}
#endif
#endif
