#ifndef _X9C103_H_
#define _X9C103_H_

#define X9C103_R_UP	1	//X9C103阻值增加
#define X9C103_R_DOWN	0	//X9C103阻值减小
#define X9C103_R_Save	1	//X9C103保存阻值

// #define X9C103_CS_W			LATD5
// #define X9C103_UD_W			LATD7
// #define X9C103_CLK_W			LATD6
// 
// #define X9C103_CS_IO		TRISD5
// #define X9C103_UD_IO		TRISD7
// #define X9C103_CLK_IO		TRISD6

void X9C103_Init(void);
void X9C103_R_Change_Step(unsigned char Mode,unsigned char N);
#endif
