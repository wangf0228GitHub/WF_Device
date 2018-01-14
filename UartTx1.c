#include "HardwareProfile.h"
//#define Uart1_BRGVAL ((FCY/Uart1_BAUDRATE)/4)-1

uint8_t UartTxQueueBuf[UartTxQueue_BufLen];
uint8_t *pInUartTxQueueBuf, *pOutUartTxQueueBuf;
void UartTxQueue_TxStart()
{	
	if (Uart_TXIF && !Uart_TXIE)        
	{
		Uart_TXIE=1;
		gFlags.bUartTxQueueFinish=0;
	}		
}
void UartTxQueue_AddStr(const char* pt)
{
	const char *p;
	p = pt;
	while (*p != '\0')                         //逐个放入缓冲区
	{
		UartTxQueue_AddByte(*p++);
	}
}
void UartTxQueue_AddByte(uint8_t tx)
{
	uint8_t *d;
	d = pInUartTxQueueBuf;
	d++;
	if (d == (UartTxQueueBuf+UartTxQueue_BufLen))         //回绕
		d = UartTxQueueBuf;
	while(d == pOutUartTxQueueBuf);         //TxBuf满
	*pInUartTxQueueBuf = tx;  //放入一个数据
	pInUartTxQueueBuf = d;    //inTxBuf后移
	UartTxQueue_TxStart();
}
void UartTxQueue_AddBytes(const void *tx, uint8_t size, uint16_t n)
{
	uint16_t count = size * n;
	uint8_t *s;
	if(count==0)
		return;
	s = (uint8_t*)tx;
	while (count--)                         //逐个放入缓冲区
	{
		UartTxQueue_AddByte(*s++);
	}
}
void UartTxQueue_Interrupt(void)
{	
	if (pOutUartTxQueueBuf == pInUartTxQueueBuf)             //TxBuf空
	{
		Uart_TXIE=0;
		gFlags.bUartTxQueueFinish=1;
		return;
	}
	//UartTx1_TXIF=0;
	UartTx1_TXREG=*pOutUartTxQueueBuf;
	pOutUartTxQueueBuf++;
	if (pOutUartTxQueueBuf == (UartTxQueueBuf+UartTxQueue_BufLen))
		pOutUartTxQueueBuf = UartTxQueueBuf;	
}
void UartTxQueue_Init( void )
{
	// 	U1MODE=0;
	// 	//U1MODEbits.UFRZ=1;//仿真器处于调试模式时，模块停止工作
	// 	U1MODEbits.USIDL=1;//当器件进入空闲模式时，模块停止工作							
	// 	U1MODEbits.BRGH=1;//高速
	// 	U1STA=0;
	// 	//U2STAbits.UTXINV=0;//UxTX 的空闲状态为1
	// 
	// 	U1BRG=Uart1_BRGVAL;//38400(8MHz)
	// 	U1MODEbits.UARTEN=1;
	// 	U1STAbits.UTXEN=1;//使能UARTx 发送器，由UARTx 控制UxTX 引脚（如果UARTEN = 1）
	pInUartTxQueueBuf=pOutUartTxQueueBuf=UartTxQueueBuf;
}

