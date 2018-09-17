#ifndef __SX1276_LORA_Conf_h__
#define __SX1276_LORA_Conf_h__

#include "gpio.h"
#include "wfSys.h"
#include "SimSPI.h"
#define bool _Bool
#define true    1
#define false   0

#define SX1276_CSN_Low() HAL_GPIO_WritePin(RF_CSN_GPIO_Port,RF_CSN_Pin,GPIO_PIN_RESET)
#define SX1276_CSN_High() HAL_GPIO_WritePin(RF_CSN_GPIO_Port,RF_CSN_Pin,GPIO_PIN_SET)

#define SX1276_RST_Low() HAL_GPIO_WritePin(RF_SDN_GPIO_Port,RF_SDN_Pin,GPIO_PIN_RESET)
#define SX1276_RST_High() HAL_GPIO_WritePin(RF_SDN_GPIO_Port,RF_SDN_Pin,GPIO_PIN_SET)


#define  SX1276_SPIProc(x) SimSPI_Proc(x);     

#endif


