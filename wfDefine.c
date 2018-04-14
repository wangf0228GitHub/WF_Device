#include "wfDefine.h"
uint8_t BCD2Char(uint8_t bcd)
{
	uint8_t h,l,n;
	h=HIGH_NIBBLE(bcd);
	l=LOW_NIBBLE(bcd);
	n=h*10;
	n=n+l;
	return n;
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
