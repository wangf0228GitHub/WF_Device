#ifndef __MS5803_02ba_h__
#define __MS5803_02ba_h__
//  #define MS5803_02ba_SCLK
//  #define MS5803_02ba_DOUT
//  #define MS5803_02ba_DIN
// #define MS5803_02ba_CSB

#define MS5803_02ba_RESET 0x1E
#define MS5803_02ba_Convert_D1_256  0x40
#define MS5803_02ba_Convert_D1_512  0x42
#define	MS5803_02ba_Convert_D1_1024 0x44
#define	MS5803_02ba_Convert_D1_2048 0x46
#define	MS5803_02ba_Convert_D1_4096 0x48
#define	MS5803_02ba_Convert_D2_256  0x50
#define	MS5803_02ba_Convert_D2_512  0x52
#define	MS5803_02ba_Convert_D2_1024 0x54
#define	MS5803_02ba_Convert_D2_2048 0x56
#define	MS5803_02ba_Convert_D2_4096 0x58
extern unsigned long MS5803_02ba_T;
void MS5803_02ba_GetCx(void);
unsigned long MS5803_02ba_Calculate(void);
void MS5803_02ba_Reset(void);
#endif // __MS5803_02ba_h__