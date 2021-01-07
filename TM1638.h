#ifndef __TM1638_h__
#define __TM1638_h__

// #define TM1638_STB TRISB1  //片选
// #define TM1638_CLK RB1      //时钟
// #define TM1638_DIO   RB1   //数据输入/输出
// 
// #define TM1638_STB_IO TRISB1
// #define TM1638_CLK_IO RB1
// #define TM1638_DIO_IO   RB1  
extern u32_wf TM1638_KeyValue;
void TM1638_Init(void);
void TM1638_WriteCommand(uint8_t c);
void TM1638_WriteData(uint8_t addr,uint8_t d);
void TM1638_WriteDatas(uint8_t addr,uint8_t* d,uint8_t count);
void TM1638_ReadKey(void);
#endif // __TM1638_h__

