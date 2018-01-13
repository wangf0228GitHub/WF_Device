#ifndef __ADS1112_h__
#define __ADS1112_h__

#include "TypeDefine.h"

#ifndef ADS1112_RetryCount
#define ADS1112_RetryCount 2
#endif

#ifndef ADS1112_ADDR_W
#define  ADS1112_ADDR_W	0x90//寻址字节写
#endif
#ifndef ADS1112_ADDR_R
#define  ADS1112_ADDR_R	0x91//寻址字节读
#endif
void ADS1112_Init(void);
typedef union   
{
	struct
	{
		unsigned PGA:2;	
		unsigned DR:2;
		unsigned SC:1;
		unsigned INP:2;//是否进入菜单
		unsigned ST_DRDY:1;//菜单状态，0等温，1变温
	};
	unsigned char AllFlag;
} _ADS1112_Status;
extern ushort_wf ADS1112_Result;
extern _ADS1112_Status ADS1112_Status;
unsigned char ADS1112_Read(void);
unsigned char ADS1112_Write(void);

#endif

