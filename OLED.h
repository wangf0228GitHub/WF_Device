#ifndef __OLED_h__
#define __OLED_h__

void OLED_Init(void);
void OLED_WriteD(uint8_t dat);
void OLED_WriteC(uint8_t cmd);
void OLED_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm); 
void OLED_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm);
void OLED_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic);
void OLED_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc);
void OLED_ClearScreen(void);
#endif // __OLED_h__
