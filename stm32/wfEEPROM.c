
#include "wfEEPROM.h"

void wfEEPROM_ReadBytes(uint16_t Addr,uint8_t *Buffer,uint16_t Length) 
{  
	uint8_t *wAddr;  
	wAddr=(uint8_t*)(wfEEPROM_BASE_ADDR+Addr);  
	while(Length--)
	{  
		*Buffer++=*wAddr++;  
	}     
}

void wfEEPROM_ReadHalfWords(uint16_t Addr,uint16_t *Buffer,uint16_t Length)  
{  
	uint32_t *wAddr;  
	wAddr=(uint32_t*)(wfEEPROM_BASE_ADDR+Addr);  
	while(Length--)
	{  
		*Buffer++=*wAddr++;  
	}     
} 

void wfEEPROM_ReadWords(uint16_t Addr,uint32_t *Buffer,uint16_t Length)  
{  
	uint32_t *wAddr;  
	wAddr=(uint32_t*)(wfEEPROM_BASE_ADDR+Addr);  
	while(Length--)
	{  
		*Buffer++=*wAddr++;  
	}     
}

void wfEEPROM_WriteBytes(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)  
{  
	uint16_t t;  
	HAL_FLASHEx_DATAEEPROM_Unlock();      
	for(t = 0;t < NumToWrite;t++)  
	{  
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,wfEEPROM_BASE_ADDR + WriteAddr + t,*(pBuffer + t));  
	}  
	HAL_FLASHEx_DATAEEPROM_Unlock();  
} 

void wfEEPROM_WriteHalfWords(uint16_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite)  
{  
	uint16_t t;  
	HAL_FLASHEx_DATAEEPROM_Unlock();      
	for(t = 0;t < NumToWrite;t++)  
	{  
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_HALFWORD,wfEEPROM_BASE_ADDR + WriteAddr + t,*(pBuffer + t));  
	}  
	HAL_FLASHEx_DATAEEPROM_Unlock();  
}

void wfEEPROM_WriteWords(uint16_t WriteAddr,uint32_t *pBuffer,uint16_t NumToWrite)  
{  
	uint16_t t;  
	HAL_FLASHEx_DATAEEPROM_Unlock();      
	for(t = 0;t < NumToWrite;t++)  
	{  
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,wfEEPROM_BASE_ADDR + WriteAddr + t,*(pBuffer + t));  
	}  
	HAL_FLASHEx_DATAEEPROM_Unlock();  
}

// void wfEEPROM_WriteByte( uint16_t WriteAddr,uint8_t data )
// {
// 	uint16_t t;  
// 	HAL_FLASHEx_DATAEEPROM_Unlock();      
// 	for(t = 0;t < NumToWrite;t++)  
// 	{  
// 		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,wfEEPROM_BASE_ADDR + WriteAddr + t,*(pBuffer + t));  
// 	}  
// 	HAL_FLASHEx_DATAEEPROM_Unlock();  
// }
// 
// void wfEEPROM_WriteHalfWord( uint16_t WriteAddr,uint16_t data )
// {
// 
// }
// 
// void wfEEPROM_WriteWord( uint16_t WriteAddr,uint32_t data )
// {
// 
// }
