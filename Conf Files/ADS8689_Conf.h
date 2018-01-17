#ifndef __ADS8689_Conf_h__
#define __ADS8689_Conf_h__

#include "gpio.h"
#include "SimSPI.h"

#define ADS8689_CS_Low() HAL_GPIO_WritePin(AD_CS_GPIO_Port,AD_CS_Pin,GPIO_PIN_RESET)
#define ADS8689_CS_High() HAL_GPIO_WritePin(AD_CS_GPIO_Port,AD_CS_Pin,GPIO_PIN_SET)

#define ADS8689_RVS_Read() HAL_GPIO_ReadPin(AD_RVS_GPIO_Port,AD_RVS_Pin)

#define ADS8689_SPIProc(x) SimSPI2_Proc(x)

#endif


