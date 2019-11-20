
#include "wfEEPROM.h"


void wfEEPROM_ReadBytes(uint32_t Addr,uint8_t *Buffer,uint32_t Length) 
{  
	uint8_t *wAddr;  
	wAddr=(uint8_t*)(wfEEPROM_BASE_ADDR+Addr);  
	while(Length--)
	{  
		*Buffer++=*wAddr++;  
	}     
}

void wfEEPROM_ReadHalfWords(uint32_t Addr,uint16_t *Buffer,uint32_t Length)  
{  
	uint32_t *wAddr;  
	wAddr=(uint32_t*)(wfEEPROM_BASE_ADDR+Addr);  
	while(Length--)
	{  
		*Buffer++=*wAddr++;  
	}     
} 

void wfEEPROM_ReadWords(uint32_t Addr,uint32_t *Buffer,uint32_t Length)  
{  
	uint32_t *wAddr;  
	wAddr=(uint32_t*)(wfEEPROM_BASE_ADDR+Addr);  
	while(Length--)
	{  
		*Buffer++=*wAddr++;  
	}     
}
#ifdef STM32_Flash4EEPROM
// void wfEEPROM_WriteBytes(uint32_t WriteAddr,uint8_t *pBuffer,uint32_t NumToWrite)  
// {
// 	FLASH_EraseInitTypeDef FlashEraseInit;
// 	HAL_StatusTypeDef FlashStatus=HAL_OK;
// 	uint32_t SectorError=0;
// 	uint32_t addrx=0;
// 	uint32_t endaddr=0;	
// 	if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//非法地址
// 
// 	HAL_FLASH_Unlock();             //解锁	
// 	addrx=WriteAddr;				//写入的起始地址
// 	endaddr=WriteAddr+NumToWrite*4;	//写入的结束地址
// 
// 	if(addrx<0X1FFF0000)
// 	{
// 		while(addrx<endaddr)		//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
// 		{
// 			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//有非0XFFFFFFFF的地方,要擦除这个扇区
// 			{   
// 				FlashEraseInit.TypeErase=FLASH_TYPEERASE_SECTORS;       //擦除类型，扇区擦除 
// 				FlashEraseInit.Sector=STMFLASH_GetFlashSector(addrx);   //要擦除的扇区
// 				FlashEraseInit.NbSectors=1;                             //一次只擦除一个扇区
// 				FlashEraseInit.VoltageRange=FLASH_VOLTAGE_RANGE_3;      //电压范围，VCC=2.7~3.6V之间!!
// 				if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
// 				{
// 					break;//发生错误了	
// 				}
// 			}else addrx+=4;
// 			FLASH_WaitForLastOperation(FLASH_WAITETIME);                //等待上次操作完成
// 		}
// 	}
// 	FlashStatus=FLASH_WaitForLastOperation(FLASH_WAITETIME);            //等待上次操作完成
// 	if(FlashStatus==HAL_OK)
// 	{
// 		while(WriteAddr<endaddr)//写数据
// 		{
// 			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,WriteAddr,*pBuffer)!=HAL_OK)//写入数据
// 			{ 
// 				break;	//写入异常
// 			}
// 			WriteAddr+=4;
// 			pBuffer++;
// 		}  
// 	}
// 	HAL_FLASH_Lock();           //上锁
// } 
// 
// void wfEEPROM_WriteHalfWords(uint32_t WriteAddr,uint16_t *pBuffer,uint32_t NumToWrite)  
// {  
// 	uint16_t t;  
// 	HAL_FLASHEx_DATAEEPROM_Unlock();      
// 	for(t = 0;t < NumToWrite;t++)  
// 	{  
// 		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_HALFWORD,wfEEPROM_BASE_ADDR + WriteAddr + t,*(pBuffer + t));  
// 	}  
// 	HAL_FLASHEx_DATAEEPROM_Unlock();  
// }
// 
// void wfEEPROM_WriteWords(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)  
// {  
// 	uint16_t t;  
// 	HAL_FLASHEx_DATAEEPROM_Unlock();      
// 	for(t = 0;t < NumToWrite;t++)  
// 	{  
// 		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,wfEEPROM_BASE_ADDR + WriteAddr + t,*(pBuffer + t));  
// 	}  
// 	HAL_FLASHEx_DATAEEPROM_Unlock();  
// }
void wfEEPROM_WriteWords(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)	
{ 
	uint32_t i;
	FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus=HAL_OK;
	uint32_t SectorError=0;
	HAL_FLASH_Unlock();             //解锁	
	FlashEraseInit.TypeErase=FLASH_TYPEERASE_PAGES;       //擦除类型，页擦除 
	FlashEraseInit.PageAddress=WriteAddr;   //要擦除的页，即写入地址
	FlashEraseInit.NbPages=1;               //只擦除一页
	if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
	{
		HAL_FLASH_Lock();           //上锁
		return;//发生错误了	
	}	
	FlashStatus=FLASH_WaitForLastOperation(FLASH_WAITETIME);            //等待上次操作完成
	if(FlashStatus==HAL_OK)
	{
		for(i=0;i<NumToWrite;i++)
		{
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,WriteAddr,*pBuffer)!=HAL_OK)//写入数据
			{ 
				break;	//写入异常
			}
			WriteAddr+=4;
			pBuffer++;
		}
	}
	HAL_FLASH_Lock();           //上锁
}
#else
void wfEEPROM_WriteBytes(uint32_t WriteAddr,uint8_t *pBuffer,uint32_t NumToWrite)  
{  
	uint32_t t;  
	HAL_FLASHEx_DATAEEPROM_Unlock();      
	for(t = 0;t < NumToWrite;t++)  
	{  
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,wfEEPROM_BASE_ADDR + WriteAddr + t,*(pBuffer + t));  
	}  
	HAL_FLASHEx_DATAEEPROM_Lock();  
} 

void wfEEPROM_WriteHalfWords(uint32_t WriteAddr,uint16_t *pBuffer,uint32_t NumToWrite)  
{  
	uint32_t t;  
	HAL_FLASHEx_DATAEEPROM_Unlock();      
	for(t = 0;t < NumToWrite;t++)  
	{  
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_HALFWORD,wfEEPROM_BASE_ADDR + WriteAddr + t,*(pBuffer + t));  
	}  
	HAL_FLASHEx_DATAEEPROM_Lock();  
}

void wfEEPROM_WriteWords(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)  
{  
	uint32_t t;  
	HAL_FLASHEx_DATAEEPROM_Unlock();      
	for(t = 0;t < NumToWrite;t++)  
	{  
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,wfEEPROM_BASE_ADDR + WriteAddr + t,*(pBuffer + t));  
	}  
	HAL_FLASHEx_DATAEEPROM_Lock();  
}
#endif


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
