#ifndef __ATCommand_h__
#define __ATCommand_h__

typedef union   
{
	struct
	{
		unsigned bChar:1;//是否收到了用的字符
		unsigned bRx:1;
		unsigned bWaitData:1;
	};
	unsigned char AllFlag;
} _ATCommand_Flags;        // general flags

extern _ATCommand_Flags ATCommand_Flags;

#ifndef ATCommand_EndChar_Ex
#define ATCommand_EndChar "\r\0"
#endif

#ifndef ATCommand_Tx_Ex
#define ATCommand_TxByte(x) Uart1_PutChar(x)
#define ATCommand_PutString(x) Uart1_PutString(x)
#endif

#ifndef ATCommand_MaxRX
#define ATCommand_MaxRX 50
#endif

#ifndef ATCommand_WaitClientInterval_Ex
#define ATCommand_WaitClientInterval() __delay_20ms(5);
#endif

#ifndef ATCommand_ResetWait_Ex
#define ATCommand_ResetWait() ;
#endif

enum {ATACK_Null=0,ATACK_OK,ATACK_Err};

extern _ATCommand_Flags ATCommand_Flags;
extern unsigned char ATCommand_RxList[ATCommand_MaxRX];
extern unsigned int ATCommand_WaitACKTick;
extern unsigned char ATCommand_RetryTimes;
extern unsigned char ATCommand_RxCount;
extern unsigned int ATCommand_WaitACKTimes;
extern char ATCommand_ErrString[15];
extern char ATCommand_OkString[15];
extern char ATCommand_Clear;
//extern char ATCommand_EndString[15];
void ATCommand_Init(void);
void ATCommand_ProcRx(unsigned char rx);
unsigned char ATCommand_SendCmd(const char *cmd);
unsigned char ATCommand_WaitData(void);
void ATCommand_InitWaitData(void);
#endif
