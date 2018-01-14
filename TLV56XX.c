#include "HardwareProfile.h"

void TLV56XX_Init(void)
{
	TLV56XX_FS_DIR=0; 
	TLV56XX_CLK_DIR=0;
	TLV56XX_DIO_DIR=0;
#ifdef TLV56XX_CS_DIR
	TLV56XX_CS_DIR=0;
#endif
	TLV56XX_FS_W=1;
	TLV56XX_CLK_W=0;
	TLV56XX_DIO_W=0;
#ifdef TLV56XX_CS_W
	TLV56XX_CS_W=1;
#endif
}
void TLV56XX_WriteData(uint16_t d)
{
	uint8_t i;
#ifdef TLV56XX_CS_W
	TLV56XX_CS_W=0;
	__delay_us(1);
#endif
	TLV56XX_FS_W=0;

	for(i=0;i<16;i++)
	{
		TLV56XX_CLK_W=1;
		if((d&0x8000)==0x8000)
			TLV56XX_DIO_W=1;
		else
			TLV56XX_DIO_W=0;
		d<<=1;
		__delay_us(1);
		TLV56XX_CLK_W=0;
	}
	TLV56XX_CLK_W=1;

	TLV56XX_FS_W=1;
#ifdef TLV56XX_CS_W
	__delay_us(1);
	TLV56XX_CS_W=1;	
#endif
}
#ifdef TLV56XX_2
void TLV56XX_2_Init(void)
{
	TLV56XX_2_FS_DIR=0; 
	TLV56XX_2_CLK_DIR=0;
	TLV56XX_2_DIO_DIR=0;
#ifdef TLV56XX_2_CS_DIR
	TLV56XX_2_CS_DIR=0;
#endif
	TLV56XX_2_FS_W=1;
	TLV56XX_2_CLK_W=0;
	TLV56XX_2_DIO_W=0;
#ifdef TLV56XX_2_CS_W
	TLV56XX_2_CS_W=1;
#endif
}
void TLV56XX_2_WriteData(uint16_t d)
{
	uint8_t i;
#ifdef TLV56XX_2_CS_W
	TLV56XX_2_CS_W=0;
	__delay_us(1);
#endif
	TLV56XX_2_FS_W=0;

	for(i=0;i<16;i++)
	{
		TLV56XX_2_CLK_W=1;
		if((d&0x8000)==0x8000)
			TLV56XX_2_DIO_W=1;
		else
			TLV56XX_2_DIO_W=0;
		d<<=1;
		__delay_us(1);
		TLV56XX_2_CLK_W=0;
	}
	TLV56XX_2_CLK_W=1;

	TLV56XX_2_FS_W=1;
#ifdef TLV56XX_2_CS_W
	__delay_us(1);
	TLV56XX_2_CS_W=1;	
#endif
}
#endif
