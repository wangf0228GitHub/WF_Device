#include "HardwareProfile.h"
#ifdef WTH040_ONELINE
void WTH040_OneLine_Play(uint8_t a)
{
	uint8_t i;
	WTH040_RST_W=0;
	__delay_us(200);
	WTH040_RST_W=1;
	__delay_ms(5);
	WTH040_DATA_W=1;
	__delay_ms(20);
	__delay_ms(20);
	__delay_ms(10);
	WTH040_DATA_W=0;
	__delay_ms(20);
	__delay_ms(20);
	__delay_ms(10);
	for(i=0;i<a;i++)
	{
		WTH040_DATA_W=1;
		__delay_us(100);
		WTH040_DATA_W=0;
		__delay_us(100);
	}
}
void WTH040_OneLine_Init(void)
{	
	WTH040_RST_W=1;
	WTH040_DATA_W=0;
	WTH040_RST_IO=0;
	WTH040_DATA_IO=0;
}
#endif
