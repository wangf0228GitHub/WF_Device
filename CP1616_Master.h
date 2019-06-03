#ifndef __CP1616_Master_h__
#define __CP1616_Master_h__

#include "HardwareProfile.h"

typedef union   
{
	struct
	{
		unsigned bRx:1;
		unsigned bWaitDataFromClient:1;	
	}Bits;
	uint8_t AllFlag;
} _CP1616_Master_Flags;        // general flags


#ifndef CP1616_Master_TxByte_Ex
#define CP1616_Master_TxByteWithVerify(x) Uart1_VerifySumAddTxByte(x)
#define CP1616_Master_TxByte(x) Uart1_PutChar(x)
#endif

#ifndef CP1616_Master_WaitClientInterval_Ex
#define CP1616_Master_WaitClientInterval() __delay_20ms(5);
#endif

#define pCP1616_MasterData 2+CP1616_Master_AddrLen+1+CP1616_Master_DataBufLen
#define pCP1616_Master_CommandIndex 2+CP1616_Master_AddrLen

#ifndef CheckVerify_CP1616_Master
#define CheckVerify_CP1616_Master()	sum=GetVerify_Sum(CP1616_Master_RxList,CP1616_Master_NeedRxCount-2); \
												if(sum==CP1616_Master_RxList[CP1616_Master_NeedRxCount-2])	\
													sum=1;	\
												else		\
													sum=0;
#endif

#ifndef MAX_CP1616_Master_RX
#define MAX_CP1616_Master_RX 50
#endif

#ifndef CP1616_Master_SetRx_Ex
#define CP1616_Master_SetRx() //while(Uart_TRMT==0);__delay_ms(1);CP1616_RS485DE_W=0
#endif

#ifndef CP1616_Master_SetTx_Ex
#define CP1616_Master_SetTx() //CP1616_RS485DE_W=1;__delay_ms(1)
#endif

// #ifndef CP1616_Master_RetryTimes
// #define CP1616_Master_RetryTimes 3
// #endif
//extern uint8_t CP1616_Master_RxErrTimes;

#if CP1616_Master_DataBufLen==1
	extern uint8_t CP1616_Master_RxCount;
	extern uint8_t CP1616_Master_NeedRxCount;
#else
	extern uint16_t CP1616_Master_RxCount;
	extern uint16_t CP1616_Master_NeedRxCount;
#endif

#if CP1616_Master_AddrLen==1
	extern uint8_t CP1616_Master_Addr;
	extern uint8_t CP1616_Master_WaitClientAddr;
#elif CP1616_Master_AddrLen==2
	extern uint16_t CP1616_Master_Addr;
	extern uint16_t CP1616_Master_WaitClientAddr;
#endif



extern volatile _CP1616_Master_Flags CP1616_Master_Flags;
extern uint8_t CP1616_Master_RxList[MAX_CP1616_Master_RX];

extern uint8_t CP1616_Master_WaitCommand;
extern uint16_t CP1616_Master_WaitClientTick;

extern uint16_t CP1616_Master_WaitClientTime;
extern uint8_t CP1616_Master_RetryTimes;

void CP1616_Master_Init(void);
void CP1616_Master_ProcRx(uint8_t rx);

#if (CP1616_Master_AddrLen==1) && (CP1616_Master_DataBufLen==1)
unsigned char CP1616_MasterWaitClientData(uint8_t Addr,uint8_t Command,uint8_t* pBuff,uint8_t Count);
#elif (CP1616_Master_AddrLen==1) && (CP1616_Master_DataBufLen==2)
unsigned char CP1616_MasterWaitClientData(uint8_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count);
#elif (CP1616_Master_AddrLen==2) && (CP1616_Master_DataBufLen==1)
unsigned char CP1616_MasterWaitClientData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint8_t Count);
#elif (CP1616_Master_AddrLen==2) && (CP1616_Master_DataBufLen==2)
unsigned char CP1616_MasterWaitClientData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count);
#elif (CP1616_Master_AddrLen==0) && (CP1616_Master_DataBufLen==1)
unsigned char CP1616_MasterWaitClientData(uint8_t Command,uint8_t* pBuff,uint8_t Count);
#elif (CP1616_Master_AddrLen==0) && (CP1616_Master_DataBufLen==2)
unsigned char CP1616_MasterWaitClientData(uint8_t Command,uint8_t* pBuff,uint16_t Count);
#endif


#if (CP1616_Master_AddrLen==1) && (CP1616_Master_DataBufLen==1)
void CP1616_MasterSendData(uint8_t Addr,uint8_t Command,uint8_t* pBuff,uint8_t Count);
#elif (CP1616_Master_AddrLen==1) && (CP1616_Master_DataBufLen==2)
void CP1616_MasterSendData(uint8_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count);
#elif (CP1616_Master_AddrLen==2) && (CP1616_Master_DataBufLen==1)
void CP1616_MasterSendData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint8_t Count);
#elif (CP1616_Master_AddrLen==2) && (CP1616_Master_DataBufLen==2)
void CP1616_MasterSendData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count);
#elif (CP1616_Master_AddrLen==0) && (CP1616_Master_DataBufLen==1)
void CP1616_MasterSendData(uint8_t Command,uint8_t* pBuff,uint8_t Count);
#elif (CP1616_Master_AddrLen==0) && (CP1616_Master_DataBufLen==2)
void CP1616_MasterSendData(uint8_t Command,uint8_t* pBuff,uint16_t Count);
#endif
#endif
