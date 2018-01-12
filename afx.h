#ifndef __afx_H_
#define __afx_H_
//#include "TypeDefine.h"
#define false 0
#define true 1
#ifndef __PICC18__

#define LOW_BYTE(x)     ((unsigned char)((x)&0xFF))
#define HIGH_BYTE(x)    ((unsigned char)(((x)>>8)&0xFF))
#define LOW_WORD(x)     ((unsigned short)((x)&0xFFFF))
#define HIGH_WORD(x)    ((unsigned short)(((x)>>16)&0xFFFF))
#define WRITETIMER1(x) ((void)(TMR1H=((x)>>8),TMR1L=((x)&0xFF)))
#define READTIMER1() (MAKE_INT(TMR1H,TMR1L))
#define WRITETIMER0(x) ((void)(TMR0H=((x)>>8),TMR0L=((x)&0xFF)))
#define READTIMER0() (MAKE_INT(TMR0H,TMR0L))
#endif

#ifdef MCC30
//#define __delay_us(x) __delay32((unsigned long)((x)*(FCY/1000000.0)))
//#define __delay_ms(x) __delay32((unsigned long)((x)*(FCY/1000.0)))
extern unsigned char wCPU_IPL;
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
#define UcQX(X,Y) (unsigned char)((unsigned char)(1<<X)*(Y) + 0.5)
#define UiQX(X,Y) (unsigned int)((unsigned int)(1<<X)*(Y) + 0.5)
#define UlQX(X,Y) (unsigned long)((unsigned long)((unsigned long)1<<X)*(Y) + 0.5)
#define cQX(X,Y) ((Y < 0.0) ? (char)((char)(1<<X)*(Y) - 0.5) : (char)((char)(1<<X)*(Y) + 0.5))
#define iQX(X,Y) ((Y < 0.0) ? (int)((int)(1<<X)*(Y) - 0.5) : (int)((int)(1<<X)*(Y) + 0.5))
#define lQX(X,Y) ((Y < 0.0) ? (long)((long)(1<<X)*(Y) - 0.5) : (long)((long)(1<<X)*(Y) + 0.5))

#define LOW_NIBBLE(x)	(x&0x0F)
#define HIGH_NIBBLE(x)	(x>>4)

#define MAKE_BYTE(h,l)	((h<<4)+(l&0x0f))
#define MAKE_INT(h,l)	(((unsigned int)h<<8)+l)
#define MAKE_WORD(h,l)	(((unsigned long)h<<16)+l)

#define GetDeltaTick(a) (SystemTick-a)
#ifdef TMR
#define GetDeltaTickUs(a) (TMR()-a)
#endif

#define BCD2CHAR(x)	(10*(x>>4)+(x&0x0f))
#define CHAR2BCD(x)	(((x/10)<<4)|(x%10))
void __delay_20ms(unsigned int x);
unsigned char BCD2Char(unsigned char bcd);
unsigned long Long2BCD(unsigned long l);
void Byte2ASCII(unsigned char b, unsigned char *h, unsigned char *l);
unsigned char ASCII2Byte_Capital(unsigned char h,unsigned char l);
unsigned char ASCII2Byte_Lowercase(unsigned char h,unsigned char l);
#ifdef WFRomOperation
_RomParams RomParams;
#ifndef eeprom_offset
#define eeprom_offset 1
#endif
unsigned char GetRomData(void);
void SaveRomData(void);
#endif

#ifdef WFRomOperation_OneByte
unsigned char WFRomOneByte;
unsigned char WFRomOneByteAddr;
unsigned char GetRomData(void);
void SaveRomData(void);
#endif

#endif
