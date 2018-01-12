#include "HardwareProfile.h"
#include "afx.h"
#include "Uart2.h"
#ifdef Uart2_ParityVerifyType
unsigned char Uart2_ParityVerifyType;
unsigned char Uart2_GetVerifyBit(unsigned char data)
{
	unsigned char i,d,c,b,ret;
	if(Uart2_ParityVerifyType==Uart2_ParityVerify_High)
		ret=1;
	else if(Uart2_ParityVerifyType==Uart2_ParityVerify_Low)
		ret=0;
	else 
	{
		d=data;
		c=0;
		for(i=0;i<8;i++)
		{
			b=d&0x01;
			if(b==1)
				c++;
			d=d>>1;
		}		
		if(c%2==0)
		{
			if(Uart2_ParityVerifyType==Uart2_ParityVerify_Even)//偶校验
				ret=0;
			else
				ret=1;
		}
		else
		{
			if(Uart2_ParityVerifyType==Uart2_ParityVerify_Even)//偶校验
				ret=1;
			else
				ret=0;
		}
	}	
	return ret;
}
#endif
void Uart2_PutChar(unsigned char c )
{
	while(Uart2_TRMT==0);
#ifdef Uart2_ParityVerifyType
	Uart2_Tx9D=Uart2_GetVerifyBit(c);
#endif
	Uart2_TXREG=c;
}

void Uart2_PutString(const char* pString )
{
	char c;
	while(1)
	{
		c=*pString;
		if(c=='\0')
			break;
		Uart2_PutChar(c);
		pString++;
	}
}


void Uart2_PutHex(unsigned char c )
{
	unsigned char  b;
	b=HIGH_NIBBLE(c);
	if (b>9) 
		b += 'A'-10;
	else 
		b += '0';
	Uart2_PutChar(b);
	b=LOW_NIBBLE(c);
	if (b>9) 
		b += 'A'-10;
	else 
		b += '0';
	Uart2_PutChar(b);
}
#ifdef Uart2TxQueue
unsigned char Uart2TxQueueBuf[Uart2TxQueue_BufLen];
unsigned char *pInUart2TxQueueBuf, *pOutUart2TxQueueBuf;
void Uart2TxQueue_TxStart()
{	
	if (Uart2_TXIF && !Uart2_TXIE)        
	{
		Uart2_TXIE=1;
		gFlags.bUart2TxQueueFinish=0;
	}		
}
void Uart2TxQueue_AddStr(const char* pt)
{
	const char *p;
	p = pt;
	while (*p != '\0')                         //逐个放入缓冲区
	{
		Uart2TxQueue_AddByte(*p++);
	}
}

void Uart2TxQueue_AddByte(unsigned char tx)
{
	unsigned char *d;
	d = pInUart2TxQueueBuf;
	d++;
	if (d == (Uart2TxQueueBuf+Uart2TxQueue_BufLen))         //回绕
		d = Uart2TxQueueBuf;
	while(d == pOutUart2TxQueueBuf);         //TxBuf满
	*pInUart2TxQueueBuf = tx;  //放入一个数据
	pInUart2TxQueueBuf = d;    //inTxBuf后移
	Uart2TxQueue_TxStart();
}
void Uart2TxQueue_AddBytes(const void *tx, unsigned char size, unsigned int n)
{
	unsigned int count = size * n;
	unsigned char *s;
	if(count==0)
		return;
	s = (unsigned char*)tx;
	while (count--)                         //逐个放入缓冲区
	{
		Uart2TxQueue_AddByte(*s++);
	}
}
void Uart2TxQueue_Interrupt(void)
{	
	if (pOutUart2TxQueueBuf == pInUart2TxQueueBuf)             //TxBuf空
	{
		Uart2_TXIE=0;
		gFlags.bUart2TxQueueFinish=1;
		return;
	}
	//Uart2_TXIF=0;
#ifdef Uart2_ParityVerifyType
	Uart2_Tx9D=Uart2_GetVerifyBit(*pOutUart2TxQueueBuf);
#endif
	Uart2_TXREG=*pOutUart2TxQueueBuf;
	pOutUart2TxQueueBuf++;
	if (pOutUart2TxQueueBuf == (Uart2TxQueueBuf+Uart2TxQueue_BufLen))
		pOutUart2TxQueueBuf = Uart2TxQueueBuf;	
}
void Uart2TxQueue_Init( void )
{	
	pInUart2TxQueueBuf=pOutUart2TxQueueBuf=Uart2TxQueueBuf;
}
#endif




