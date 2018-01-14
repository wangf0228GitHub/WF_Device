#ifndef __LC160160B_h__
#define __LC160160B_h__

void LC160160B_Init(void);
void LC160160B_WriteD(uint8_t dat);
void LC160160B_WriteC(uint8_t cmd);
/******************************************************************************** 
函数名:Void ShowHZ16x16(unsigned Addr,uint16_t hzcode) 
函数功能：显示一个汉字(16*16点阵)
           Addr: 显示位置
        hzcode: 汉字代码(自定义的) 
注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
********************************************************************************/ 
void LC160160B_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm); 

/******************************************************************************** 
函数名:Void ShowHZ16x16(unsigned Addr,uint16_t hzcode) 
函数功能：显示一个汉字(16*16点阵)
           Addr: 显示位置
        hzcode: 汉字代码(自定义的) 
注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
********************************************************************************/ 
void LC160160B_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm);

void LC160160B_ShowPic(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic);

/********************************************************************************
函数名: Void ClearScreen(uint16_t ram)
函数功能: 清除整个屏幕
     ram : 需要清零的单元数
********************************************************************************/
void LC160160B_ClearScreen(void);

void LC160160B_Write8Dots2LCD(uint8_t uc_dat);

#endif // __LC160160B_h__
