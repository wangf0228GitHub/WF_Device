#include "CP1616_Client.h"
#include "wfDefine.h"

#if CP1616_Client_DataBufLen==1
uint8_t CP1616_Client_RxCount;
uint8_t CP1616_Client_NeedRxCount;
#else
uint16_t CP1616_Client_RxCount;
uint16_t CP1616_Client_NeedRxCount;
#endif


#if CP1616_Client_AddrLen==1
uint8_t CP1616_Client_Addr;
#elif CP1616_Client_AddrLen==2
uint16_t CP1616_Client_Addr;
#endif

_CP1616_Client_Flags CP1616_Client_Flags;

#ifndef CP1616_Client_Tx_OneByOne
uint8_t CP1616_Client_TxList[CP1616_Client_TxList_LenMax];
#endif
uint8_t CP1616_Client_RxList[CP1616_Client_RxList_LenMax];
void CP1616_Client_Init(void)
{
	CP1616_Client_SetRx();
	CP1616_Client_EndProcCommand();
}
void CP1616_Client_EndProcCommand(void)
{
	CP1616_Client_Flags.Bits.bRx=0;
#if CP1616_Client_DataBufLen==1
	CP1616_Client_NeedRxCount=0xff;
#else
	CP1616_Client_NeedRxCount=0xffff;
#endif
	
	CP1616_Client_RxCount=0;
}
void CP1616_Client_ProcRx(uint8_t rx)
{
#ifdef CP1616_Client_NeedCheckVerify
	uint8_t sum;
#endif
	if(CP1616_Client_Flags.Bits.bRx==1)
		return;
	CP1616_Client_RxList[CP1616_Client_RxCount++]=rx;
	if(CP1616_Client_RxCount>pCP1616_ClientData)
	{
		if(rx==0x0d && CP1616_Client_RxCount==CP1616_Client_NeedRxCount)
		{			
#ifdef CP1616_Client_NeedCheckVerify
			sum=CP1616_Client_VerifyProc(CP1616_Client_RxList,CP1616_Client_NeedRxCount-2);
			if(sum==CP1616_Client_RxList[CP1616_Client_NeedRxCount-2])	
			{
				CP1616_Client_Flags.Bits.bRx=1;
			}
			else
			{
				CP1616_Client_RxCount=0;
			}
#else
			CP1616_Client_Flags.Bits.bRx=1;
#endif						
		}
		else if(CP1616_Client_RxCount>CP1616_Client_NeedRxCount)
		{
			CP1616_Client_RxCount=0;
#if CP1616_Client_DataBufLen==1
			CP1616_Client_NeedRxCount=0xff;
#else
			CP1616_Client_NeedRxCount=0xffff;
#endif
		}
		else if(CP1616_Client_RxCount>CP1616_Client_RxList_LenMax)
		{
			CP1616_Client_RxCount=0;
#if CP1616_Client_DataBufLen==1
			CP1616_Client_NeedRxCount=0xff;
#else
			CP1616_Client_NeedRxCount=0xffff;
#endif				
		}
	}
	else if(CP1616_Client_RxCount==pCP1616_ClientData)
	{
#if CP1616_Client_DataBufLen==1
		CP1616_Client_NeedRxCount=CP1616_Client_RxList[pCP1616_ClientData-1]+pCP1616_ClientData+2;
#else
		CP1616_Client_NeedRxCount=MAKE_SHORT(CP1616_Client_RxList[pCP1616_ClientData-2],CP1616_Client_RxList[pCP1616_ClientData-1])+pCP1616_ClientData+2;
#endif
		if(CP1616_Client_NeedRxCount>CP1616_Client_RxList_LenMax)
			CP1616_Client_RxCount=0;
	}
#if CP1616_Client_AddrLen==1
	else if(CP1616_Client_RxCount==3)//判断地址
	{
		//地址不符，退出当前接收状态				
		if(CP1616_Client_RxList[2]!=CP1616_Client_Addr)
		{
			if(CP1616_Client_RxList[2]!=0xff)//0xff 广播地址
			{
				CP1616_Client_RxCount=0;				
			}
		}
	}
#elif CP1616_Client_AddrLen==2
	else if(CP1616_Client_RxCount==4)//判断地址
	{
		//地址不符，退出当前接收状态				
		if(CP1616_Client_RxList[2]!=HIGH_BYTE(CP1616_Client_Addr) || CP1616_Client_RxList[3]!=LOW_BYTE(CP1616_Client_Addr))
		{
			if(CP1616_Client_RxList[2]!=0xff || CP1616_Client_RxList[3]!=0xff)//0xffff 广播地址
			{
				CP1616_Client_RxCount=0;				
			}
		}
	}
#endif	
	else if(CP1616_Client_RxCount==2)
	{
		if(rx!=0x16)
		{
			CP1616_Client_RxCount=0;
		}
	}
	else if(CP1616_Client_RxCount==1)
	{
		if(rx!=0x16)
		{
			CP1616_Client_RxCount=0;
		}
	}	
}
void CP1616_Client_SendData(uint8_t CommandIndex,uint8_t* pBuff,uint16_t Count)
{
	uint8_t sum;
	uint16_t i;
	Count++;
#ifndef CP1616_Client_Tx_OneByOne
	uint16_t txIndex=0;
#endif
	sum=0;
	CP1616_Client_SetTx();
#ifdef CP1616_Client_Tx_OneByOne
	CP1616_Client_TxByteWithVerify(0x16);
	CP1616_Client_TxByteWithVerify(0x16);
#if CP1616_Client_AddrLen==1
	CP1616_Client_TxByteWithVerify(CP1616_Client_Addr);
#elif CP1616_Client_AddrLen==2
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(CP1616_Client_Addr));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(CP1616_Client_Addr));
#endif
	CP1616_Client_TxByteWithVerify(CommandIndex);

