#ifndef __ModbusRTU_Master_h__
#define __ModbusRTU_Master_h__

typedef union   
{
	struct
	{
		unsigned bRx:1;
		unsigned bWaitClient:1;
	};
	unsigned char AllFlag;
} _ModbusRTU_Master_Flags;        // general flags

extern _ModbusRTU_Master_Flags ModbusRTU_Master_Flags;


#ifndef ModbusRTU_Master_TxByte_Ex
#define ModbusRTU_Master_VerifyTxByte(x) Uart1_VerifyCRC16AddTxByte(x)
#define ModbusRTU_Master_TxByte(x) Uart1_PutChar(x)
#endif

#ifndef ModbusRTU_Master_WaitClientInterval_Ex
#define ModbusRTU_Master_WaitClientInterval() __delay_20ms(5);
#endif

#define pModbusRTU_MasterData 7
#define CheckVerify_ModbusRTU_Master()	crc16=GetVerify_CRC16(ModbusRTU_Master_RxList,ModbusRTU_Master_NeedRxCount-2); \
										if(crc16.u8s[0]==ModbusRTU_Master_RxList[ModbusRTU_Master_NeedRxCount-1] && crc16.u8s[1]==ModbusRTU_Master_RxList[ModbusRTU_Master_NeedRxCount-2])	\
											crc16.u8s[0]=1;	\
										else	\
											crc16.u8s[0]=0;
#ifndef MAX_ModbusRTU_Master_RX
#define MAX_ModbusRTU_Master_RX 50
#endif


#ifndef SetRx_ModbusRTU_Master_Ex
#define SetRx_ModbusRTU_Master() while(ModbusRTU_Master_Uart_TRMT==0);__delay_ms(1);ModbusRTU_RS485DE_W=0
#endif

#ifndef SetTx_ModbusRTU_Master_Ex
#define SetTx_ModbusRTU_Master() ModbusRTU_RS485DE_W=1;__delay_ms(1)
#endif

#define ModbusRTU_Master_preRxProcInit() ModbusRTU_Master_Flags.bRx=0;ModbusRTU_Master_Flags.bWaitClient=1;ModbusRTU_Master_RxCount=0;ModbusRTU_Master_WaitClientTick=SystemTick;ModbusRTU_Master_NeedRxCount=0xff

extern unsigned char ModbusRTU_Master_RxList[MAX_ModbusRTU_Master_RX];
extern unsigned char ModbusRTU_Master_RxCount;
extern unsigned char ModbusRTU_Master_NeedRxCount;
extern unsigned char ModbusRTU_Master_TargetAddr;
//extern uint ModbusRTU_Master_FirstRegAddr;
extern unsigned char ModbusRTU_Master_RetryTimes;
extern unsigned int ModbusRTU_Master_WaitClientTick;
extern unsigned int ModbusRTU_Master_WaitClientTime;

void Init_ModbusRTU_Master(void);
void ProcRx_ModbusRTU_Master(unsigned char rx);
void ModbusRTU_Master_SendCommand16(unsigned int RegAddr,unsigned char *pBuff,unsigned char count);
unsigned char ModbusRTU_Master_ProcCommand16(unsigned int RegAddr,unsigned char* pBuff,unsigned int Count);
void ModbusRTU_Master_SendCommand03(unsigned int RegAddr,unsigned char count);
unsigned char ModbusRTU_Master_ProcCommand03(unsigned int RegAddr,unsigned char count);
void ModbusRTU_Master_SendCommand04(unsigned int RegAddr,unsigned char count);
unsigned char ModbusRTU_Master_ProcCommand04(unsigned int RegAddr,unsigned char count);
#endif
