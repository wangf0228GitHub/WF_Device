#ifndef __ModbusRTU_Master_h__
#define __ModbusRTU_Master_h__

#include "main.h"
#include "stdint.h"
#include "ModbusRTU_Master_Conf.h"
typedef union   
{
	struct
	{
		unsigned bRx:1;
		unsigned bWaitClient:1;
	};
	uint8_t AllFlag;
} _ModbusRTU_Master_Flags;        // general flags

extern _ModbusRTU_Master_Flags ModbusRTU_Master_Flags;




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

#define ModbusRTU_Master_preRxProcInit() ModbusRTU_Master_Flags.bRx=0;ModbusRTU_Master_Flags.bWaitClient=1;ModbusRTU_Master_RxCount=0;ModbusRTU_Master_WaitClientTick=wfGetTick();ModbusRTU_Master_NeedRxCount=0xff

extern uint8_t ModbusRTU_Master_RxList[MAX_ModbusRTU_Master_RX];
#ifdef MCU_STM32
extern uint32_t ModbusRTU_Master_RxCount;
extern uint32_t ModbusRTU_Master_NeedRxCount;
extern uint32_t ModbusRTU_Master_TargetAddr;
extern uint32_t ModbusRTU_Master_RetryTimes;
extern uint32_t ModbusRTU_Master_WaitClientTick;
extern uint32_t ModbusRTU_Master_WaitClientTime;
#else
extern uint8_t ModbusRTU_Master_RxCount;
extern uint8_t ModbusRTU_Master_NeedRxCount;
extern uint8_t ModbusRTU_Master_TargetAddr;
extern uint8_t ModbusRTU_Master_RetryTimes;
extern uint16_t ModbusRTU_Master_WaitClientTick;
extern uint16_t ModbusRTU_Master_WaitClientTime;
#endif



#ifdef ModbusRTU_Master_UseTxList
#ifndef MAX_ModbusRTU_Master_TX
	#define MAX_ModbusRTU_Master_TX 50
#endif
extern uint8_t ModbusRTU_Master_TxList[MAX_ModbusRTU_Master_RX];
extern uint32_t ModbusRTU_Master_TxCount;
#else
	#ifndef ModbusRTU_Master_TxByte_Ex
		#define ModbusRTU_Master_VerifyTxByte(x) Uart1_VerifyCRC16AddTxByte(x)
		#define ModbusRTU_Master_TxByte(x) Uart1_PutChar(x)
	#endif
#endif


void Init_ModbusRTU_Master(void);
void ProcRx_ModbusRTU_Master(uint8_t rx);
void ModbusRTU_Master_SendCommand16(uint16_t RegAddr,uint8_t *pBuff,uint8_t count);
uint8_t ModbusRTU_Master_ProcCommand16(uint16_t RegAddr,uint8_t* pBuff,uint16_t Count);
void ModbusRTU_Master_SendCommand03(uint16_t RegAddr,uint8_t count);
uint8_t ModbusRTU_Master_ProcCommand03(uint16_t RegAddr,uint8_t count);
void ModbusRTU_Master_SendCommand04(uint16_t RegAddr,uint8_t count);
uint8_t ModbusRTU_Master_ProcCommand04(uint16_t RegAddr,uint8_t count);
#endif
