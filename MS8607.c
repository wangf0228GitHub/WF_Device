#include "HardwareProfile.h"
#include "MS8607.h"
#include "TypeDefine.h"
#include <stdint.h>

#define PRESSURE_SENSITIVITY_INDEX 1
#define PRESSURE_OFFSET_INDEX 2
#define TEMP_COEFF_OF_PRESSURE_SENSITIVITY_INDEX 3
#define TEMP_COEFF_OF_PRESSURE_OFFSET_INDEX 4
#define REFERENCE_TEMPERATURE_INDEX 5
#define TEMP_COEFF_OF_TEMPERATURE_INDEX 6
#define COEFFICIENT_NUMBERS 7

// uint8_t MS8607_reset(void) 
// {
// 	status = hsensor_reset();
// 	if (status != ms8607_status_ok)
// 		return status;
// 	status = psensor_reset();
// 	if (status != ms8607_status_ok)
// 		return status;
// 
// 	return ms8607_status_ok;
// }
#ifdef MS8607_SimI2C
#include "SimI2C.h"
#define I2C_Start() SimI2C_Start()
#define I2C_Stop() SimI2C_Stop()
#define I2C_RecAck() SimI2C_RecAck()
#define I2C_Ack() SimI2C_Ack()
#define I2C_NoAck() SimI2C_NoAck()
#define I2C_SendByte(x) SimI2C_SendByte(x)//写数据
#define I2C_ReadByte() SimI2C_ReadByte()//读数据
#endif
#define MS8607_PT_Addr 0xec //0x76
#define MS8607_RH_Addr 0x80 //0x40
uint8_t MS8607_Buf[10];
uint16_t MS8607_eeprom[8];
_MS8607_Flags MS8607_Flags;
ulong MS8607_adcT;
ulong MS8607_adcP;
uint MS8607_adcRH;
float32 MS8607_Temperature;
float32 MS8607_Pressure;
float32 MS8607_RH;
uint8_t MS8607_Geteeprom(void);
uint8_t MS8607_I2CRead(uint8_t Addr,uint8_t NeedReadLen);
uint8_t MS8607_Init(void)
{
	MS8607_Flags.bInit=0;
	MS8607_Flags.bHold=1;
	if(MS8607_I2CProc(MS8607_PT_Addr,0x1e,0)==0)
		return 0;
	if(MS8607_I2CProc(MS8607_RH_Addr,0xfe,0)==0)
		return 0;
	if(MS8607_Geteeprom()==0)
		return 0;
	MS8607_Flags.bInit=1;
	return 1;
}
void MS8607_CalculatePT(void)
{
	int32_t dT, TEMP;
	int64_t OFF, SENS, P, T2, OFF2, SENS2;
	// Difference between actual and reference temperature = D2 - Tref
	dT = (int32_t)MS8607_adcT.u32 -
		((int32_t)MS8607_eeprom[REFERENCE_TEMPERATURE_INDEX] << 8);

	// Actual temperature = 2000 + dT * TEMPSENS
	TEMP = 2000 + ((int64_t)dT *
		(int64_t)MS8607_eeprom[TEMP_COEFF_OF_TEMPERATURE_INDEX] >>
		23);

	// Second order temperature compensation
	if (TEMP < 2000) 
	{
		T2 = (3 * ((int64_t)dT * (int64_t)dT)) >> 33;
		OFF2 = 61 * ((int64_t)TEMP - 2000) * ((int64_t)TEMP - 2000) / 16;
		SENS2 = 29 * ((int64_t)TEMP - 2000) * ((int64_t)TEMP - 2000) / 16;

		if (TEMP < -1500) {
			OFF2 += 17 * ((int64_t)TEMP + 1500) * ((int64_t)TEMP + 1500);
			SENS2 += 9 * ((int64_t)TEMP + 1500) * ((int64_t)TEMP + 1500);
		}
	} else 
	{
		T2 = (5 * ((int64_t)dT * (int64_t)dT)) >> 38;
		OFF2 = 0;
		SENS2 = 0;
	}

	// OFF = OFF_T1 + TCO * dT
	OFF = ((int64_t)(MS8607_eeprom[PRESSURE_OFFSET_INDEX]) << 17) +
		(((int64_t)(MS8607_eeprom[TEMP_COEFF_OF_PRESSURE_OFFSET_INDEX]) * dT) >>
		6);
	OFF -= OFF2;

	// Sensitivity at actual temperature = SENS_T1 + TCS * dT
	SENS =
		((int64_t)MS8607_eeprom[PRESSURE_SENSITIVITY_INDEX] << 16) +
		(((int64_t)MS8607_eeprom[TEMP_COEFF_OF_PRESSURE_SENSITIVITY_INDEX] * dT) >>
		7);
	SENS -= SENS2;

	// Temperature compensated pressure = D1 * SENS - OFF
	P = (((MS8607_adcP.u32 * SENS) >> 21) - OFF) >> 15;

	MS8607_Temperature.f32 = ((float)TEMP - T2) / 100;
	MS8607_Pressure.f32 = (float)P / 100;
}
uint8_t MS8607_ReadPT(uint8_t resolution_osr)
{
	uint8_t cmd=resolution_osr<<1;
	cmd |= 0x50;//
	if(MS8607_I2CProc(MS8607_PT_Addr,cmd,0)==0)
		return 0;
	// 20ms wait for conversion
	__delay_20ms(1);
	if(MS8607_I2CProc(MS8607_PT_Addr,0x00,3)==0)
		return 0;
	MS8607_adcT.u16H.u8H=0;
	MS8607_adcT.u16H.u8L=MS8607_Buf[0];
	MS8607_adcT.u16L.u8H=MS8607_Buf[1];
	MS8607_adcT.u16L.u8L=MS8607_Buf[2];

	cmd |= 0x40;//
	if(MS8607_I2CProc(MS8607_PT_Addr,cmd,0)==0)
		return 0;
	// 20ms wait for conversion
	__delay_20ms(1);
	if(MS8607_I2CProc(MS8607_PT_Addr,0x00,3)==0)
		return 0;
	MS8607_adcP.u16H.u8H=0;
	MS8607_adcP.u16H.u8L=MS8607_Buf[0];
	MS8607_adcP.u16L.u8H=MS8607_Buf[1];
	MS8607_adcP.u16L.u8L=MS8607_Buf[2];
	if(MS8607_adcP.u32==0 ||MS8607_adcT.u32==0)
		return 0;
	MS8607_CalculatePT();
	return 1;
}
uint8_t MS8607_ReadRH(void)
{
	uint8_t crc;
	uint32_t polynom = 0x988000; // x^8 + x^5 + x^4 + 1
	uint32_t msb = 0x800000;
	uint32_t mask = 0xFF8000;
	uint32_t result; // Pad with zeros as specified in spec
	if(MS8607_Flags.bHold)
	{
		if(MS8607_I2CProc(MS8607_RH_Addr,0xe5,0)==0)
			return 0;
		MS8607_I2C_CLK_IO=1;
		__delay_ms(1);
		while(MS8607_I2C_CLK_R==0);
		MS8607_I2C_CLK_IO=0;
	}
	else
	{
		if(MS8607_I2CProc(MS8607_RH_Addr,0xf5,0)==0)
			return 0;
		__delay_20ms(10);		
	}
	if(MS8607_I2CRead(MS8607_RH_Addr,3)==0)
		return 0;
	MS8607_adcRH.u8H=MS8607_Buf[0];
	MS8607_adcRH.u8L=MS8607_Buf[1];
	crc=MS8607_Buf[2];

	result = (uint32_t)MS8607_adcRH.u16 << 8; // Pad with zeros as specified in spec

	while (msb != 0x80) 
	{
		// Check if msb of current value is 1 and apply XOR mask
		if (result & msb)
			result = ((result ^ polynom) & mask) | (result & ~mask);

		// Shift by one
		msb >>= 1;
		mask >>= 1;
		polynom >>= 1;
	}
	if (result == crc)
	{
		//MS8607_CalculateRH();
		MS8607_RH.f32 = (float)MS8607_adcRH.u16 * 125.0 / (1UL << 16) + (-6);
		return 1;
	}
	else
		return 0;
}
uint8_t MS8607_CRCCheck(uint16_t* pBuf,uint8_t crc)
{
	uint8_t cnt, n_bit,h,l;
	uint16_t n_rem;
	n_rem = 0x00;	
	for (cnt = 0; cnt < 8; cnt++) 
	{
		h=HIGH_BYTE(pBuf[cnt]);
		l=LOW_BYTE(pBuf[cnt]);
		n_rem^=h;
		for (n_bit = 8; n_bit > 0; n_bit--) 
		{
			if (n_rem & 0x8000)
				n_rem = (n_rem << 1) ^ 0x3000;
			else
				n_rem <<= 1;
		}
		n_rem^=l;
		for (n_bit = 8; n_bit > 0; n_bit--) 
		{
			if (n_rem & 0x8000)
				n_rem = (n_rem << 1) ^ 0x3000;
			else
				n_rem <<= 1;
		}
		// Get next byte
// 		if (cnt % 2 == 1)
// 			n_rem ^= pBuf[cnt >> 1] & 0x00FF;
// 		else
// 			n_rem ^= pBuf[cnt >> 1] >> 8;		
	}
	n_rem >>= 12;	
	if(n_rem==crc)
		return 1;
	else
		return 0;
}
uint8_t MS8607_Geteeprom(void)
{
	uint8_t i,crc;
	uint16_t crc_read;
	for(i=0;i<7;i++)
	{
		if(MS8607_I2CProc(MS8607_PT_Addr,0xa0+i * 2,2)==0)
			return 0;
		MS8607_eeprom[i]=MAKE_INT(MS8607_Buf[0],MS8607_Buf[1]);		
	}
	MS8607_eeprom[7]=0;
	crc=HIGH_BYTE(MS8607_eeprom[0]);
	crc=HIGH_NIBBLE(crc);

	crc_read = MS8607_eeprom[0];
	//pBuf[COEFFICIENT_NUMBERS] = 0;
	MS8607_eeprom[0] = (0x0FFF & (MS8607_eeprom[0])); // Clear the CRC byte	
	if(MS8607_CRCCheck(MS8607_eeprom,crc)==0)
		return 0;
	MS8607_eeprom[0] = crc_read;
	return 1;
}
uint8_t MS8607_I2CRead(uint8_t Addr,uint8_t NeedReadLen)
{
	uint8_t i;	
	I2C_Start();
	I2C_SendByte(Addr|0x01);//读
	if(I2C_RecAck())
		return 0;
	i=0;
	while(--NeedReadLen)
	{
		MS8607_Buf[i++]=I2C_ReadByte();
		I2C_Ack();
	}
	MS8607_Buf[i]=I2C_ReadByte();//read last byte data
	I2C_NoAck();
	I2C_Stop();
	return 1;
}
uint8_t MS8607_I2CProc(uint8_t Addr,uint8_t Command,uint8_t NeedReadLen)
{
	uint8_t i;
	I2C_Start();
	I2C_SendByte(Addr);//写
	if(I2C_RecAck())
	 	return 0;	
	I2C_SendByte(Command);//写读写地址高字节
	if(I2C_RecAck())
	 	return 0;
	I2C_Stop();
	if(NeedReadLen==0)
		return 1;
	I2C_Start();
	I2C_SendByte(Addr|0x01);//读
	if(I2C_RecAck())
		return 0;	
	i=0;
	while(--NeedReadLen)
	{
		MS8607_Buf[i++]=I2C_ReadByte();
		I2C_Ack();
	}
	MS8607_Buf[i]=I2C_ReadByte();//read last byte data
	I2C_NoAck();
	I2C_Stop();
	return 1;
}



