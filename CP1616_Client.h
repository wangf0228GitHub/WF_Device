#ifndef __CP1616_Client_h__
#define __CP1616_Client_h__

#include "stdint.h"
#include "CP1616_Client_Conf.h"

typedef union   
{
	struct
	{
		unsigned bRx:1;
	}Bits;
	uint8_t AllFlag;
} _CP1616_Client_Flags;        // general flags

#define pCP1616_ClientData 2+CP1616_AddrLen+1+CP1616_DataBufLen
#define pCP1616_CommandIndex 2+CP1616_AddrLen

_CP1616_Client_Flags CP1616_Client_Flags;
uint8_t CP1616_Client_RxList[MAX_CP1616_Client_RX];


#if CP1616_DataBufLen==1
uint8_t CP1616_Client_RxCount;
uint8_t CP1616_Client_NeedRxCount;
#else
uint16_t CP1616_Client_RxCount;
uint16_t CP1616_Client_NeedRxCount;
#endif


#if CP1616_AddrLen==1
uint8_t CP1616_Client_Addr;
#elif CP1616_AddrLen==2
uint16_t CP1616_Client_Addr;
#endif



void CP1616_Client_Init(void);
void CP1616_Client_EndProcCommand(void);
void CP1616_Client_ProcRx(uint8_t rx);
void CP1616_Client_SendData(uint8_t CommandIndex,uint8_t* pBuff,uint16_t Count);
void CP1616_Client_SendOK(uint8_t CommandIndex);
void CP1616_Client_SendError(uint8_t CommandIndex,uint8_t errNum);

#endif


