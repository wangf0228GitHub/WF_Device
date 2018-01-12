#include "HardwareProfile.h"
#include "afx.h"
#include "Uart.h"
#ifdef Uart_UseTxQueue
_UartTxQueueFlags UartTxQueueFlags;
#endif
#ifdef Uart_Uart1
	#ifdef Uart1_UsedParityVerify
		unsigned char Uart1_ParityVerifyType;
		unsigned char Uart1_GetVerifyBit(unsigned char data)
		{
			unsigned char i,d,c,b,ret;
			if(Uart1_ParityVerifyType==Uart1_ParityVerify_High)
				ret=1;
			else if(Uart1_ParityVerifyType==Uart1_ParityVerify_Low)
				ret=0;
			else 
			{
				d=data;
				c=0;
				for(i=0;i<8;i++)
				{
					b=d&0x01;
					if(b==1)
						c++;
					d=d>>1;
				}		
				if(c%2==0)
				{
					if(Uart1_ParityVerifyType==Uart1_ParityVerify_Even)//偶校验
						ret=0;
					else
						ret=1;
				}
				else
				{
					if(Uart1_ParityVerifyType==Uart1_ParityVerify_Even)//偶校验
						ret=1;
					else
						ret=0;
				}
			}	
			return ret;
		}
	#endif
	void Uart1_PutChar(unsigned char c )
	{
		while(Uart1_TRMT==0);
		#ifdef Uart1_UsedParityVerify
			Uart1_Tx9D=Uart1_GetVerifyBit(c);
		#endif
		Uart1_TXREG=c;
	}
	void Uart1_PutChars(const unsigned char* pBuf,unsigned char len)
	{
		unsigned char i;
		for(i=0;i<len;i++)
		{
			Uart1_PutChar(pBuf[i]);
		}
	}
	void Uart1_PutString(const char* pString )
	{
		char c;
		while(1)
		{
			c=*pString;
			if(c=='\0')
				break;
			Uart1_PutChar(c);
			pString++;
		}
	}


	void Uart1_PutHex(unsigned char c )
	{
		unsigned char  b;
		b=HIGH_NIBBLE(c);
		if (b>9) 
			b += 'A'-10;
		else 
			b += '0';
		Uart1_PutChar(b);
		b=LOW_NIBBLE(c);
		if (b>9) 
			b += 'A'-10;
		else 
			b += '0';
		Uart1_PutChar(b);
	}
	#ifdef Uart1TxQueue
		unsigned char Uart1TxQueueBuf[Uart1TxQueue_BufLen];
		unsigned char *pInUart1TxQueueBuf, *pOutUart1TxQueueBuf;
		void Uart1TxQueue_TxStart()
		{	
			if (Uart1_TXIF && !Uart1_TXIE)        
			{
#ifdef Uart1_485
				Uart1_Set485Tx();
#endif
				Uart1_TXIE=1;
				UartTxQueueFlags.bUart1TxQueueFinish=0;
			}		
		}
		void Uart1TxQueue_AddStr(const char* pt)
		{
			const char *p;
			p = pt;
			while (*p != '\0')                         //逐个放入缓冲区
			{
				Uart1TxQueue_AddByte(*p++);
			}
		}

		void Uart1TxQueue_AddByte(unsigned char tx)
		{
			unsigned char *d;
			d = pInUart1TxQueueBuf;
			d++;
			if (d == (Uart1TxQueueBuf+Uart1TxQueue_BufLen))         //回绕
				d = Uart1TxQueueBuf;
			while(d == pOutUart1TxQueueBuf);         //TxBuf满
			*pInUart1TxQueueBuf = tx;  //放入一个数据
			pInUart1TxQueueBuf = d;    //inTxBuf后移
			Uart1TxQueue_TxStart();
		}
		void Uart1TxQueue_AddBytes(const void *tx, unsigned char size, unsigned int n)
		{
			unsigned int count = size * n;
			unsigned char *s;
			if(count==0)
				return;
			s = (unsigned char*)tx;
			while (count--)                         //逐个放入缓冲区
			{
				Uart1TxQueue_AddByte(*s++);
			}
		}
		void Uart1TxQueue_Interrupt(void)
		{	
			if (pOutUart1TxQueueBuf == pInUart1TxQueueBuf)             //TxBuf空
			{
				Uart1_TXIE=0;
				UartTxQueueFlags.bUart1TxQueueFinish=1;
#ifdef Uart1_485
				Uart1_Set485Rx();
#endif
				return;
			}
			Uart1_TXIF=0;
			#ifdef Uart1_UsedParityVerify
				Uart1_Tx9D=Uart1_GetVerifyBit(*pOutUart1TxQueueBuf);
			#endif
			Uart1_TXREG=*pOutUart1TxQueueBuf;
			pOutUart1TxQueueBuf++;
			if (pOutUart1TxQueueBuf == (Uart1TxQueueBuf+Uart1TxQueue_BufLen))
				pOutUart1TxQueueBuf = Uart1TxQueueBuf;	
		}
		void Uart1TxQueue_Init( void )
		{	
			pInUart1TxQueueBuf=pOutUart1TxQueueBuf=Uart1TxQueueBuf;
		}
	#endif
