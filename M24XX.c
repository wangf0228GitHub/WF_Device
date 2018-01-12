#include "HardwareProfile.h"
#include "M24XX.h"
#ifdef SimI2C
#include "SimI2C.h"
#endif

//uchar  Reeprom[5];

#ifdef SimI2C
void M24XX_Init(void)
{
	SimI2C_Init();
#ifdef M24XX_WP_W
	M24XX_WP_IO=0;
	M24XX_WP_W=0;
#endif
}
#ifdef M24XX_1024
unsigned char M24XX_Read( unsigned char *pBuff,unsigned int Count,unsigned long Address )
#else
unsigned char M24XX_Read( unsigned char *pBuff,unsigned int Count,unsigned int Address )
#endif
{
	unsigned char ErrTimes=M24XX_RetryCount;	
	unsigned char AddrL,AddrH;
	unsigned char bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();
#ifdef M24XX_1024
		if(Address>0xffff)
			SimI2C_SendByte(M24XX_ADDR_W|0x02);//Ð´
		else
			SimI2C_SendByte(M24XX_ADDR_W);//Ð´
#else
		SimI2C_SendByte(M24XX_ADDR_W);//Ð´
#endif
		if(SimI2C_RecAck())
			continue;//ÎÞÓ¦´ð·µ»Øµ½Ñ­»·,±íÊ¾³ö´í
		AddrL=Address;
		AddrH=Address>>8;
		SimI2C_SendByte(AddrH);//Ð´¶ÁÐ´µØÖ·¸ß×Ö½Ú
		if(SimI2C_RecAck())
			continue;
		SimI2C_SendByte(AddrL);//Ð´¶ÁÐ´µØÖ·µÍ×Ö½Ú
		if(SimI2C_RecAck())
			continue;
		SimI2C_Start();
#ifdef M24XX_1024
		if(Address>0xffff)
			SimI2C_SendByte(M24XX_ADDR_R|0x02);//¶Á
		else
			SimI2C_SendByte(M24XX_ADDR_R);//¶Á
#else
		SimI2C_SendByte(M24XX_ADDR_R);//¶Á
#endif
		if(SimI2C_RecAck())
			continue;
		while(--Count)
		{
			*pBuff=SimI2C_ReadByte();
			pBuff++;
			SimI2C_Ack();
		}
		*pBuff=SimI2C_ReadByte();//read last byte data
		SimI2C_NoAck();
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
#ifdef M24XX_1024
unsigned char M24XX_Write( unsigned char *pBuff,unsigned int Count,unsigned long Address )
#else
unsigned char M24XX_Write( unsigned char *pBuff,unsigned char Count,unsigned int Address )
#endif
{
	unsigned char AddrH;
	unsigned char AddrL;
#ifdef M24XX_1024
	unsigned int N;
#else
	unsigned char N;
#endif
	unsigned char* pB;
	unsigned char ErrTimes=M24XX_RetryCount;
	unsigned char bRight=0;	
	while(ErrTimes--)
	{
		SimI2C_Start();		
#ifdef M24XX_1024
		if(Address>0xffff)
			SimI2C_SendByte(M24XX_ADDR_W|0x02);//Ð´
		else
			SimI2C_SendByte(M24XX_ADDR_W);//Ð´
#else
		SimI2C_SendByte(M24XX_ADDR_W);//Ð´
#endif
		if(SimI2C_RecAck())
			continue;//ÎÞÓ¦´ð·µ»Øµ½Ñ­»·
		AddrL=Address;
		AddrH=Address>>8;
		SimI2C_SendByte(AddrH);           //Ð´¶ÁÐ´µØÖ·¸ß×Ö½Ú
		if(SimI2C_RecAck())
			continue;
		SimI2C_SendByte(AddrL);              //Ð´¶ÁÐ´µØÖ·µÍ×Ö½Ú
		if(SimI2C_RecAck())
			continue;
#ifdef M24XX_WP_W
//		__delay_us(500);
 		M24XX_WP_W=0;
 		__delay_us(5);
#endif		
		N=Count;
		bRight=1;//********clr bErr
		pB=pBuff;
		while(N--)
		{
			SimI2C_SendByte(*pB);
			pB++;
			if(!SimI2C_RecAck())
				continue;
			bRight=0;
			break;
		}
		if(bRight==0)
			continue;
		break;		
	}
	SimI2C_Stop();
	__delay_us(5);
#ifdef M24XX_WP_W
// 	__delay_ms(20);
 	M24XX_WP_W=1;
 	__delay_us(5);
#endif
	return bRight;
}
#endif

