#include "HardwareProfile.h"

#define MS5536c_CLK() MS5536c_SCLK=0;__delay_us(1);MS5536c_SCLK=1;__delay_us(1)
#define MS5536c_Start() MS5536c_DIN=1;MS5536c_CLK();MS5536c_CLK();MS5536c_CLK()
#define MS5536c_Stop() MS5536c_DIN=0;MS5536c_CLK();MS5536c_CLK();MS5536c_CLK()
#define MS5536c_WB(lx) MS5536c_DIN=lx;MS5536c_CLK()
uint16_t MS5536c_c1;
uint16_t MS5536c_c2;
uint16_t MS5536c_c3;
uint16_t MS5536c_c4;
uint16_t MS5536c_c5;
uint16_t MS5536c_c6;
uint16_t MS5536c_T;
void MS5536c_Reset(void)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MS5536c_WB(1); 
		//MS5536c_CLK();
		MS5536c_WB(0);
		//MS5536c_CLK();
	}
	MS5536c_CLK();
	MS5536c_CLK();
	MS5536c_CLK();
	MS5536c_CLK();
	MS5536c_CLK();
	while(!MS5536c_DOUT);
}
uint16_t MS5536c_GetT(void)
{
	uint16_t t;
	uint8_t i;
	t=0;
	//MS5536c_SCLK=1;__delay_us(1);MS5536c_SCLK=0;__delay_us(1);
	MS5536c_Start();
	/************************************************************************/
	/* 1001                                                                 */
	/************************************************************************/
	MS5536c_WB(1);
	while(MS5536c_DOUT);
	MS5536c_WB(0);
	MS5536c_WB(0);
	MS5536c_WB(1);
	
	MS5536c_Stop();	

	MS5536c_CLK();//附加时钟
	while(!MS5536c_DOUT);
	MS5536c_CLK();

	while(MS5536c_DOUT);

	for(i=0;i<16;i++)
	{
		t=t<<1;
		MS5536c_CLK();
		if(MS5536c_DOUT)
			t=t|0x01;		
	}
	return t;
}
uint16_t MS5536c_GetP(void)
{
	uint16_t p;
	uint8_t i;
	p=0;
	MS5536c_Start();
	/************************************************************************/
	/* 1010                                                                 */
	/************************************************************************/
	MS5536c_WB(1);
	while(MS5536c_DOUT);
	MS5536c_WB(0);
	MS5536c_WB(1);
	MS5536c_WB(0);

	MS5536c_Stop();

	while(!MS5536c_DOUT);
	MS5536c_CLK();//附加时钟	
	MS5536c_CLK();

	while(MS5536c_DOUT);

	for(i=0;i<16;i++)
	{
		p=p<<1;
		MS5536c_CLK();
		if(MS5536c_DOUT)
			p=p|0x01;		
	}
	return p;
}
void MS5536c_GetCx(void)
{
	uint16_t w1,w2,w3,w4,x;
	uint8_t i;
	w1=0;
	w2=0;
	w3=0;
	w4=0;
	while(!MS5536c_DOUT);
 	MS5536c_Start();
 	/************************************************************************/
 	/* w1 010101                                                            */
 	/************************************************************************/
 	MS5536c_WB(0);
 	while(MS5536c_DOUT);
 	MS5536c_WB(1);
 	MS5536c_WB(0);
 	MS5536c_WB(1);
 	MS5536c_WB(0);
 	MS5536c_WB(1);
 
 	MS5536c_Stop();
 	
 	MS5536c_CLK();//附加时钟	
 	while(!MS5536c_DOUT);
 	//MS5536c_CLK();
 	for(i=0;i<16;i++)
 	{
 		w1=w1<<1;
 		MS5536c_CLK();		
 		if(MS5536c_DOUT)
 			w1=w1|0x01; 
 				
 	}
	MS5536c_CLK();
 	MS5536c_Start();
 	/************************************************************************/
 	/* w2 010110                                                            */
 	/************************************************************************/
 	MS5536c_WB(0);
 	while(MS5536c_DOUT);
 	MS5536c_WB(1);
 	MS5536c_WB(0);
 	MS5536c_WB(1);
 	MS5536c_WB(1);
 	MS5536c_WB(0);
 
 	MS5536c_Stop();
 
 	while(!MS5536c_DOUT);
 	MS5536c_CLK();//附加时钟		
 
 	for(i=0;i<16;i++)
 	{
 		w2=w2<<1;
 		MS5536c_CLK();
 		if(MS5536c_DOUT)
 			w2=w2|0x01; 		
 	}
	MS5536c_CLK();
 	MS5536c_Start();
 	/************************************************************************/
 	/* w3 011001                                                            */
 	/************************************************************************/
 	MS5536c_WB(0);
 	while(MS5536c_DOUT);
 	MS5536c_WB(1);
 	MS5536c_WB(1);
 	MS5536c_WB(0);
 	MS5536c_WB(0);
 	MS5536c_WB(1);
 
 	MS5536c_Stop();
 
 	MS5536c_CLK();//附加时钟	
 	while(!MS5536c_DOUT);
 
 	for(i=0;i<16;i++)
 	{
 		w3=w3<<1;
 		MS5536c_CLK();
 		if(MS5536c_DOUT)
 			w3=w3|0x01; 		
 	}
	MS5536c_CLK();
 	MS5536c_Start();
 	/************************************************************************/
 	/* w4 011010                                                            */
 	/************************************************************************/
 	MS5536c_WB(0);
 	while(MS5536c_DOUT);
 	MS5536c_WB(1);
 	MS5536c_WB(1);
 	MS5536c_WB(0);
 	MS5536c_WB(1);
 	MS5536c_WB(0);
 
 	MS5536c_Stop();
 
 	while(!MS5536c_DOUT);
 	MS5536c_CLK();//附加时钟	
 
 	for(i=0;i<16;i++)
 	{
 		w4=w4<<1;
 		MS5536c_CLK();
 		if(MS5536c_DOUT)
 			w4=w4|0x01; 		
 	}
	MS5536c_CLK();
	MS5536c_c1=w3&0x0fff;
	if((w4&0x8000)==0x8000)
		MS5536c_c1=MS5536c_c1|(1<<12);
	MS5536c_c2=w4&0x1fff;
	MS5536c_c3=w1&0xff00;
	MS5536c_c3=MS5536c_c3>>8;
	if((w4&0x2000)==0x2000)
		MS5536c_c3=MS5536c_c3|(1<<8);
	MS5536c_c4=w2&0xff00;
	MS5536c_c4=MS5536c_c4>>8;
	if((w4&0x4000)==0x4000)
		MS5536c_c4=MS5536c_c4|(1<<8);
	MS5536c_c5=w1&0x00ff;
	x=w3&0xf000;
	x=x>>4;
	MS5536c_c5=MS5536c_c5|x;
	MS5536c_c6=w2&0x00ff;
	if(MS5536c_c6==0)
		MS5536c_c5=0;
}
uint16_t MS5536c_Calculate(void)
{
	uint16_t UT1;
	uint16_t t,p;
	uint32_t lx;	
	uint16_t dT,OFF,SENS,X,P;
	UT1=(MS5536c_c5<<2)+15136;
	p=MS5536c_GetP();
	t=MS5536c_GetT();	
	if(t>UT1)
	{
		dT=t-UT1;
		lx=(uint32_t)dT*(MS5536c_c6+262);
		lx=lx>>9;
		lx=lx+2000;
		MS5536c_T=lx;
		if(MS5536c_c4>243)
			OFF=MS5536c_c2+10381+(((long)(MS5536c_c4-243)*(long)dT)>>12);
		else
		{
			OFF=MS5536c_c2+10381-(((long)(243-MS5536c_c4)*(long)dT)>>12);
		}
	}
	else
	{
		dT=UT1-dT;
		if(MS5536c_c4>243)
			OFF=MS5536c_c2+10381-(((long)(MS5536c_c4-243)*(long)dT)>>12);
		else
		{
			OFF=MS5536c_c2+10381+(((long)(243-MS5536c_c4)*(long)dT)>>12);
		}
	}
	SENS=MS5536c_c1+10179+(((long)(MS5536c_c3+222)*(long)dT)>>11);
	if(p>OFF)
	{
		X=((long)SENS*(long)(p-OFF))>>12;
	}
	else
	{
		X=((long)SENS*(long)(OFF-P))>>12;
	}
	lx=(long)X*(long)1365;
	lx=lx>>9;
	P=lx;
	return P;
}
