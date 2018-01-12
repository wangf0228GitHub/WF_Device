#include "HardwareProfile.h"


//#define Max7221_DATA_W LATC1   
//#define Max7221_WR_W  LATC2   
//#define Max7221_CS_W 	 LATC3	
//
//#define Max7221_DIN_DIR RC1    
//#define Max7221_WR_DIR  RC2    
//#define Max7221_CS_DIR 	 RC3

void Max7221_Init(void)       
{  
	Max7221_DIN_DIR=0;
	Max7221_CLK_DIR=0;
	Max7221_CS_DIR=0;
// 	Max7221_WriteData(0x09,0x00);   
// 	Max7221_WriteData(0x0a,0x07); 
// 	Max7221_WriteData(0x0b,0x03); 
// 	Max7221_WriteData(0x0c,0x01); 
// 	Max7221_WriteData(0x01,0xFF); 
// 	Max7221_WriteData(0x02,0xFF);
// 	Max7221_WriteData(0x03,0xFF);
// 	Max7221_WriteData(0x04,0xFF);
}
void Max7221_WriteData(unsigned char addr,unsigned char data)      
{  
	unsigned char i;
	Max7221_CS_W=0;
	for(i=0;i<8;i++)
	{
		Max7221_CLK_W=0;
		if((addr&0x80)==0x80)
			Max7221_DIN_W=1;
		else
			Max7221_DIN_W=0;
		addr<<=1;
		Max7221_CLK_W=1;
		__delay_us(1);
		Max7221_CLK_W=0;
	}
	for(i=0;i<8;i++)
	{
		Max7221_CLK_W=0;
		if((data&0x80)==0x80)
			Max7221_DIN_W=1;
		else
			Max7221_DIN_W=0;
		data<<=1;
		Max7221_CLK_W=1;
		__delay_us(1);
		Max7221_CLK_W=0;
	}
	Max7221_CS_W=1;
}

#ifdef Max7221_2
void Max7221_Init_2(void)       
{  
	Max7221_DIN_DIR_2=0;
	Max7221_CLK_DIR_2=0;
	Max7221_CS_DIR_2=0;
	// 	Max7221_WriteData(0x09,0x00);   
	// 	Max7221_WriteData(0x0a,0x07); 
	// 	Max7221_WriteData(0x0b,0x03); 
	// 	Max7221_WriteData(0x0c,0x01); 
	// 	Max7221_WriteData(0x01,0xFF); 
	// 	Max7221_WriteData(0x02,0xFF);
	// 	Max7221_WriteData(0x03,0xFF);
	// 	Max7221_WriteData(0x04,0xFF);
}
void Max7221_WriteData_2(unsigned char addr,unsigned char data)      
{  
	unsigned char i;
	Max7221_CS_W_2=0;
	for(i=0;i<8;i++)
	{
		Max7221_CLK_W_2=0;
		if((addr&0x80)==0x80)
			Max7221_DIN_W_2=1;
		else
			Max7221_DIN_W_2=0;
		addr<<=1;
		Max7221_CLK_W_2=1;
		__delay_us(1);
		Max7221_CLK_W_2=0;
	}
	for(i=0;i<8;i++)
	{
		Max7221_CLK_W_2=0;
		if((data&0x80)==0x80)
			Max7221_DIN_W_2=1;
		else
			Max7221_DIN_W_2=0;
		data<<=1;
		Max7221_CLK_W_2=1;
		__delay_us(1);
		Max7221_CLK_W_2=0;
	}
	Max7221_CS_W_2=1;
}
#endif

#ifdef Max7221_3
void Max7221_Init_3(void)       
{  
	Max7221_DIN_DIR_3=0;
	Max7221_CLK_DIR_3=0;
	Max7221_CS_DIR_3=0;
	// 	Max7221_WriteData(0x09,0x00);   
	// 	Max7221_WriteData(0x0a,0x07); 
	// 	Max7221_WriteData(0x0b,0x03); 
	// 	Max7221_WriteData(0x0c,0x01); 
	// 	Max7221_WriteData(0x01,0xFF); 
	// 	Max7221_WriteData(0x02,0xFF);
	// 	Max7221_WriteData(0x03,0xFF);
	// 	Max7221_WriteData(0x04,0xFF);
}
void Max7221_WriteData_3(unsigned char addr,unsigned char data)      
{  
	unsigned char i;
	Max7221_CS_W_3=0;
	for(i=0;i<8;i++)
	{
		Max7221_CLK_W_3=0;
		if((addr&0x80)==0x80)
			Max7221_DIN_W_3=1;
		else
			Max7221_DIN_W_3=0;
		addr<<=1;
		Max7221_CLK_W_3=1;
		__delay_us(1);
		Max7221_CLK_W_3=0;
	}
	for(i=0;i<8;i++)
	{
		Max7221_CLK_W_3=0;
		if((data&0x80)==0x80)
			Max7221_DIN_W_3=1;
		else
			Max7221_DIN_W_3=0;
		data<<=1;
		Max7221_CLK_W_3=1;
		__delay_us(1);
		Max7221_CLK_W_3=0;
	}
	Max7221_CS_W_3=1;
}
#endif