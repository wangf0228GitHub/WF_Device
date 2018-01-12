#ifndef __Lcd1602_H__
#define __Lcd1602_H__

//逐行，阴码，顺向
//#define LCD160X_PORT_DIR
// #define LCD160X_CD     //命令
// #define LCD160X_WR     //读
// #define LCD160X_E 
/******************1602液晶常量及操作******************/
#define LCD1602_A_FUNCTION	0x38   	// 液晶模式为8位，2行，5*8字符
#define LCD1602_G_FUNCTION	0x3e   	// 液晶模式为8位，2行，5*8字符
#define LCD1604_A_FUNCTION  0x30	// 液晶模式为8位，4行，5*8字符
#define LCD1604_G_FUNCTION  0x36	// 液晶模式为8位，4行，5*8字符

#define LCD160X_COMMAND  0	//指令标志
#define LCD160X_DATA     1	//数据标志		

#define LCD160X_A_CLR	0x01		// 清屏
#define LCD160X_A_HOME	0x02		// 地址返回原点，不改变DDRAM内容
#define LCD160X_A_ENTRY 0x06		// 设定输入模式，光标加，屏幕不移动
#define LCD160X_A_C2L	0x10		// 光标左移
#define LCD160X_A_C2R	0x14		// 光标右移
#define LCD160X_A_D2L	0x18		// 屏幕左移
#define LCD160X_A_D2R	0x1C		// 屏幕又移

#define LCD160X_A_ON	0x0C		// 打开显示
#define LCD160X_A_OFF	0x08		// 关闭显示
#define LCD160X_A_CURON	0x0E		// 显示光标
#define LCD160X_A_CURFLA	0x0F		// 打开光标闪烁

// #ifndef LCD160X_LineStart
// const unsigned char LCD160X_LineStart[4]={0x80,0x90,0x88,0x98};
// #endif

#define LCD160X_OFF() LCD160X_Write(LCD160X_COMMAND,0x08)  //关显示

/*------------------初始化-----------------*/
void LCD160X_Init(void);
/*---------------显示汉字或字符----------------*/
void LCD160X_DispString(unsigned char X,unsigned char Y,const char *pString);
void LCD160X_DispOneChar(unsigned char Addr,unsigned char c);
void LCD160X_DispOneCharByXY(unsigned char X,unsigned char Y,unsigned char c);
/************************************************************************/
/* 光标动作                                                             */
/************************************************************************/
void LCD160X_CurLeft(void);
void LCD160X_CurRight(void);
void LCD160X_CurShowByAddr(unsigned char Addr,unsigned char bFlicker);
void LCD160X_CurShowByXY(unsigned char X,unsigned char Y,unsigned char bFlicker );
void LCD160X_CurHide(void);
/*--------------清DDRAM------------------*/
void LCD160X_ClrRam(void);

#ifdef LCD160X_CGRAMADDR
void LCD160X_DispCGRAM(unsigned char X,unsigned char Y,unsigned char nIndex);
void Lcd1602_InitCGRAM(const char  *pC);
#endif

void LCD160X_Write(unsigned char dat_comm,unsigned char content);

/************************************************************************/
/* 绘图相关                                                             */
/************************************************************************/
void LCD160X_ShowHZ16x16(unsigned char x,unsigned char y,const unsigned char* zm);
void LCD160X_ShowHZ8x16(unsigned char x,unsigned char y,const unsigned char* zm1,const unsigned char* zm2);
void LCD160X_ShowPicByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,const unsigned char* Pic);
void LCD160X_ShowFullByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,unsigned char fc);
#endif

