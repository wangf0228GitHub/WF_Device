#ifndef __CP68_Client_Conf_h__
#define __CP68_Client_Conf_h__

#include "usart.h"
#include "wfSys.h"
#define CP68_USART_Handle huart1
/************************************************************************/
/* 用户命令定义                                                         */
/************************************************************************/
#define CP68_UserCommand_ReadAD 0x21 //读取当前3路AD值
#define CP68_UserCommand_WriteTCalc 0x22 //写入温度计算系数
#define CP68_UserCommand_ReadPress 0x23 //写入温度计算系数
#define CP68_UserCommand_WriteQCalc 0x24 //写入流量计算系数
#define CP68_UserCommand_WriteDeviceParams 0x25 //写入温度计算系数
#endif