#endif

#ifdef Uart_Uart2
	#ifdef Uart2_UsedParityVerify
		unsigned char Uart2_ParityVerifyType;
		unsigned char Uart2_GetVerifyBit(unsigned char data)
		{
			unsigned char i,d,c,b,ret;
			if(Uart2_ParityVerifyType==Uart2_ParityVerify_High)
				ret=1;
			else if(Uart2_ParityVerifyType==Uart2_ParityVerify_Low)
				ret=0;
			else 
			{
				d=data;
				c=0;
				for(i=0;i<8;i++)
				{
					b=d&0x01;
					if(b==1)
						c++;
					d=d>>1;
				}		
				if(c%2==0)
				{
					if(Uart2_ParityVerifyType==Uart2_ParityVerify_Even)//偶校验
						ret=0;
					else
						ret=1;
				}
				else
				{
					if(Uart2_ParityVerifyType==Uart2_ParityVerify_Even)//偶校验
						ret=1;
					else
						ret=0;
				}
			}	
			return ret;
		}
	#endif
	void Uart2_PutChar(unsigned char c )
	{
		while(Uart2_TRMT==0);
		#ifdef Uart2_UsedParityVerify
			Uart2_Tx9D=Uart2_GetVerifyBit(c);
		#endif
		Uart2_TXREG=c;
	}

	void Uart2_PutString(const char* pString )
	{
		char c;
		while(1)
		{
			c=*pString;
			if(c=='\0')
				break;
			Uart2_PutChar(c);
			pString++;
		}
	}


	void Uart2_PutHex(unsigned char c )
	{
		unsigned char  b;
		b=HIGH_NIBBLE(c);
		if (b>9) 
			b += 'A'-10;
		else 
			b += '0';
		Uart2_PutChar(b);
		b=LOW_NIBBLE(c);
		if (b>9) 
			b += 'A'-10;
		else 
			b += '0';
		Uart2_PutChar(b);
	}
	#ifdef Uart2TxQueue
		unsigned char Uart2TxQueueBuf[Uart2TxQueue_BufLen];
		unsigned char *pInUart2TxQueueBuf, *pOutUart2TxQueueBuf;
		void Uart2TxQueue_TxStart()
		{	
			if (Uart2_TXIF && !Uart2_TXIE)        
			{
				Uart2_TXIE=1;
				UartTxQueueFlags.bUart2TxQueueFinish=0;
			}		
		}
		void Uart2TxQueue_AddStr(const char* pt)
		{
			const char *p;
			p = pt;
			while (*p != '\0')                         //逐个放入缓冲区
			{
				Uart2TxQueue_AddByte(*p++);
			}
		}

		void Uart2TxQueue_AddByte(unsigned char tx)
		{
			unsigned char *d;
			d = pInUart2TxQueueBuf;
			d++;
			if (d == (Uart2TxQueueBuf+Uart2TxQueue_BufLen))         //回绕
				d = Uart2TxQueueBuf;
			while(d == pOutUart2TxQueueBuf);         //TxBuf满
			*pInUart2TxQueueBuf = tx;  //放入一个数据
			pInUart2TxQueueBuf = d;    //inTxBuf后移
			Uart2TxQueue_TxStart();
		}
		void Uart2TxQueue_AddBytes(const void *tx, unsigned char size, unsigned int n)
		{
			unsigned int count = size * n;
			unsigned char *s;
			if(count==0)
				return;
			s = (unsigned char*)tx;
			while (count--)                         //逐个放入缓冲区
			{
				Uart2TxQueue_AddByte(*s++);
			}
		}
		void Uart2TxQueue_Interrupt(void)
		{	
			if (pOutUart2TxQueueBuf == pInUart2TxQueueBuf)             //TxBuf空
			{
				Uart2_TXIE=0;
				UartTxQueueFlags.bUart2TxQueueFinish=1;
				return;
			}
			//Uart2_TXIF=0;
			#ifdef Uart2_UsedParityVerify
				Uart2_Tx9D=Uart2_GetVerifyBit(*pOutUart2TxQueueBuf);
			#endif
			Uart2_TXREG=*pOutUart2TxQueueBuf;
			pOutUart2TxQueueBuf++;
			if (pOutUart2TxQueueBuf == (Uart2TxQueueBuf+Uart2TxQueue_BufLen))
				pOutUart2TxQueueBuf = Uart2TxQueueBuf;	
		}
		void Uart2TxQueue_Init( void )
		{	
			pInUart2TxQueueBuf=pOutUart2TxQueueBuf=Uart2TxQueueBuf;
		}
	#endif
