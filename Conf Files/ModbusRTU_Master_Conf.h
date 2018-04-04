#ifndef __ModbusRTU_Master_Conf_h__
#define __ModbusRTU_Master_Conf_h__

#include "main.h"
#include "stdint.h"
#include "usart.h"
#define ModbusRTU_MasterUart huart6

#define ModbusRTU_Master_UseTxList
#define ModbusRTU_Master_TxDataBuf(len) HAL_UART_Transmit(&ModbusRTU_MasterUart,ModbusRTU_Master_TxList,len,1000);

#define ModbusRTU_Master_WaitClientInterval_Ex
#define ModbusRTU_Master_WaitClientInterval() wfDelay_ms(100);

#define pModbusRTU_MasterData 7


#ifndef MAX_ModbusRTU_Master_RX
#define MAX_ModbusRTU_Master_RX 50
#endif


#define SetRx_ModbusRTU_Master_Ex
#define SetRx_ModbusRTU_Master() wfDelay_ms(1);HAL_GPIO_WritePin(RS485_DE_GPIO_Port,RS485_DE_Pin,GPIO_PIN_RESET)


#define SetTx_ModbusRTU_Master_Ex
#define SetTx_ModbusRTU_Master() HAL_GPIO_WritePin(RS485_DE_GPIO_Port,RS485_DE_Pin,GPIO_PIN_SET);wfDelay_ms(1)


//#define ModbusRTU_Master_preRxProcInit() //ModbusRTU_Master_Flags.bRx=0;ModbusRTU_Master_Flags.bWaitClient=1;ModbusRTU_Master_RxCount=0;ModbusRTU_Master_WaitClientTick=SystemTick;ModbusRTU_Master_NeedRxCount=0xff

#endif
