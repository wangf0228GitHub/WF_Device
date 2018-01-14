#ifndef __LCD_T6963_H__
#define __LCD_T6963_H__

//逐行，顺向，阴码
/************************************************************ 

                       指令代码定义 

************************************************************/ 
#define   T6963_CursorPointer    0x21          // 光标地址设置 
#define   T6963_OffsetReg        0x22          // CGRAM偏移地址设置 
#define   T6963_AddrSet          0x24          // 显示地址设置 
#define   T6963_TextHomeAddr     0x40          // 文本首地址 
#define   T6963_TextArea         0x41          // 文本宽度设置 
#define   T6963_GraHomeAddr      0x42          // 图形首地址设置 
#define   T6963_GraArea          0x43          // 图形宽度设置 
#define   T6963_OrMode           0x80          // 或模式显示 
#define   T6963_ExorMode         0x81          // 异或模式显示 
#define   T6963_AndMode          0x83          // 与模式显示 
#define   T6963_TextAttMode      0x84          // 文本属性模式 
#define   T6963_InterCGROM       0             // 内部CGROM 
#define   T6963_ExCGRAM          0x08          // 外部CGRAM 
#define   T6963_DisplayOff       0x90          // 显示关闭 
#define   T6963_CursorOn         0x92          // 光标显示，但不闪烁 
#define   T6963_CursorBlink      0x93          // 光标闪烁 
#define   T6963_TextOn           0x94          // 文本模式打开 
#define   T6963_GraOn            0x98          // 图形模式打开 
#define   T6963_TGAllOn          0x9c          // 文本图形模式都打开 
#define   T6963_DataAutoWrite    0xb0          // 数据自动写 
#define   T6963_DataAutoRead     0xb1          // 数据自动读 
#define   T6963_ExitAutoRW       0xb2          // 退出数据自动读写模式 
#define   T6963_DataWAddrI       0xc0          // 数据写，地址加1 
#define   T6963_DataWAddrD       0xc2          // 数据写，地址减1 
#define   T6963_DataWAddrNV      0xc4          // 数据写，地址不变 
#define   T6963_DataRAddrI       0xc1          // 数据读，地址加1 
#define   T6963_DataRAddrD       0xc3          // 数据读，地址减1 
#define   T6963_DataRAddrNV      0xc5          // 数据读，地址不变 
#define   T6963_ScreenPeek       0xe0          // 屏读 
#define   T6963_ScreenCopy       0xe1          // 屏拷贝 
void LCD_T6963_Init(void);
void LCD_T6963_ClearScreen(uint16_t ram);
void LCD_T6963_WriteCmd0(uint8_t cmd);
void LCD_T6963_WriteCmd1(uint8_t dat,uint8_t cmd);
void LCD_T6963_WriteCmd2(uint8_t dat1,uint8_t dat2,uint8_t cmd);
void LCD_T6963_AutoWriteStart(uint16_t Addr);
void LCD_T6963_AutoWriteData(uint8_t dat);
void LCD_T6963_AutoWriteEnd(void);
void LCD_T6963_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm);
void LCD_T6963_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm);
void LCD_T6963_ShowPic(uint16_t Addr,uint8_t Width,uint8_t Height,const uint8_t* Pic);
void LCD_T6963_ShowFull(uint16_t Addr,uint8_t Width,uint8_t Height,uint8_t fc);
void LCD_T6963_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc);
void LCD_T6963_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic);
#endif
