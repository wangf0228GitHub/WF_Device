/*************
数字电位器驱动程序
数字电位器总阻值10KΩ
*************/
#include "HardwareProfile.h"

void X9C103_Init(void)
{
	X9C103_CS_IO = 0;
	X9C103_UD_IO = 0;
	X9C103_CLK_IO = 0;
	X9C103_CS_W = 0;
	X9C103_UD_W = 0;
	X9C103_CLK_W = 0;
	
	//X9C103_R_Change_Step(X9C103_R_DOWN,99);
}

void X9C103_R_Change_Step(uint8_t Mode,uint8_t N)
{
   	uint8_t i=0; 
   	if(Mode==1)	
   	{
   		X9C103_UD_W = 1;	//增加电阻
   	}
   	else
   	{
   		X9C103_UD_W = 0;//减小电阻
   	}
   	__delay_us(3);         // 延时大约2us
   	X9C103_CS_W = 0; 	 // CS  拉低
   	for(i=N;i>0;i--) 
  	{ 
     	X9C103_CLK_W = 1;  // 拉高INC    因为INC的下沿有效
     	__delay_us(2);         // 延时2us左右
     	X9C103_CLK_W = 0;   // INC 拉低;  // 产生一个下沿
     	__delay_us(100);       // 延时大约500us, Rw等待输出稳定
  	}
  	X9C103_CLK_W = 1;	//保存模式
   	X9C103_CS_W = 1;	// 完毕CS拉高 //store
}

