#include "HardwareProfile.h"
#include "DAC8830.h"

// #define DAC8830_SCLK_DIR	TRISA1
// #define DAC8830_DIN_DIR	TRISA2
// #define DAC8830_SYNC_DIR	TRISA0
// #define DAC8830_LDAC_DIR	TRISA0
// 
// #define DAC8830_SCLK	RA1
// #define DAC8830_DIN	RA2	
// #define DAC8830_SYNC	RA0
// #define DAC8830_LDAC	RA0

void DAC8830_Init(void)
{	
	DAC8830_SCLK_SetOut();
	DAC8830_SDI_SetOut();
	DAC8830_CS_SetOut();

	DAC8830_CS_SetHigh();
	DAC8830_SCLK_SetLow();		
	DAC8830_SDI_SetHigh();
}

void DAC8830_Setting(uint16_t set)
{
	uint8_t i;	
	DAC8830_CS_SetLow();
	for(i=0;i<16;i++)
	{		
		if ((set & 0x8000) == 0x8000)
		{
			DAC8830_SDI_SetHigh();
		}
		else
		{
			DAC8830_SDI_SetLow();
		}
		DAC8830_SCLK_SetHigh();		
		set=set<<1;
		DAC8830_SCLK_SetLow();	//上升沿发送数据			
	}
	DAC8830_CS_SetHigh();
}

#ifdef DAC8830_2
void DAC8830_2_Init(void)
{
	DAC8830_2_SCLK_SetOut();
	DAC8830_2_SDI_SetOut();
	DAC8830_2_CS_SetOut();

	DAC8830_2_CS_SetHigh();
	DAC8830_2_SCLK_SetLow();
	DAC8830_2_SDI_SetHigh();
}

void DAC8830_2_Setting(uint16_t set)
{
	uint8_t i;
	DAC8830_2_CS_SetLow();
	for (i = 0; i < 16; i++)
	{
		if ((set & 0x8000) == 0x8000)
		{
			DAC8830_2_SDI_SetHigh();
		}
		else
		{
			DAC8830_2_SDI_SetLow();
		}
		DAC8830_2_SCLK_SetHigh();
		set = set << 1;
		DAC8830_2_SCLK_SetLow();	//上升沿发送数据			
	}
	DAC8830_2_CS_SetHigh();
}
#endif

#ifdef DAC8830_3
void DAC8830_3_Init(void)
{
	DAC8830_3_SCLK_SetOut();
	DAC8830_3_SDI_SetOut();
	DAC8830_3_CS_SetOut();

	DAC8830_3_CS_SetHigh();
	DAC8830_3_SCLK_SetLow();
	DAC8830_3_SDI_SetHigh();
}

void DAC8830_3_Setting(uint16_t set)
{
	uint8_t i;
	DAC8830_3_CS_SetLow();
	for (i = 0; i < 16; i++)
	{
		if ((set & 0x8000) == 0x8000)
		{
			DAC8830_3_SDI_SetHigh();
		}
		else
		{
			DAC8830_3_SDI_SetLow();
		}
		DAC8830_3_SCLK_SetHigh();
		set = set << 1;
		DAC8830_3_SCLK_SetLow();	//上升沿发送数据			
	}
	DAC8830_3_CS_SetHigh();
}
#endif

