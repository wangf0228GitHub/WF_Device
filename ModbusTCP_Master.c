#include "HardwareProfile.h"

unsigned char CurCommand;//当前操作的指令号
void Init_ModbusTCP_Master(void)
{
	ModbusTCP_Master_MBAPIndex.u16=0;
}

void ProcRx_ModbusTCP_Master(unsigned char rx)
{
	if(ModbusTCP_Master_Flags.bRx)//之前没处理完
		return;
	if(!ModbusTCP_Master_Flags.bWaitClient)//当前没在等待
		return;
	ModbusTCP_Master_RxList[ModbusTCP_Master_RxCount++]=rx;
	if(ModbusTCP_Master_RxCount>10)
	{
		if(ModbusTCP_Master_RxCount==ModbusTCP_Master_NeedRxCount)
		{			
			ModbusTCP_Master_Flags.bRx=1;			
		}
		else if(ModbusTCP_Master_RxCount>ModbusTCP_Master_NeedRxCount)
		{
			ModbusTCP_Master_RxCount=0;
			ModbusTCP_Master_NeedRxCount=0xff;
		}
		else if(ModbusTCP_Master_RxCount>MAX_ModbusTCP_Master_RX)
		{
			ModbusTCP_Master_RxCount=0;
			ModbusTCP_Master_NeedRxCount=0xff;				
		}
	}	
	else if(ModbusTCP_Master_RxCount==9)//对于读来讲是字节数量
	{
		switch(CurCommand)
		{
		case 0x03://读入从机寄存器，接收时应接收rx+9个字节
			if(ModbusTCP_Master_NeedRxCount!=rx+9)
			{
				ModbusTCP_Master_RxCount=0;
				ModbusTCP_Master_NeedRxCount=0xff;
			}
			break;
		}
	}
	else if(ModbusTCP_Master_RxCount==8)//命令号
	{
		if(rx!=CurCommand)
		{
			ModbusTCP_Master_RxCount=0;
		}
		else
		{
			switch(CurCommand)
			{
			case 0x10://写入从机寄存器，接收时应接收12个字节
				if(ModbusTCP_Master_NeedRxCount!=12)
				{
					ModbusTCP_Master_RxCount=0;
					ModbusTCP_Master_NeedRxCount=0xff;
				}
				break;
			}
		}
	}
	else if(ModbusTCP_Master_RxCount==7)//子机地址
	{
		if(rx!=ModbusTCP_Master_SubAddr)
		{
			ModbusTCP_Master_RxCount=0;
		}
	}	
	else if(ModbusTCP_Master_RxCount==6)//长度
	{
		ModbusTCP_Master_NeedRxCount=MAX_ModbusTCP_Master_RX-6;
		if(rx>ModbusTCP_Master_NeedRxCount)//超出了目标缓冲区
		{
			ModbusTCP_Master_RxCount=0;
			ModbusTCP_Master_NeedRxCount=0xff;
		}
		else
			ModbusTCP_Master_NeedRxCount=rx+6;
	}
	else if(ModbusTCP_Master_RxCount==5)//长度高位为0
	{
		if(rx!=0)
		{
			ModbusTCP_Master_RxCount=0;
		}
	}	
	else if(ModbusTCP_Master_RxCount==4)//协议标识
	{
		if(rx!=0)
		{
			ModbusTCP_Master_RxCount=0;
		}
	}	
	else if(ModbusTCP_Master_RxCount==3)//协议标识
	{
		if(rx!=0)
		{
			ModbusTCP_Master_RxCount=0;
		}
	}	
	else if(ModbusTCP_Master_RxCount==2)//事务元标识符
	{
		if(rx!=ModbusTCP_Master_MBAPIndex.u8L)
		{
			ModbusTCP_Master_RxCount=0;
		}
	}	
	else if(ModbusTCP_Master_RxCount==1)//事务元标识符
	{
		if(rx!=ModbusTCP_Master_MBAPIndex.u8H)
		{
			ModbusTCP_Master_RxCount=0;
		}
	}	
}
#define ModbusTCP_Master_TxHeader() ModbusTCP_Master_TxByte(ModbusTCP_Master_MBAPIndex.u8H);\
									ModbusTCP_Master_TxByte(ModbusTCP_Master_MBAPIndex.u8L);\
									ModbusTCP_Master_TxByte(0);\
									ModbusTCP_Master_TxByte(0);\
									ModbusTCP_Master_TxByte(0);\
									ModbusTCP_Master_TxByte(count+7);\
									ModbusTCP_Master_TxByte(ModbusTCP_Master_SubAddr);
void SendCommand16_ModbusTCP_Master(unsigned char *pBuff,unsigned char count)
{
	unsigned char i;
	CurCommand=0x10;
	ModbusTCP_Master_TxHeader();
  	ModbusTCP_Master_TxByte(0x10);
  	ModbusTCP_Master_TxByte(ModbusTCP_Master_FirstRegAddr.u8H);
  	ModbusTCP_Master_TxByte(ModbusTCP_Master_FirstRegAddr.u8L);
  	i=count>>1;
  	ModbusTCP_Master_TxByte(0);
  	ModbusTCP_Master_TxByte(i);
  	ModbusTCP_Master_TxByte(count);
  	for(i=0;i<count;i++)
  	{
  		ModbusTCP_Master_TxByte(pBuff[i]);
  	}
}
