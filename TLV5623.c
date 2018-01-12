#include "HardwareProfile.h"

void TLV5623_Init(void)
{
	TLV5623_FS_IO=0; 
	TLV5623_CLK_IO=0;
	TLV5623_DIO_IO=0;
#ifdef TLV5623_CS_IO
	TLV5623_CS_IO=0;
#endif
	TLV5623_FS_W=1;
	TLV5623_CLK_W=0;
	TLV5623_DIO_W=0;
#ifdef TLV5623_CS_W
	TLV5623_CS_W=1;
#endif
}
void TLV5623_WriteData(unsigned char d)
{
	unsigned char i;
#ifdef TLV5623_CS_W
	TLV5623_CS_W=0;
	__delay_us(1);
#endif
	TLV5623_FS_W=0;

	TLV5623_CLK_W=1;
	TLV5623_DIO_W=0;	
	__delay_us(1);
	TLV5623_CLK_W=0;

	TLV5623_CLK_W=1;
	if(TLV5623State.SPD)
		TLV5623_DIO_W=1;	
	else
		TLV5623_DIO_W=0;
	__delay_us(1);
	TLV5623_CLK_W=0;

	TLV5623_CLK_W=1;
	if(TLV5623State.PWR)
		TLV5623_DIO_W=1;	
	else
		TLV5623_DIO_W=0;
	__delay_us(1);
	TLV5623_CLK_W=0;

	TLV5623_CLK_W=1;
	TLV5623_DIO_W=0;	
	__delay_us(1);
	TLV5623_CLK_W=0;

	for(i=0;i<8;i++)
	{
		TLV5623_CLK_W=1;
		if((d&0x80)==0x80)
			TLV5623_DIO_W=1;
		else
			TLV5623_DIO_W=0;
		d<<=1;
		__delay_us(1);
		TLV5623_CLK_W=0;
	}
	for(i=0;i<4;i++)
	{
		TLV5623_CLK_W=1;
		TLV5623_DIO_W=0;	
		__delay_us(1);
		TLV5623_CLK_W=0;
	}
	TLV5623_CLK_W=1;

	TLV5623_FS_W=1;
#ifdef TLV5623_CS_W
	__delay_us(1);
	TLV5623_CS_W=1;	
#endif
}

