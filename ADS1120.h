#ifndef __ADS1120_h__
#define __ADS1120_h__

#ifndef ADS1120_RetryCount
#define ADS1120_RetryCount 2
#endif

#ifndef ADS1120_ADDR_W
#define  ADS1120_ADDR_W	0x90//寻址字节写
#endif
#ifndef ADS1120_ADDR_R
#define  ADS1120_ADDR_R	0x91//寻址字节读
#endif
void ADS1120_Init(void);
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
} _ADS1120_Status;
extern uint ADS1120_Result;
extern _ADS1120_Status ADS1120_Status;
unsigned char ADS1120_Read(void);
unsigned char ADS1120_Write(void);

#endif

