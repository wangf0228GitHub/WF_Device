#include "HardwareProfile.h"
void HT9200_Init(void)
{
	HT9200_CE_IO=0; 
	HT9200_CLK_IO=0;
	HT9200_DATA_IO=0;

	HT9200_CE_W=1;
	HT9200_CLK_W=1;
	HT9200_DATA_W=0;
}
#ifndef HT9200_Parallel
void HT9200_PhoneCall(const char* pPhoneNumber)
{
	uint8_t i,x;	
	while(*pPhoneNumber!='\0')
	{
		HT9200_CE_W=0;
		__delay_ms(15);
		switch(*pPhoneNumber)
		{
		case '0':
			x=10;
			break;
		case '*':
			x=11;
			break;
		case '#':
			x=12;
			break;
		case 'A':
			x=13;
			break;
		case 'B':
			x=14;
			break;
		case 'C':
			x=15;
			break;
		case 'D':
			x=0;
			break;
		default:
			x=*pPhoneNumber-'0';
			break;
		}		
		for(i=0;i<5;i++)
		{
			if((x&0x01)==0x01)
				HT9200_DATA_W=1;
			else
				HT9200_DATA_W=0;
			HT9200_Serial_Delay();
			HT9200_CLK_W=0;
			HT9200_Serial_Delay();
			HT9200_CLK_W=1;
			HT9200_Serial_Delay();
			x=x>>1;
		}
		pPhoneNumber++;		
		__delay_20ms(10);
		HT9200_CE_W=1;
		__delay_20ms(5);
	}
// 	HT9200_DATA_W=1;//DTMF OFF
// 	for(i=0;i<5;i++)
// 	{
// 		HT9200_Serial_Delay();
// 		HT9200_CLK_W=0;
// 		HT9200_Serial_Delay();
// 		HT9200_CLK_W=1;
// 		HT9200_Serial_Delay();
// 	}	
}
void HT9200_CallNum(char Number)
{
	uint8_t i,x;	
	HT9200_CE_W=0;
	__delay_ms(15);
	switch(Number)
	{
	case '0':
		x=10;
		break;
	case '*':
		x=11;
		break;
	case '#':
		x=12;
		break;
	case 'A':
		x=13;
		break;
	case 'B':
		x=14;
		break;
	case 'C':
		x=15;
		break;
	case 'D':
		x=0;
		break;
	default:
		x=Number-'0';
		break;
	}		
	for(i=0;i<5;i++)
	{
		if((x&0x01)==0x01)
			HT9200_DATA_W=1;
		else
			HT9200_DATA_W=0;
		HT9200_Serial_Delay();
		HT9200_CLK_W=0;
		HT9200_Serial_Delay();
		HT9200_CLK_W=1;
		HT9200_Serial_Delay();
		x=x>>1;
	}		
	__delay_20ms(20);
	HT9200_CE_W=1;
	__delay_20ms(5);
}
#endif