#if CP1616_Client_DataBufLen==1
	CP1616_Client_TxByteWithVerify(Count);
#else
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(Count));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(Count));
#endif
	CP1616_Client_TxByteWithVerify(0x01);
	for(i=0;i<(Count-1);i++)
	{
		CP1616_Client_TxByteWithVerify(pBuff[i]);
	}
	CP1616_Client_TxByte(sum);
	CP1616_Client_TxByte(0x0d);
#else//数组发送
	CP1616_Client_TxList[txIndex++]=0x16;
	CP1616_Client_TxList[txIndex++]=0x16;
#if CP1616_Client_AddrLen==1
	CP1616_Client_TxList[txIndex++]=CP1616_Client_Addr;
#elif CP1616_Client_AddrLen==2
	CP1616_Client_TxList[txIndex++]=HIGH_BYTE(CP1616_Client_Addr);
	CP1616_Client_TxList[txIndex++]=LOW_BYTE(CP1616_Client_Addr);
#endif
	CP1616_Client_TxList[txIndex++]=CommandIndex;

#if CP1616_Client_DataBufLen==1
	CP1616_Client_TxList[txIndex++]=Count;
#else
	CP1616_Client_TxList[txIndex++]=HIGH_BYTE(Count);
	CP1616_Client_TxList[txIndex++]=LOW_BYTE(Count);
#endif
	CP1616_Client_TxList[txIndex++]=0x01;
	for(i=0;i<(Count-1);i++)
	{
		CP1616_Client_TxList[txIndex++]=pBuff[i];
	}
	sum=CP1616_Client_VerifyProc(CP1616_Client_TxList,txIndex);
	CP1616_Client_TxList[txIndex++]=sum;
	CP1616_Client_TxList[txIndex++]=0x0d;
	CP1616_Client_TxProc(CP1616_Client_TxList,txIndex);
#endif	
	CP1616_Client_SetRx();
	CP1616_Client_EndProcCommand();
}
void CP1616_Client_SendOK(uint8_t CommandIndex)
{
	uint8_t sum;
#ifndef CP1616_Client_Tx_OneByOne
	uint16_t txIndex=0;
#endif
	sum=0;
	CP1616_Client_SetTx();
#ifdef CP1616_Client_Tx_OneByOne
	CP1616_Client_TxByteWithVerify(0x16);
	CP1616_Client_TxByteWithVerify(0x16);

#if CP1616_Client_AddrLen==1
	CP1616_Client_TxByteWithVerify(CP1616_Client_Addr);
#elif CP1616_Client_AddrLen==2
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(CP1616_Client_Addr));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(CP1616_Client_Addr));
#endif
	CP1616_Client_TxByteWithVerify(CommandIndex);

#if CP1616_Client_DataBufLen==1
	CP1616_Client_TxByteWithVerify(0x01);
#else
	CP1616_Client_TxByteWithVerify(0x00);
	CP1616_Client_TxByteWithVerify(0x01);
