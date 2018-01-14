#ifndef __ModbusRTU_Client_h__
#define __ModbusRTU_Client_h__


typedef union   
{
	struct
	{
		unsigned bRx:1;
	};
	uint8_t AllFlag;
} _ModbusRTU_Client_Flags;        // general flags

_ModbusRTU_Client_Flags ModbusRTU_Client_Flags;

#ifndef ModbusRTU_Client_VerifyTxByte_Ex
#define ModbusRTU_Client_VerifyTxByte(x) Uart1_VerifyCRC16AddTxByte(x)
#endif

#ifndef ModbusRTU_Client_TxByte_Ex
#define ModbusRTU_Client_TxByte(x) Uart1_PutChar(x)
#endif

#define pModbusRTU_ClientData 7
#define CheckVerify_ModbusRTU_Client()	crc16=GetVerify_CRC16(ModbusRTU_Client_RxList,ModbusRTU_Client_NeedRxCount-2); \
										if(crc16.u8s[0]==ModbusRTU_Client_RxList[ModbusRTU_Client_NeedRxCount-1] && crc16.u8s[1]==ModbusRTU_Client_RxList[ModbusRTU_Client_NeedRxCount-2])	\
											crc16.u8s[0]=1;	\
										else	\
											crc16.u8s[0]=0;
#ifndef MAX_ModbusRTU_Client_RX
#define MAX_ModbusRTU_Client_RX 50
#endif

#ifndef SetRx_ModbusRTU_Client_Ex
#define SetRx_ModbusRTU_Client() while(Uart_TRMT==0);__delay_ms(1);RS485DE_W=0
#endif

#ifndef SetTx_ModbusRTU_Client_Ex
#define SetTx_ModbusRTU_Client() RS485DE_W=1;__delay_ms(1)
#endif

uint8_t ModbusRTU_Client_RxList[MAX_ModbusRTU_Client_RX];
uint8_t ModbusRTU_Client_RxCount;
uint8_t ModbusRTU_Client_MyAddr;
uint ModbusRTU_Client_FirstRegAddr;

void Init_ModbusRTU_Client(void);
void ProcRx_ModbusRTU_Client(uint8_t rx);
void SendCommand03_ModbusRTU_Client(uint8_t *pBuff,uint8_t count);
void SendCommand16_ModbusRTU_Client(uint16_t FirstReg,uint8_t count);
#endif
