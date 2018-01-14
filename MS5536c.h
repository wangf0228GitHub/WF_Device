#ifndef __MS5536c_h__
#define __MS5536c_h__
// #define MS5536c_SCLK
// #define MS5536c_DOUT
// #define MS5536c_DIN
extern uint16_t MS5536c_T;
void MS5536c_Reset(void);
void MS5536c_GetCx(void);
uint16_t MS5536c_Calculate(void);
#endif // __MS5536c_h__