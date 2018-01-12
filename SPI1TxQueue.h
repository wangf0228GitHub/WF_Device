#ifndef __SPI1TxQueue_h__
#define __SPI1TxQueue_h__


void SPI1AddStr(const char* pt);
void SPI1AddByte(unsigned char tx);
void SPI1AddBytes(const void *tx, size_t size, size_t n);
void SPI1TxQueueInterrupt(void);
void InitSPI1TxQueue(void);
#endif // __SPI1TxQueue_h__