#endif
	CP1616_Client_TxByteWithVerify(0x01);
	CP1616_Client_TxByte(sum);
	CP1616_Client_TxByte(0x0d);
#else
	CP1616_Client_TxList[txIndex++]=0x16;
	CP1616_Client_TxList[txIndex++]=0x16;

#if CP1616_Client_AddrLen==1
	CP1616_Client_TxList[txIndex++]=CP1616_Client_Addr;
#elif CP1616_Client_AddrLen==2
	CP1616_Client_TxList[txIndex++]=HIGH_BYTE(CP1616_Client_Addr);
	CP1616_Client_TxList[txIndex++]=LOW_BYTE(CP1616_Client_Addr);
#endif
	CP1616_Client_TxList[txIndex++]=CommandIndex;

#if CP1616_Client_DataBufLen==1
	CP1616_Client_TxList[txIndex++]=0x01;
#else
	CP1616_Client_TxList[txIndex++]=0x00;
	CP1616_Client_TxList[txIndex++]=0x01;
#endif
	CP1616_Client_TxList[txIndex++]=0x01;
	sum=CP1616_Client_VerifyProc(CP1616_Client_TxList,txIndex);
	CP1616_Client_TxList[txIndex++]=sum;
	CP1616_Client_TxList[txIndex++]=0x0d;
	CP1616_Client_TxProc(CP1616_Client_TxList,txIndex);
#endif
	CP1616_Client_SetRx();
	CP1616_Client_EndProcCommand();
}

void CP1616_Client_SendError(uint8_t CommandIndex,uint8_t errNum)
{
	uint8_t sum;
#ifndef CP1616_Client_Tx_OneByOne
	uint16_t txIndex=0;
#endif
	sum=0;
	CP1616_Client_SetTx();
#ifdef CP1616_Client_Tx_OneByOne
	CP1616_Client_TxByteWithVerify(0x16);
	CP1616_Client_TxByteWithVerify(0x16);
#if CP1616_Client_AddrLen==1
	CP1616_Client_TxByteWithVerify(CP1616_Client_Addr);
#elif CP1616_Client_AddrLen==2
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(CP1616_Client_Addr));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(CP1616_Client_Addr));
#endif
	CP1616_Client_TxByteWithVerify(CommandIndex);

#if CP1616_Client_DataBufLen==1
	CP1616_Client_TxByteWithVerify(0x01);
#else
	CP1616_Client_TxByteWithVerify(0x00);
	CP1616_Client_TxByteWithVerify(0x01);
#endif
	CP1616_Client_TxByteWithVerify(errNum);
	CP1616_Client_TxByte(sum);
	CP1616_Client_TxByte(0x0d);
#else
	CP1616_Client_TxList[txIndex++]=0x16;
	CP1616_Client_TxList[txIndex++]=0x16;
#if CP1616_Client_AddrLen==1
	CP1616_Client_TxList[txIndex++]=CP1616_Client_Addr;
#elif CP1616_Client_AddrLen==2
	CP1616_Client_TxList[txIndex++]=HIGH_BYTE(CP1616_Client_Addr);
	CP1616_Client_TxList[txIndex++]=LOW_BYTE(CP1616_Client_Addr);
#endif
	CP1616_Client_TxList[txIndex++]=CommandIndex;

#if CP1616_Client_DataBufLen==1
	CP1616_Client_TxList[txIndex++]=0x01;
#else
	CP1616_Client_TxList[txIndex++]=0x00;
	CP1616_Client_TxList[txIndex++]=0x01;
#endif
	CP1616_Client_TxList[txIndex++]=errNum;
	sum=CP1616_Client_VerifyProc(CP1616_Client_TxList,txIndex);
	CP1616_Client_TxList[txIndex++]=sum;
	CP1616_Client_TxList[txIndex++]=0x0d;
	CP1616_Client_TxProc(CP1616_Client_TxList,txIndex);
#endif
	CP1616_Client_SetRx();
	CP1616_Client_EndProcCommand();
}

uint8_t CP1616_Client_SendHeader( uint8_t CommandIndex,uint16_t Count )
{
	uint8_t sum;
	uint16_t i;
#ifndef CP1616_Client_Tx_OneByOne
	uint16_t txIndex=0;
#endif
	sum=0;
	CP1616_Client_SetTx();
#ifdef CP1616_Client_Tx_OneByOne
	CP1616_Client_TxByteWithVerify(0x16);
	CP1616_Client_TxByteWithVerify(0x16);
#if CP1616_Client_AddrLen==1
	CP1616_Client_TxByteWithVerify(CP1616_Client_Addr);
#elif CP1616_Client_AddrLen==2
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(CP1616_Client_Addr));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(CP1616_Client_Addr));
#endif
	CP1616_Client_TxByteWithVerify(CommandIndex);

