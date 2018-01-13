
#include "CP68_Client.h"
#include "Verify.h"

volatile _CP68_Client_Flags CP68_Client_Flags;
volatile _CP68_Client_RxBuf CP68_Client_RxBuf;
volatile uint16_t CP68_Client_RxBufIndex;
volatile uint16_t CP68_Client_NeedRxCount;
volatile uint32_t CP68_Client_NoRxTick;
volatile _CP68_Client_TxBuf CP68_Client_TxBuf;
volatile uint32_t CP68_Client_TxTimeOut;
void CP68_Client_Init(void)
{
	CP68_Client_EndProcCommand();
	CP68_Client_TxTimeOut=1000;
	CP68_Client_TxBuf.TxStruct.FrameHeader=0x68;
}
void CP68_Client_EndProcCommand(void)
{
	CP68_Client_Flags.Bits.bRx=0;
	CP68_Client_NeedRxCount=0xffff;
	CP68_Client_RxBufIndex=0;
}
void CP68_Client_ProcRx(uint8_t rx)
{
	CP68_Client_NoRxTick=rx;
	CP68_Client_NoRxTick=HAL_GetTick();
	if(CP68_Client_Flags.Bits.bRx)
 		return;
	CP68_Client_RxBuf.AllRxData[CP68_Client_RxBufIndex++]=rx;
	if(CP68_Client_RxBufIndex>12)
	{
 		if(rx==0x16 && CP68_Client_RxBufIndex==CP68_Client_NeedRxCount)
 		{			
 			CP68_Client_Flags.Bits.bRx=1;			
 		}
 		else if(CP68_Client_RxBufIndex>CP68_Client_NeedRxCount)
 		{
 			CP68_Client_RxBufIndex=0;
 			CP68_Client_NeedRxCount=0xffff;
 		}
 		else if(CP68_Client_RxBufIndex>=(CP68_Client_RxDataBufLen+CP68_FrameOther-2))
 		{
 			CP68_Client_RxBufIndex=0;
 			CP68_Client_NeedRxCount=0xffff;				
 		}
	}
	else if(CP68_Client_RxBufIndex==11)//数据包长度
	{
 		CP68_Client_NeedRxCount=CP68_Client_RxBuf.RxStruct.DataLen+CP68_FrameOther;
	}
	else if(CP68_Client_RxBufIndex==10)//控制码
	{
		if((rx & 0x80)==0x80)
		{
			CP68_Client_RxBufIndex=0;
		}
	}
// 	else if(CP68_Client_RxBufIndex==9)
// 	{
// 		if(rx!=CP68_Client_TxBuf.TxStruct.DeviceAddr[6])
// 		{
// 			CP68_Client_RxBufIndex=0;
// 		}
// 	}
// 	else if(CP68_Client_RxBufIndex==8)
// 	{
// 		if(rx!=CP68_Client_TxBuf.TxStruct.DeviceAddr[5])
// 		{
// 			CP68_Client_RxBufIndex=0;
// 		}
// 	}
// 	else if(CP68_Client_RxBufIndex==7)
// 	{
// 		if(rx!=CP68_Client_TxBuf.TxStruct.DeviceAddr[4])
// 		{
// 			CP68_Client_RxBufIndex=0;
// 		}
// 	}
// 	else if(CP68_Client_RxBufIndex==6)
// 	{
// 		if(rx!=CP68_Client_TxBuf.TxStruct.DeviceAddr[3])
// 		{
// 			CP68_Client_RxBufIndex=0;
// 		}
// 	}
// 	else if(CP68_Client_RxBufIndex==5)
// 	{
// 		if(rx!=CP68_Client_TxBuf.TxStruct.DeviceAddr[2])
// 		{
// 			CP68_Client_RxBufIndex=0;
// 		}
// 	}
// 	else if(CP68_Client_RxBufIndex==4)
// 	{
// 		if(rx!=CP68_Client_TxBuf.TxStruct.DeviceAddr[1])
// 		{
// 			CP68_Client_RxBufIndex=0;
// 		}
// 	}
// 	else if(CP68_Client_RxBufIndex==3)
// 	{
// 		if(rx!=CP68_Client_TxBuf.TxStruct.DeviceAddr[0])
// 		{
// 			CP68_Client_RxBufIndex=0;
// 		}
// 	}
	else if(CP68_Client_RxBufIndex==2)
	{
 		if(rx!=CP68_Client_TxBuf.TxStruct.DeviceType)
 		{
 			CP68_Client_RxBufIndex=0;
 		}
	}
	else if(CP68_Client_RxBufIndex==1)
	{
 		if(rx!=0x68)
 		{
 			CP68_Client_RxBufIndex=0;
 		}
	}	
}

