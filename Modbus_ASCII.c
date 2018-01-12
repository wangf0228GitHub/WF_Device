#include <stdafx.h>
unsigned char Modbus_ASCII_Inner_RxBuffer[(Modbus_ASCII_RxBufLen<<1)+7];
unsigned char Modbus_ASCII_Inner_TxBuffer[(Modbus_ASCII_TxBufLen<<1)+7];
unsigned char Modbus_ASCII_Inner_RxCount;
unsigned char Modbus_ASCII_Slave_Addr;
unsigned char Modbus_ASCII_RxBuffer[Modbus_ASCII_RxBufLen];
unsigned char Modbus_ASCII_TxBuffer[Modbus_ASCII_TxBufLen];
unsigned char Modbus_ASCII_RxCount;
void Modbus_ASCII_Init(void)
{
	unsigned char i;
	for(i=0;i<Modbus_ASCII_RxBufLen;i++)
	{
		Modbus_ASCII_RxBuffer[i]=0;
	}
	for(i=0;i<(Modbus_ASCII_RxBufLen<<1)+5;i++)
	{
		Modbus_ASCII_Inner_RxBuffer[i]=0;
	}
	for(i=0;i<Modbus_ASCII_TxBufLen;i++)
	{
		Modbus_ASCII_TxBuffer[i]=0;
	}
	for(i=0;i<(Modbus_ASCII_TxBufLen<<1)+5;i++)
	{
		Modbus_ASCII_Inner_TxBuffer[i]=0;
	}	
	Modbus_ASCII_Inner_TxBuffer[0]=':';	
#ifdef Modbus_ASCII_Slave
	Byte2ASCII(Modbus_ASCII_Slave_Addr,&Modbus_ASCII_Inner_TxBuffer[1],&Modbus_ASCII_Inner_TxBuffer[2]);
#endif
}
void Modbus_ASCII_RxCommand(unsigned char rx)
{
	unsigned char i;
	if(gFlags.Modbus_ASCII_Rx)
		return;
	Modbus_ASCII_Inner_RxBuffer[Modbus_ASCII_Inner_RxCount++]=rx;
	if(Modbus_ASCII_Inner_RxCount==1)
	{
		if(Modbus_ASCII_Inner_RxBuffer[0]==':')
		{
			//收到头，则启动计时1s，若在1s中未收到完整帧，则放弃之前收到的数据
			//Modbus_ASCII_Slave_Timer();
		}
		else
			Modbus_ASCII_Inner_RxCount=0;
	}
	else if(Modbus_ASCII_Inner_RxCount==3)
	{
		i=ASCII2Byte_Capital(Modbus_ASCII_Inner_RxBuffer[1],Modbus_ASCII_Inner_RxBuffer[2]);
		if(i!=0 && i!=Modbus_ASCII_Slave_Addr)//地址相同
			Modbus_ASCII_Inner_RxCount=0;
	}
	else if(rx==0x0a)
	{
		if(Modbus_ASCII_Inner_RxBuffer[Modbus_ASCII_Inner_RxCount-2]==0x0d)//收到结束位
		{		
			Modbus_ASCII_RxCount=Modbus_ASCII_Inner_RxCount-3;
			Modbus_ASCII_RxCount=Modbus_ASCII_RxCount>>1;
			for(i=0;i<Modbus_ASCII_RxCount;i++)
				Modbus_ASCII_RxBuffer[i]=ASCII2Byte_Capital(Modbus_ASCII_Inner_RxBuffer[1+(i<<1)],Modbus_ASCII_Inner_RxBuffer[1+(i<<1)+1]);
			gFlags.Modbus_ASCII_Rx=1;
			Modbus_ASCII_Inner_RxCount=0;
		}
		else
			Modbus_ASCII_Inner_RxCount=0;
	}
}
#ifdef Modbus_ASCII_Slave
void Modbus_ASCII_TxCommand(unsigned char len)
{
	unsigned char i;
	for(i=0;i<len;i++)
		Byte2ASCII(Modbus_ASCII_TxBuffer[i],&Modbus_ASCII_Inner_TxBuffer[3+(i<<1)],&Modbus_ASCII_Inner_TxBuffer[3+(i<<1)+1]);
	i=GetVerify_Sum(Modbus_ASCII_TxBuffer,len);
	i=i+Modbus_ASCII_Slave_Addr;
	Byte2ASCII(i,&Modbus_ASCII_Inner_TxBuffer[(len<<1)+3],&Modbus_ASCII_Inner_TxBuffer[(len<<1)+4]);
	Modbus_ASCII_Inner_TxBuffer[(len<<1)+5]=0x0d;
	Modbus_ASCII_Inner_TxBuffer[(len<<1)+6]=0x0a;
	for(i=0;i<(len<<1)+7;i++)
	{
#ifdef Modbus_Parity_None
		Modbus_ASCII_Inner_TxBuffer[i] |= 0x80;
#endif		
	}
	UartTxQueue1_AddBytes(Modbus_ASCII_Inner_TxBuffer,(len<<1)+7);
}	
#endif
