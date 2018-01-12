#ifndef __I2CDefs_h__
#define __I2CDefs_h__

typedef enum _I2C_STATE
{
	I2C_S=0,
	I2C_RCACK,
	I2C_TXACK,
	I2C_TXNOACK,
	I2C_READ,
	I2C_RS,
	I2C_P,
	I2C_BUSY=0xf0,
	I2C_IDLE=0xf1
} I2C_STATE;

/************************************************************************/
/* 第一个为最低位                                                       */
/************************************************************************/
typedef union   
{
	struct
	{		
		unsigned Write:1;
		unsigned WriteAddrH:1;
		unsigned WriteAddrL:1;
		unsigned RS:1;
		unsigned Wait:1;
	}Bits;
	unsigned char AllFlag;
}I2CFlags;        // general flags
#endif // __I2CDefs_h__
