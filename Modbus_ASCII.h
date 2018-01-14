#ifndef __Modbus_ASCII_h__
#define __Modbus_ASCII_h__

// #define Modbus_ASCII_InnerRxBufLen	100
//#define Modbus_ASCII_RxBufLen	100
extern uint8_t Modbus_ASCII_RxBuffer[Modbus_ASCII_RxBufLen];
extern uint8_t Modbus_ASCII_TxBuffer[Modbus_ASCII_TxBufLen];
extern uint8_t Modbus_ASCII_RxCount;
extern uint8_t Modbus_ASCII_Slave_Addr;
void Modbus_ASCII_Init(void);
void Modbus_ASCII_RxCommand(uint8_t rx);
void Modbus_ASCII_TxCommand(uint8_t len);
//#define Modbus_ASCII_Slave_Timer() TMR0ON=1
#endif // __Modbus_ASCII_h__