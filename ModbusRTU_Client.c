#include "HardwareProfile.h"
void Init_ModbusRTU_Client(void)
{
	SetRx_ModbusRTU_Client();
}

void ProcRx_ModbusRTU_Client(unsigned char rx)
{
	if(ModbusRTU_Client_Flags.bRx)//之前没处理完
		return;
	ModbusRTU_Client_ResetWait();
	ModbusRTU_Client_RxList[ModbusRTU_Client_RxCount++]=rx;
	if(ModbusRTU_Client_RxCount>MAX_ModbusRTU_Client_RX)
	{
		ModbusRTU_Client_RxCount=0;			
	}	
}
void SendCommand03_ModbusRTU_Client(unsigned char *pBuff,unsigned char count)
{
	unsigned char i;
	uint crc;	
	unsigned char uIndex ; /* CRC循环中的索引 */
	crc.u16=0xffff;
	SetTx_ModbusRTU_Client();
  	ModbusRTU_Client_VerifyTxByte(ModbusRTU_Client_MyAddr);
  	ModbusRTU_Client_VerifyTxByte(3);
  	ModbusRTU_Client_VerifyTxByte(count);
  	for(i=0;i<count;i++)
  	{
  		ModbusRTU_Client_VerifyTxByte(pBuff[i]);
  	}
  	ModbusRTU_Client_TxByte(crc.u8H);
  	ModbusRTU_Client_TxByte(crc.u8L);
	SetRx_ModbusRTU_Client();
}
void SendCommand16_ModbusRTU_Client(unsigned int FirstReg,unsigned char count)
{
	uint crc;	
	unsigned char uIndex ; /* CRC循环中的索引 */
	crc.u16=0xffff;
	SetTx_ModbusRTU_Client();
	ModbusRTU_Client_VerifyTxByte(ModbusRTU_Client_MyAddr);
	ModbusRTU_Client_VerifyTxByte(16);
	ModbusRTU_Client_VerifyTxByte(HIGH_BYTE(FirstReg));
	ModbusRTU_Client_VerifyTxByte(LOW_BYTE(FirstReg));
	ModbusRTU_Client_VerifyTxByte(0);
	ModbusRTU_Client_VerifyTxByte(count);	
	ModbusRTU_Client_TxByte(crc.u8H);
	ModbusRTU_Client_TxByte(crc.u8L);
	SetRx_ModbusRTU_Client();
}