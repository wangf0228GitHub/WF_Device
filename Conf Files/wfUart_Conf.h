#ifndef __Uart_Conf_h__
#define __Uart_Conf_h__

#include "usart.h"

// #define Uart1_TRMT TRMT
// #define Uart1_TXREG TXREG USARTx->DR = (Data & (uint16_t)0x01FF);
#define Uart_Uart1
#define Uart1_IsBusy() __HAL_UART_GET_FLAG(huart2,USART_FLAG_TXE)
#define Uart1_IsSendOk() __HAL_UART_GET_FLAG(huart2,USART_FLAG_TC)
#define Uart1_TxChar(data) huart2.Instance->DR = (data & (uint16_t)0x01FF);
#endif


