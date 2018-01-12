#include "HardwareProfile.h"
#include "ModbusRTU_Master.h"
unsigned char ModbusRTU_Master_RxList[MAX_ModbusRTU_Master_RX];
unsigned char ModbusRTU_Master_RxCount;
unsigned char ModbusRTU_Master_NeedRxCount;
unsigned char ModbusRTU_Master_TargetAddr;
//uint ModbusRTU_Master_FirstRegAddr;
unsigned char ModbusRTU_Master_RetryTimes;
unsigned int ModbusRTU_Master_WaitClientTick;
unsigned int ModbusRTU_Master_WaitClientTime;

unsigned char CurCommand;//当前操作的指令号

_ModbusRTU_Master_Flags ModbusRTU_Master_Flags;
void Init_ModbusRTU_Master(void)
{
	SetTx_ModbusRTU_Master();
	ModbusRTU_Master_RetryTimes=3;
	ModbusRTU_Master_WaitClientTime=3;
}

void ProcRx_ModbusRTU_Master(unsigned char rx)
{
	if(ModbusRTU_Master_Flags.bRx)//之前没处理完
		return;
	if(!ModbusRTU_Master_Flags.bWaitClient)//当前没在等待
		return;
	ModbusRTU_Master_RxList[ModbusRTU_Master_RxCount++]=rx;
	if(ModbusRTU_Master_RxCount>3)
	{
		if(ModbusRTU_Master_RxCount==ModbusRTU_Master_NeedRxCount)
		{			
			ModbusRTU_Master_Flags.bRx=1;			
		}
		else if(ModbusRTU_Master_RxCount>ModbusRTU_Master_NeedRxCount)
		{
			ModbusRTU_Master_RxCount=0;
			ModbusRTU_Master_NeedRxCount=0xff;
		}
		else if(ModbusRTU_Master_RxCount>MAX_ModbusRTU_Master_RX)
		{
			ModbusRTU_Master_RxCount=0;
			ModbusRTU_Master_NeedRxCount=0xff;				
		}
	}	
	else if(ModbusRTU_Master_RxCount==3)//对于读来讲是字节数量
	{
		switch(CurCommand)
		{
		case 0x03://读入从机寄存器，接收时应接收rx+5个字节
			ModbusRTU_Master_NeedRxCount=rx+5;
			if(ModbusRTU_Master_NeedRxCount>MAX_ModbusRTU_Master_RX)
				ModbusRTU_Master_RxCount=0;
			break;
		case 0x04://读输入寄存器，接收时应接收rx+5个字节
			ModbusRTU_Master_NeedRxCount=rx+5;
			if(ModbusRTU_Master_NeedRxCount>MAX_ModbusRTU_Master_RX)
				ModbusRTU_Master_RxCount=0;
			break;
		}
	}
	else if(ModbusRTU_Master_RxCount==2)//命令号
	{
		if(rx!=CurCommand)
		{
			ModbusRTU_Master_RxCount=0;
		}
		else
		{
			switch(CurCommand)
			{
			case 0x10://写入从机寄存器，接收时应接收8个字节
				ModbusRTU_Master_NeedRxCount=8;
				break;
			}
		}
	}
	else if(ModbusRTU_Master_RxCount==1)//从机地址
	{
		if(rx!=ModbusRTU_Master_TargetAddr)
		{
			ModbusRTU_Master_RxCount=0;
		}
	}	
}
void ModbusRTU_Master_SendCommand16(unsigned int RegAddr,unsigned char *pBuff,unsigned char count)
{
	unsigned char i;
	uint crc;	
	unsigned char uIndex ; /* CRC循环中的索引 */
	crc.u16=0xffff;
	CurCommand=0x10;
	SetTx_ModbusRTU_Master();
  	ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
  	ModbusRTU_Master_VerifyTxByte(0x10);
  	ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
  	ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
  	i=count>>1;
  	ModbusRTU_Master_VerifyTxByte(0);
  	ModbusRTU_Master_VerifyTxByte(i);
  	ModbusRTU_Master_VerifyTxByte(count);
  	for(i=0;i<count;i++)
  	{
  		ModbusRTU_Master_VerifyTxByte(pBuff[i]);
  	}
  	ModbusRTU_Master_TxByte(crc.u8H);
  	ModbusRTU_Master_TxByte(crc.u8L);
	SetRx_ModbusRTU_Master();
}
unsigned char ModbusRTU_Master_ProcCommand16(unsigned int RegAddr,unsigned char* pBuff,unsigned int Count)
{	
	unsigned char i;
	uint crc;	
	unsigned char uIndex ; /* CRC循环中的索引 */
	unsigned char retry;
	unsigned char ret;	
	CurCommand=0x10;
	retry=ModbusRTU_Master_RetryTimes;
	ret=0;
	while(retry!=0)
	{
		crc.u16=0xffff;
		SetTx_ModbusRTU_Master();
		ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
		ModbusRTU_Master_VerifyTxByte(0x10);
		ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
		i=Count>>1;
		ModbusRTU_Master_VerifyTxByte(0);
		ModbusRTU_Master_VerifyTxByte(i);
		ModbusRTU_Master_VerifyTxByte(Count);
		for(i=0;i<Count;i++)
		{
			ModbusRTU_Master_VerifyTxByte(pBuff[i]);
		}
		ModbusRTU_Master_TxByte(crc.u8H);
		ModbusRTU_Master_TxByte(crc.u8L);
		SetRx_ModbusRTU_Master();
		ModbusRTU_Master_Flags.bRx=0;
		ModbusRTU_Master_Flags.bWaitClient=1;
		ModbusRTU_Master_WaitClientTick=SystemTick;
		ModbusRTU_Master_RxCount=0;
		//ModbusRTU_Master_RxErrTimes=0;
		ModbusRTU_Master_NeedRxCount=0xff;
		while(1)
		{
			if(ModbusRTU_Master_Flags.bRx)
				break;
			if((SystemTick-ModbusRTU_Master_WaitClientTick)>ModbusRTU_Master_WaitClientTime)//200ms等待超时
				break;
		}
		ModbusRTU_Master_Flags.bWaitClient=0;
		if(ModbusRTU_Master_Flags.bRx)
		{
			ret=1;
			break;
		}
		ModbusRTU_Master_WaitClientInterval();
		retry--;
	}
	SetTx_ModbusRTU_Master();
	return ret;
}
void ModbusRTU_Master_SendCommand03(unsigned int RegAddr,unsigned char count)
{
	uint crc;	
	unsigned char uIndex ; /* CRC循环中的索引 */
	crc.u16=0xffff;
	CurCommand=0x03;
	SetTx_ModbusRTU_Master();
	ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
	ModbusRTU_Master_VerifyTxByte(0x03);
	ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(0);
	ModbusRTU_Master_VerifyTxByte(count);
	ModbusRTU_Master_TxByte(crc.u8H);
	ModbusRTU_Master_TxByte(crc.u8L);
	SetRx_ModbusRTU_Master();
}
unsigned char ModbusRTU_Master_ProcCommand03(unsigned int RegAddr,unsigned char count)
{
	uint crc;	
	unsigned char uIndex ; /* CRC循环中的索引 */
	unsigned char retry;
	unsigned char ret;	
	CurCommand=0x03;
	retry=ModbusRTU_Master_RetryTimes;
	ret=0;
	while(retry!=0)
	{
		crc.u16=0xffff;
		SetTx_ModbusRTU_Master();
		ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
		ModbusRTU_Master_VerifyTxByte(0x03);
		ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(0);
		ModbusRTU_Master_VerifyTxByte(count);
		ModbusRTU_Master_TxByte(crc.u8H);
		ModbusRTU_Master_TxByte(crc.u8L);
		SetRx_ModbusRTU_Master();
		ModbusRTU_Master_Flags.bRx=0;
		ModbusRTU_Master_Flags.bWaitClient=1;
		ModbusRTU_Master_WaitClientTick=SystemTick;
		ModbusRTU_Master_RxCount=0;
		//ModbusRTU_Master_RxErrTimes=0;
		ModbusRTU_Master_NeedRxCount=0xff;
		while(1)
		{
			if(ModbusRTU_Master_Flags.bRx)
				break;
			if((SystemTick-ModbusRTU_Master_WaitClientTick)>ModbusRTU_Master_WaitClientTime)//200ms等待超时
				break;
		}
		ModbusRTU_Master_Flags.bWaitClient=0;
		if(ModbusRTU_Master_Flags.bRx)
		{
			ret=1;
			break;
		}
		ModbusRTU_Master_WaitClientInterval();
		retry--;
	}
	SetTx_ModbusRTU_Master();
	return ret;
}
void ModbusRTU_Master_SendCommand04(unsigned int RegAddr,unsigned char count)
{
	uint crc;	
	unsigned char uIndex ; /* CRC循环中的索引 */
	crc.u16=0xffff;
	CurCommand=0x04;
	SetTx_ModbusRTU_Master();
	ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
	ModbusRTU_Master_VerifyTxByte(0x04);
	ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(0);
	ModbusRTU_Master_VerifyTxByte(count);
	ModbusRTU_Master_TxByte(crc.u8H);
	ModbusRTU_Master_TxByte(crc.u8L);
	SetRx_ModbusRTU_Master();
}
unsigned char ModbusRTU_Master_ProcCommand04(unsigned int RegAddr,unsigned char count)
{
	uint crc;	
	unsigned char uIndex ; /* CRC循环中的索引 */
	unsigned char retry;
	unsigned char ret;	
	CurCommand=0x04;
	retry=ModbusRTU_Master_RetryTimes;
	ret=0;
	while(retry!=0)
	{
		crc.u16=0xffff;
		SetTx_ModbusRTU_Master();
		ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
		ModbusRTU_Master_VerifyTxByte(0x04);
		ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(0);
		ModbusRTU_Master_VerifyTxByte(count);
		ModbusRTU_Master_TxByte(crc.u8H);
		ModbusRTU_Master_TxByte(crc.u8L);
		SetRx_ModbusRTU_Master();
		ModbusRTU_Master_Flags.bRx=0;
		ModbusRTU_Master_Flags.bWaitClient=1;
		ModbusRTU_Master_WaitClientTick=SystemTick;
		ModbusRTU_Master_RxCount=0;
		//ModbusRTU_Master_RxErrTimes=0;
		ModbusRTU_Master_NeedRxCount=0xff;
		while(1)
		{
			if(ModbusRTU_Master_Flags.bRx)
				break;
			if((SystemTick-ModbusRTU_Master_WaitClientTick)>ModbusRTU_Master_WaitClientTime)//200ms等待超时
				break;
		}
		ModbusRTU_Master_Flags.bWaitClient=0;
		if(ModbusRTU_Master_Flags.bRx)
		{
			ret=1;
			break;
		}
		ModbusRTU_Master_WaitClientInterval();
		retry--;
	}
	SetTx_ModbusRTU_Master();
	return ret;
}
