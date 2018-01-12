#ifndef __UartTx2_h__
#define __UartTx2_h__
#ifdef UartTxQueue2
void UartTxQueue2_Init(void);
void UartTxQueue2_AddByte(unsigned char tx);
void UartTxQueue2_AddBytes(const void *tx, unsigned char size, unsigned int n);
void UartTxQueue2_AddStr(const char* pt);
void UartTxQueue2_Interrupt(void);
#else
void UartTx2Bytes(const void *tx, unsigned char size, unsigned int n);
void UartTx2Byte(unsigned int tx);
#endif
#endif // __UartTxQueue_h__