#if CP1616_Client_DataBufLen==1
	CP1616_Client_TxByteWithVerify(Count);
#else
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(Count));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(Count));
#endif
	
#else//数组发送
	CP1616_Client_TxList[txIndex++]=0x16;
	CP1616_Client_TxList[txIndex++]=0x16;
#if CP1616_Client_AddrLen==1
	CP1616_Client_TxList[txIndex++]=CP1616_Client_Addr;
#elif CP1616_Client_AddrLen==2
	CP1616_Client_TxList[txIndex++]=HIGH_BYTE(CP1616_Client_Addr);
	CP1616_Client_TxList[txIndex++]=LOW_BYTE(CP1616_Client_Addr);
#endif
	CP1616_Client_TxList[txIndex++]=CommandIndex;

#if CP1616_Client_DataBufLen==1
	CP1616_Client_TxList[txIndex++]=Count;
#else
	CP1616_Client_TxList[txIndex++]=HIGH_BYTE(Count);
	CP1616_Client_TxList[txIndex++]=LOW_BYTE(Count);
#endif
	sum=CP1616_Client_VerifyProc(CP1616_Client_TxList,pCP1616_ClientData);
	CP1616_Client_TxProc(CP1616_Client_TxList,txIndex);
#endif	
	return sum;
// 	CP1616_Client_SetRx();
// 	CP1616_Client_EndProcCommand();
}

#ifdef CP1717_Client

#if CP1717_DataBufLen==1
uint8_t CP1717_Client_RxCount;
uint8_t CP1717_Client_NeedRxCount;
#else
uint16_t CP1717_Client_RxCount;
uint16_t CP1717_Client_NeedRxCount;
#endif


#if CP1717_AddrLen==1
uint8_t CP1717_Client_Addr;
#elif CP1717_AddrLen==2
uint16_t CP1717_Client_Addr;
#endif

_CP1717_Client_Flags CP1717_Client_Flags;

