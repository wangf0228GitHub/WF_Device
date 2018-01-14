#include "HardwareProfile.h"

uint16_t MS5803_02ba_c1;
uint16_t MS5803_02ba_c2;
uint16_t MS5803_02ba_c3;
uint16_t MS5803_02ba_c4;
uint16_t MS5803_02ba_c5;
uint16_t MS5803_02ba_c6;
uint32_t MS5803_02ba_T;
#ifdef MS5803_02ba_SimI2C
uint32_t MS5803_02ba_GetParam(uint8_t param)
{
	ulong t;
	uint8_t i,x;
	t.u32=0;
	SimI2C_Start();
	SimI2C_SendByte(MS5803_02ba_ADDR_W);//Ð´
	if(SimI2C_RecAck())
		return FALSE;	
	SimI2C_SendByte(param);//Ð´¶ÁÐ´µØÖ·¸ß×Ö½Ú
	if(SimI2C_RecAck())
		return FALSE;
	SimI2C_Stop();
	while(true)
	{
		SimI2C_Start();
		SimI2C_SendByte(MS5803_02ba_ADDR_W);//¶Á
		if(SimI2C_RecAck())
			continue;
		break;
	}
	SimI2C_SendByte(0x00);//¶Á
	if(SimI2C_RecAck())
		return FALSE;
	SimI2C_Stop();
	SimI2C_Start();
	SimI2C_SendByte(MS5803_02ba_ADDR_R);
	if(SimI2C_RecAck())
		return FALSE;
	t.u8s[2]=SimI2C_ReadByte();
	SimI2C_Ack();
	t.u8s[1]=SimI2C_ReadByte();
	SimI2C_Ack();
	t.u8s[0]=SimI2C_ReadByte();
	SimI2C_NoAck();
	SimI2C_Stop();
	return t.u32;
}
uint8_t MS5803_02ba_Reset(void)
{
	SimI2C_Start();
	SimI2C_SendByte(MS5803_02ba_ADDR_W);//Ð´
	if(SimI2C_RecAck())
		return FALSE;	
	SimI2C_SendByte(MS5803_02ba_RESET);//Ð´¶ÁÐ´µØÖ·¸ß×Ö½Ú
	if(SimI2C_RecAck())
		return FALSE;	
	SimI2C_Stop();
	return true;
}
uint8_t MS5803_02ba_GetCx(void)
{	
	uint8_t i,j,param;
	uint c[7];
	for(i=0;i<7;i++)
		c[i].u16=0;	
	for(i=6;i>0;i--)
	{
		param=i<<1;
		param=param+0xa0;
		SimI2C_Start();
		SimI2C_SendByte(MS5803_02ba_ADDR_W);//Ð´
		if(SimI2C_RecAck())
			return FALSE;	
		SimI2C_SendByte(param);//Ð´¶ÁÐ´µØÖ·¸ß×Ö½Ú
		if(SimI2C_RecAck())
			return FALSE;
		SimI2C_Stop();
		SimI2C_Start();
		SimI2C_SendByte(MS5803_02ba_ADDR_W);//¶Á
		if(SimI2C_RecAck())
			continue;
		c[i].u8s[1]=SimI2C_ReadByte();
		SimI2C_Ack();
		c[i].u8s[0]=SimI2C_ReadByte();
		SimI2C_NoAck();
		SimI2C_Stop();
	}
	MS5803_02ba_c1=c[1];
	MS5803_02ba_c2=c[2];
	MS5803_02ba_c3=c[3];
	MS5803_02ba_c4=c[4];
	MS5803_02ba_c5=c[5];
	MS5803_02ba_c6=c[6];
}
#else
#define MS5803_02ba_CLK() MS5803_02ba_SCLK=0;__delay_us(1);MS5803_02ba_SCLK=1;__delay_us(1)
uint32_t MS5803_02ba_GetParam(uint8_t param)
{
	uint32_t t;
	uint8_t i,x;
	t=0;
	x=param;
	MS5803_02ba_CSB=0;
	__delay_us(1);
	while(!MS5803_02ba_DOUT);
	for(i=0;i<8;i++)
	{
		if((x&0x80)==0x80)
			MS5803_02ba_DIN=1;
		else
			MS5803_02ba_DIN=0;
		MS5803_02ba_CLK();
		x=x<<1;
	}
	//while(!MS5803_02ba_DOUT);
	__delay_us(1);
	MS5803_02ba_CSB=1;
	__delay_us(1);

	MS5803_02ba_CSB=0;
	while(!MS5803_02ba_DOUT);
	MS5803_02ba_DIN=0;
	__delay_us(1);
	for(i=0;i<8;i++)
	{		
		MS5803_02ba_CLK();
	}
	while(MS5803_02ba_DOUT);
	t=0;
	for(i=0;i<24;i++)
	{
		t=t<<1;
		MS5803_02ba_CLK();
		if(MS5803_02ba_DOUT)
			t=t|0x00000001;		
	}
	MS5803_02ba_CSB=1;
	__delay_20ms(1);
	return t;
}
void MS5803_02ba_Reset(void)
{
	uint8_t i,param;
	param=MS5803_02ba_RESET;
	MS5803_02ba_CSB=0;
	__delay_us(1);
	while(!MS5803_02ba_DOUT);
	for(i=0;i<8;i++)
	{
		if((param&0x80)==0x80)
			MS5803_02ba_DIN=1;
		else
			MS5803_02ba_DIN=0;
		MS5803_02ba_CLK();
		param=param<<1;
	}
	while(!MS5803_02ba_DOUT);
	__delay_20ms(1);
	MS5803_02ba_CSB=1;	
}
void MS5803_02ba_GetCx(void)
{	
	uint8_t i,j,param;
	uint16_t c[7];
	for(i=0;i<7;i++)
		c[i]=0;	
	for(i=6;i>0;i--)
	{
		param=i<<1;
		param=param+0xa0;
		MS5803_02ba_CSB=0;
		__delay_us(1);
		while(!MS5803_02ba_DOUT);
		for(j=0;j<8;j++)
		{
			if((param&0x80)==0x80)
				MS5803_02ba_DIN=1;
			else
				MS5803_02ba_DIN=0;
			MS5803_02ba_CLK();
			param=param<<1;
		}
		//while(MS5803_02ba_DOUT);		
		for(j=0;j<16;j++)
		{
			c[i]=c[i]<<1;
			MS5803_02ba_CLK();
			if(MS5803_02ba_DOUT)
				c[i]=c[i]|0x0001;			
		}
		MS5803_02ba_CSB=1;
		__delay_20ms(1);
	}
	MS5803_02ba_c1=c[1];
	MS5803_02ba_c2=c[2];
	MS5803_02ba_c3=c[3];
	MS5803_02ba_c4=c[4];
	MS5803_02ba_c5=c[5];
	MS5803_02ba_c6=c[6];
}
#endif
uint32_t MS5803_02ba_Calculate(void)
{
	uint32_t t,pp;
	uint32_t Tref,dT,OFF2,SENS2;
	u64 OFF,SENS,P,x64;	
	OFF2=0;
	SENS2=0;
	pp=MS5803_02ba_GetParam(MS5803_02ba_Convert_D1_4096);
	t=MS5803_02ba_GetParam(MS5803_02ba_Convert_D2_4096);

	Tref=((uint32_t)MS5803_02ba_c5)<<8;
	x64=u64_shl(u64_lo((uint32_t)MS5803_02ba_c2),17);
	if(t>Tref)//dT>0
	{
		dT=t-Tref;
		MS5803_02ba_T=u64_shr(u64_lmul(dT,MS5803_02ba_c6),23).lo;		
		MS5803_02ba_T=MS5803_02ba_T+2000;
		OFF=u64_lmul(MS5803_02ba_c4,dT);
		OFF=u64_shr(OFF,6);
		
		OFF=u64_plus(OFF,x64.hi,x64.lo);
		SENS=u64_lmul(MS5803_02ba_c3,dT);
		SENS=u64_shr(SENS,7);		
		SENS=u64_plus(SENS,0,((uint32_t)MS5803_02ba_c1)<<16);
		P=u64_plus(OFF,SENS.hi,SENS.lo);
	}
	else//dT<0
	{
		dT=Tref-t;
		MS5803_02ba_T=u64_shr(u64_lmul(dT,MS5803_02ba_c6),23).lo;
		MS5803_02ba_T=MS5803_02ba_T+2000;
		OFF2=(MS5803_02ba_T*MS5803_02ba_T)>>4;
		OFF2=OFF2*61;
		if(MS5803_02ba_T<2000)//ÕýÎÂ¶È
		{			
			MS5803_02ba_T=2000-MS5803_02ba_T;
		}
		else//¸ºÎÂ¶È
		{
			MS5803_02ba_T=MS5803_02ba_T-2000;
			if(MS5803_02ba_T>3500)//T<-15
			{
				OFF2=OFF2+20*((MS5803_02ba_T-1500)*(MS5803_02ba_T-1500));
				SENS2=SENS2+12*((MS5803_02ba_T-1500)*(MS5803_02ba_T-1500));
			}
		}
		OFF=u64_lmul(MS5803_02ba_c4,dT);
		OFF=u64_shr(OFF,6);
		OFF=u64_decrease(OFF,x64.hi,x64.lo);
		SENS=u64_lmul(MS5803_02ba_c3,dT);
		SENS=u64_shr(SENS,7);
		SENS=u64_decrease(SENS,0,(uint32_t)MS5803_02ba_c1<<16);
		OFF=u64_decrease(OFF,0,OFF2);
		SENS=u64_decrease(SENS,0,SENS2);
	}
	P=u64_lmuu64(SENS,pp);
	P=u64_shr(P,21);
	P=u64_decrease(P,OFF.hi,OFF.lo);
	P=u64_shr(P,15);
	return P.lo;
}
