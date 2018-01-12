#include "HardwareProfile.h"

void CP1616_Client_Init(void)
{
	SetRx_CP1616_Client();
	CP1616_Client_EndProcCommand();
	//SetCOM1TX();
//	/while(1)
//	{
//		Uart_PutChar(0xff);
//	}
}
void CP1616_Client_EndProcCommand(void)
{
	CP1616_Client_Flags.bRx=0;
	CP1616_Client_NeedRxCount=0xffff;
	CP1616_Client_RxCount=0;
}
void CP1616_Client_ProcRx(unsigned char rx)
{
#ifdef SystemTick
	CP1616_Client_NoRxTick=SystemTick;
#endif	
	if(CP1616_Client_Flags.bRx==1)
		return;
	CP1616_Client_RxList[CP1616_Client_RxCount++]=rx;
	if(CP1616_Client_RxCount>pCP1616_ClientData)
	{
		if(rx==0x0d && CP1616_Client_RxCount==CP1616_Client_NeedRxCount)
		{			
			CP1616_Client_Flags.bRx=1;			
		}
		else if(CP1616_Client_RxCount>CP1616_Client_NeedRxCount)
		{
			CP1616_Client_RxCount=0;
			CP1616_Client_NeedRxCount=0xffff;
		}
		else if(CP1616_Client_RxCount>MAX_CP1616_Client_RX)
		{
			CP1616_Client_RxCount=0;
			CP1616_Client_NeedRxCount=0xffff;				
		}
	}
	else if(CP1616_Client_RxCount==pCP1616_ClientData)
	{
		CP1616_Client_NeedRxCount=MAKE_INT(CP1616_Client_RxList[5],CP1616_Client_RxList[6])+9;
	}
	else if(CP1616_Client_RxCount==4)//判断地址
	{
		//地址不符，退出当前接收状态				
		if(CP1616_Client_RxList[2]!=CP1616_Client_Addr.u8H || CP1616_Client_RxList[3]!=CP1616_Client_Addr.u8L)
		{
			if(CP1616_Client_RxList[2]!=0xff || CP1616_Client_RxList[3]!=0xff)//0xffff 广播地址
			{
				CP1616_Client_RxCount=0;				
				CP1616_Client_NeedRxCount=0xffff;
			}
		}
	}
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
void CP1616_Client_SendData(unsigned char CommandIndex,unsigned char* pBuff,unsigned int Count)
{
	unsigned char sum;
	unsigned int i;
	sum=0;
	SetTx_CP1616_Client();
	CP1616_Client_AddTxHeader();
	CP1616_Client_TxByteWithVerify(CommandIndex);
	CP1616_Client_TxByteWithVerify(HIGH_BYTE(Count));
	CP1616_Client_TxByteWithVerify(LOW_BYTE(Count));
	for(i=0;i<Count;i++)
	{
		CP1616_Client_TxByteWithVerify(pBuff[i]);
	}
	CP1616_Client_AddTxEnder();
	SetRx_CP1616_Client();
	CP1616_Client_EndProcCommand();
}
void CP1616_Client_SendOK(unsigned char CommandIndex)
{
	unsigned char sum;
	sum=0;
	SetTx_CP1616_Client();
	CP1616_Client_AddTxHeader();
	CP1616_Client_TxByteWithVerify(CommandIndex);
	CP1616_Client_TxByteWithVerify(0x00);
	CP1616_Client_TxByteWithVerify(0x02);
	CP1616_Client_TxByteWithVerify('O');
	CP1616_Client_TxByteWithVerify('K');
	CP1616_Client_AddTxEnder();
	SetRx_CP1616_Client();
	CP1616_Client_EndProcCommand();
}

void CP1616_Client_SendError( unsigned char CommandIndex )
{
	unsigned char sum;
	sum=0;
	SetTx_CP1616_Client();
	CP1616_Client_AddTxHeader();
	CP1616_Client_TxByteWithVerify(CommandIndex);
	CP1616_Client_TxByteWithVerify(0x00);
	CP1616_Client_TxByteWithVerify(0x03);
	CP1616_Client_TxByteWithVerify('E');
	CP1616_Client_TxByteWithVerify('R');
	CP1616_Client_TxByteWithVerify('R');
	CP1616_Client_AddTxEnder();
	SetRx_CP1616_Client();
	CP1616_Client_EndProcCommand();
}
#ifdef CP1616_Client2
void CP1616_Client2_Init(void)
{
	SetRx_CP1616_Client2();
	CP1616_Client2_EndProcCommand();
	//SetCOM1TX();
	//	/while(1)
	//	{
	//		Uart_PutChar(0xff);
	//	}
}
void CP1616_Client2_EndProcCommand(void)
{
	CP1616_Client2_Flags.bRx=0;
	CP1616_Client2_NeedRxCount=0xffff;
	CP1616_Client2_RxCount=0;
}
void CP1616_Client2_ProcRx(unsigned char rx)
{
	CP1616_Client2_NoRxTick=SystemTick;
	if(CP1616_Client2_Flags.bRx==1)
		return;
	CP1616_Client2_RxList[CP1616_Client2_RxCount++]=rx;
	if(CP1616_Client2_RxCount>7)
	{
		if(rx==0x0d && CP1616_Client2_RxCount==CP1616_Client2_NeedRxCount)
		{			
			CP1616_Client2_Flags.bRx=1;			
		}
		else if(CP1616_Client2_RxCount>CP1616_Client2_NeedRxCount)
		{
			CP1616_Client2_RxCount=0;
			CP1616_Client2_NeedRxCount=0xffff;
		}
		else if(CP1616_Client2_RxCount>MAX_CP1616_Client2_RX)
		{
			CP1616_Client2_RxCount=0;
			CP1616_Client2_NeedRxCount=0xffff;				
		}
	}
	else if(CP1616_Client2_RxCount==7)
	{
		CP1616_Client2_NeedRxCount=MAKE_INT(CP1616_Client2_RxList[5],CP1616_Client2_RxList[6])+9;
	}
	else if(CP1616_Client2_RxCount==4)//判断地址
	{
		//地址不符，退出当前接收状态				
		if(CP1616_Client2_RxList[2]!=CP1616_Client2_Addr.u8H || CP1616_Client2_RxList[3]!=CP1616_Client2_Addr.u8L)
		{
			if(CP1616_Client2_RxList[2]!=0xff || CP1616_Client2_RxList[3]!=0xff)//0xffff 广播地址
			{
				CP1616_Client2_RxCount=0;				
				CP1616_Client2_NeedRxCount=0xffff;
			}
		}
	}
	else if(CP1616_Client2_RxCount==2)
	{
		if(rx!=0x16)
		{
			CP1616_Client2_RxCount=0;
		}
	}
	else if(CP1616_Client2_RxCount==1)
	{
		if(rx!=0x16)
		{
			CP1616_Client2_RxCount=0;
		}
	}	
}
void CP1616_Client2_SendData(unsigned char CommandIndex,unsigned char* pBuff,unsigned int Count)
{
	unsigned char sum;
	unsigned int i;
	sum=0;
	SetTx_CP1616_Client2();
	CP1616_Client2_AddTxHeader();
	CP1616_Client2_TxByteWithVerify(CommandIndex);
	CP1616_Client2_TxByteWithVerify(HIGH_BYTE(Count));
	CP1616_Client2_TxByteWithVerify(LOW_BYTE(Count));
	for(i=0;i<Count;i++)
	{
		CP1616_Client2_TxByteWithVerify(pBuff[i]);
	}
	CP1616_Client2_AddTxEnder();
	SetRx_CP1616_Client2();
	CP1616_Client2_EndProcCommand();
}
void CP1616_Client2_SendOK(unsigned char CommandIndex)
{
	unsigned char sum;
	sum=0;
	SetTx_CP1616_Client2();
	CP1616_Client2_AddTxHeader();
	CP1616_Client2_TxByteWithVerify(CommandIndex);
	CP1616_Client2_TxByteWithVerify(0x00);
	CP1616_Client2_TxByteWithVerify(0x02);
	CP1616_Client2_TxByteWithVerify('O');
	CP1616_Client2_TxByteWithVerify('K');
	CP1616_Client2_AddTxEnder();
	SetRx_CP1616_Client2();
	CP1616_Client2_EndProcCommand();
}

void CP1616_Client2_SendError( unsigned char CommandIndex )
{
	unsigned char sum;
	sum=0;
	SetTx_CP1616_Client2();
	CP1616_Client2_AddTxHeader();
	CP1616_Client2_TxByteWithVerify(CommandIndex);
	CP1616_Client2_TxByteWithVerify(0x00);
	CP1616_Client2_TxByteWithVerify(0x03);
	CP1616_Client2_TxByteWithVerify('E');
	CP1616_Client2_TxByteWithVerify('R');
	CP1616_Client2_TxByteWithVerify('R');
	CP1616_Client2_AddTxEnder();
	SetRx_CP1616_Client2();
	CP1616_Client2_EndProcCommand();
}
#endif
