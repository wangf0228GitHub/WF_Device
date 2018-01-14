#include "HardwareProfile.h"

void HT162X_Setting(uint8_t x)
{
	uint8_t i;
	HT162X_WR_W=0;
	HT162X_CS_W=0;
	__delay_us(10);
	HT162X_DATA_W=1;
	__delay_us(1);
	HT162X_WR_W=1;
	__delay_us(10);
	HT162X_WR_W=0;
	__delay_us(1);
	HT162X_DATA_W=0;
	__delay_us(10);
	HT162X_WR_W=1;
	__delay_us(10);
	HT162X_WR_W=0;
	__delay_us(10);
	HT162X_DATA_W=0;
	__delay_us(10);
	HT162X_WR_W=1;
	__delay_us(10);
	HT162X_WR_W=0;
	for(i=0; i<9; i++) 
	{   
		if((x & 0x80)==0x80) 
			HT162X_DATA_W=1; 
		else 
			HT162X_DATA_W=0; 
		__delay_us(10);
		HT162X_WR_W=1;
		__delay_us(10);
		HT162X_WR_W=0;
		x=x<<1; 
	}  
	HT162X_CS_W=1;
	HT162X_WR_W=1;
}
void HT162X_WriteData(uint8_t reg,uint8_t d)
{
	uint8_t i;
	HT162X_WR_W=0;
	HT162X_CS_W=0;
	__delay_us(10);
	HT162X_DATA_W=1;
	__delay_us(10);
	HT162X_WR_W=1;
	__delay_us(10);
	HT162X_WR_W=0;
	__delay_us(10);
	HT162X_DATA_W=0;
	__delay_us(10);
	HT162X_WR_W=1;
	__delay_us(10);
	HT162X_WR_W=0;
	__delay_us(10);
	HT162X_DATA_W=1;
	__delay_us(10);
	HT162X_WR_W=1;
	__delay_us(10);
	HT162X_WR_W=0;
	reg=reg<<2;
	for(i=0; i<6; i++) 
	{   
		if((reg & 0x80)==0x80) 
			HT162X_DATA_W=1; 
		else 
			HT162X_DATA_W=0; 
		__delay_us(10);
		HT162X_WR_W=1;
		__delay_us(10);
		HT162X_WR_W=0;
		reg=reg<<1; 
	}  
	for(i=0; i<5; i++) 
	{   
		if((d & 0x01)==0x01) 
			HT162X_DATA_W=1; 
		else 
			HT162X_DATA_W=0; 
		__delay_us(10);
		HT162X_WR_W=1;
		__delay_us(10);
		HT162X_WR_W=0;
		d=d>>1; 
	}
	HT162X_CS_W=1;
	HT162X_WR_W=1;
}
void HT162X_WriteDatas(uint8_t reg,const uint8_t* pBuf,uint8_t count)
{
	uint8_t i,j,x;
	HT162X_WR_W=0;
	HT162X_CS_W=0;
	__delay_us(10);
	HT162X_DATA_W=1;
	__delay_us(1);
	HT162X_WR_W=1;
	__delay_us(1);
	HT162X_WR_W=0;
	__delay_us(1);
	HT162X_DATA_W=0;
	__delay_us(1);
	HT162X_WR_W=1;
	__delay_us(1);
	HT162X_WR_W=0;
	__delay_us(1);
	HT162X_DATA_W=1;
	__delay_us(1);
	HT162X_WR_W=1;
	__delay_us(1);
	HT162X_WR_W=0;
	reg=reg<<2;
	for(i=0; i<6; i++) 
	{   
		if((reg & 0x80)==0x80) 
			HT162X_DATA_W=1; 
		else 
			HT162X_DATA_W=0; 
		__delay_us(1);
		HT162X_WR_W=1;
		__delay_us(1);
		HT162X_WR_W=0;
		reg<<=1; 
	}  
	for(i=0; i<count; i++) 
	{   
		x=*pBuf;
		for(j=0;j<4;j++)
		{
			if((x & 0x01)==0x01) 
				HT162X_DATA_W=1; 
			else 
				HT162X_DATA_W=0; 
			__delay_us(1);
			HT162X_WR_W=1;
			__delay_us(1);
			HT162X_WR_W=0;
			x>>=1; 
		}
		pBuf++;
	}  
	HT162X_CS_W=1;
	HT162X_WR_W=1;
}

void HT162X_Init( void )
{
	HT162X_DATA_IO=0;
	HT162X_CS_IO=0;
	HT162X_WR_IO=0;
#ifdef HT162X_RD_W
	HT162X_RD_W_IO=0; 
#endif	

	HT162X_CS_W=1;
	HT162X_WR_W=1;
	HT162X_DATA_W=0;
#ifdef HT162X_RD_W
	HT162X_RD_W=1;
#endif
}
