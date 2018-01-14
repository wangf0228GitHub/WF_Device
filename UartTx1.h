#ifndef __UartTx1_h__
#define __UartTx1_h__

#ifndef UartTxQueue1_BufLen
#define UartTxQueue1_BufLen 20
#endif
#define UartTxQueue1_VerifySumAddTxByte(c)  UartTxQueue1_AddByte(c);sum=(uint8_t)(sum+c)
#define UartTxQueue1_VerifyCRC16AddTxByte(c)  UartTxQueue1_AddByte(c);VERIFYCRC16(c)
void UartTxQueue1_Init(void);
void UartTxQueue1_AddByte(uint8_t tx);
void UartTxQueue1_AddBytes(const void *tx, uint8_t size, uint16_t n);
void UartTxQueue1_AddStr(const char* pt);
void UartTxQueue1_Interrupt(void);



#endif // __UartTxQueue_h__
