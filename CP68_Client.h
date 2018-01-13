#ifndef __CP68_Client_h__
#define __CP68_Client_h__

#include "main.h"
#include "CP68_Client_Conf.h"

/************************************************************************/
/* 命令定义                                                             */
/************************************************************************/
#define CP68_SysCommand_ReadData 0x01 //读数据
#define CP68_SysCommand_WriteData 0x04 //写数据
#define CP68_SysCommand_ReadPSWVer 0x09 //读密匙版本号
#define CP68_SysCommand_ReadAddr 0x03 //读地址（表号）
#define CP68_SysCommand_WriteAddr 0x15 //写地址（表号）
#define CP68_SysCommand_WriteSync 0x16 //写机电同步数（置表底数）


typedef union   
{
	struct
	{
		unsigned bRx:1;
		unsigned bValid:1;
	}Bits;
	uint8_t AllFlag;
} _CP68_Client_Flags;        // general flags


#define CP68_FrameOther 1+1+7+1+1+1+1
#define CP68__FrameDataOffset 11

#define CP68_Client_RxDataBufLen 100
typedef union   
{
	struct
	{
		uint8_t FrameHeader;
		uint8_t DeviceType;//仪表类型
		uint8_t DeviceAddr[7];//表地址
		uint8_t ControlCode;//控制码
		uint8_t DataLen;
		uint8_t DataBuf[CP68_Client_RxDataBufLen+2];			
	}RxStruct;
	uint8_t AllRxData[CP68_Client_RxDataBufLen+CP68_FrameOther];
} _CP68_Client_RxBuf;        // general flags


//#ifndef CP68_Client_TxDataBufLen
#define CP68_Client_TxDataBufLen 50
//#endif

typedef union   
{
	struct
	{
		uint8_t FrameHeader;
		uint8_t DeviceType;//仪表类型
		uint8_t DeviceAddr[7];//表地址
		uint8_t ControlCode;//控制码
		uint8_t DataLen;
		uint8_t DataBuf[CP68_Client_TxDataBufLen+2];	
				
	}TxStruct;
	uint8_t AllTxData[CP68_Client_TxDataBufLen+CP68_FrameOther];
} _CP68_Client_TxBuf;        // general flags

// 
extern volatile _CP68_Client_Flags CP68_Client_Flags;
extern volatile uint32_t CP68_Client_NoRxTick;
extern volatile uint16_t CP68_Client_RxBufIndex;
extern volatile _CP68_Client_RxBuf CP68_Client_RxBuf;
extern volatile _CP68_Client_TxBuf CP68_Client_TxBuf;
extern volatile uint32_t CP68_Client_TxTimeOut;
// extern volatile uint8_t myDeviceAddr[7];//仪表类型
// extern volatile uint8_t DeviceType;//仪表类型

void CP68_Client_CheckRxBuf(void);
void CP68_Client_Init(void);
void CP68_Client_EndProcCommand(void);
void CP68_Client_ProcRx(uint8_t rx);
void CP68_Client_SendData(uint8_t CommandIndex,uint8_t* pBuff,uint8_t Count);
void CP68_Client_SendSelf(uint8_t ControlCode,uint8_t Count);
//void ProcCommandFromPC( void );
// void CP68_Client_SendOK(uint8_t CommandIndex);
// void CP68_Client_SendError(uint8_t CommandIndex,uint8_t errCode);
#endif


