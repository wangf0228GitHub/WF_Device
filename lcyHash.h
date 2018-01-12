#ifndef __lcyHash_H__
#define __lcyHash_H__
extern unsigned char lcyHashIn[0x08];
extern unsigned char lcyHashOut[0x08];
void lcyHashOnce();
void lcyHashCalc(unsigned char n);
#endif
