#ifndef __CP1616_Client_h__
#define __CP1616_Client_h__


#include "HardwareProfile.h"

#ifndef CP1616_Client_SetRx_Ex
#define CP1616_Client_SetRx()
#endif

#ifndef CP1616_Client_SetTx_Ex
#define CP1616_Client_SetTx()
#endif


typedef union   
{
	struct
	{
		unsigned bRx:1;
	}Bits;
#ifdef MCU32
	uint32_t AllFlag;
#else 
    uint8_t AllFlag;
#endif
} _CP1616_Client_Flags;        // general flags

#define pCP1616_Client_DataIndex 2u+CP1616_Client_AddrLen+1u+CP1616_Client_DataBufLen
#define pCP1616_Client_CommandIndex 2u+CP1616_Client_AddrLen



#ifndef CP1616_Client_RxList_LenMax
#define CP1616_Client_RxList_LenMax 100
#endif

#if CP1616_Client_DataBufLen==1
extern volatile uint8_t CP1616_Client_RxCount;
extern volatile uint8_t CP1616_Client_NeedRxCount;
#else
extern volatile uint16_t CP1616_Client_RxCount;
extern volatile uint16_t CP1616_Client_NeedRxCount;
#endif


#if CP1616_Client_AddrLen==1
extern volatile uint8_t CP1616_Client_Addr;
#elif CP1616_Client_AddrLen==2
extern volatile uint16_t CP1616_Client_Addr;
#endif

#ifndef CP1616_Client_Tx_OneByOne
#ifndef CP1616_Client_TxList_LenMax
#define CP1616_Client_TxList_LenMax 100
#endif
extern volatile uint8_t CP1616_Client_TxList[CP1616_Client_TxList_LenMax];
#endif

extern volatile uint8_t CP1616_Client_RxList[CP1616_Client_RxList_LenMax];
extern volatile _CP1616_Client_Flags CP1616_Client_Flags;

void CP1616_Client_Init(void);
void CP1616_Client_EndProcCommand(void);
void CP1616_Client_ProcRx(uint8_t rx);
void CP1616_Client_SendData(uint8_t CommandIndex,uint8_t* pBuff,uint16_t Count);
void CP1616_Client_SendOK(uint8_t CommandIndex);
void CP1616_Client_SendError(uint8_t CommandIndex,uint8_t errNum);
uint8_t CP1616_Client_SendHeader(uint8_t CommandIndex,uint16_t Count);

#ifndef CP1616_Client_Tx_OneByOne
void CP1616_Client_SendAllData(uint8_t CommandIndex, uint16_t Count);
#endif


#ifdef CP1717_Client
#ifndef CP1717_Client_SetRx_Ex
#define CP1717_Client_SetRx()
#endif

#ifndef CP1717_Client_SetTx_Ex
#define CP1717_Client_SetTx()
#endif


typedef union   
{
	struct
	{
		unsigned bRx:1;
	}Bits;
#ifdef MCU32
	uint32_t AllFlag;
#else
    uint8_t AllFlag;
#endif
} _CP1717_Client_Flags;        // general flags

#define pCP1717_ClientData 2+CP1717_Client_AddrLen+1+CP1717_Client_DataBufLen
#define pCP1717_CommandIndex 2+CP1717_Client_AddrLen



#ifndef CP1717_Client_RxList_LenMax
#define CP1717_Client_RxList_LenMax 100
#endif

#if CP1717_Client_DataBufLen==1
extern uint8_t CP1717_Client_RxCount;
extern uint8_t CP1717_Client_NeedRxCount;
#else
extern uint16_t CP1717_Client_RxCount;
extern uint16_t CP1717_Client_NeedRxCount;
#endif


#if CP1717_Client_AddrLen==1
extern uint8_t CP1717_Client_Addr;
#elif CP1717_Client_AddrLen==2
extern uint16_t CP1717_Client_Addr;
#endif

#ifndef CP1717_Client_Tx_OneByOne
#ifndef CP1717_Client_TxList_LenMax
#define CP1717_Client_TxList_LenMax 100
#endif
extern uint8_t CP1717_Client_TxList[CP1717_Client_TxList_LenMax];
#endif

extern uint8_t CP1717_Client_RxList[CP1717_Client_RxList_LenMax];
extern _CP1717_Client_Flags CP1717_Client_Flags;

void CP1717_Client_Init(void);
void CP1717_Client_EndProcCommand(void);
void CP1717_Client_ProcRx(uint8_t rx);
void CP1717_Client_SendData(uint8_t CommandIndex,uint8_t* pBuff,uint16_t Count);
void CP1717_Client_SendOK(uint8_t CommandIndex);
void CP1717_Client_SendError(uint8_t CommandIndex,uint8_t errNum);
uint8_t CP1717_Client_SendHeader(uint8_t CommandIndex,uint16_t Count);
#endif
#endif


