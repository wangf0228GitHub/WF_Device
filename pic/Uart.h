#ifndef __UART_H__
#define __UART_H__

#include "main.h"

#ifdef Uart_UseTxQueue
typedef union   
{
	struct
	{
		unsigned bUart1TxQueueFinish:1;
		unsigned bUart2TxQueueFinish:1;
		unsigned bUart3TxQueueFinish:1;
		unsigned bUart4TxQueueFinish:1;
	};
	uint8_t AllFlag;
} _UartTxQueueFlags;
extern _UartTxQueueFlags UartTxQueueFlags;
#endif
#ifdef Uart_Uart1

	#ifndef Uart1_TRMT
		#define Uart1_TRMT TRMT
	#endif

	#ifndef Uart1_TXREG
		#define Uart1_TXREG TXREG
	#endif


	#ifdef Uart1_UsedParityVerify
		#define Uart1_ParityVerify_Even 1//偶校验
		#define Uart1_ParityVerify_Odd 2//
		#define Uart1_ParityVerify_High 3
		#define Uart1_ParityVerify_Low 4

		extern uint8_t Uart1_ParityVerifyType;
		uint8_t Uart1_GetVerifyBit(uint8_t data);
	#endif 

	#define Uart1_VerifySumAddTxByte(c)  Uart1_PutChar(c);sum=(uint8_t)(sum+c)
	#define Uart1_VerifyCRC16AddTxByte(c)  Uart1_PutChar(c);VERIFYCRC16(c)
	#define Uart1_VerifyXORTxByte(c)  Uart1_PutChar(c);xor=(uint8_t)(xor^c)
	void Uart1_PutChar(uint8_t c);
	void Uart1_PutChars(const uint8_t* pBuf,uint8_t len);
	void Uart1_PutString(const char* pString);
	void Uart1_PutHex(uint8_t c);

	#ifdef Uart1TxQueue
		#ifndef Uart1TxQueue_BufLen
			#define Uart1TxQueue_BufLen 20
		#endif
		#ifdef Uart1_485
			#ifndef Uart1_Set485Rx_Ex
				#define Uart1_Set485Rx() while(Uart1_TRMT==0);__delay_ms(1);Uart1_RS485DE_W=0
			#endif

			#ifndef Uart1_Set485Tx_Ex
				#define Uart1_Set485Tx() Uart1_RS485DE_W=1;__delay_ms(1)
			#endif
		#endif

		#define Uart1TxQueue_VerifySumAddTxByte(c)  Uart1TxQueue_AddByte(c);sum=(uint8_t)(sum+c)
		#define Uart1TxQueue_VerifyCRC16AddTxByte(c)  Uart1TxQueue_AddByte(c);VERIFYCRC16(c)
		void Uart1TxQueue_Init(void);
		void Uart1TxQueue_AddByte(uint8_t tx);
		void Uart1TxQueue_AddBytes(const void *tx, uint8_t size, uint16_t n);
		void Uart1TxQueue_AddStr(const char* pt);
		void Uart1TxQueue_Interrupt(void);
	#endif
#endif
		
#ifdef Uart_Uart2

	#ifndef Uart2_TRMT
		#define Uart2_TRMT TRMT
	#endif

	#ifndef Uart2_TXREG
		#define Uart2_TXREG TXREG
	#endif


	#ifdef Uart2_UsedParityVerify
		#define Uart2_ParityVerify_Even 1//偶校验
		#define Uart2_ParityVerify_Odd 2//
		#define Uart2_ParityVerify_High 3
		#define Uart2_ParityVerify_Low 4

		extern uint8_t Uart2_ParityVerifyType;
		uint8_t Uart2_GetVerifyBit(uint8_t data);
	#endif 

	#define Uart2_VerifySumAddTxByte(c)  Uart2_PutChar(c);sum=(uint8_t)(sum+c)
	#define Uart2_VerifyCRC16AddTxByte(c)  Uart2_PutChar(c);VERIFYCRC16(c)
	#define Uart2_VerifyXORTxByte(c)  Uart2_PutChar(c);xor=(uint8_t)(xor^c)
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

