#ifndef __MS5536c_h__
#define __MS5536c_h__
// #define MS5536c_SCLK
// #define MS5536c_DOUT
// #define MS5536c_DIN
extern unsigned int MS5536c_T;
void MS5536c_Reset(void);
void MS5536c_GetCx(void);
unsigned int MS5536c_Calculate(void);
#endif // __MS5536c_h__