#ifndef __M24XX_h__
#define __M24XX_h__

#ifndef M24XX_RetryCount
#define M24XX_RetryCount 2
#endif

#ifndef M24XX_ADDR_W
#define  M24XX_ADDR_W	0xa0//Ѱַ�ֽ�д
#endif
#ifndef M24XX_ADDR_R
#define  M24XX_ADDR_R	0xa1//Ѱַ�ֽڶ�
#endif
void M24XX_Init(void);

#ifdef M24XX_1024
	uint8_t M24XX_Read(uint8_t *pBuff,uint16_t Count,uint32_t Address);
	uint8_t M24XX_Write(uint8_t *pBuff,uint16_t Count,uint32_t Address);
#else
	uint8_t M24XX_Read(uint8_t *pBuff,uint16_t Count,uint16_t Address);
	uint8_t M24XX_Write(uint8_t *pBuff,uint8_t Count,uint16_t Address);
#endif

#endif

