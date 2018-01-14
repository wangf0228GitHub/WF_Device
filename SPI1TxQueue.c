#include "HardwareProfile.h"
#include "SPI1TxQueue.h"
//#define Uart1_BRGVAL ((FCY/Uart1_BAUDRATE)/4)-1

uint8_t SPI1TxQueue[SPI1TxQueueLen];
uint8_t *pSPI1In, *pSPI1Out;

void SPI1TxStart()
{	
	if(__SPI1TBF==0)   //发送寄存器为空    
	{
		__SPI1TXREG=*pSPI1Out;
		pSPI1Out++;
		if (pSPI1Out == (SPI1TxQueue+SPI1TxQueueLen))
			pSPI1Out = SPI1TxQueue;	
	}		
}
void SPI1AddStr(const char* pt)
{
	const char *p;
	p = pt;
	while (*p != '\0')                         //逐个放入缓冲区
	{
		SPI1AddByte(*p++);
	}
}
void SPI1AddByte(uint8_t tx)
{
	uint8_t *d;
	d = pSPI1In;
	d++;
	if (d == (SPI1TxQueue+SPI1TxQueueLen))         //回绕
		d = SPI1TxQueue;
	while(d == pSPI1Out);         //TxBuf满
	*pSPI1In = tx;  //放入一个数据
	pSPI1In = d;    //inTxBuf后移
	SPI1TxStart();
}
void SPI1AddBytes(const void *tx, size_t size, size_t n)
{
	size_t count = size * n;
	uint8_t *s;
	if(count==0)
		return;
	s = (uint8_t*)tx;
	while (count--)                         //逐个放入缓冲区
	{
		SPI1AddByte(*s++);
	}
}
void SPI1TxQueueInterrupt(void)
{	
	if (pSPI1Out == pSPI1In)             //TxBuf空
	{		
		return;
	}	
	__SPI1TXREG=*pSPI1Out;
	pSPI1Out++;
	if (pSPI1Out == (SPI1TxQueue+SPI1TxQueueLen))
		pSPI1Out = SPI1TxQueue;	
}
void InitSPI1TxQueue(void)
{
	pSPI1Out=pSPI1In=SPI1TxQueue;
}
