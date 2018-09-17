#ifndef __CP1616_Client_Conf_h__
#define __CP1616_Client_Conf_h__

#include "usart.h"

#define CP1616_AddrLen 0
#define CP1616_DataBufLen 2

// #define CP1616_Client_Tx_OneByOne
// #define CP1616_Client_TxByteWithVerify(x)// Uart1_VerifySumAddTxByte(x)
// #define CP1616_Client_TxByte(x)// Uart1_PutChar(x)

#define CP1616_Client_TxProc(pBuf,len) HAL_UART_Transmit(&huart3,pBuf,len,1000)


#define Verify_Sum
#include "Verify.h"
#define CP1616_Client_VerifyProc(pBuf,len) GetVerify_Sum(pBuf,len)
// #define CheckVerify_CP1616_Client()	sum=GetVerify_Sum(CP1616_Client_RxList,CP1616_Client_NeedRxCount-2); \
// 												if(sum==CP1616_Client_RxList[CP1616_Client_NeedRxCount-2])	\
// 													{sum=1;}\
// 												else\
// 													{sum=0;}


#define MAX_CP1616_Client_RX 100
#endif


