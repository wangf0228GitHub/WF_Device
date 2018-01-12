#ifndef __OLED_h__
#define __OLED_h__

void OLED_Init(void);
void OLED_WriteD(unsigned char dat);
void OLED_WriteC(unsigned char cmd);
void OLED_ShowHZ16x16(unsigned char x,unsigned char y,const unsigned char* zm); 
void OLED_ShowHZ8x16(unsigned char x,unsigned char y,const unsigned char* zm);
void OLED_ShowPicByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,const unsigned char* Pic);
void OLED_ShowFullByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,unsigned char fc);
void OLED_ClearScreen(void);
#endif // __OLED_h__
