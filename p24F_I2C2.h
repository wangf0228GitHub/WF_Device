#ifndef __p24F_I2C2_h__
#define __p24F_I2C2_h__

extern unsigned char I2C2Buf[I2C2BufLen];
void I2C2Init();
int I2C2AddByte(unsigned char b);
int I2C2AddBytes(const void *tx, size_t size, size_t n);
int I2C2AddStr(const char* pt);
int I2C2Write(unsigned char slaveAddr,unsigned int writeAddr);
int I2C2Read(unsigned char slaveAddr,unsigned int writeAddr,size_t count);
#endif // __p24F_I2C2_h__
