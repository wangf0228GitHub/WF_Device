#ifndef __LC160160B_h__
#define __LC160160B_h__

void LC160160B_Init(void);
void LC160160B_WriteD(unsigned char dat);
void LC160160B_WriteC(unsigned char cmd);
/******************************************************************************** 
函数名:Void ShowHZ16x16(unsigned Addr,unsigned int hzcode) 
函数功能：显示一个汉字(16*16点阵)
           Addr: 显示位置
        hzcode: 汉字代码(自定义的) 
注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
********************************************************************************/ 
void LC160160B_ShowHZ16x16(unsigned char x,unsigned char y,const unsigned char* zm); 

/******************************************************************************** 
函数名:Void ShowHZ16x16(unsigned Addr,unsigned int hzcode) 
函数功能：显示一个汉字(16*16点阵)
           Addr: 显示位置
        hzcode: 汉字代码(自定义的) 
注:超出范围的将直接写到RAM中,可以实现卷屏效果????????
********************************************************************************/ 
void LC160160B_ShowHZ8x16(unsigned char x,unsigned char y,const unsigned char* zm);

void LC160160B_ShowPic(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,const unsigned char* Pic);

/********************************************************************************
函数名: Void ClearScreen(unsigned int ram)
函数功能: 清除整个屏幕
     ram : 需要清零的单元数
********************************************************************************/
void LC160160B_ClearScreen(void);

void LC160160B_Write8Dots2LCD(unsigned char uc_dat);

#endif // __LC160160B_h__
