#ifndef __SIMI2C_Conf_h__
#define __SIMI2C_Conf_h__

#include "gpio.h"
#include "wfSys.h"

#define SimI2C_Delay_Ex
#define SimI2C_Delay() wfDelay_ms(1);


#define SIMI2C_SCL_Low() HAL_GPIO_WritePin(SimI2C_SCL_GPIO_Port,SimI2C_SCL_Pin,GPIO_PIN_RESET)
#define SIMI2C_SCL_High() HAL_GPIO_WritePin(SimI2C_SCL_GPIO_Port,SimI2C_SCL_Pin,GPIO_PIN_SET)

#define SIMI2C_SDA_Low() HAL_GPIO_WritePin(SimI2C_SDA_GPIO_Port,SimI2C_SDA_Pin,GPIO_PIN_RESET)
#define SIMI2C_SDA_High() HAL_GPIO_WritePin(SimI2C_SDA_GPIO_Port,SimI2C_SDA_Pin,GPIO_PIN_SET)

#define SIMI2C_SDA_Read() HAL_GPIO_ReadPin(SimI2C_SDA_GPIO_Port,SimI2C_SDA_Pin)
#endif


