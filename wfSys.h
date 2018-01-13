#ifndef _wfSys_H
#define _wfSys_H

#include "main.h"

#define MAKE_BYTE(h,l)	((h<<4)+(l&0x0f))
#define MAKE_SHORT(h,l)	(((uint16_t)h<<8)+l)
#define MAKE_INT(h,l)	(((uint32_t)h<<16)+l)

#define LOW_NIBBLE(x)	(x&0x0F)
#define HIGH_NIBBLE(x)	(x>>4)
#define LOW_BYTE(x)     ((uint8_t)((x)&0xFF))
#define HIGH_BYTE(x)    ((uint8_t)(((x)>>8)&0xFF))
#define LOW_SHORT(x)     ((uint16_t)((x)&0xFFFF))
#define HIGH_SHORT(x)    ((uint16_t)(((x)>>16)&0xFFFF))

#define WF_CHECK_FLAG(__Instance__, __FLAG__)   ((((__Instance__) & (__FLAG__)) != 0) ? 1 : 0)
#define GetDeltaTick(a) (HAL_GetTick() - a)

void wfDelay_init(uint8_t SYSCLK);
void wfDelay_ms(uint16_t nms);
void wfDelay_us(uint32_t nus);

#ifdef USE_USART_PUTSTRING
#ifndef  Usart_PutString_Len
#define Usart_PutString_Len 100
#endif
void Usart_PutString(UART_HandleTypeDef *huart,char* pString, ...);
#endif


// #ifndef PRINTF_UART
// #define PRINTF_UART USART1
// #endif
//以下为汇编函数
// void WFI_SET(void);		//执行WFI指令
// void INTX_DISABLE(void);//关闭所有中断
// void INTX_ENABLE(void);	//开启所有中断
// void MSR_MSP(uint32_t addr);	//设置堆栈地址 
#endif