#ifndef CP1717_Client_Tx_OneByOne
uint8_t CP1717_Client_TxList[CP1717_Client_TxList_LenMax];
#endif
uint8_t CP1717_Client_RxList[CP1717_Client_RxList_LenMax];
void CP1717_Client_Init(void)
{
	CP1717_Client_SetRx();
	CP1717_Client_EndProcCommand();
}
void CP1717_Client_EndProcCommand(void)
{
	CP1717_Client_Flags.Bits.bRx=0;
#if CP1717_DataBufLen==1
	CP1717_Client_NeedRxCount=0xff;
#else
	CP1717_Client_NeedRxCount=0xffff;
#endif

	CP1717_Client_RxCount=0;
}
void CP1717_Client_ProcRx(uint8_t rx)
{
#ifdef CP1717_Client_NeedCheckVerify
	uint8_t sum;
#endif
	if(CP1717_Client_Flags.Bits.bRx==1)
		return;
	CP1717_Client_RxList[CP1717_Client_RxCount++]=rx;
	if(CP1717_Client_RxCount>pCP1717_ClientData)
	{
		if(rx==0x0d && CP1717_Client_RxCount==CP1717_Client_NeedRxCount)
		{			
#ifdef CP1717_Client_NeedCheckVerify
			sum=CP1717_Client_VerifyProc(CP1717_Client_RxList,CP1717_Client_NeedRxCount-2);
			if(sum==CP1717_Client_RxList[CP1717_Client_NeedRxCount-2])	
			{
				CP1717_Client_Flags.Bits.bRx=1;
			}
			else
			{
				CP1717_Client_RxCount=0;
			}
#else
			CP1717_Client_Flags.Bits.bRx=1;
#endif						
		}
		else if(CP1717_Client_RxCount>CP1717_Client_NeedRxCount)
		{
			CP1717_Client_RxCount=0;
#if CP1717_DataBufLen==1
			CP1717_Client_NeedRxCount=0xff;
#else
			CP1717_Client_NeedRxCount=0xffff;
#endif
		}
		else if(CP1717_Client_RxCount>CP1717_Client_RxList_LenMax)
		{
			CP1717_Client_RxCount=0;
#if CP1717_DataBufLen==1
			CP1717_Client_NeedRxCount=0xff;
#else
			CP1717_Client_NeedRxCount=0xffff;
#endif				
		}
	}
	else if(CP1717_Client_RxCount==pCP1717_ClientData)
	{
#if CP1717_DataBufLen==1
		CP1717_Client_NeedRxCount=CP1717_Client_RxList[pCP1717_ClientData-1]+pCP1717_ClientData+2;
#else
		CP1717_Client_NeedRxCount=MAKE_SHORT(CP1717_Client_RxList[pCP1717_ClientData-2],CP1717_Client_RxList[pCP1717_ClientData-1])+pCP1717_ClientData+2;
#endif
		if(CP1717_Client_NeedRxCount>CP1717_Client_RxList_LenMax)
			CP1717_Client_RxCount=0;
	}
#if CP1717_AddrLen==1
	else if(CP1717_Client_RxCount==3)//判断地址
	{
		//地址不符，退出当前接收状态				
		if(CP1717_Client_RxList[2]!=CP1717_Client_Addr)
		{
			if(CP1717_Client_RxList[2]!=0xff)//0xff 广播地址
			{
				CP1717_Client_RxCount=0;				
#if CP1717_DataBufLen==1
				CP1717_Client_NeedRxCount=0xff;
#else
				CP1717_Client_NeedRxCount=0xffff;
#endif
			}
		}
	}
#elif CP1717_AddrLen==2
	else if(CP1717_Client_RxCount==4)//判断地址
	{
		//地址不符，退出当前接收状态				
		if(CP1717_Client_RxList[2]!=HIGH_BYTE(CP1717_Client_Addr) || CP1717_Client_RxList[3]!=LOW_BYTE(CP1717_Client_Addr))
		{
			if(CP1717_Client_RxList[2]!=0xff || CP1717_Client_RxList[3]!=0xff)//0xffff 广播地址
			{
				CP1717_Client_RxCount=0;				
#if CP1717_DataBufLen==1
				CP1717_Client_NeedRxCount=0xff;
#else
				CP1717_Client_NeedRxCount=0xffff;
#endif
			}
		}
	}
#endif	
	else if(CP1717_Client_RxCount==2)
	{
		if(rx!=0x16)
		{
			CP1717_Client_RxCount=0;
		}
	}
	else if(CP1717_Client_RxCount==1)
	{
		if(rx!=0x16)
		{
			CP1717_Client_RxCount=0;
		}
	}	
}
void CP1717_Client_SendData(uint8_t CommandIndex,uint8_t* pBuff,uint16_t Count)
{
	uint8_t sum;
	uint16_t i;
	Count++;
#ifndef CP1717_Client_Tx_OneByOne
	uint16_t txIndex=0;
#endif
	sum=0;
	CP1717_Client_SetTx();
#ifdef CP1717_Client_Tx_OneByOne
	CP1717_Client_TxByteWithVerify(0x16);
	CP1717_Client_TxByteWithVerify(0x16);
#if CP1717_AddrLen==1
	CP1717_Client_TxByteWithVerify(CP1717_Client_Addr);
#elif CP1717_AddrLen==2
	CP1717_Client_TxByteWithVerify(HIGH_BYTE(CP1717_Client_Addr));
	CP1717_Client_TxByteWithVerify(LOW_BYTE(CP1717_Client_Addr));
#endif
	CP1717_Client_TxByteWithVerify(CommandIndex);

#if CP1717_DataBufLen==1
	CP1717_Client_TxByteWithVerify(Count);
#else
	CP1717_Client_TxByteWithVerify(HIGH_BYTE(Count));
	CP1717_Client_TxByteWithVerify(LOW_BYTE(Count));
#endif
	CP1717_Client_TxByteWithVerify(0x01);
	for(i=0;i<(Count-1);i++)
	{
		CP1717_Client_TxByteWithVerify(pBuff[i]);
	}
	CP1717_Client_TxByte(sum);
	CP1717_Client_TxByte(0x0d);
#else//数组发送
	CP1717_Client_TxList[txIndex++]=0x16;
	CP1717_Client_TxList[txIndex++]=0x16;
#if CP1717_AddrLen==1
	CP1717_Client_TxList[txIndex++]=CP1717_Client_Addr;
#elif CP1717_AddrLen==2
	CP1717_Client_TxList[txIndex++]=HIGH_BYTE(CP1717_Client_Addr);
	CP1717_Client_TxList[txIndex++]=LOW_BYTE(CP1717_Client_Addr);
#endif
	CP1717_Client_TxList[txIndex++]=CommandIndex;

#if CP1717_DataBufLen==1
	CP1717_Client_TxList[txIndex++]=Count;
#else
	CP1717_Client_TxList[txIndex++]=HIGH_BYTE(Count);
	CP1717_Client_TxList[txIndex++]=LOW_BYTE(Count);
#endif
	CP1717_Client_TxList[txIndex++]=0x01;
	for(i=0;i<(Count-1);i++)
	{
		CP1717_Client_TxList[txIndex++]=pBuff[i];
	}
	sum=CP1717_Client_VerifyProc(CP1717_Client_TxList,txIndex);
	CP1717_Client_TxList[txIndex++]=sum;
	CP1717_Client_TxList[txIndex++]=0x0d;
	CP1717_Client_TxProc(CP1717_Client_TxList,txIndex);
#endif	
	CP1717_Client_SetRx();
	CP1717_Client_EndProcCommand();
}
void CP1717_Client_SendOK(uint8_t CommandIndex)
{
	uint8_t sum;
#ifndef CP1717_Client_Tx_OneByOne
	uint16_t txIndex=0;
#endif
	sum=0;
	CP1717_Client_SetTx();
#ifdef CP1717_Client_Tx_OneByOne
	CP1717_Client_TxByteWithVerify(0x16);
	CP1717_Client_TxByteWithVerify(0x16);

#if CP1717_AddrLen==1
	CP1717_Client_TxByteWithVerify(CP1717_Client_Addr);
#elif CP1717_AddrLen==2
	CP1717_Client_TxByteWithVerify(HIGH_BYTE(CP1717_Client_Addr));
	CP1717_Client_TxByteWithVerify(LOW_BYTE(CP1717_Client_Addr));
#endif
	CP1717_Client_TxByteWithVerify(CommandIndex);

#if CP1717_DataBufLen==1
	CP1717_Client_TxByteWithVerify(0x01);
#else
	CP1717_Client_TxByteWithVerify(0x00);
	CP1717_Client_TxByteWithVerify(0x01);
#endif
	CP1717_Client_TxByteWithVerify(0x01);
	CP1717_Client_TxByte(sum);
	CP1717_Client_TxByte(0x0d);
#else
	CP1717_Client_TxList[txIndex++]=0x16;
	CP1717_Client_TxList[txIndex++]=0x16;

#if CP1717_AddrLen==1
	CP1717_Client_TxList[txIndex++]=CP1717_Client_Addr;
#elif CP1717_AddrLen==2
	CP1717_Client_TxList[txIndex++]=HIGH_BYTE(CP1717_Client_Addr);
	CP1717_Client_TxList[txIndex++]=LOW_BYTE(CP1717_Client_Addr);
#endif
	CP1717_Client_TxList[txIndex++]=CommandIndex;

#if CP1717_DataBufLen==1
	CP1717_Client_TxList[txIndex++]=0x01;
#else
	CP1717_Client_TxList[txIndex++]=0x00;
	CP1717_Client_TxList[txIndex++]=0x01;
#endif
	CP1717_Client_TxList[txIndex++]=0x01;
	sum=CP1717_Client_VerifyProc(CP1717_Client_TxList,txIndex);
	CP1717_Client_TxList[txIndex++]=sum;
	CP1717_Client_TxList[txIndex++]=0x0d;
	CP1717_Client_TxProc(CP1717_Client_TxList,txIndex);
#endif
	CP1717_Client_SetRx();
	CP1717_Client_EndProcCommand();
}

