#ifndef __UartTx2_h__
#define __UartTx2_h__
#ifdef UartTxQueue2
void UartTxQueue2_Init(void);
void UartTxQueue2_AddByte(uint8_t tx);
void UartTxQueue2_AddBytes(const void *tx, uint8_t size, uint16_t n);
void UartTxQueue2_AddStr(const char* pt);
void UartTxQueue2_Interrupt(void);
#else
void UartTx2Bytes(const void *tx, uint8_t size, uint16_t n);
void UartTx2Byte(uint16_t tx);
#endif
#endif // __UartTxQueue_h__
