#ifndef __wfEEPROM_h__
#define __wfEEPROM_h__

#include <stdint.h>

#ifndef wfEEPROM_INFO
#define wfEEPROM_BASE_ADDR    0x08080000    
#define wfEEPROM_BYTE_SIZE    0x0FFF
#endif

#define wfEEPROM_ReadByte(Addr) *((uint8_t*)(wfEEPROM_BASE_ADDR+Addr))
#define wfEEPROM_ReadHalfWord(Addr) *((uint32_t*)(wfEEPROM_BASE_ADDR+Addr))
#define wfEEPROM_ReadWord(Addr) *((uint32_t*)(wfEEPROM_BASE_ADDR+Addr))

#define wfEEPROM_WriteByte(Addr,x) HAL_FLASHEx_DATAEEPROM_Unlock();HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,wfEEPROM_BASE_ADDR + Addr,x);HAL_FLASHEx_DATAEEPROM_Unlock()
#define wfEEPROM_WriteHalfWord(Addr,x) HAL_FLASHEx_DATAEEPROM_Unlock();HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_HALFWORD,wfEEPROM_BASE_ADDR + Addr,x);HAL_FLASHEx_DATAEEPROM_Unlock()
#define wfEEPROM_WriteWord(Addr,x) HAL_FLASHEx_DATAEEPROM_Unlock();HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,wfEEPROM_BASE_ADDR + Addr,x);HAL_FLASHEx_DATAEEPROM_Unlock()
// __STATIC_INLINE uint8_t wfEEPROM_ReadByte(uint16_t Addr
// {
// 	return *((uint8_t*)(wfEEPROM_BASE_ADDR+Addr));
// }
void wfEEPROM_ReadBytes(uint16_t Addr,uint8_t *Buffer,uint16_t Length);
void wfEEPROM_ReadHalfWords(uint16_t Addr,uint16_t *Buffer,uint16_t Length);
void wfEEPROM_ReadWords(uint16_t Addr,uint32_t *Buffer,uint16_t Length);
void wfEEPROM_WriteBytes(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);
void wfEEPROM_WriteHalfWords(uint16_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);
void wfEEPROM_WriteWords(uint16_t WriteAddr,uint32_t *pBuffer,uint16_t NumToWrite);
#endif // __SimSPI_h__
