#include "AD5302.h"

// #define AD5302_SCLK_DIR	TRISA1
// #define AD5302_DIN_DIR	TRISA2
// #define AD5302_SYNC_DIR	TRISA0
// #define AD5302_LDAC_DIR	TRISA0
// 
// #define AD5302_SCLK	RA1
// #define AD5302_DIN	RA2	
// #define AD5302_SYNC	RA0
// #define AD5302_LDAC	RA0

void AD5302_Init(void)
{	
	AD5302_SCLK_DIR=0;
	AD5302_DIN_DIR=0;
	AD5302_SYNC_DIR=0;
	AD5302_LDAC_DIR=0;

	AD5302_SCLK=1;	
	AD5302_SYNC=1;
	AD5302_LDAC=1;
	AD5302_DIN=1;
}

void AD5302_Setting(uint16_t set)
{
	uint8_t i;	
	AD5302_SYNC=0;
	for(i=0;i<16;i++)
	{		
		AD5302_SCLK=1;	
		if((set&0x8000)==0x8000)
			AD5302_DIN=1;
		else
			AD5302_DIN=0;
		set=set<<1;
		AD5302_SCLK=0;	//上升沿发送数据			
	}
	AD5302_SCLK=1;	
	AD5302_SYNC=1;
	AD5302_LDAC=0;//加载数据
	__delay_us(1);
	AD5302_LDAC=1;
}

