#ifndef _wfDefine_H
#define _wfDefine_H

#include <stdint.h>

#define MAKE_BYTE(h,l)	((h<<4)+(l&0x0f))
#define MAKE_SHORT(h,l)	(((uint16_t)h<<8)+l)
#define MAKE_INT(h,l)	(((uint32_t)h<<16)+l)

#define LOW_NIBBLE(x)	(x&0x0F)
#define HIGH_NIBBLE(x)	(x>>4)
#define LOW_BYTE(x)     ((uint8_t)((x)&0xFF))
#define HIGH_BYTE(x)    ((uint8_t)(((x)>>8)&0xFF))
#define LOW_SHORT(x)     ((uint16_t)((x)&0xFFFF))
#define HIGH_SHORT(x)    ((uint16_t)(((x)>>16)&0xFFFF))

#define WF_CHECK_FLAG(__Instance__, __FLAG__)   ((((__Instance__) & (__FLAG__)) != 0) ? 1 : 0)
#define ClrBit_uint8(b,index) b &= (uint8_t)(~(1 << index))
#define SetBit_uint8(b,index) b |= (uint8_t)(1 << index)

#define ClrBit_uin16(b,index) b &= (uint16_t)(~(1 << index))
#define SetBit_uint16(b,index) b |= (uint16_t)(1 << index)

#define ClrBit_uint32(b,index) b &= (uint32_t)(~(1 << index))
#define SetBit_uint32(b,index) b |= (uint32_t)(1 << index)

#define GetBit(b,index) ((((b) & (1<<index)) != 0) ? 1 : 0)

uint8_t BCD2Char(uint8_t bcd);
void Byte2ASCII(uint8_t b, uint8_t *h, uint8_t *l);
uint8_t ASCII2Byte_Capital(uint8_t h,uint8_t l);
uint8_t ASCII2Byte_Lowercase(uint8_t h,uint8_t l);

#endif

