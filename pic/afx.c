#include "afx.h"
#include "TypeDefine.h"
#include "wfDefine.h"
#ifdef MCC30
uint8_t wCPU_IPL;
#endif
void __delay_20ms(uint16_t x)
{
	while(x--)
	{
		__delay_ms(20);
	}
}

uint8_t BCD2Char(uint8_t bcd)
{
	uint8_t h,l,n;
	h=HIGH_NIBBLE(bcd);
	l=LOW_NIBBLE(bcd);
	n=h*10;
	n=n+l;
	return n;
}
//没有之前的无用0
void Int2BCD_Array_NoH0(uint16_t Value,uint8_t* Buffer)
{
	uint8_t i;
	uint16_t Digit;
	uint16_t Divisor;
	uint8_t Printed = 0;

	if(Value)
	{
		for(i = 0, Divisor = 10000; i < 5u; i++)
		{
			Digit = Value/Divisor;
			if(Digit || (Printed==1))
			{
				*Buffer++ = Digit;
				Value -= Digit*Divisor;
				Printed = 1;
			}
			Divisor /= 10;
		}
	}
	else
	{
		*Buffer++ = '0';
	}
	*Buffer = '\0';
}
uint32_t Long2BCD(uint32_t l)
{
	u32_wf ret;
	uint8_t x;
	ret.u32=0;
	if(l>99999999)
		return 0;
	x=l/10000000;//8
	ret.u8s[3]=HIGH_NIBBLE(x);
	l=l-x*10000000;
	x=l/1000000;//7
	ret.u8s[3]=LOW_NIBBLE(x);
	l=l-x*1000000;
	x=l/100000;//6
	ret.u8s[2]=HIGH_NIBBLE(x);
	l=l-x*100000;
	x=l/10000;//5
	ret.u8s[2]=LOW_NIBBLE(x);
	l=l-x*10000;
	x=l/1000;//4
	ret.u8s[1]=HIGH_NIBBLE(x);
	l=l-x*1000;
	x=l/100;//3
	ret.u8s[1]=LOW_NIBBLE(x);
	l=l-x*100;
	x=l/10;//2
	ret.u8s[0]=HIGH_NIBBLE(x);
	l=l-x*10;
	//x=l/10000;//1
	ret.u8s[0]=LOW_NIBBLE(x);
	return ret.u32;
}
void Byte2ASCII(uint8_t b, uint8_t *h, uint8_t *l)
{
	//h=(uint8_t)h;
	//l=(uint8_t)l;
	*h = HIGH_NIBBLE(b);
	*l = LOW_NIBBLE(b);
	if (*h > 9)
		*h = *h - 0x0a + 'A';
	else
		*h = *h + '0';
	if (*l > 9)
		*l = *l - 0x0a + 'A';
	else
		*l = *l + '0';
}
uint8_t ASCII2Byte_Capital(uint8_t h,uint8_t l)
{
	if(h>'9')
		h=h-55;//-'A'+10;
	else
		h=h-'0';
	if(l>'9')
		l=l-55;//-'A'+10;
	else
		l=l-'0';
	return MAKE_BYTE(h,l);
}
uint8_t ASCII2Byte_Lowercase(uint8_t h,uint8_t l)
{
	if(h>'9')
		h=h-87;//-'a'+10;
	else
		h=h-'0';
	if(l>'9')
		l=l-87;//-'a'+10;
	else
		l=l-'0';
	return MAKE_BYTE(h,l);
}
#ifdef WFRomOperation
uint8_t GetRomData(void)
{
	uint8_t i;	
	for(i=0;i<RomCount;i++)
		RomParams.All[i]=eeprom_read(i);
	i=GetVerify_Sum(&RomParams.All[1],RomCount-1);
	i+=eeprom_offset;
	if(i==RomParams.sum)//存储区校验成功
	{		
		return 1;
	}
	else
		return 0;	
}
void SaveRomData(void)
{
	uint8_t i;
	RomParams.sum=GetVerify_Sum(&RomParams.All[1],RomCount-1);
	RomParams.sum+=eeprom_offset;
	for(i=0;i<RomCount;i++)
		eeprom_write(i,RomParams.All[i]);
}
#endif
#ifdef WFRomOperation_OneByte
uint8_t GetRomData(void)
{
	uint8_t x,x1;	
	x=eeprom_read(WFRomOneByteAddr);
	x1=eeprom_read(WFRomOneByteAddr+1);
	x1=~x1;
	if(x==x1)
	{
		WFRomOneByte=x;
		return 1;
	}
	else
		return 0;	
}
void SaveRomData(void)
{
	eeprom_write(WFRomOneByteAddr,WFRomOneByte);
	eeprom_write(WFRomOneByteAddr+1,~WFRomOneByte);
}
#endif
