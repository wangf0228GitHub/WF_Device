#include "HardwareProfile.h"
void ST7565R_WriteCommand(uint8_t com)
{ 
	uint8_t i ;  
	ST7565R_CS_W=0;  
	ST7565R_CD_W=0;	
	for(i=0;i<8;i++)
	{ 
		ST7565R_SCL_W=0;
		if((com&0x80)==0x80)
			ST7565R_DATA_W=1;
		else
			ST7565R_DATA_W=0;
		com=com<<1;
		ST7565R_SCL_W=1;
	}
	ST7565R_CS_W=1;
	ST7565R_CD_W=1;
}

void ST7565R_WriteData(uint8_t dat)
{  
	uint8_t i;
	ST7565R_CS_W=0;  
	ST7565R_CD_W=1;

	for(i=0;i<8;i++)
	{ 
		ST7565R_SCL_W=0;	
		if((dat&0x80)==0x80)
			ST7565R_DATA_W=1;
		else
			ST7565R_DATA_W=0;
		dat=dat<<1;
		ST7565R_SCL_W=1;
	}
	ST7565R_CS_W=1;
	ST7565R_CD_W=1;
}
void ST7565R_Init(void)
{
#ifdef ST7565R_Serial
#ifdef ST7565R_RST_DIR
	ST7565R_RST_DIR=0;
	ST7565R_RST_W=1;
	__delay_ms(20);
	ST7565R_RST_W=0;
	__delay_20ms(20);
	ST7565R_RST_W=1;
#endif
	ST7565R_CS_DIR=0;
	ST7565R_CD_DIR=0;
	ST7565R_SCL_DIR=0;
	ST7565R_DATA_DIR=0; 	

	ST7565R_CS_W=1;
	ST7565R_CD_W=1;
	ST7565R_SCL_W=1;
	ST7565R_DATA_W=1;
#endif

}
/******************************************************************************** 
函数名:Void ShowHZ16x16(unsigned Addr,uint16_t hzcode) 
函数功能：显示一个汉字(16*16点阵)
           Addr: 显示位置
        hzcode: 汉字代码(自定义的) 
注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
********************************************************************************/ 
void ST7565R_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{ 
	uint8_t col,i;
 	col=x<<3;
 	ST7565R_ColOffset(col);
 	ST7565R_WriteCommand(0xb0+ST7565R_ComTable[y]);
 	ST7565R_WriteCommand(0x10+HIGH_NIBBLE(col));
 	ST7565R_WriteCommand(LOW_NIBBLE(col));
 	for(i=0;i<16;i++)
 		ST7565R_WriteData(*zm++);	
 	ST7565R_WriteCommand(0xb0+ST7565R_ComTable[y+1]);
 	ST7565R_WriteCommand(0x10+HIGH_NIBBLE(col));
 	ST7565R_WriteCommand(LOW_NIBBLE(col));
 	for(i=0;i<16;i++)
 		ST7565R_WriteData(*zm++);
}
void ST7565R_SetVop(uint8_t vop)
{
	ST7565R_WriteCommand(0x81);  // select resistor ratio Rb/Ra
 	ST7565R_WriteCommand(vop);  // select volume 
}
 /******************************************************************************** 
 函数名:Void ShowHZ16x16(unsigned Addr,uint16_t hzcode) 
 函数功能：显示一个汉字(16*16点阵)
            Addr: 显示位置
         hzcode: 汉字代码(自定义的) 
 注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
 ********************************************************************************/ 
 void ST7565R_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm) 
 { 
	 uint8_t col,i;
	 col=x<<3;
	 ST7565R_ColOffset(col);
	 ST7565R_WriteCommand(0xb0+ST7565R_ComTable[y]);
	 ST7565R_WriteCommand(0x10+HIGH_NIBBLE(col));
	 ST7565R_WriteCommand(LOW_NIBBLE(col));
	 for(i=0;i<8;i++)
		 ST7565R_WriteData(*zm++);	
	 ST7565R_WriteCommand(0xb0+ST7565R_ComTable[y+1]);
	 ST7565R_WriteCommand(0x10+HIGH_NIBBLE(col));
	 ST7565R_WriteCommand(LOW_NIBBLE(col));
	 for(i=0;i<8;i++)
		 ST7565R_WriteData(*zm++);
 } 
 void ST7565R_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic)
 {
	 uint8_t col,i,j;
	 col=x<<3;
	 ST7565R_ColOffset(col);
	 Height=Height>>3;
	 for(i=0;i<Height;i++)
	 {
		 ST7565R_WriteCommand(0xb0+ST7565R_ComTable[y+i]);
		 ST7565R_WriteCommand(0x10+HIGH_NIBBLE(col));
		 ST7565R_WriteCommand(LOW_NIBBLE(col));
		 for(j=0;j<Width;j++)
			 ST7565R_WriteData(*Pic++);	
	 }
 }
 void ST7565R_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc)
 {
	 uint8_t col,i,j;
	 col=x<<3;
	 ST7565R_ColOffset(col);
	 Height=Height>>3;
	 for(i=0;i<Height;i++)
	 {
		 ST7565R_WriteCommand(0xb0+ST7565R_ComTable[y+i]);
		 ST7565R_WriteCommand(0x10+HIGH_NIBBLE(col));
		 ST7565R_WriteCommand(LOW_NIBBLE(col));
		 for(j=0;j<Width;j++)
			 ST7565R_WriteData(fc);	
	 }
 }
 /********************************************************************************
 函数名: Void ClearScreen(uint16_t ram)
 函数功能: 清除整个屏幕
      ram : 需要清零的单元数
 ********************************************************************************/
 void ST7565R_ClearScreen(void)
 {
	 uint8_t col,i;
	 for(i=0xb0;i<0xb8;i++)
	 {
		 ST7565R_WriteCommand(i);
		 ST7565R_WriteCommand(0x10);
		 ST7565R_WriteCommand(0x00);
		 for(col=0;col<131;col++)
			 ST7565R_WriteData(0);	
	 }	 
 }
// void ST7565R_ClearScreenEx(uint16_t start,uint16_t ram)
// {
// 	uint16_t i;
// 	LCD_T6963_AutoWriteStart(start);          // 清显示 RAM 区 0000h--2000h (8k)     
// 	for(i=0x00;i<ram;i++) 
// 		LCD_T6963_AutoWriteData(0x00);        // data=0;
// 	LCD_T6963_AutoWriteEnd();                // 自动写结束
// }
// 
// /********************************************************************************
// 函数名:    ReadSdate(void)
// 函数功能: IOPORT输出数据并检查LCD忙数据。
// 返回数据：checkbusy
// /********************************************************************************/
// uint8_t ST7565R_ReadState()
// {
// 	uint8_t state;
// 	LCD_T6963_CD_W=1;    //控制字
// #ifdef LCD_T6963_PORT_DIR
// 	LCD_T6963_PORT_W=0xff;//输入
// #else
// 	LCD_T6963_SetPortRead();
// #endif
// 	LCD_T6963_RD_W=0;    //读有效
// 	__delay_us(1);
// #ifdef LCD_T6963_PORT_DIR
// 	state=LCD_T6963_PORT;
// #else
// 	state=LCD_T6963_GetPortData();
// #endif	
// 	LCD_T6963_RD_W=1;    //控制字
// #ifdef LCD_T6963_PORT_DIR
// 	LCD_T6963_PORT_DIR=0x00;//输出
// #else
// 	LCD_T6963_SetPortWrite();
// #endif
// 	return ( state );  //返回LCD数据口数据
// }