#ifdef Uart_Uart3

	#ifndef Uart3_TRMT
		#define Uart3_TRMT TRMT
	#endif

	#ifndef Uart3_TXREG
		#define Uart3_TXREG TXREG
	#endif


	#ifdef Uart3_UsedParityVerify
		#define Uart3_ParityVerify_Even 1//偶校验
		#define Uart3_ParityVerify_Odd 2//
		#define Uart3_ParityVerify_High 3
		#define Uart3_ParityVerify_Low 4

		extern uint8_t Uart3_ParityVerifyType;
		uint8_t Uart3_GetVerifyBit(uint8_t data);
	#endif 

	#define Uart3_VerifySumAddTxByte(c)  Uart3_PutChar(c);sum=(uint8_t)(sum+c)
	#define Uart3_VerifyXORTxByte(c)  Uart3_PutChar(c);xor=(uint8_t)(xor^c)
	#define Uart3_VerifyCRC16AddTxByte(c)  Uart3_PutChar(c);VERIFYCRC16(c)
	void Uart3_PutChar(uint8_t c);
	void Uart3_PutString(const char* pString);
	void Uart3_PutHex(uint8_t c);

	#ifdef Uart3TxQueue
		#ifndef Uart3TxQueue_BufLen
			#define Uart3TxQueue_BufLen 20
		#endif
		#define Uart3TxQueue_VerifySumAddTxByte(c)  Uart3TxQueue_AddByte(c);sum=(uint8_t)(sum+c)
		#define Uart3TxQueue_VerifyCRC16AddTxByte(c)  Uart3TxQueue_AddByte(c);VERIFYCRC16(c)
		void Uart3TxQueue_Init(void);
		void Uart3TxQueue_AddByte(uint8_t tx);
		void Uart3TxQueue_AddBytes(const void *tx, uint8_t size, uint16_t n);
		void Uart3TxQueue_AddStr(const char* pt);
		void Uart3TxQueue_Interrupt(void);
	#endif
#endif

#ifdef Uart_Uart4

	#ifndef Uart4_TRMT
		#define Uart4_TRMT TRMT
	#endif

	#ifndef Uart4_TXREG
		#define Uart4_TXREG TXREG
	#endif


	#ifdef Uart4_UsedParityVerify
		#define Uart4_ParityVerify_Even 1//偶校验
		#define Uart4_ParityVerify_Odd 2//
		#define Uart4_ParityVerify_High 3
		#define Uart4_ParityVerify_Low 4

		extern uint8_t Uart4_ParityVerifyType;
		uint8_t Uart4_GetVerifyBit(uint8_t data);
	#endif 

	#define Uart4_VerifySumAddTxByte(c)  Uart4_PutChar(c);sum=(uint8_t)(sum+c)
	#define Uart4_VerifyCRC16AddTxByte(c)  Uart4_PutChar(c);VERIFYCRC16(c)
	#define Uart4_VerifyXORTxByte(c)  Uart4_PutChar(c);xor=(uint8_t)(xor^c)
	void Uart4_PutChar(uint8_t c);
	void Uart4_PutString(const char* pString);
	void Uart4_PutHex(uint8_t c);

	#ifdef Uart4TxQueue
		#ifndef Uart4TxQueue_BufLen
			#define Uart4TxQueue_BufLen 20
		#endif
		#define Uart4TxQueue_VerifySumAddTxByte(c)  Uart4TxQueue_AddByte(c);sum=(uint8_t)(sum+c)
		#define Uart4TxQueue_VerifyCRC16AddTxByte(c)  Uart4TxQueue_AddByte(c);VERIFYCRC16(c)
		void Uart4TxQueue_Init(void);
		void Uart4TxQueue_AddByte(uint8_t tx);
		void Uart4TxQueue_AddBytes(const void *tx, uint8_t size, uint16_t n);
		void Uart4TxQueue_AddStr(const char* pt);
		void Uart4TxQueue_Interrupt(void);
	#endif
#endif

#endif