#endif

#ifdef Uart_Uart3
	#ifdef Uart3_UsedParityVerify
		unsigned char Uart3_ParityVerifyType;
		unsigned char Uart3_GetVerifyBit(unsigned char data)
		{
			unsigned char i,d,c,b,ret;
			if(Uart3_ParityVerifyType==Uart3_ParityVerify_High)
				ret=1;
			else if(Uart3_ParityVerifyType==Uart3_ParityVerify_Low)
				ret=0;
			else 
			{
				d=data;
				c=0;
				for(i=0;i<8;i++)
				{
					b=d&0x01;
					if(b==1)
						c++;
					d=d>>1;
				}		
				if(c%2==0)
				{
					if(Uart3_ParityVerifyType==Uart3_ParityVerify_Even)//偶校验
						ret=0;
					else
						ret=1;
				}
				else
				{
					if(Uart3_ParityVerifyType==Uart3_ParityVerify_Even)//偶校验
						ret=1;
					else
						ret=0;
				}
			}	
			return ret;
		}
	#endif
	void Uart3_PutChar(unsigned char c )
	{
		while(Uart3_TRMT==0);
		#ifdef Uart3_UsedParityVerify
			Uart3_Tx9D=Uart3_GetVerifyBit(c);
		#endif
		Uart3_TXREG=c;
	}

	void Uart3_PutString(const char* pString )
	{
		char c;
		while(1)
		{
			c=*pString;
			if(c=='\0')
				break;
			Uart3_PutChar(c);
			pString++;
		}
	}


	void Uart3_PutHex(unsigned char c )
	{
		unsigned char  b;
		b=HIGH_NIBBLE(c);
		if (b>9) 
			b += 'A'-10;
		else 
			b += '0';
		Uart3_PutChar(b);
		b=LOW_NIBBLE(c);
		if (b>9) 
			b += 'A'-10;
		else 
			b += '0';
		Uart3_PutChar(b);
	}
	#ifdef Uart3TxQueue
		unsigned char Uart3TxQueueBuf[Uart3TxQueue_BufLen];
		unsigned char *pInUart3TxQueueBuf, *pOutUart3TxQueueBuf;
		void Uart3TxQueue_TxStart()
		{	
			if (Uart3_TXIF && !Uart3_TXIE)        
			{
				Uart3_TXIE=1;
				UartTxQueueFlags.bUart3TxQueueFinish=0;
			}		
		}
		void Uart3TxQueue_AddStr(const char* pt)
		{
			const char *p;
			p = pt;
			while (*p != '\0')                         //逐个放入缓冲区
			{
				Uart3TxQueue_AddByte(*p++);
			}
		}

		void Uart3TxQueue_AddByte(unsigned char tx)
		{
			unsigned char *d;
			d = pInUart3TxQueueBuf;
			d++;
			if (d == (Uart3TxQueueBuf+Uart3TxQueue_BufLen))         //回绕
				d = Uart3TxQueueBuf;
			while(d == pOutUart3TxQueueBuf);         //TxBuf满
			*pInUart3TxQueueBuf = tx;  //放入一个数据
			pInUart3TxQueueBuf = d;    //inTxBuf后移
			Uart3TxQueue_TxStart();
		}
		void Uart3TxQueue_AddBytes(const void *tx, unsigned char size, unsigned int n)
		{
			unsigned int count = size * n;
			unsigned char *s;
			if(count==0)
				return;
			s = (unsigned char*)tx;
			while (count--)                         //逐个放入缓冲区
			{
				Uart3TxQueue_AddByte(*s++);
			}
		}
		void Uart3TxQueue_Interrupt(void)
		{	
			if (pOutUart3TxQueueBuf == pInUart3TxQueueBuf)             //TxBuf空
			{
				Uart3_TXIE=0;
				UartTxQueueFlags.bUart3TxQueueFinish=1;
				return;
			}
			//Uart3_TXIF=0;
			#ifdef Uart3_UsedParityVerify
				Uart3_Tx9D=Uart3_GetVerifyBit(*pOutUart3TxQueueBuf);
			#endif
			Uart3_TXREG=*pOutUart3TxQueueBuf;
			pOutUart3TxQueueBuf++;
			if (pOutUart3TxQueueBuf == (Uart3TxQueueBuf+Uart3TxQueue_BufLen))
				pOutUart3TxQueueBuf = Uart3TxQueueBuf;	
		}
		void Uart3TxQueue_Init( void )
		{	
			pInUart3TxQueueBuf=pOutUart3TxQueueBuf=Uart3TxQueueBuf;
		}
	#endif
