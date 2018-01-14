#ifndef __ReBiaoCP_h__
#define __ReBiaoCP_h__


typedef union   
{
	struct
	{
		unsigned bRx:1;
		unsigned bWaitDataFromClient:1;	
	};
	uint8_t AllFlag;
} _ReBiaoCP_Flags;        // general flags


#ifndef ReBiaoCP_TxByte_Ex
#define ReBiaoCP_TxByteWithVerify(x) Uart1_VerifySumAddTxByte(x)
#define ReBiaoCP_TxByte(x) Uart1_PutChar(x)
#endif

#ifndef ReBiaoCP_WaitClientInterval_Ex
#define ReBiaoCP_WaitClientInterval() __delay_20ms(5);
#endif

#define pReBiaoCPData 7
#ifndef CheckVerify_ReBiaoCP
#define CheckVerify_ReBiaoCP()	sum=GetVerify_Sum(ReBiaoCP_RxList,ReBiaoCP_NeedRxCount-2); \
												if(sum==ReBiaoCP_RxList[ReBiaoCP_NeedRxCount-2])	\
													sum=1;	\
												else		\
													sum=0;
#endif

#define ReBiaoCP_AddTxHeader()	ReBiaoCP_TxByteWithVerify(0x16);	\
									ReBiaoCP_TxByteWithVerify(0x16);	\
									ReBiaoCP_TxByteWithVerify(ReBiaoCP_WaitClientAddr.u8H);	\
									ReBiaoCP_TxByteWithVerify(ReBiaoCP_WaitClientAddr.u8L);	\
									ReBiaoCP_TxByteWithVerify(ReBiaoCP_WaitCommand);
#define ReBiaoCP_AddTxEnder()	ReBiaoCP_TxByte(sum);	\
									ReBiaoCP_TxByte(0x0d);

#ifndef MAX_ReBiaoCP_RX
#define MAX_ReBiaoCP_RX 150
#endif

#ifndef SetRx_ReBiaoCP_Ex
#define SetRx_ReBiaoCP()  //NOP()//while(Uart_TRMT==0);__delay_ms(1);CP1616_RS485DE_W=0
#endif

#ifndef SetTx_ReBiaoCP_Ex
#define SetTx_ReBiaoCP() //NOP()//CP1616_RS485DE_W=1;__delay_ms(1)
#endif

// #ifndef ReBiaoCP_RetryTimes
// #define ReBiaoCP_RetryTimes 3
// #endif
extern _ReBiaoCP_Flags ReBiaoCP_Flags;
extern uint8_t ReBiaoCP_RxList[MAX_ReBiaoCP_RX];
extern uint8_t ReBiaoCP_RxCount;
extern uint8_t ReBiaoCP_NeedRxCount;
//extern uint ReBiaoCP_WaitClientAddr;
//extern uint8_t ReBiaoCP_WaitCommand;
extern uint16_t ReBiaoCP_WaitClientTick;
//extern uint8_t ReBiaoCP_RxErrTimes;
extern uint16_t ReBiaoCP_WaitClientTime;
extern uint8_t ReBiaoCP_RetryTimes;

void Init_ReBiaoCP(void);
void ProcRx_ReBiaoCP(uint8_t rx);
//uint8_t ReBiaoCPWaitClientData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count);
//void ReBiaoCPSendData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count);

uint8_t ReBiaoCP_Read10(uint8_t Addr);
#endif
