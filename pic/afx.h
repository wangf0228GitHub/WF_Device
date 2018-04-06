#ifndef __afx_H_
#define __afx_H_

#include "main.h"
#include <stdint.h>

#ifndef __PICC18__

#define LOW_BYTE(x)     ((uint8_t)((x)&0xFF))
#define HIGH_BYTE(x)    ((uint8_t)(((x)>>8)&0xFF))
#define LOW_WORD(x)     ((unsigned short)((x)&0xFFFF))
#define HIGH_WORD(x)    ((unsigned short)(((x)>>16)&0xFFFF))
#define WRITETIMER1(x) ((void)(TMR1H=((x)>>8),TMR1L=((x)&0xFF)))
#define READTIMER1() (MAKE_INT(TMR1H,TMR1L))
#define WRITETIMER0(x) ((void)(TMR0H=((x)>>8),TMR0L=((x)&0xFF)))
#define READTIMER0() (MAKE_INT(TMR0H,TMR0L))
#endif

#ifdef MCC30
//#define __delay_us(x) __delay32((uint32_t)((x)*(FCY/1000000.0)))
//#define __delay_ms(x) __delay32((uint32_t)((x)*(FCY/1000.0)))
extern uint8_t wCPU_IPL;
#define di() SET_AND_SAVE_CPU_IPL(wCPU_IPL,7)//(_IPL=7)
#define ei() RESTORE_CPU_IPL(wCPU_IPL)//(_IPL=0)

#define _EE_int        1
#define _EE_2WORDs     4
#ifndef __PIC24F__
#define _EEDATA(N)   __attribute__((space(eedata),aligned(N)))
#define _EE_WORD        2
#define _EE_4WORDS      8
#define _EE_8WORDS     16
#endif
#endif
#define UcQX(X,Y) (uint8_t)((uint8_t)(1<<X)*(Y) + 0.5)
#define UiQX(X,Y) (uint16_t)((uint16_t)(1<<X)*(Y) + 0.5)
#define UlQX(X,Y) (uint32_t)((uint32_t)((uint32_t)1<<X)*(Y) + 0.5)
#define cQX(X,Y) ((Y < 0.0) ? (char)((char)(1<<X)*(Y) - 0.5) : (char)((char)(1<<X)*(Y) + 0.5))
#define iQX(X,Y) ((Y < 0.0) ? (int)((int)(1<<X)*(Y) - 0.5) : (int)((int)(1<<X)*(Y) + 0.5))
#define lQX(X,Y) ((Y < 0.0) ? (long)((long)(1<<X)*(Y) - 0.5) : (long)((long)(1<<X)*(Y) + 0.5))

#define LOW_NIBBLE(x)	(x&0x0F)
#define HIGH_NIBBLE(x)	(x>>4)

#define MAKE_BYTE(h,l)	((h<<4)+(l&0x0f))
#define MAKE_INT(h,l)	(((uint16_t)h<<8)+l)
#define MAKE_WORD(h,l)	(((uint32_t)h<<16)+l)

#define GetDeltaTick(a) (SystemTick-a)
#ifdef TMR
#define GetDeltaTickUs(a) (TMR()-a)
#endif

#define BCD2CHAR(x)	(10*(x>>4)+(x&0x0f))
#define CHAR2BCD(x)	(((x/10)<<4)|(x%10))
void __delay_20ms(uint16_t x);
uint8_t BCD2Char(uint8_t bcd);
uint32_t Long2BCD(uint32_t l);
void Byte2ASCII(uint8_t b, uint8_t *h, uint8_t *l);
uint8_t ASCII2Byte_Capital(uint8_t h,uint8_t l);
uint8_t ASCII2Byte_Lowercase(uint8_t h,uint8_t l);
#ifdef WFRomOperation
_RomParams RomParams;
#ifndef eeprom_offset
#define eeprom_offset 1
#endif
uint8_t GetRomData(void);
void SaveRomData(void);
#endif

#ifdef WFRomOperation_OneByte
uint8_t WFRomOneByte;
uint8_t WFRomOneByteAddr;
uint8_t GetRomData(void);
void SaveRomData(void);
#endif

#endif
