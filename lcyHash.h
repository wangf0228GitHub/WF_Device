#ifndef __lcyHash_H__
#define __lcyHash_H__

#include <stdint.h>
extern uint8_t lcyHashIn[0x08];
extern uint8_t lcyHashOut[0x08];
void lcyHashOnce();
void lcyHashCalc(uint8_t n);
#endif