void CP68_Client_SendDatas(uint8_t ControlCode,uint8_t* pBuff,uint8_t Count)
{
	uint16_t i;
	CP68_Client_TxBuf.TxStruct.ControlCode = ControlCode | 0x80;
	CP68_Client_TxBuf.TxStruct.DataLen=Count;
	for(i=0;i<Count;i++)
	{
 		CP68_Client_TxBuf.TxStruct.DataBuf[i]=pBuff[i];
	}
	CP68_Client_TxBuf.TxStruct.DataBuf[Count]=GetVerify_Sum((uint8_t *)CP68_Client_TxBuf.AllTxData,Count+CP68_FrameOther-2);
	CP68_Client_TxBuf.TxStruct.DataBuf[Count+1]=0x16;
	HAL_UART_Transmit(&CP68_USART_Handle,(uint8_t*)CP68_Client_TxBuf.AllTxData,Count+CP68_FrameOther,CP68_Client_TxTimeOut);
	CP68_Client_EndProcCommand();
}

void CP68_Client_SendSelf(uint8_t ControlCode,uint8_t Count)
{
	CP68_Client_TxBuf.TxStruct.ControlCode = ControlCode | 0x80;
	CP68_Client_TxBuf.TxStruct.DataLen=Count;
	CP68_Client_TxBuf.TxStruct.DataBuf[Count]=GetVerify_Sum((uint8_t *)CP68_Client_TxBuf.AllTxData,Count+CP68_FrameOther-2);
	CP68_Client_TxBuf.TxStruct.DataBuf[Count+1]=0x16;
	HAL_UART_Transmit(&CP68_USART_Handle,(uint8_t*)CP68_Client_TxBuf.AllTxData,Count+CP68_FrameOther,CP68_Client_TxTimeOut);
	CP68_Client_EndProcCommand();
}

void CP68_Client_CheckRxBuf( void )
{
	uint8_t i,sum;
	/************************************************************************/
	/* 判断地址                                                             */
	/************************************************************************/
	CP68_Client_Flags.Bits.bValid=1;
	for(i=0;i<7;i++)
	{
		if(CP68_Client_RxBuf.RxStruct.DeviceAddr[i]!=CP68_Client_TxBuf.TxStruct.DeviceAddr[i])
		{
			CP68_Client_Flags.Bits.bValid=0;
			break;
		}
	}
	/************************************************************************/
	/* AAAAAAAAAAA为通用地址                                                */
	/************************************************************************/
	if(CP68_Client_Flags.Bits.bValid==0)
	{
		CP68_Client_Flags.Bits.bValid=1;
		for(i=0;i<7;i++)
		{
			if(CP68_Client_RxBuf.RxStruct.DeviceAddr[i]!=0xaa)
			{
				CP68_Client_Flags.Bits.bValid=0;
				break;
			}
		}
	}
	if(CP68_Client_Flags.Bits.bValid==0)
	{
		CP68_Client_EndProcCommand();
		return;
	}
	sum=GetVerify_Sum((uint8_t*)CP68_Client_RxBuf.AllRxData,CP68_Client_RxBufIndex-2);
	if(sum!=CP68_Client_RxBuf.AllRxData[CP68_Client_RxBufIndex-2])
	{
		CP68_Client_EndProcCommand();
		CP68_Client_Flags.Bits.bValid=0;
		return;
	}
}

// void CP68_Client_SendOK(uint8_t CommandIndex)
// {
// 	CP68_Client_SendData(CommandIndex,"OK",2);
// }
// 
// void CP68_Client_SendError( uint8_t CommandIndex ,uint8_t errCode)
// {
// 	CP68_Client_TxBuf.TxStruct.bError=1;
// 	CP68_Client_TxBuf.TxStruct.CommandIndex=CommandIndex;
// 	CP68_Client_TxBuf.TxStruct.ErrCode=errCode;
// 	CP68_Client_TxBuf.TxStruct.DataLen=0;
// 	CP68_Client_TxBuf.TxStruct.Data[0]=GetVerify_Sum((uint8_t*)CP68_Client_TxBuf.AllData,UART_WithPC_TxFrameOther-2);
// 	CP68_Client_TxBuf.TxStruct.Data[1]=0x0d;
// 	HAL_UART_Transmit(&UART_WithPC_Handle,(uint8_t*)CP68_Client_TxBuf.AllData,UART_WithPC_TxFrameOther,1000);
// 	CP68_Client_EndProcCommand();
// }

