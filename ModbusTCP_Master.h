#ifndef __ModbusTCP_Master_h__
#define __ModbusTCP_Master_h__

typedef union   
{
	struct
	{
		unsigned bRx:1;
		unsigned bWaitClient:1;
	};
	unsigned char AllFlag;
} _ModbusTCP_Master_Flags;        // general flags

_ModbusTCP_Master_Flags ModbusTCP_Master_Flags;

#ifndef ModbusTCP_Master_TxByte
#define ModbusTCP_Master_TxByte(x) Uart_PutChar(x)
#endif

#define pModbusTCP_MasterData 8

#ifndef MAX_ModbusTCP_Master_RX
#define MAX_ModbusTCP_Master_RX 50
#endif
unsigned char ModbusTCP_Master_RxList[MAX_ModbusTCP_Master_RX];
unsigned char ModbusTCP_Master_RxCount;
unsigned char ModbusTCP_Master_NeedRxCount;
uint ModbusTCP_Master_FirstRegAddr;
uint ModbusTCP_Master_MBAPIndex;//事务元标识符
//const uint ModbusTCP_ProtocolID=0;//协议标识符，modbus为0
unsigned char ModbusTCP_Master_SubAddr;//单元标识符,即子机地址,通过路由器连接

void Init_ModbusTCP_Master(void);
void ProcRx_ModbusTCP_Master(unsigned char rx);
void SendCommand16_ModbusTCP_Master(unsigned char *pBuff,unsigned char count);

#endif
