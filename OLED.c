#include "HardwareProfile.h"

// #define OLED_RD RE2
// #define OLED_WR RB0
// #define OLED_CS RE1
// #define OLED_CD RE4
// #define OLED_RST PORTD
// #define OLED_PORT PORTD
// 
// 
// #define OLED_RST_DIR TRISE2
// #define OLED_RD_DIR TRISE2
// #define OLED_WR_DIR TRISB0
// #define OLED_CS_DIR TRISE1
// #define OLED_CD_DIR TRISE4
// #define OLED_PORT_DIR TRISD
uint8_t OLED_ReadState()
{
	uint8_t state;
	OLED_CD_W=1;    //控制字
#ifdef OLED_PORT_DIR
	OLED_PORT_W=0xff;//输入
#else
	OLED_SetPortRead();
#endif
	OLED_RD_W=0;    //读有效
	__delay_us(1);
#ifdef OLED_PORT_DIR
	state=OLED_PORT;
#else
	state=OLED_GetPortData();
#endif	
	OLED_RD_W=1;    //控制字
#ifdef OLED_PORT_DIR
	OLED_PORT_DIR=0x00;//输出
#else
	OLED_SetPortWrite();
#endif
	return ( state );  //返回LCD数据口数据
}

void OLED_Init(void)
{
	
#ifdef OLED_RST_DIR
	OLED_RST_DIR=0;
	OLED_RST_W=0;
	__delay_20ms(25);
	OLED_RST_W=1;
	__delay_20ms(25);
#endif

#ifdef OLED_M6800
	OLED_PORT_DIR=0x00;//输出
	OLED_E_DIR=0;
	OLED_WR_DIR=0;
	OLED_CD_DIR=0;
	OLED_CS_DIR=0;

	OLED_E_W=1;
	OLED_WR_W=1;
	OLED_CD_W=1;
	OLED_CS_W=1;
#elif defined(OLED_SPI)

#else

#ifdef OLED_PORT_DIR
	OLED_PORT_DIR=0x00;//输出
#endif	
	OLED_RD_DIR=0;
	OLED_WR_DIR=0;
	OLED_CD_DIR=0;
	OLED_CS_DIR=0;

	OLED_RD_W=1;
	OLED_WR_W=1;
	OLED_CD_W=1;
	OLED_CS_W=1;
#endif
	
	while(1)
	{
		// 设置列首地址低半字节；
		OLED_WriteC(0x00);
		// 设置列地址的高半字节；
		OLED_WriteC(0x10);
		// 设置存储区的地址模式；
		OLED_WriteC(0x20);
		OLED_WriteC(0x00); /* 选水平地址模式 *///02
		// 设置列窗口；
		OLED_WriteC(0x21);
		OLED_WriteC(0x00);
		OLED_WriteC(0x7f); /* 128 宽度的窗口 */
		// 设置页窗口；
		OLED_WriteC(0x22);
		OLED_WriteC(0x00);
		OLED_WriteC(0x07); /* 8 页的窗口 */
		// 设置显示起始行;
		OLED_WriteC(0x40); /* 0*/
		// 设置bank0 对比度；
		OLED_WriteC(0x81);
		OLED_WriteC(0x80); /* 共256 级 */
		// 设置彩色亮度；
		OLED_WriteC(0x82);
		OLED_WriteC(0x80); /* 共256 级 */
		// 设置SEG 可逆；
		OLED_WriteC(0xA1); /* 改变SEG 与地址
						   的对应关系 */
		// 设置全显；
		OLED_WriteC(0xA4); /* 不全显 */
		// 设置反显；
		OLED_WriteC(0xA6); /* 不反显 */
		// 设置显示行；
		OLED_WriteC(0xA8);
		OLED_WriteC(0x1f);
		/* 64 行，改变的是可显示的row*/
		// Vcc 来源；
		OLED_WriteC(0xAD);
		OLED_WriteC(0x8E); /* 8E=外部 */
		// 设置页首地址；
		OLED_WriteC(0xB0); /* 第0 页 */
		// 设置COM 扫描方向；
		OLED_WriteC(0xC8); /* COM 反向 */
		// 设置显示分支；
		OLED_WriteC(0xD3);
		OLED_WriteC(0x00); /* 0 */
		// 设置D 和Fosc;
		OLED_WriteC(0xD5);
		OLED_WriteC(0xD1); /* F=D D=2 */ //a0
		// 彩色与省电模式选择；
		OLED_WriteC(0xD8);
		OLED_WriteC(0); /* 48 为彩色，5 为省电 */
		// 设置 P1 P2；
		OLED_WriteC(0xD9);
		OLED_WriteC(0x22); /* P1=2 P2=2 */
		//设置COM 的硬件接法；
		OLED_WriteC(0xDA);
		OLED_WriteC(0x12);
		//设置Vcomh;
		OLED_WriteC(0xDB);
		OLED_WriteC(0x00);
		OLED_ClearScreen();
		OLED_WriteC(0xAF);
		/* AF=ON, AE=Sleep Mode，AC=Dim */
		if((OLED_ReadState()&0x40)==0x00)
			break;
	}
}
//x:0~15,y:0,1
void OLED_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{
     uint8_t i=0;
	 i=(x<<3)+4;
	 OLED_WriteC(0x21);
	 OLED_WriteC(i);
	 OLED_WriteC(i+15);
	 OLED_WriteC(0x22);
	 if(y==0)//上两行
	 {		 
		 OLED_WriteC(0);
		 OLED_WriteC(1);
	 }
	 else//下两行 
	 {
		 OLED_WriteC(2);
		 OLED_WriteC(3);
	 }
     for(i=0;i<32;i++) 
     { 
		OLED_WriteD(*zm++);
     } 
}
//x:0~15,y:0,1
void OLED_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{ 
	uint8_t i=0;
	i=(x<<3)+4;
	OLED_WriteC(0x21);
	OLED_WriteC(i);
	OLED_WriteC(i+7);
	OLED_WriteC(0x22);
	if(y==0)//上两行
	{		 
		OLED_WriteC(0);
		OLED_WriteC(1);
	}
	else//下两行 
	{
		OLED_WriteC(2);
		OLED_WriteC(3);
	}
	for(i=0;i<16;i++) 
	{ 
		OLED_WriteD(*zm++);
	}
}
void OLED_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic)
{
	uint16_t n,ii;
	n=Width*Height;
	n=n>>3;
	x=x<<3;
	x=x+4;
	OLED_WriteC(0x21);
	OLED_WriteC(x);
	Width=Width+x;
	Width=Width-1;
	OLED_WriteC(Width);
	OLED_WriteC(0x22);
	OLED_WriteC(y);
	Height=Height>>3;
	Height=Height+y;
	Height--;
	OLED_WriteC(Height);	
	for(ii=0;ii<n;ii++) 
	{ 
		OLED_WriteD(Pic[ii]);
	}
}
void OLED_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc)
{
	uint16_t n,ii;
	n=Width*Height;
	n=n>>3;
	x=x<<3;
	x=x+4;
	OLED_WriteC(0x21);
	OLED_WriteC(x);
	Width=Width+x;
	Width=Width-1;
	OLED_WriteC(Width);
	OLED_WriteC(0x22);
	OLED_WriteC(y);
	Height=Height>>3;
	Height=Height+y;
	Height--;
	OLED_WriteC(Height);	
	for(ii=0;ii<n;ii++) 
	{ 
		OLED_WriteD(fc);
	}
}
/********************************************************************************
函数名: Void ClearScreen(uint16_t ram)
函数功能: 清除整个屏幕
     ram : 需要清零的单元数
********************************************************************************/
void OLED_ClearScreen(void)
{
	uint16_t i=0;
	OLED_WriteC(0x21);
	OLED_WriteC(4);
	OLED_WriteC(131);
	OLED_WriteC(0x22);
	OLED_WriteC(0);
	OLED_WriteC(3);
	for(i=0;i<512;i++) 
	{ 
		OLED_WriteD(0x00);
	}
}
void OLED_WriteD(uint8_t dat)
{
	OLED_RD_W=1;
	OLED_CS_W=0;
	OLED_CD_W=1;    //数据	
	OLED_WR_W=0;
#ifdef OLED_PORT_DIR
	OLED_PORT_W=dat;
#else
	OLED_SetPortData(dat);
#endif
	OLED_WR_W=1;	
	OLED_CS_W=1;
}
void OLED_WriteC(uint8_t cmd)
{	
	OLED_RD_W=1;
	OLED_CS_W=0;
	OLED_CD_W=0;    //命令	
	OLED_WR_W=0;
#ifdef OLED_PORT_DIR
	OLED_PORT_W=cmd;
#else
	OLED_SetPortData(cmd);
#endif
	OLED_WR_W=1;	
	OLED_CS_W=1;
}
