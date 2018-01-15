#include "HardwareProfile.h"
#include "I2CDefs.h"


I2CFlags I2C2Flag;

I2C_STATE I2C2State;
uint8_t I2C2Buf[I2C2BufLen];
uint16_t I2C2BufIndex;
uint16_t I2C2PageIndex;
uint8_t SlaveAddr;
uint16_t I2C2TxCount;
uint16_t I2C2RxCount;
uint16_t I2C2Error;
UINT16_VAL WriteAddr;
void I2C2Init()
{
	I2C2BRG=FCY/2/I2C2Fscl-1;
	I2C2CONbits.I2CEN=1;
	I2C2Flag.AllFlag=0;
	I2C2State=I2C_IDLE;
	_MI2C2IE=1;
	_MI2C2IP=1;
	_MI2C2IF=0;	
	I2C2Error=0;
	I2C2BufIndex=0;
}

int I2C2AddByte(uint8_t b)
{
	if(I2C2TxCount==I2C2BufLen)
	{
		I2C2TxCount=0;
		return -1;
	}
	if(I2C2State!=I2C_IDLE)
		return -2;
	I2C2Buf[I2C2TxCount++]=b;
	return 1;
}
int I2C2AddBytes(const void *tx, size_t size, size_t n)
{
	size_t count = size * n;
	uint16_t ret=1;	
	uint8_t *s;
	if(count==0)
		return -1;
	s = (uint8_t*)tx;
	while (count--)                         //逐个放入缓冲区
	{
		ret=I2C2AddByte(*s++);
		if(ret!=1)
			return ret;
	}
	return ret;
}
int I2C2AddStr(const char* pt)
{
	const char *p;
	uint16_t ret;	
	p = pt;
	while (*p != '\0')                         //逐个放入缓冲区
	{
		ret=I2C2AddByte(*p++);
		if(ret!=1)
			return ret;
	}
	return ret;
}
int I2C2Write(uint8_t slaveAddr,uint16_t writeAddr)
{
	if(I2C2State!=I2C_IDLE)
		return -2;
	I2C2Flag.Bits.Write=1;
	SlaveAddr=slaveAddr & 0xfe;
	WriteAddr.Val=writeAddr;
	I2C2BufIndex=0;
	I2C2PageIndex=1;
	I2C2State=I2C_S;
	I2C2CONbits.SEN=1;
	gFlags.I2C2Error=0;
	I2C2Flag.Bits.Wait=1;
#ifdef I2C2ERRORCOUNT
	I2C2Error=0;
#endif
	return 1;
}
int I2C2Read(uint8_t slaveAddr,uint16_t writeAddr,size_t count)
{
	if(I2C2State!=I2C_IDLE)
		return -2;
	I2C2Flag.Bits.Write=0;
	SlaveAddr=slaveAddr & 0xfe;
	WriteAddr.Val=writeAddr;
	I2C2BufIndex=0;	
	I2C2RxCount=count;
	I2C2State=I2C_S;
	I2C2CONbits.SEN=1;	
	gFlags.I2C2Error=0;
	I2C2Flag.Bits.Wait=1;
#ifdef I2C2ERRORCOUNT	
	I2C2Error=0;		
#endif
	return 1;
}
void __attribute__((__interrupt__,auto_psv)) _MI2C2Interrupt(void)
{
	_MI2C2IF=0;
	while((I2C2CON&0x001f)!=0);
	if(I2C2STATbits.BCL)
	{
		I2C2Flag.AllFlag=I2C2Flag.AllFlag&0x0f;
		I2C2State=I2C_S;
		I2C2STATbits.BCL=0;
		I2C2CONbits.SEN=1;
	}
	switch(I2C2State)
	{
	case I2C_S:
		I2C2TRN=SlaveAddr;
		I2C2State=I2C_RCACK;
		I2C2STATbits.BCL=0;
		break;
	case I2C_P://停止位发送完成
		if(gFlags.I2C2Error)
		{
			I2C2State=I2C_IDLE;	
			I2C2Flag.AllFlag=0;
		}
		else if(I2C2Flag.Bits.Wait)
		{
			I2C2State=I2C_S;
			I2C2CONbits.SEN=1;
		}
		else
		{
			if(I2C2Flag.Bits.Write)
				gFlags.I2C2TxDone=1;
			else
				gFlags.I2C2RxDone=1;
			I2C2State=I2C_IDLE;	
			I2C2Flag.AllFlag=0;
		}	
		break;
	case I2C_RS:
		I2C2TRN=SlaveAddr | 0x01;
		I2C2State=I2C_RCACK;
		break;
	case I2C_RCACK:
		if(I2C2STATbits.ACKSTAT)//ack错误
		{
			
#ifdef I2C2ERRORCOUNT
			if(!I2C2Flag.Bits.Wait)
			{
				I2C2Error++;
				if(I2C2Error>=I2C2ERRORCOUNT)
				{
					gFlags.I2C2Error=1;
				}
			}
#endif		
			I2C2State=I2C_P;
			I2C2CONbits.PEN=1;//重新启动	
		}
		else
		{
			I2C2Flag.Bits.Wait=0;	
			if(I2C2Flag.Bits.WriteAddrH && I2C2Flag.Bits.WriteAddrL)//地址已经写完了
			{
				if(I2C2Flag.Bits.Write)//当前为写状态
				{					
					if(I2C2BufIndex==I2C2TxCount)//发送完成了
					{
						I2C2State=I2C_P;
						I2C2CONbits.PEN=1;
						I2C2TxCount=0;
					}
					else
					{
						if(I2C2BufIndex>=(I2C2PageIndex*I2C2PageSize))
						{
							I2C2State=I2C_P;
							I2C2CONbits.PEN=1;//重新启动
							I2C2PageIndex++;
							I2C2Flag.Bits.Wait=1;
							WriteAddr.Val += I2C2PageSize;	
							I2C2Flag.Bits.WriteAddrH=0;
							I2C2Flag.Bits.WriteAddrL=0;
						}
						else
						{
							I2C2TRN=I2C2Buf[I2C2BufIndex];
							I2C2State=I2C_RCACK;	
							I2C2BufIndex++;
						}						
					}					
				}
				else//读状态
				{
					if(I2C2Flag.Bits.RS)
					{
						I2C2CONbits.RCEN=1;
						I2C2State=I2C_READ;
					}
					else
					{
						I2C2State=I2C_RS;
						I2C2CONbits.RSEN=1;//重新启动
						I2C2Flag.Bits.RS=1;
					}					
				}
			}
			else if(I2C2Flag.Bits.WriteAddrH)//子机地址已经发送完成
			{				
				I2C2TRN=WriteAddr.byte.LB;
				I2C2State=I2C_RCACK;	
				I2C2Flag.Bits.WriteAddrL=1;
			}
			else
			{
				I2C2TRN=WriteAddr.byte.HB;
				I2C2State=I2C_RCACK;	
				I2C2Flag.Bits.WriteAddrH=1;
			}
		}
		break;
	case I2C_READ:
		I2C2Buf[I2C2BufIndex]=I2C2RCV;		
		I2C2BufIndex++;
		if(I2C2BufIndex==I2C2RxCount)//接收完成了
		{
			I2C2CONbits.ACKDT=1;
			I2C2CONbits.ACKEN=1;
			I2C2State=I2C_TXNOACK;
		}
		else
		{
			I2C2CONbits.ACKDT=0;
			I2C2CONbits.ACKEN=1;
			I2C2State=I2C_TXACK;	
		}
		break;
	case I2C_TXACK:
		I2C2CONbits.RCEN=1;
		I2C2State=I2C_READ;
		break;
	case I2C_TXNOACK:
		I2C2State=I2C_P;
		I2C2CONbits.PEN=1;//重新启动
	default:
		break;
	}
}
