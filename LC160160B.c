#include "HardwareProfile.h"

// #define LC160160B_RD RE2
// #define LC160160B_WR RB0
// #define LC160160B_CS RE1
// #define LC160160B_CD RE4
// #define LC160160B_RST PORTD
// #define LC160160B_PORT PORTD
// 
// 
// #define LC160160B_RST_DIR TRISE2
// #define LC160160B_RD_DIR TRISE2
// #define LC160160B_WR_DIR TRISB0
// #define LC160160B_CS_DIR TRISE1
// #define LC160160B_CD_DIR TRISE4
// #define LC160160B_PORT_DIR TRISD




void LC160160B_WriteD(uint8_t dat);
void LC160160B_WriteC(uint8_t cmd);
void LC160160B_Init(void)
{
	
#ifdef LC160160B_RST
	uint8_t i;
	LC160160B_RST_DIR=0;
	LC160160B_RST=0;
	__delay_20ms(25);
	LC160160B_RST=1;
	__delay_20ms(25);
#endif
	LC160160B_PORT_DIR=0x00;//输出
	LC160160B_RD_DIR=0;
	LC160160B_WR_DIR=0;
	LC160160B_CD_DIR=0;
	LC160160B_CS_DIR=0;
	
	LC160160B_RD=1;
	LC160160B_WR=1;
	LC160160B_CD=1;
	LC160160B_CS=1;

	LC160160B_WriteC(0xE2);//System Reset 
	__delay_20ms(5);

	LC160160B_WriteC(0xAE);//Set Display Disable

	LC160160B_WriteC(0x26);//Set Temperature Compensation // 10-0.15% best
	LC160160B_WriteC(0x2B);//Set Power Control (Interal VLCD;Panel loading definition>13nF)
	LC160160B_WriteC(0xE9); //Set LCD Bias ratio:1/10

	LC160160B_WriteC(0x81); //Set gain and potentiometer Mode
	LC160160B_WriteC(0xC0); //Program Gain:01;PM value:xx  通过修改此参数的值来调节LCD显示的深浅，越大越深

	LC160160B_WriteC(0x89); //Set RAM Address Control
	LC160160B_WriteC(0xC4); //Set LCD Maping Control (MY=1, MX=0)

	LC160160B_WriteC(0xDE); //Set COM Scan Function

	LC160160B_WriteC(0xC8); //Set N-Line Inversion
	LC160160B_WriteC(0x18); //Set COM Scan Function

	LC160160B_WriteC(0xA3); //Set Line Rate

	LC160160B_WriteC(0xD5); //Set Color Mode (4K)
	LC160160B_WriteC(0xD1); //Set Color Pattern (RGB)

	LC160160B_WriteC(0x84); //Set Partial Display Off

	LC160160B_WriteC(0xF4); //Set Windows Program Starting Column Address
	LC160160B_WriteC(0x25); //

	LC160160B_WriteC(0xF6); //Set Windows Program Ending Column Address
	LC160160B_WriteC(0x5A); //

	LC160160B_WriteC(0xF5); //Set Windows Program Starting Row Address
	LC160160B_WriteC(0x00); //

	LC160160B_WriteC(0xF7); //Set Windows Program Ending Row Address
	LC160160B_WriteC(0x9F); //

	LC160160B_WriteC(0xF8); //Set Windows Program Mode: Inside Mode

	LC160160B_WriteC(0xAD); //Set Display Enable
}
/******************************************************************************** 
函数名:Void ShowHZ16x16(unsigned Addr,uint16_t hzcode) 
函数功能：显示一个汉字(16*16点阵)
           Addr: 显示位置
        hzcode: 汉字代码(自定义的) 
注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
********************************************************************************/ 
void LC160160B_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{ 
     uint8_t CA; 
     uint8_t i=0;
	 CA=0x25+y;
     for(i=0;i<16;i++) 
     { 
		LC160160B_WriteC(0x60|LOW_NIBBLE(x));
		LC160160B_WriteC(0x70|HIGH_NIBBLE(x));		
		LC160160B_WriteC(LOW_NIBBLE(CA));
		LC160160B_WriteC(0x01|HIGH_NIBBLE(CA));
		LC160160B_Write8Dots2LCD(*zm++);
		LC160160B_Write8Dots2LCD(*zm++);		
		x++;            // 换到下一行
     } 
}
/******************************************************************************** 
函数名:Void ShowHZ16x16(unsigned Addr,uint16_t hzcode) 
函数功能：显示一个汉字(16*16点阵)
           Addr: 显示位置
        hzcode: 汉字代码(自定义的) 
注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
********************************************************************************/ 
void LC160160B_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{ 
	uint8_t CA; 
	uint8_t i=0;
	CA=0x25+y;
	for(i=0;i<16;i++) 
	{ 
		LC160160B_WriteC(0x60|LOW_NIBBLE(x));
		LC160160B_WriteC(0x70|HIGH_NIBBLE(x));		
		LC160160B_WriteC(LOW_NIBBLE(CA));
		LC160160B_WriteC(0x10|HIGH_NIBBLE(CA));
		LC160160B_Write8Dots2LCD(*zm++);		
		x++;            // 换到下一行
	} 
}
void LC160160B_ShowPic(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic)
{
	uint8_t i,j,CA;
	uint8_t s3;
	s3=Width<<3;
	s3=s3%3;
	s3=3-s3;
	CA=0x25+y;	
	for(i=0;i<Height;i++) 
	{ 
		LC160160B_WriteC(0x60|LOW_NIBBLE(x));
		LC160160B_WriteC(0x70|HIGH_NIBBLE(x));		
		LC160160B_WriteC(LOW_NIBBLE(CA));
		LC160160B_WriteC(0x10|HIGH_NIBBLE(CA));
		for(j=0;j<Width;j++)
		{			
			LC160160B_Write8Dots2LCD(*Pic++);	
		}		
		for(j=0;j<s3;j++)
		{
			LC160160B_WriteD(0);
		}
		x++;            // 换到下一行
	} 
}
/********************************************************************************
函数名: Void ClearScreen(uint16_t ram)
函数功能: 清除整个屏幕
     ram : 需要清零的单元数
********************************************************************************/
void LC160160B_ClearScreen(void)
{
     uint8_t i,x,j,CA;
	 CA=0x25;
	 x=0;   
	 for(i=0;i<160;i++)  
	 {
		 LC160160B_WriteC(0x60|LOW_NIBBLE(x));
		 LC160160B_WriteC(0x70|HIGH_NIBBLE(x));		
		 LC160160B_WriteC(LOW_NIBBLE(CA));
		 LC160160B_WriteC(0x10|HIGH_NIBBLE(CA));
		 for(j=0x00;j<20;j++) 
			 LC160160B_Write8Dots2LCD(0x00);        // data=0;
		 LC160160B_WriteD(0);
		 x++;
	 }  	      
}
void LC160160B_Write8Dots2LCD(uint8_t uc_dat)
{
	uint8_t uc_dat0;

	uc_dat0 =0;
	if ((uc_dat &0x80)==0x80) uc_dat0=0xF0;
	if ((uc_dat &0x40)==0x40) uc_dat0|=0x0F;
	LC160160B_WriteD(uc_dat0);

	uc_dat0 =0;
	if ((uc_dat &0x20)==0x20) uc_dat0=0xF0;
	if ((uc_dat &0x10)==0x10) uc_dat0|=0x0F;
	LC160160B_WriteD(uc_dat0);

	uc_dat0 =0;
	if ((uc_dat &0x08)==0x08) uc_dat0=0xF0;
	if ((uc_dat &0x04)==0x04) uc_dat0|=0x0F;
	LC160160B_WriteD(uc_dat0);

	uc_dat0 =0;
	if ((uc_dat &0x02)==0x02) uc_dat0=0xF0;
	if ((uc_dat &0x01)==0x01) uc_dat0|=0x0F;
	LC160160B_WriteD(uc_dat0);
}
void LC160160B_WriteD(uint8_t dat)
{
	
	LC160160B_CD=1;    //数据
	LC160160B_CS=0;
	LC160160B_WR=0;
	LC160160B_PORT=dat;
	LC160160B_WR=1;	
	LC160160B_CS=1;
}
void LC160160B_WriteC(uint8_t cmd)
{	
	LC160160B_CD=0;    //命令
	LC160160B_CS=0;
	LC160160B_WR=0;
	LC160160B_PORT=cmd;
	LC160160B_WR=1;	
	LC160160B_CS=1;
}
