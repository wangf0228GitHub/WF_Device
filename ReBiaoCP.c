#include "HardwareProfile.h"

_ReBiaoCP_Flags ReBiaoCP_Flags;
unsigned char ReBiaoCP_RxList[MAX_ReBiaoCP_RX];
unsigned char ReBiaoCP_RxCount;
unsigned char ReBiaoCP_NeedRxCount;
uint ReBiaoCP_WaitClientAddr;
unsigned char ReBiaoCP_WaitCommand;
unsigned int ReBiaoCP_WaitClientTick;
//unsigned char ReBiaoCP_RxErrTimes;
unsigned int ReBiaoCP_WaitClientTime;
unsigned char ReBiaoCP_RetryTimes;

void Init_ReBiaoCP(void)
{
	SetTx_ReBiaoCP();
	ReBiaoCP_WaitClientTime=3;
	ReBiaoCP_RetryTimes=3;
	//SetCOM1TX();
//	/while(1)
//	{
//		Uart_PutChar(0xff);
//	}
}
void ProcRx_ReBiaoCP(unsigned char rx)
{
	if(ReBiaoCP_Flags.bRx)//之前没处理完
		return;
	if(!ReBiaoCP_Flags.bWaitDataFromClient)//当前没在等待
		return;
	ReBiaoCP_RxList[ReBiaoCP_RxCount++]=rx;
	if(ReBiaoCP_RxCount>7)
	{
		if(rx==0x16 && ReBiaoCP_RxCount==ReBiaoCP_NeedRxCount)
		{			
			ReBiaoCP_Flags.bRx=1;			
		}
		else if(ReBiaoCP_RxCount>ReBiaoCP_NeedRxCount)
		{
			ReBiaoCP_RxCount=0;
			ReBiaoCP_NeedRxCount=0xff;
		}
		else if(ReBiaoCP_RxCount>MAX_ReBiaoCP_RX)
		{
			ReBiaoCP_RxCount=0;
			ReBiaoCP_NeedRxCount=0xff;				
		}
	}
// 	else if(ReBiaoCP_RxCount==7)//控制信息字段
// 	{
// 		
// 	}
// 	else if(ReBiaoCP_RxCount==6)//判断地址
// 	{
// 		if(rx!=ReBiaoCP_WaitCommand)
// 		{
// 			ReBiaoCP_RxCount=0;
// 		}
// 	}
// 	else if(ReBiaoCP_RxCount==5)//判断命令
// 	{
// 		if(rx!=ReBiaoCP_WaitClientAddr.u8L)
// 		{
// 			ReBiaoCP_RxCount=0;
// 		}
// 	}
	else if(ReBiaoCP_RxCount==3)
	{
		if(ReBiaoCP_RxList[1]==ReBiaoCP_RxList[2])
		{
			ReBiaoCP_NeedRxCount=ReBiaoCP_RxList[1]+6;
		}
		else
			ReBiaoCP_RxCount=0;
	}
	else if(ReBiaoCP_RxCount==1)
	{
		if(rx!=0x68)
		{
			ReBiaoCP_RxCount=0;
		}
	}	
}
// void ReBiaoCPSendData(unsigned int Addr,unsigned char Command,unsigned char* pBuff,unsigned int Count)
// {
// 	unsigned char sum;
// 	unsigned int i;
// 	ReBiaoCP_WaitClientAddr.u16=Addr;
// 	ReBiaoCP_WaitCommand=Command;
// 	SetTx_ReBiaoCP();
// 	sum=0;
// 	ReBiaoCP_AddTxHeader();
// 	ReBiaoCP_TxByteWithVerify(HIGH_BYTE(Count));
// 	ReBiaoCP_TxByteWithVerify(LOW_BYTE(Count));
// 	for(i=0;i<Count;i++)
// 	{
// 		ReBiaoCP_TxByteWithVerify(pBuff[i]);	
// 	}
// 	ReBiaoCP_AddTxEnder();
// 	SetRx_ReBiaoCP();
// 	ReBiaoCP_Flags.bRx=0;
// 	ReBiaoCP_WaitClientTick=SystemTick;
// 	ReBiaoCP_RxCount=0;
// //	ReBiaoCP_RxErrTimes=0;
// 	ReBiaoCP_NeedRxCount=0xff;
// 	ReBiaoCP_Flags.bWaitDataFromClient=1;
// }
// unsigned char ReBiaoCPWaitClientData(unsigned int Addr,unsigned char Command,unsigned char* pBuff,unsigned int Count)
// {	
// 	unsigned char sum,retry;
// 	unsigned char ret;
// 	unsigned int i;
// 	ret=0;
// 	ReBiaoCP_WaitClientAddr.u16=Addr;
// 	ReBiaoCP_WaitCommand=Command;
// 	retry=ReBiaoCP_RetryTimes;
// 	while(retry!=0)
// 	{
// 		SetTx_ReBiaoCP();
// 		sum=0;
// 		ReBiaoCP_AddTxHeader();
// 		ReBiaoCP_TxByteWithVerify(HIGH_BYTE(Count));
// 		ReBiaoCP_TxByteWithVerify(LOW_BYTE(Count));
// 		for(i=0;i<Count;i++)
// 		{
// 			ReBiaoCP_TxByteWithVerify(pBuff[i]);	
// 		}
// 		ReBiaoCP_AddTxEnder();
// 		SetRx_ReBiaoCP();
// 		ReBiaoCP_Flags.bRx=0;
// 		ReBiaoCP_WaitClientTick=SystemTick;
// 		ReBiaoCP_RxCount=0;
// 		//ReBiaoCP_RxErrTimes=0;
// 		ReBiaoCP_NeedRxCount=0xff;
// 		ReBiaoCP_Flags.bWaitDataFromClient=1;
// 		while(1)
// 		{
// 			if(ReBiaoCP_Flags.bRx)
// 				break;
// 			if((SystemTick-ReBiaoCP_WaitClientTick)>ReBiaoCP_WaitClientTime)//200ms等待超时
// 				break;
// 		}
// 		ReBiaoCP_Flags.bWaitDataFromClient=0;
// 		if(ReBiaoCP_Flags.bRx)
// 		{
// 			ret=1;
// 			break;
// 		}
// 		ReBiaoCP_WaitClientInterval();
// 		retry--;
// 	}
// 	SetTx_ReBiaoCP();
// 	return ret;
// }

