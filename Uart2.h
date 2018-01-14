#ifndef __Uart2_H__
#define __Uart2_H__

#ifndef Uart2_TRMT
#define Uart2_TRMT TRMT2
#endif

#ifndef Uart2_TXREG
#define Uart2_TXREG TXREG2
#endif

#ifdef Uart2_ParityVerifyType
#define Uart2_ParityVerify_Even 1//Å¼Ð£Ñé
#define Uart2_ParityVerify_Odd 2//
#define Uart2_ParityVerify_High 3
#define Uart2_ParityVerify_Low 4

extern uint8_t Uart2_ParityVerifyType;
uint8_t Uart2_GetVerifyBit(uint8_t data);
#endif 

#define Uart2_VerifySumAddTxByte(c)  Uart2_PutChar(c);sum=(uint8_t)(sum+c)
#define Uart2_VerifyCRC16AddTxByte(c)  Uart2_PutChar(c);VERIFYCRC16(c)
void Uart2_PutChar(uint8_t c);
void Uart2_PutString(const char* pString);
void Uart2_PutHex(uint8_t c);

#ifdef Uart2TxQueue
#ifndef Uart2TxQueue_BufLen
#define Uart2TxQueue_BufLen 20
#endif
#define Uart2TxQueue_VerifySumAddTxByte(c)  Uart2TxQueue_AddByte(c);sum=(uint8_t)(sum+c)
#define Uart2TxQueue_VerifyCRC16AddTxByte(c)  Uart2TxQueue_AddByte(c);VERIFYCRC16(c)
void Uart2TxQueue_Init(void);
void Uart2TxQueue_AddByte(uint8_t tx);
void Uart2TxQueue_AddBytes(const void *tx, uint8_t size, uint16_t n);
void Uart2TxQueue_AddStr(const char* pt);
void Uart2TxQueue_Interrupt(void);
#endif

#endif
