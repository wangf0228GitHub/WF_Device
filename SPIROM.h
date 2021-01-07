#ifndef __SPIROM_h__
#define __SPIROM_h__


#include "HardwareProfile.h" //"SPIROM_Conf.h"

//cs��wp���г�ʼ��
//���ⲿ����SPIROM_SPIInit()�����ڳ�ʼ��spi��ص�3������
//���ⲿ����uint8_t SPIROM_SPIProc(uint8_t c)
/************************************************************************/
/* ����оƬ                                                             */
/* 1. FM25H20  ״̬����WIPδ�ã��趨��SPIROM_Addr24						*/
/************************************************************************/

/************************************************************************
* EEPROM Commands                                                       
************************************************************************/
// #define SPIROM_PAGE_SIZE    (unsigned)64
// #define SPIROM_PAGE_MASK    (unsigned)0x003f
#define SPIROM_CMD_READ     (unsigned)0x03
#define SPIROM_CMD_WRITE    (unsigned)0x02
#define SPIROM_CMD_WRDI     (unsigned)0x04
#define SPIROM_CMD_WREN     (unsigned)0x06
#define SPIROM_CMD_RDSR     (unsigned)0x05
#define SPIROM_CMD_WRSR     (unsigned)0x01
/************************************************************************
* Structure STATREG and union _EEPROMStatus_                            
*                                                                       
* Overview: provide bits and byte access to EEPROM status value      
*                                                                       
************************************************************************/
typedef union   
{
	struct
	{
		unsigned WIP : 1;
		unsigned WEL : 1;
		unsigned BP0 : 1;
		unsigned BP1 : 1;
		unsigned RESERVED : 3;
		unsigned WPEN : 1;
	}Bits;
	uint8_t All;
} _SPIROM_Status;        // general flags
extern _SPIROM_Status SPIROM_Status;



void SPIROM_Init(void);

void SPIROM_ReadStatus(void);

#ifdef SPIROM_Addr24
void SPIROM_WriteByte(uint32_t address,uint8_t data);
#else
void SPIROM_WriteByte(uint16_t address,uint8_t data);
#endif

#ifdef SPIROM_Addr24
uint8_t SPIROM_ReadByte(uint32_t address);
#else
uint8_t SPIROM_ReadByte(uint16_t address);
#endif

#ifdef SPIROM_Addr24
void SPIROM_WriteArray(uint32_t address, uint8_t* pData,uint16_t nCount);
#else
void SPIROM_WriteArray(uint16_t address, uint8_t* pData,uint16_t nCount);
#endif
#ifdef SPIROM_Addr24
void SPIROM_Fill(uint32_t address, uint8_t Data,uint32_t nCount);
#else
void SPIROM_Fill(uint16_t address, uint8_t Data,uint16_t nCount);
#endif
#ifdef SPIROM_Addr24
void SPIROM_ReadArray(uint32_t address, uint8_t* pData,uint16_t nCount);
#else
void SPIROM_ReadArray(uint16_t address, uint8_t* pData,uint16_t nCount);
#endif

#endif // __SPIROM_h__