unsigned char ReBiaoCP_Read10(unsigned char Addr)
{	
	unsigned char CS,retry;
	unsigned char ret;
	unsigned int i;
	ret=0;
	ReBiaoCP_WaitClientAddr.u16=Addr;
	retry=ReBiaoCP_RetryTimes;
	while(retry!=0)
	{
		//SetTx_ReBiaoCP();
		ReBiaoCP_TxByte(0x10);
		ReBiaoCP_TxByte(0x5b);
		ReBiaoCP_TxByte(Addr);
		CS=(unsigned char)(0x5b+Addr);
		ReBiaoCP_TxByte(CS);
		ReBiaoCP_TxByte(0x16);
		//SetRx_ReBiaoCP();
		ReBiaoCP_Flags.bRx=0;
		ReBiaoCP_WaitClientTick=SystemTick;
		ReBiaoCP_RxCount=0;
		//ReBiaoCP_RxErrTimes=0;
		ReBiaoCP_NeedRxCount=0xff;
		ReBiaoCP_Flags.bWaitDataFromClient=1;
		while(1)
		{
			if(ReBiaoCP_Flags.bRx)
				break;
			if((SystemTick-ReBiaoCP_WaitClientTick)>ReBiaoCP_WaitClientTime)//200ms等待超时
				break;
		}
		ReBiaoCP_Flags.bWaitDataFromClient=0;
		if(ReBiaoCP_Flags.bRx)
		{
			ret=1;
			break;
		}
		ReBiaoCP_WaitClientInterval();
		retry--;
	}
	//SetTx_ReBiaoCP();
	return ret;
}
