#ifndef __p24F_I2C2_h__
#define __p24F_I2C2_h__

extern uint8_t I2C2Buf[I2C2BufLen];
void I2C2Init();
int I2C2AddByte(uint8_t b);
int I2C2AddBytes(const void *tx, size_t size, size_t n);
int I2C2AddStr(const char* pt);
int I2C2Write(uint8_t slaveAddr,uint16_t writeAddr);
int I2C2Read(uint8_t slaveAddr,uint16_t writeAddr,size_t count);
#endif // __p24F_I2C2_h__
