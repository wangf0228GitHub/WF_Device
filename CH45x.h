#ifndef __CH45x_h__
#define __CH45x_h__

#include "main.h"
//CH45xW4
// #define CH45x_DCLK_W TRISB1  //串行数据时钟上升延激活
// #define CH45x_DIN_W RB1      //串行数据输出，接CH45x的数据输入
// #define CH45x_LOAD_W   RB1   //串行命令加载，上升延激活
// #define CH45x_DOUT_R   RB1   //INT1，键盘中断和键值数据输入，接CH45x的数据输出
// #define CH45x_RST_W   RB1   //INT1，键盘中断和键值数据输入，接CH45x的数据输出
// 
// 
// #define CH45x_DCLK_IO TRISB1
// #define CH45x_DIN_IO RB1
// #define CH45x_LOAD_IO   RB1  
// #define CH45x_DOUT_IO   RB1 
// #define CH45x_RST_IO   RB1   //INT1，键盘中断和键值数据输入，接CH45x的数据输出

#define CH45x_RESET      0X0201    //复位
#define CH45x_LEFTMOV    0X0300    //左移
#define CH45x_LEFTCYC    0X0301    //左循
#define CH45x_RIGHTMOV   0X0302   //右移
#define CH45x_RIGHTCYC   0X0303   //右循
#define CH45x_SYSOFF     0x0400     //关显示、键盘、看门狗
#define CH45x_SYSON1     0x0401     //开显示
#define CH45x_SYSON2     0x0403     //开显示、键盘
#define CH45x_SYSON3     0x0407     //开显示、键盘、看门狗功能
#define CH45x_DSP        0x0500     //设置默认显示方式
#define CH45x_BCD        0x0580     //设置BCD译码方式
#define CH45x_TWINKLE    0x0600     //设置闪烁控制

#ifdef CH45x_noINT
#define CH45x_CloseINT()
#define CH45x_OpenINT() 
#endif
void CH45x_Init(void);
uint8_t CH45x_Read(void);
void CH45x_Write(uint16_t command);
#endif // __CH45x_h__
