#include "HardwareProfile.h"

// #define LCD_T6963_RD RE2
// #define LCD_T6963_WR RB0
// #define LCD_T6963_CE RE1
// #define LCD_T6963_CD RE4
// #define LCD_T6963_PORT PORTD
// 
// #define LCD_T6963_RD_DIR TRISE2
// #define LCD_T6963_WR_DIR TRISB0
// #define LCD_T6963_CE_DIR TRISE1
// #define LCD_T6963_CD_DIR TRISE4
// #define LCD_T6963_PORT_DIR TRISD
// #define LCD_T6963_LineChar 20  // 设置宽度

unsigned char LCD_T6963_ReadState();
void LCD_T6963_WriteD(unsigned char dat);
void LCD_T6963_WriteC(unsigned char cmd);
void LCD_T6963_Init(void)
{
	unsigned int x;
#ifdef LCD_T6963_RST_DIR
	LCD_T6963_RST_DIR=0;
	LCD_T6963_RST_W=1;
	__delay_ms(1);
	LCD_T6963_RST_W=0;
	__delay_20ms(20);
	LCD_T6963_RST_W=1;
#endif
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_DIR=0x00;//输出
#else
	LCD_T6963_SetPortWrite();
#endif	
	LCD_T6963_RD_DIR=0;
	LCD_T6963_WR_DIR=0;
	LCD_T6963_CD_DIR=0;
	LCD_T6963_CE_DIR=0;
	LCD_T6963_RD_W=1;
	LCD_T6963_WR_W=1;
	LCD_T6963_CD_W=1;
	LCD_T6963_CE_W=1;

	x=LCD_T6963_LineChar*LCD_T6963_Columns;
	x=x<<3;
	LCD_T6963_WriteCmd2(LOW_BYTE(x),HIGH_BYTE(x),T6963_TextHomeAddr);   //文本首地址,0x0a00,相当于一行
	LCD_T6963_WriteCmd2(LCD_T6963_LineChar,0x00,T6963_TextArea);   //文本宽度设置
	LCD_T6963_WriteCmd2(0x00,0x00,T6963_GraHomeAddr);   // 图形首地址
	LCD_T6963_WriteCmd2(LCD_T6963_LineChar,0x00,T6963_GraArea);   //设置图形宽度  
	//即一行显示所占字节数
	LCD_T6963_WriteCmd0(0xa0);             //光标设置
	LCD_T6963_WriteCmd0(T6963_OrMode);             //显示方式设置   逻辑异或合成
	LCD_T6963_WriteCmd0(T6963_GraOn);             //显示开关
	LCD_T6963_ClearScreen(x); 
}
/******************************************************************************** 
函数名:Void ShowHZ16x16(unsigned Addr,unsigned int hzcode) 
函数功能：显示一个汉字(16*16点阵)
           Addr: 显示位置
        hzcode: 汉字代码(自定义的) 
注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
********************************************************************************/ 
void LCD_T6963_ShowHZ16x16(unsigned char x,unsigned char y,const unsigned char* zm) 
{ 
     unsigned int StartAddr; 
     unsigned char i=0;
     //unsigned char* zm=ZM;
     StartAddr=x;
     StartAddr+=((unsigned int)y*LCD_T6963_LineChar)<<3;        //定位起始行
     for(i=0;i<16;i++) 
     { 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		LCD_T6963_WriteCmd1(*zm++, T6963_DataWAddrI);              // 左半部 地址加一 
		LCD_T6963_WriteCmd1(*zm++, T6963_DataWAddrNV);             // 右半部 显示地址不变
		StartAddr=StartAddr + LCD_T6963_LineChar;            // 换到下一行
     } 
}
/******************************************************************************** 
函数名:Void ShowHZ16x16(unsigned Addr,unsigned int hzcode) 
函数功能：显示一个汉字(16*16点阵)
           Addr: 显示位置
        hzcode: 汉字代码(自定义的) 
注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
********************************************************************************/ 
void LCD_T6963_ShowHZ8x16(unsigned char x,unsigned char y,const unsigned char* zm) 
{ 
     unsigned int StartAddr; 
     unsigned char i=0;
     //unsigned char* zm=ZM;
     StartAddr=x;
     StartAddr+=((unsigned int)y*LCD_T6963_LineChar)<<3;        //定位起始行
     for(i=0;i<16;i++) 
     { 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		LCD_T6963_WriteCmd1(*zm++, T6963_DataWAddrNV);             // 右半部 显示地址不变
		StartAddr=StartAddr + LCD_T6963_LineChar;            // 换到下一行
     } 
}
void LCD_T6963_ShowPic(unsigned int Addr,unsigned char Width,unsigned char Height,const unsigned char* Pic)
{
	unsigned int StartAddr; 
	unsigned char i,j;
	//unsigned char* zm=ZM;
	StartAddr=Addr;        //定位起始行
	Width=Width>>3;
	for(i=0;i<Height;i++) 
	{ 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		for(j=0;j<Width;j++)
		{
			LCD_T6963_WriteCmd1(*Pic++, T6963_DataWAddrI);
		}
		StartAddr=StartAddr + LCD_T6963_LineChar;            // 换到下一行
	} 
}
void LCD_T6963_ShowFull(unsigned int Addr,unsigned char Width,unsigned char Height,unsigned char fc)
{
	unsigned int StartAddr; 
	unsigned char i,j;
	//unsigned char* zm=ZM;
	StartAddr=Addr;        //定位起始行
	Width=Width>>3;
	for(i=0;i<Height;i++) 
	{ 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		for(j=0;j<Width;j++)
		{
			LCD_T6963_WriteCmd1(fc, T6963_DataWAddrI);
		}
		StartAddr=StartAddr + LCD_T6963_LineChar;            // 换到下一行
	} 
}
void LCD_T6963_ShowPicByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,const unsigned char* Pic)
{
	unsigned int StartAddr; 
	unsigned char i,j;
	//unsigned char* zm=ZM;
	StartAddr=x;
	StartAddr+=((unsigned int)y*LCD_T6963_LineChar)<<3;        //定位起始行
	Width=Width>>3;
	for(i=0;i<Height;i++) 
	{ 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		for(j=0;j<Width;j++)
		{
			LCD_T6963_WriteCmd1(*Pic++, T6963_DataWAddrI);
		}
		StartAddr=StartAddr + LCD_T6963_LineChar;            // 换到下一行
	} 
}
void LCD_T6963_ShowFullByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,unsigned char fc)
{
	unsigned int StartAddr; 
	unsigned char i,j;
	//unsigned char* zm=ZM;
	StartAddr=x;
	StartAddr+=((unsigned int)y*LCD_T6963_LineChar)<<3;        //定位起始行
	Width=Width>>3;
	for(i=0;i<Height;i++) 
	{ 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		for(j=0;j<Width;j++)
		{
			LCD_T6963_WriteCmd1(fc, T6963_DataWAddrI);
		}
		StartAddr=StartAddr + LCD_T6963_LineChar;            // 换到下一行
	} 
}
/********************************************************************************
函数名: Void ClearScreen(unsigned int ram)
函数功能: 清除整个屏幕
     ram : 需要清零的单元数
********************************************************************************/
void LCD_T6963_ClearScreen(unsigned int ram)
{
     unsigned int i;
     LCD_T6963_AutoWriteStart(0x0000);          // 清显示 RAM 区 0000h--2000h (8k)     
     for(i=0x00;i<ram;i++) 
		 LCD_T6963_AutoWriteData(0x00);        // data=0;
     LCD_T6963_AutoWriteEnd();                // 自动写结束
}
void LCD_T6963_ClearScreenEx(unsigned int start,unsigned int ram)
{
	unsigned int i;
	LCD_T6963_AutoWriteStart(start);          // 清显示 RAM 区 0000h--2000h (8k)     
	for(i=0x00;i<ram;i++) 
		LCD_T6963_AutoWriteData(0x00);        // data=0;
	LCD_T6963_AutoWriteEnd();                // 自动写结束
}
/********************************************************************************
函数名:    Void LCD_T6963_WriteCmd1(unsigned char cmd)
           Void LCD_T6963_WriteCmd2(unsigned char dat1,unsigned char cmd)
           Void LCD_T6963_WriteCmd3(unsigned char dat1,unsigned char dat2,unsigned char cmd)
     Void LCD_T6963_WriteData(unsigned char dat)
函数功能: 写指令和写数据子程序
********************************************************************************/
void LCD_T6963_WriteD(unsigned char dat)
{
	while( (LCD_T6963_ReadState()&0x03)!=0x03 );
	LCD_T6963_CD_W=0;    //数据
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_W=dat;//输出
#else
	LCD_T6963_SetPortData(dat);
#endif
	LCD_T6963_WR_W=0;
	__delay_us(1);
	LCD_T6963_WR_W=1;	
}
void LCD_T6963_WriteC(unsigned char cmd)
{
	while( (LCD_T6963_ReadState()&0x03)!=0x03 );
	LCD_T6963_CD_W=1;    //数据
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_W=cmd;//输出
#else
	LCD_T6963_SetPortData(cmd);
#endif
	LCD_T6963_WR_W=0;
	__delay_us(1);
	LCD_T6963_WR_W=1;

}
void LCD_T6963_WriteCmd0(unsigned char cmd)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//片选
#endif

	LCD_T6963_WriteC(cmd);

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=1;//片选
#endif

}
void LCD_T6963_WriteCmd1(unsigned char dat,unsigned char cmd)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//片选
#endif

	LCD_T6963_WriteD(dat);
	LCD_T6963_WriteC(cmd);

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=1;//片选
#endif

}
void LCD_T6963_WriteCmd2(unsigned char dat1,unsigned char dat2,unsigned char cmd)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//片选
#endif

	LCD_T6963_WriteD(dat1);
	LCD_T6963_WriteD(dat2);
	LCD_T6963_WriteC(cmd);

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=1;//片选
#endif

}
void LCD_T6963_AutoWriteStart(unsigned int Addr)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//片选
#endif

	LCD_T6963_WriteD(LOW_BYTE(Addr));
	LCD_T6963_WriteD(HIGH_BYTE(Addr));
	LCD_T6963_WriteC(T6963_AddrSet);	
	LCD_T6963_WriteC(T6963_DataAutoWrite);  // 设置自动写状态
}
void LCD_T6963_AutoWriteData(unsigned char dat)
{
	while( !(LCD_T6963_ReadState()&0x08) );
	LCD_T6963_CD_W=0;    //数据
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_W=0x00;//输出
#else
	LCD_T6963_SetPortData(dat);
#endif
	LCD_T6963_WR_W=0;
	__delay_us(1);
	LCD_T6963_WR_W=1;	
}
void LCD_T6963_AutoWriteEnd(void)
{
	LCD_T6963_WriteC(T6963_ExitAutoRW);

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=1;//片选
#endif

}
/********************************************************************************
函数名:    ReadSdate(void)
函数功能: IOPORT输出数据并检查LCD忙数据。
返回数据：checkbusy
/********************************************************************************/
unsigned char LCD_T6963_ReadState()
{
	unsigned char state;
	LCD_T6963_CD_W=1;    //控制字
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_DIR=0xff;//输入
#else
	LCD_T6963_SetPortRead();
#endif
	LCD_T6963_RD_W=0;    //读有效
	__delay_us(1);
#ifdef LCD_T6963_PORT_DIR
	state=LCD_T6963_PORT_R;
#else
	state=LCD_T6963_GetPortData();
#endif	
	LCD_T6963_RD_W=1;    //控制字
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_DIR=0x00;//输出
#else
	LCD_T6963_SetPortWrite();
#endif
	return ( state );  //返回LCD数据口数据
}
