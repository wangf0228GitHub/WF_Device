#include "HardwareProfile.h"
#include "MCP3201.h"

// #define MCP3201_CLK_DIR	TRISA1
// #define MCP3201_DIN_DIR	TRISA2
// #define MCP3201_SYNC_DIR	TRISA0
// #define MCP3201_LDAC_DIR	TRISA0
// 
// #define MCP3201_CLK	RA1
// #define MCP3201_DIN	RA2	
// #define MCP3201_SYNC	RA0
// #define MCP3201_LDAC	RA0

void MCP3201_Init(void)
{	
	MCP3201_CLK_SetOut();
	MCP3201_Dout_SetIn();
	MCP3201_CS_SetOut();

	MCP3201_CS_SetHigh();
	MCP3201_CLK_SetLow();
}

uint16_t MCP3201_ReadAD(void)
{
	uint8_t i;
	uint16_t ret = 0;
	MCP3201_CS_SetLow();
	for(i=0;i<16;i++)
	{	
		ret = ret << 1;
		MCP3201_CLK_SetLow();
		if (MCP3201_Dout_Read() != 0)
		{
			ret = ret | 0x01;
		}
		MCP3201_CLK_SetHigh();
		
	}
	MCP3201_CS_SetHigh();
	//ret=ret & 0x0fff;
	return ret;
}

