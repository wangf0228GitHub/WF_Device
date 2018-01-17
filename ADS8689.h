#ifndef __ADS8689_h__
#define __ADS8689_h__

#include "main.h"
#include "TypeDefine.h"

void ADS8689_Setting(uint8_t reg,uint16_t data);
u16_wf ADS8689_ReadReg(uint8_t reg);
u32_wf ADS8689_ReadResult(void);
#endif

