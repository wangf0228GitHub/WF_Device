#include "main.h"
#include "CP1616_Client.h"
#include "wfDefine.h"

void CP1616_Client_Init(void)
{
	SetRx_CP1616_Client();
	CP1616_Client_EndProcCommand();
}
void CP1616_Client_EndProcCommand(void)
{
	CP1616_Client_Flags.Bits.bRx=0;
#if CP1616_DataBufLen==1
	CP1616_Client_NeedRxCount=0xff;
#else
	CP1616_Client_NeedRxCount=0xffff;
#endif
	
	CP1616_Client_RxCount=0;
}
void CP1616_Client_ProcRx(uint8_t rx)
{
	if(CP1616_Client_Flags.Bits.bRx==1)
		return;
	CP1616_Client_RxList[CP1616_Client_RxCount++]=rx;
	if(CP1616_Client_RxCount>pCP1616_ClientData)
	{
		if(rx==0x0d && CP1616_Client_RxCount==CP1616_Client_NeedRxCount)
		{			
			CP1616_Client_Flags.Bits.bRx=1;			
		}
		else if(CP1616_Client_RxCount>CP1616_Client_NeedRxCount)
		{
			CP1616_Client_RxCount=0;
#if CP1616_DataBufLen==1
			CP1616_Client_NeedRxCount=0xff;
#else
			CP1616_Client_NeedRxCount=0xffff;
#endif
		}
		else if(CP1616_Client_RxCount>MAX_CP1616_Client_RX)
		{
			CP1616_Client_RxCount=0;
#if CP1616_DataBufLen==1
			CP1616_Client_NeedRxCount=0xff;
#else
			CP1616_Client_NeedRxCount=0xffff;
#endif				
		}
	}
	else if(CP1616_Client_RxCount==pCP1616_ClientData)
	{
#if CP1616_DataBufLen==1
		CP1616_Client_NeedRxCount=CP1616_Client_RxList[pCP1616_ClientData-1]+pCP1616_ClientData+2;
#else
		CP1616_Client_NeedRxCount=MAKE_INT(CP1616_Client_RxList[pCP1616_ClientData-2],CP1616_Client_RxList[pCP1616_ClientData-1])+pCP1616_ClientData+2;
#endif
		
	}
#if CP1616_AddrLen==1
	else if(CP1616_Client_RxCount==3)//判断地址
	{
		//地址不符，退出当前接收状态				
		if(CP1616_Client_RxList[2]!=CP1616_Client_Addr)
		{
			if(CP1616_Client_RxList[2]!=0xff)//0xff 广播地址
			{
				CP1616_Client_RxCount=0;				
#if CP1616_DataBufLen==1
				CP1616_Client_NeedRxCount=0xff;
#else
				CP1616_Client_NeedRxCount=0xffff;
#endif
			}
		}
	}
#elif CP1616_AddrLen==2
	else if(CP1616_Client_RxCount==4)//判断地址
	{
		//地址不符，退出当前接收状态				
		if(CP1616_Client_RxList[2]!=HIGH_BYTE(CP1616_Client_Addr) || CP1616_Client_RxList[3]!=LOW_BYTE(CP1616_Client_Addr))
		{
			if(CP1616_Client_RxList[2]!=0xff || CP1616_Client_RxList[3]!=0xff)//0xffff 广播地址
			{
				CP1616_Client_RxCount=0;				
#if CP1616_DataBufLen==1
				CP1616_Client_NeedRxCount=0xff;
#else
				CP1616_Client_NeedRxCount=0xffff;
#endif
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
	sum=0;
	SetTx_CP1616_Client();
	CP1616_Client_TxByteWithVerify(0x16);
	CP1616_Client_TxByteWithVerify(0x16);
#if CP1616_AddrLen==1
	CP1616_Client_TxByteWithVerify(CP1616_Client_Addr);
#elif CP1616_AddrLen==2
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(CP1616_Client_Addr));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(CP1616_Client_Addr));
#endif
	CP1616_Client_TxByteWithVerify(CommandIndex);

#if CP1616_DataBufLen==1
	CP1616_Client_TxByteWithVerify(Count);
#else
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(Count));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(Count));
#endif
	for(i=0;i<Count;i++)
	{
		CP1616_Client_TxByteWithVerify(pBuff[i]);
	}
	CP1616_Client_TxByte(sum);
	CP1616_Client_TxByte(0x0d);
	SetRx_CP1616_Client();
	CP1616_Client_EndProcCommand();
}
void CP1616_Client_SendOK(uint8_t CommandIndex)
{
	uint8_t sum;
	sum=0;
	SetTx_CP1616_Client();
	CP1616_Client_TxByteWithVerify(0x16);
	CP1616_Client_TxByteWithVerify(0x16);

#if CP1616_AddrLen==1
	CP1616_Client_TxByteWithVerify(CP1616_Client_Addr);
#elif CP1616_AddrLen==2
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(CP1616_Client_Addr));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(CP1616_Client_Addr));
#endif
	CP1616_Client_TxByteWithVerify(CommandIndex);

#if CP1616_DataBufLen==1
	CP1616_Client_TxByteWithVerify(0x01);
#else
	CP1616_Client_TxByteWithVerify(0x00);
	CP1616_Client_TxByteWithVerify(0x01);
#endif
	CP1616_Client_TxByteWithVerify(0x01);
	CP1616_Client_TxByte(sum);
	CP1616_Client_TxByte(0x0d);
	SetRx_CP1616_Client();
	CP1616_Client_EndProcCommand();
}

void CP1616_Client_SendError(uint8_t CommandIndex,uint8_t errNum)
{
	uint8_t sum;
	sum=0;
	SetTx_CP1616_Client();
	CP1616_Client_TxByteWithVerify(0x16);
	CP1616_Client_TxByteWithVerify(0x16);
#if CP1616_AddrLen==1
	CP1616_Client_TxByteWithVerify(CP1616_Client_Addr);
#elif CP1616_AddrLen==2
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(CP1616_Client_Addr));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(CP1616_Client_Addr));
#endif
	CP1616_Client_TxByteWithVerify(CommandIndex);

#if CP1616_DataBufLen==1
	CP1616_Client_TxByteWithVerify(0x01);
#else
	CP1616_Client_TxByteWithVerify(0x00);
	CP1616_Client_TxByteWithVerify(0x01);
#endif
	CP1616_Client_TxByteWithVerify(errNum);
	CP1616_Client_TxByte(sum);
	CP1616_Client_TxByte(0x0d);
	SetRx_CP1616_Client();
	CP1616_Client_EndProcCommand();
}

