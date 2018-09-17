

#include "wfSys.h"
#include "main.h"
#include <stdarg.h>

static uint32_t fac_us=0;							//us延时倍乘数

//初始化延迟函数
//SYSCLK:系统时钟频率
void wfDelay_init(uint8_t SYSCLK)
{
	fac_us=SYSCLK;
}

//延时nus
//nus为要延时的us数.	
//nus:0~190887435(最大值即2^32/fac_us@fac_us=22.5)	 
void wfDelay_us(uint32_t nus)
{		
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
	ticks=nus*fac_us; 						//需要的节拍数 
	told=SysTick->VAL;        				//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	};
}
//延时nms
//nms:要延时的ms数
#ifdef Delay_ms_wfus
void wfDelay_ms(uint16_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) wfDelay_us(1000);
}
#endif

#ifdef USE_USART_PUTSTRING
void Usart_PutString(UART_HandleTypeDef *huart,char* pString, ...)
{
	//vsnprintf
	va_list ap;
	char s[Usart_PutString_Len];
	int n=0;
	va_start(ap, pString); //获得可变参数列表,分析fmt，得出各个参数的类型，也是分析参数中类似”%d%s“的字符串
	n=vsnprintf (s, Usart_PutString_Len, pString, ap); //写入字符串s
	va_end(ap); //释放资源,必须与va_start成对调用
	HAL_UART_Transmit(huart,s,n,2000);
}
#endif
// 
// //THUMB指令不支持汇编内联
// //采用如下方法实现执行汇编指令WFI  
// __asm void WFI_SET(void)
// {
// 	WFI;		  
// }
// //关闭所有中断(但是不包括fault和NMI中断)
// __asm void INTX_DISABLE(void)
// {
// 	CPSID   I
// 	BX      LR	  
// }
// //开启所有中断
// __asm void INTX_ENABLE(void)
// {
// 	CPSIE   I
// 	BX      LR  
// }
// //设置栈顶地址
// //addr:栈顶地址
// __asm void MSR_MSP(uint32_t addr) 
// {
// 	MSR MSP, r0 			//set Main Stack value
// 	BX r14
// }