#endif

#ifdef Uart_Uart4
	#ifdef Uart4_UsedParityVerify
		unsigned char Uart4_ParityVerifyType;
		unsigned char Uart4_GetVerifyBit(unsigned char data)
		{
			unsigned char i,d,c,b,ret;
			if(Uart4_ParityVerifyType==Uart4_ParityVerify_High)
				ret=1;
			else if(Uart4_ParityVerifyType==Uart4_ParityVerify_Low)
				ret=0;
			else 
			{
				d=data;
				c=0;
				for(i=0;i<8;i++)
				{
					b=d&0x01;
					if(b==1)
						c++;
					d=d>>1;
				}		
				if(c%2==0)
				{
					if(Uart4_ParityVerifyType==Uart4_ParityVerify_Even)//偶校验
						ret=0;
					else
						ret=1;
				}
				else
				{
					if(Uart4_ParityVerifyType==Uart4_ParityVerify_Even)//偶校验
						ret=1;
					else
						ret=0;
				}
			}	
			return ret;
		}
	#endif
	void Uart4_PutChar(unsigned char c )
	{
		while(Uart4_TRMT==0);
		#ifdef Uart4_UsedParityVerify
			Uart4_Tx9D=Uart4_GetVerifyBit(c);
		#endif
		Uart4_TXREG=c;
	}

	void Uart4_PutString(const char* pString )
	{
		char c;
		while(1)
		{
			c=*pString;
			if(c=='\0')
				break;
			Uart4_PutChar(c);
			pString++;
		}
	}


	void Uart4_PutHex(unsigned char c )
	{
		unsigned char  b;
		b=HIGH_NIBBLE(c);
		if (b>9) 
			b += 'A'-10;
		else 
			b += '0';
		Uart4_PutChar(b);
		b=LOW_NIBBLE(c);
		if (b>9) 
			b += 'A'-10;
		else 
			b += '0';
		Uart4_PutChar(b);
	}
	#ifdef Uart4TxQueue
		unsigned char Uart4TxQueueBuf[Uart4TxQueue_BufLen];
		unsigned char *pInUart4TxQueueBuf, *pOutUart4TxQueueBuf;
		void Uart4TxQueue_TxStart()
		{	
			if (Uart4_TXIF && !Uart4_TXIE)        
			{
				Uart4_TXIE=1;
				UartTxQueueFlags.bUart4TxQueueFinish=0;
			}		
		}
		void Uart4TxQueue_AddStr(const char* pt)
		{
			const char *p;
			p = pt;
			while (*p != '\0')                         //逐个放入缓冲区
			{
				Uart4TxQueue_AddByte(*p++);
			}
		}

		void Uart4TxQueue_AddByte(unsigned char tx)
		{
			unsigned char *d;
			d = pInUart4TxQueueBuf;
			d++;
			if (d == (Uart4TxQueueBuf+Uart4TxQueue_BufLen))         //回绕
				d = Uart4TxQueueBuf;
			while(d == pOutUart4TxQueueBuf);         //TxBuf满
			*pInUart4TxQueueBuf = tx;  //放入一个数据
			pInUart4TxQueueBuf = d;    //inTxBuf后移
			Uart4TxQueue_TxStart();
		}
		void Uart4TxQueue_AddBytes(const void *tx, unsigned char size, unsigned int n)
		{
			unsigned int count = size * n;
			unsigned char *s;
			if(count==0)
				return;
			s = (unsigned char*)tx;
			while (count--)                         //逐个放入缓冲区
			{
				Uart4TxQueue_AddByte(*s++);
			}
		}
		void Uart4TxQueue_Interrupt(void)
		{	
			if (pOutUart4TxQueueBuf == pInUart4TxQueueBuf)             //TxBuf空
			{
				Uart4_TXIE=0;
				UartTxQueueFlags.bUart4TxQueueFinish=1;
				return;
			}
			//Uart4_TXIF=0;
			#ifdef Uart4_UsedParityVerify
				Uart4_Tx9D=Uart4_GetVerifyBit(*pOutUart4TxQueueBuf);
			#endif
			Uart4_TXREG=*pOutUart4TxQueueBuf;
			pOutUart4TxQueueBuf++;
			if (pOutUart4TxQueueBuf == (Uart4TxQueueBuf+Uart4TxQueue_BufLen))
				pOutUart4TxQueueBuf = Uart4TxQueueBuf;	
		}
		void Uart4TxQueue_Init( void )
		{	
			pInUart4TxQueueBuf=pOutUart4TxQueueBuf=Uart4TxQueueBuf;
		}
	#endif
#endif


