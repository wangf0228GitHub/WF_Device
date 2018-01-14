#ifndef __HT162X_h__
#define __HT162X_h__


// #define HT162X_DATA_DIR TRISB1
// #define HT162X_DATA RB1
// #define HT162X_CS   RB1  
// #define HT162X_WR   RB1  
// #define HT162X_RD	RB1
/************************************************************************/
/* 命令字宏定义                                                         */
/************************************************************************/
#define HT162X_SYS_DIS	0b00000000 // 关闭系统振荡器和LCD 偏压发生器
#define HT162X_SYS_EN	0b00000001 // 打开系统振荡器
#define HT162X_LCD_OFF	0b00000010 // 关闭LCD 偏压发生器
#define HT162X_LCD_ON	0b00000011 // 打开LCD 偏压发生器
#define HT162X_TIMER_DIS 0b00000100 // 时基输出失效
#define HT162X_WDT_DIS	0b00000101 // WDT 溢出标志输出失效
#define HT162X_TIMER_EN 0b00000110 // 时基输出使能
#define HT162X_WDT_EN	0b00000111 // WDT 溢出标志输出有效
#define HT162X_TONE_OFF 0b00001000 // 关闭声音输出
#define HT162X_TONE_ON	0b00001001 // 打开声音输出
#define HT162X_CLR_TIMER 0b00001100 // 时基发生器清零
#define HT162X_CLR_WDT	0b00001110 // 清除WDT 状态
#define HT162X_XTAL_32K	0b00010100 // 系统时钟源晶振
#define HT162X_RC_256K	0b00011000 // 系统时钟源片内RC 振荡器
#define HT162X_EXT_256K 0b00011100 // 系统时钟源外部时钟源
#define HT162X_TONE_4K	0b01000000 // 声音频率4KHz
#define HT162X_TONE_2K	0b01100000 // 声音频率2KHz
#define HT162X_IRQ_DIS	0b10000000 // 使/IRQ 输出失效
#define HT162X_IRQ_EN	0b10001000 // 使/IRQ 输出有效
#define HT162X_F1	0b10100000 // 时基/WDT 时钟输出1Hz
#define HT162X_F2	0b10100001 // 时基/WDT 时钟输出2Hz
#define HT162X_F4	0b10100010 // 时基/WDT 时钟输出4Hz
#define HT162X_F8	0b10100011 // 时基/WDT 时钟输出8Hz
#define HT162X_F16	0b10100100 // 时基/WDT 时钟输出16Hz
#define HT162X_F32	0b10100101 // 时基/WDT 时钟输出32Hz
#define HT162X_F64	0b10100110 // 时基/WDT 时钟输出64Hz
#define HT162X_F128 0b10100111 // 时基/WDT 时钟输出128Hz
#define HT162X_TOPT 0b11100000 // 测试模式
#define HT162X_TNORMAL 0b11100011 // 普通模式


void HT162X_Setting(uint8_t x);

void HT162X_WriteData(uint8_t reg,uint8_t data);

void HT162X_WriteDatas(uint8_t reg,const uint8_t* pBuf,uint8_t count);

void HT162X_Init(void);
#endif