void CP1717_Client_SendError(uint8_t CommandIndex,uint8_t errNum)
{
	uint8_t sum;
#ifndef CP1717_Client_Tx_OneByOne
	uint16_t txIndex=0;
#endif
	sum=0;
	CP1717_Client_SetTx();
#ifdef CP1717_Client_Tx_OneByOne
	CP1717_Client_TxByteWithVerify(0x16);
	CP1717_Client_TxByteWithVerify(0x16);
#if CP1717_AddrLen==1
	CP1717_Client_TxByteWithVerify(CP1717_Client_Addr);
#elif CP1717_AddrLen==2
	CP1717_Client_TxByteWithVerify(HIGH_BYTE(CP1717_Client_Addr));
	CP1717_Client_TxByteWithVerify(LOW_BYTE(CP1717_Client_Addr));
#endif
	CP1717_Client_TxByteWithVerify(CommandIndex);

#if CP1717_DataBufLen==1
	CP1717_Client_TxByteWithVerify(0x01);
#else
	CP1717_Client_TxByteWithVerify(0x00);
	CP1717_Client_TxByteWithVerify(0x01);
#endif
	CP1717_Client_TxByteWithVerify(errNum);
	CP1717_Client_TxByte(sum);
	CP1717_Client_TxByte(0x0d);
#else
	CP1717_Client_TxList[txIndex++]=0x16;
	CP1717_Client_TxList[txIndex++]=0x16;
#if CP1717_AddrLen==1
	CP1717_Client_TxList[txIndex++]=CP1717_Client_Addr;
#elif CP1717_AddrLen==2
	CP1717_Client_TxList[txIndex++]=HIGH_BYTE(CP1717_Client_Addr);
	CP1717_Client_TxList[txIndex++]=LOW_BYTE(CP1717_Client_Addr);
#endif
	CP1717_Client_TxList[txIndex++]=CommandIndex;

#if CP1717_DataBufLen==1
	CP1717_Client_TxList[txIndex++]=0x01;
#else
	CP1717_Client_TxList[txIndex++]=0x00;
	CP1717_Client_TxList[txIndex++]=0x01;
#endif
	CP1717_Client_TxList[txIndex++]=errNum;
	sum=CP1717_Client_VerifyProc(CP1717_Client_TxList,txIndex);
	CP1717_Client_TxList[txIndex++]=sum;
	CP1717_Client_TxList[txIndex++]=0x0d;
	CP1717_Client_TxProc(CP1717_Client_TxList,txIndex);
#endif
	CP1717_Client_SetRx();
	CP1717_Client_EndProcCommand();
}

