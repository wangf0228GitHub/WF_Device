#ifndef __CP1616_Client_h__
#define __CP1616_Client_h__

#ifndef SetRx_CP1616_Client_Ex
#define SetRx_CP1616_Client() while(TRMT==0);__delay_ms(1);RS485DE_W=0;
#endif

#ifndef SetTx_CP1616_Client_Ex
#define SetTx_CP1616_Client() __delay_ms(1);RS485DE_W=1;__delay_ms(1);
#endif
typedef union   
{
	struct
	{
		unsigned bRx:1;
	};
	uint8_t AllFlag;
} _CP1616_Client_Flags;        // general flags

#ifndef CP1616_Client_TxByteWithVerify_Ex
#define CP1616_Client_TxByteWithVerify(x) Uart1_VerifySumAddTxByte(x)
#define CP1616_Client_TxByte(x) Uart1_PutChar(x)
#endif

#define pCP1616_ClientData 7
#define pCP1616_CommandIndex 4

#ifndef CheckVerify_CP1616_Client
#define CheckVerify_CP1616_Client()	sum=GetVerify_Sum(CP1616_Client_RxList,CP1616_Client_NeedRxCount-2); \
												if(sum==CP1616_Client_RxList[CP1616_Client_NeedRxCount-2])	\
													{sum=1;}\
												else\
													{sum=0;}
#endif

#define CP1616_Client_AddTxHeader()	CP1616_Client_TxByteWithVerify(0x16);	\
						CP1616_Client_TxByteWithVerify(0x16);	\
						CP1616_Client_TxByteWithVerify(CP1616_Client_Addr.u8H);	\
						CP1616_Client_TxByteWithVerify(CP1616_Client_Addr.u8L);
#define CP1616_Client_AddTxEnder()	CP1616_Client_TxByte(sum);	\
						CP1616_Client_TxByte(0x0d);

#ifndef MAX_CP1616_Client_RX
#define MAX_CP1616_Client_RX 50
#endif

_CP1616_Client_Flags CP1616_Client_Flags;
uint8_t CP1616_Client_RxList[MAX_CP1616_Client_RX];
uint16_t CP1616_Client_RxCount;
uint16_t CP1616_Client_NeedRxCount;
uint16_t CP1616_Client_NoRxTick;
uint CP1616_Client_Addr;

void CP1616_Client_Init(void);
void CP1616_Client_EndProcCommand(void);
void CP1616_Client_ProcRx(uint8_t rx);
void CP1616_Client_SendData(uint8_t CommandIndex,uint8_t* pBuff,uint16_t Count);
void CP1616_Client_SendOK(uint8_t CommandIndex);
void CP1616_Client_SendError(uint8_t CommandIndex);


#ifdef CP1616_Client2
#ifndef SetRx_CP1616_Client2_Ex
#define SetRx_CP1616_Client2() while(TRMT==0);__delay_ms(1);CONTROL485_2=0;
#endif

#ifndef SetTx_CP1616_Client2_Ex
#define SetTx_CP1616_Client2() __delay_ms(1);CONTROL485_2=1;__delay_ms(1);
#endif
typedef union   
{
	struct
	{
		unsigned bRx:1;
	};
	uint8_t AllFlag;
} _CP1616_Client2_Flags;        // general flags

#ifndef CP1616_Client2_TxByteWithVerify
#define CP1616_Client2_TxByteWithVerify(x) Uart2_VerifySumAddTxByte(x)
#define CP1616_Client2_TxByte(x) Uart2_PutChar(x)
#endif


#define pCP1616_Client2Data 7
#define pCP1616_CommandIndex 4

#ifndef CheckVerify_CP1616_Client2
#define CheckVerify_CP1616_Client2()	sum=GetVerify_Sum(CP1616_Client2_RxList,CP1616_Client2_NeedRxCount-2); \
	if(sum==CP1616_Client2_RxList[CP1616_Client2_NeedRxCount-2])	\
{sum=1;}\
												else\
{sum=0;}
#endif

#define CP1616_Client2_AddTxHeader()	CP1616_Client2_TxByteWithVerify(0x16);	\
	CP1616_Client2_TxByteWithVerify(0x16);	\
	CP1616_Client2_TxByteWithVerify(CP1616_Client2_Addr.u8H);	\
	CP1616_Client2_TxByteWithVerify(CP1616_Client2_Addr.u8L);
#define CP1616_Client2_AddTxEnder()	CP1616_Client2_TxByte(sum);	\
	CP1616_Client2_TxByte(0x0d);

#ifndef MAX_CP1616_Client2_RX
#define MAX_CP1616_Client2_RX 50
#endif
_CP1616_Client2_Flags CP1616_Client2_Flags;
uint8_t CP1616_Client2_RxList[MAX_CP1616_Client2_RX];
uint16_t CP1616_Client2_RxCount;
uint16_t CP1616_Client2_NeedRxCount;
uint16_t CP1616_Client2_NoRxTick;
uint CP1616_Client2_Addr;

void CP1616_Client2_Init(void);
void CP1616_Client2_EndProcCommand(void);
void CP1616_Client2_ProcRx(uint8_t rx);
void CP1616_Client2_SendData(uint8_t CommandIndex,uint8_t* pBuff,uint16_t Count);
void CP1616_Client2_SendOK(uint8_t CommandIndex);
void CP1616_Client2_SendError(uint8_t CommandIndex);
#endif
#endif


