#include "CP1616_Master.h"
#include "wfDefine.h"
volatile _CP1616_Master_Flags CP1616_Master_Flags;
uint8_t CP1616_Master_RxList[MAX_CP1616_Master_RX];

#if CP1616_Master_DataBufLen==1
	uint8_t CP1616_Master_RxCount;
	uint8_t CP1616_Master_NeedRxCount;	
#else
	uint16_t CP1616_Master_RxCount;
	uint16_t CP1616_Master_NeedRxCount;	
#endif


#if CP1616_Master_AddrLen==1
	uint8_t CP1616_Master_Addr;
	uint8_t CP1616_Master_WaitClientAddr;
#elif CP1616_Master_AddrLen==2
	uint16_t CP1616_Master_Addr;
	uint16_t CP1616_Master_WaitClientAddr;
#endif

uint8_t CP1616_Master_WaitCommand;
uint16_t CP1616_Master_WaitClientTick;
//uint8_t CP1616_Master_RxErrTimes;
uint16_t CP1616_Master_WaitClientTime;
uint8_t CP1616_Master_RetryTimes;

#ifndef CP1616_Master_Tx_OneByOne
uint8_t CP1616_Master_TxList[CP1616_Master_TxList_LenMax];
#endif
void CP1616_Master_Init(void)
{
	CP1616_Master_SetTx();
	CP1616_Master_WaitClientTime=3;
	CP1616_Master_RetryTimes=3;
}
void CP1616_Master_ProcRx(uint8_t rx)
{
#ifdef CP1616_Master_NeedCheckVerify
	uint8_t sum;
#endif
	if(CP1616_Master_Flags.Bits.bRx)//之前没处理完
		return;
	if(!CP1616_Master_Flags.Bits.bWaitDataFromClient)//当前没在等待
		return;
	CP1616_Master_RxList[CP1616_Master_RxCount++]=rx;
	if(CP1616_Master_RxCount>7)
	{
		if(rx==0x0d && CP1616_Master_RxCount==CP1616_Master_NeedRxCount)
		{			
#ifdef CP1616_Master_NeedCheckVerify
			sum=CP1616_Master_VerifyProc(CP1616_Master_RxList,CP1616_Master_NeedRxCount-2);
			if(sum==CP1616_Master_RxList[CP1616_Master_NeedRxCount-2])	
			{
				CP1616_Master_Flags.Bits.bRx=1;
			}
			else
			{
				CP1616_Master_RxCount=0;
			}
#else
			CP1616_Master_Flags.Bits.bRx=1;
#endif		
		}
		else if(CP1616_Master_RxCount>CP1616_Master_NeedRxCount)
		{
			CP1616_Master_RxCount=0;
#if CP1616_Master_DataBufLen==1
			CP1616_Master_NeedRxCount=0xff;
#else
			CP1616_Master_NeedRxCount=0xffff;
#endif
		}
		else if(CP1616_Master_RxCount>MAX_CP1616_Master_RX)
		{
			CP1616_Master_RxCount=0;
#if CP1616_Master_DataBufLen==1
			CP1616_Master_NeedRxCount=0xff;
#else
			CP1616_Master_NeedRxCount=0xffff;
#endif				
		}
	}
	else if(CP1616_Master_RxCount==pCP1616_MasterData)//生成帧长度
	{
#if CP1616_Master_DataBufLen==1
		CP1616_Master_NeedRxCount=CP1616_Master_RxList[pCP1616_MasterData-1]+pCP1616_MasterData+2;
#else
		CP1616_Master_NeedRxCount=MAKE_SHORT(CP1616_Master_RxList[pCP1616_MasterData-2],CP1616_Master_RxList[pCP1616_MasterData-1])+pCP1616_MasterData+2;
#endif
		if(CP1616_Master_NeedRxCount>CP1616_Master_RxList_LenMax)
		{
			CP1616_Master_RxCount=0;
#if CP1616_Master_DataBufLen==1
			CP1616_Master_NeedRxCount=0xff;
#else
			CP1616_Master_NeedRxCount=0xffff;
#endif
		}		
	}
#if CP1616_Master_AddrLen==1
	else if(CP1616_Master_RxCount==4)//判断命令
	{
		if(rx!=CP1616_Master_WaitCommand)
		{
			CP1616_Master_RxCount=0;
		}
	}
	else if(CP1616_Master_RxCount==3)//判断地址
	{
		//地址不符，退出当前接收状态	
		if(rx!=CP1616_Master_WaitClientAddr)
		{
			CP1616_Master_RxCount=0;
		}		
	}
#elif CP1616_Master_AddrLen==2
	else if(CP1616_Master_RxCount==5)//判断命令
	{
		if(rx!=CP1616_Master_WaitCommand)
		{
			CP1616_Master_RxCount=0;
		}
	}
	else if(CP1616_Master_RxCount==4)//判断地址
	{
		//地址不符，退出当前接收状态	
		if(CP1616_Master_RxList[2]!=HIGH_BYTE(CP1616_Master_WaitClientAddr) || CP1616_Master_RxList[3]!=LOW_BYTE(CP1616_Master_WaitClientAddr))
		{
			CP1616_Master_RxCount=0;
		}		
	}
#elif CP1616_Master_AddrLen==0
	else if(CP1616_Master_RxCount==3)//判断命令
	{
		if(rx!=CP1616_Master_WaitCommand)
		{
			CP1616_Master_RxCount=0;
		}
	}
#endif	
	else if(CP1616_Master_RxCount==2)
	{
		if(rx!=0x16)
		{
			CP1616_Master_RxCount=0;
		}
	}
	else if(CP1616_Master_RxCount==1)
	{
		if(rx!=0x16)
		{
			CP1616_Master_RxCount=0;
		}
	}		
}
#if (CP1616_Master_AddrLen==1) && (CP1616_Master_DataBufLen==1)
void CP1616_MasterSendData(uint8_t Addr,uint8_t Command,uint8_t* pBuff,uint8_t Count)
#elif (CP1616_Master_AddrLen==1) && (CP1616_Master_DataBufLen==2)
void CP1616_MasterSendData(uint8_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count)
#elif (CP1616_Master_AddrLen==2) && (CP1616_Master_DataBufLen==1)
void CP1616_MasterSendData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint8_t Count)
#elif (CP1616_Master_AddrLen==2) && (CP1616_Master_DataBufLen==2)
void CP1616_MasterSendData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count)
#elif (CP1616_Master_AddrLen==0) && (CP1616_Master_DataBufLen==1)
void CP1616_MasterSendData(uint8_t Command,uint8_t* pBuff,uint8_t Count)
#elif (CP1616_Master_AddrLen==0) && (CP1616_Master_DataBufLen==2)
void CP1616_MasterSendData(uint8_t Command,uint8_t* pBuff,uint16_t Count)
#endif
{
	uint8_t sum;
	uint16_t i;
#ifndef CP1616_Master_Tx_OneByOne
	uint16_t txIndex=0;
#endif
#if CP1616_Master_AddrLen!=0
	CP1616_Master_WaitClientAddr=Addr;
#endif	
	CP1616_Master_WaitCommand=Command;
	CP1616_Master_SetTx();
	sum=0;
	//帧头
#ifdef CP1616_Master_Tx_OneByOne
	CP1616_Master_TxByteWithVerify(0x16);
	CP1616_Master_TxByteWithVerify(0x16);
#if CP1616_Master_AddrLen==1
	CP1616_Master_TxByteWithVerify(Addr);
#elif CP1616_Master_AddrLen==2
	CP1616_Master_TxByteWithVerify(HIGH_BYTE(Addr));
	CP1616_Master_TxByteWithVerify(LOW_BYTE(Addr));
#endif
	CP1616_Master_TxByteWithVerify(Command);

#if CP1616_Master_DataBufLen==1
	CP1616_Master_TxByteWithVerify(Count);
#else
	CP1616_Master_TxByteWithVerify(HIGH_BYTE(Count));
	CP1616_Master_TxByteWithVerify(LOW_BYTE(Count));
#endif
	for(i=0;i<Count;i++)
	{
		CP1616_Master_TxByteWithVerify(pBuff[i]);
	}
	CP1616_Master_TxByte(sum);
	CP1616_Master_TxByte(0x0d);
#else//数组发送
	CP1616_Master_TxList[txIndex++]=0x16;
	CP1616_Master_TxList[txIndex++]=0x16;
#if CP1616_Master_AddrLen==1
	CP1616_Master_TxList[txIndex++]=Addr;
#elif CP1616_Master_AddrLen==2
	CP1616_Master_TxList[txIndex++]=HIGH_BYTE(Addr);
	CP1616_Master_TxList[txIndex++]=LOW_BYTE(Addr);
#endif
	CP1616_Master_TxList[txIndex++]=CommandIndex;

#if CP1616_Master_DataBufLen==1
	CP1616_Master_TxList[txIndex++]=Count;
#else
	CP1616_Master_TxList[txIndex++]=HIGH_BYTE(Count);
	CP1616_Master_TxList[txIndex++]=LOW_BYTE(Count);
#endif
	for(i=0;i<Count;i++)
	{
		CP1616_Master_TxList[txIndex++]=pBuff[i];
	}
	sum=CP1616_Master_VerifyProc(CP1616_Master_TxList,txIndex);
	CP1616_Master_TxList[txIndex++]=sum;
	CP1616_Master_TxList[txIndex++]=0x0d;
	CP1616_Master_TxProc(CP1616_Master_TxList,txIndex);
#endif	
	CP1616_Master_SetRx();
	CP1616_Master_Flags.Bits.bRx=0;
	CP1616_Master_WaitClientTick=SystemTick;
	CP1616_Master_RxCount=0;
#if CP1616_Master_DataBufLen==1
	CP1616_Master_NeedRxCount=0xff;
#else
	CP1616_Master_NeedRxCount=0xffff;
#endif
	CP1616_Master_Flags.Bits.bWaitDataFromClient=1;
}
#if (CP1616_Master_AddrLen==1) && (CP1616_Master_DataBufLen==1)
unsigned char CP1616_MasterWaitClientData(uint8_t Addr,uint8_t Command,uint8_t* pBuff,uint8_t Count)
#elif (CP1616_Master_AddrLen==1) && (CP1616_Master_DataBufLen==2)
unsigned char CP1616_MasterWaitClientData(uint8_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count)
#elif (CP1616_Master_AddrLen==2) && (CP1616_Master_DataBufLen==1)
unsigned char CP1616_MasterWaitClientData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint8_t Count)
#elif (CP1616_Master_AddrLen==2) && (CP1616_Master_DataBufLen==2)
unsigned char CP1616_MasterWaitClientData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count)
#elif (CP1616_Master_AddrLen==0) && (CP1616_Master_DataBufLen==1)
unsigned char CP1616_MasterWaitClientData(uint8_t Command,uint8_t* pBuff,uint8_t Count)
#elif (CP1616_Master_AddrLen==0) && (CP1616_Master_DataBufLen==2)
unsigned char CP1616_MasterWaitClientData(uint8_t Command,uint8_t* pBuff,uint16_t Count)
#endif
{	
	uint8_t sum,retry;
	uint8_t ret;
	uint16_t i;
#ifndef CP1616_Master_Tx_OneByOne
	uint16_t txIndex=0;
#endif
	ret=0;
#if CP1616_Master_AddrLen!=0
	CP1616_Master_WaitClientAddr=Addr;
#endif
	CP1616_Master_WaitCommand=Command;
	retry=CP1616_Master_RetryTimes;
	while(retry!=0)
	{
		CP1616_Master_SetTx();
		sum=0;
#ifdef CP1616_Master_Tx_OneByOne
		CP1616_Master_TxByteWithVerify(0x16);
		CP1616_Master_TxByteWithVerify(0x16);
#if CP1616_Master_AddrLen==1
		CP1616_Master_TxByteWithVerify(Addr);
#elif CP1616_Master_AddrLen==2
		CP1616_Master_TxByteWithVerify(HIGH_BYTE(Addr));
		CP1616_Master_TxByteWithVerify(LOW_BYTE(Addr));
#endif
		CP1616_Master_TxByteWithVerify(Command);

#if CP1616_Master_DataBufLen==1
		CP1616_Master_TxByteWithVerify(Count);
#else
		CP1616_Master_TxByteWithVerify(HIGH_BYTE(Count));
		CP1616_Master_TxByteWithVerify(LOW_BYTE(Count));
#endif
		for(i=0;i<Count;i++)
		{
			CP1616_Master_TxByteWithVerify(pBuff[i]);
		}
		CP1616_Master_TxByte(sum);
		CP1616_Master_TxByte(0x0d);
#else//数组发送
		CP1616_Master_TxList[txIndex++]=0x16;
		CP1616_Master_TxList[txIndex++]=0x16;
#if CP1616_Master_AddrLen==1
		CP1616_Master_TxList[txIndex++]=Addr;
#elif CP1616_Master_AddrLen==2
		CP1616_Master_TxList[txIndex++]=HIGH_BYTE(Addr);
		CP1616_Master_TxList[txIndex++]=LOW_BYTE(Addr);
#endif
		CP1616_Master_TxList[txIndex++]=CommandIndex;

#if CP1616_Master_DataBufLen==1
		CP1616_Master_TxList[txIndex++]=Count;
#else
		CP1616_Master_TxList[txIndex++]=HIGH_BYTE(Count);
		CP1616_Master_TxList[txIndex++]=LOW_BYTE(Count);
#endif
		for(i=0;i<Count;i++)
		{
			CP1616_Master_TxList[txIndex++]=pBuff[i];
		}
		sum=CP1616_Master_VerifyProc(CP1616_Master_TxList,txIndex);
		CP1616_Master_TxList[txIndex++]=sum;
		CP1616_Master_TxList[txIndex++]=0x0d;
		CP1616_Master_TxProc(CP1616_Master_TxList,txIndex);
#endif	
		CP1616_Master_SetRx();
		CP1616_Master_Flags.Bits.bRx=0;
		CP1616_Master_WaitClientTick=SystemTick;
		CP1616_Master_RxCount=0;
#if CP1616_Master_DataBufLen==1
		CP1616_Master_NeedRxCount=0xff;
#else
		CP1616_Master_NeedRxCount=0xffff;
#endif
		CP1616_Master_Flags.Bits.bWaitDataFromClient=1;
		while(1)
		{
			if(CP1616_Master_Flags.Bits.bRx)
				break;
			if((SystemTick-CP1616_Master_WaitClientTick)>CP1616_Master_WaitClientTime)//200ms等待超时
				break;
		}
		CP1616_Master_Flags.Bits.bWaitDataFromClient=0;
		if(CP1616_Master_Flags.Bits.bRx)
		{
			ret=1;
			break;
		}
		CP1616_Master_WaitClientInterval();
		retry--;
	}
	CP1616_Master_SetTx();
	return ret;
}