uint8_t CP1717_Client_SendHeader( uint8_t CommandIndex,uint16_t Count )
{
	uint8_t sum;
	uint16_t i;
#ifndef CP1717_Client_Tx_OneByOne
	uint16_t txIndex=0;
#endif
	sum=0;
	CP1717_Client_SetTx();
#ifdef CP1717_Client_Tx_OneByOne
	CP1717_Client_TxByteWithVerify(0x16);
	CP1717_Client_TxByteWithVerify(0x16);
#if CP1717_AddrLen==1
	CP1717_Client_TxByteWithVerify(CP1717_Client_Addr);
#elif CP1717_AddrLen==2
	CP1717_Client_TxByteWithVerify(HIGH_BYTE(CP1717_Client_Addr));
	CP1717_Client_TxByteWithVerify(LOW_BYTE(CP1717_Client_Addr));
#endif
	CP1717_Client_TxByteWithVerify(CommandIndex);

#if CP1717_DataBufLen==1
	CP1717_Client_TxByteWithVerify(Count);
#else
	CP1717_Client_TxByteWithVerify(HIGH_BYTE(Count));
	CP1717_Client_TxByteWithVerify(LOW_BYTE(Count));
#endif

#else//数组发送
	CP1717_Client_TxList[txIndex++]=0x16;
	CP1717_Client_TxList[txIndex++]=0x16;
#if CP1717_AddrLen==1
	CP1717_Client_TxList[txIndex++]=CP1717_Client_Addr;
#elif CP1717_AddrLen==2
	CP1717_Client_TxList[txIndex++]=HIGH_BYTE(CP1717_Client_Addr);
	CP1717_Client_TxList[txIndex++]=LOW_BYTE(CP1717_Client_Addr);
#endif
	CP1717_Client_TxList[txIndex++]=CommandIndex;

#if CP1717_DataBufLen==1
	CP1717_Client_TxList[txIndex++]=Count;
#else
	CP1717_Client_TxList[txIndex++]=HIGH_BYTE(Count);
	CP1717_Client_TxList[txIndex++]=LOW_BYTE(Count);
#endif
	sum=CP1717_Client_VerifyProc(CP1717_Client_TxList,pCP1717_ClientData);
	CP1717_Client_TxProc(CP1717_Client_TxList,txIndex);
#endif	
	return sum;
	// 	CP1717_Client_SetRx();
	// 	CP1717_Client_EndProcCommand();
}
#endif
