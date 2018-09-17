#ifndef __ATCommand_Conf_h__
#define __ATCommand_Conf_h__

#include "usart.h"
#include <string.h>
#include "wfSys.h"
#include "SIM800CProc.h"

#define ATCommand_Tx_Ex
#define ATCommand_TxByte(x) txChar=x;HAL_UART_Transmit(&huart2,(uint8_t *)&txChar,1,1000)
#define ATCommand_PutString(x) HAL_UART_Transmit(&huart2,(uint8_t *)x,strlen(x),1000)
#endif


