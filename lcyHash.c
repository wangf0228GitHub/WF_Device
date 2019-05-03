#include "lcyHash.h"

uint8_t lcyHashIn[0x08];
uint8_t lcyHashOut[0x08];
uint8_t F_calsel;

uint8_t Ht[0x10];

void sub_add_4B(uint8_t* p)
{
	uint8_t i,C;
	uint16_t Sum;
	C=0;
	for(i=0;i<0x04;i++)
	{
		Sum=Ht[0x0B-i]+p[0x03-i]+C;
		Ht[0x0B-i]=Ht[0x0B-i]+p[0x03-i]+C;
		if(Sum>0xFF)
		{
			C=0x01;
		}
		else
		{
			C=0x00;
		}
	}
}
/*---------------------------------------------------------------------*/
void sub_Shift_L(uint8_t N)//N is cnt
{
	uint8_t C,Ct,i,j;
	for(i=0;i<N;i++)
	{
		C=Ht[0x08]&0x80;
		for(j=0;j<0x04;j++)
		{
			Ct=Ht[0x0B-j]&0x80;
			Ht[0x0B-j]=Ht[0x0B-j]<<1;
			if(0x00==C)
			{
				Ht[0x0B-j]=Ht[0x0B-j]&0xFE;
			}
			else
			{
				Ht[0x0B-j]=Ht[0x0B-j]|0x01;
			}
			C=Ct;
		}
	}
}
/*---------------------------------------------------------------------*/
void sub_Shift_R(uint8_t N)//N is cnt
{
	uint8_t C,Ct,i,j;
	for(i=0;i<N;i++)
	{
		C=Ht[0x0B]&0x01;
		for(j=0;j<0x04;j++)
		{
			Ct=Ht[0x08+j]&0x01;
			Ht[0x08+j]=Ht[0x08+j]>>1;
			if(0x00==C)
			{
				Ht[0x08+j]=Ht[0x08+j]&0x7F;
			}
			else
			{
				Ht[0x08+j]=Ht[0x08+j]|0x80;
			}
			C=Ct;
		}
	}
}
/*---------------------------------------------------------------------*/
void sub_Mixed_A()//
{
	//                              +0   +1   +2   +3   +4   +5   +6   +7   +8   +9   +A   +B   +C   +D   +E   +F
	const uint8_t Ta[0x10]={0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0F,0x0C,0x0D,0x0E,0x00,0x01,0x02,0x03};
	uint8_t tmp[0x10];
	uint8_t i,j;

	for(i=0;i<0x10;i++)
	{
		j=Ta[i];
		tmp[j]=Ht[i];
	}
	//
	for(i=0;i<0x10;i++)
	{
		Ht[i]=tmp[i];
	}
}
/*---------------------------------------------------------------------*/
void sub_Mixed_B()//
{
	//                              +0   +1   +2   +3   +4   +5   +6   +7   +8   +9   +A   +B   +C   +D   +E   +F
	const uint8_t Tb[0x10]={0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0E,0x0F,0x0C,0x0D,0x00,0x01,0x02,0x03};
	uint8_t tmp[0x10];
	uint8_t i,j;

	for(i=0;i<0x10;i++)
	{
		j=Tb[i];
		tmp[j]=Ht[i];
	}
	//
	for(i=0;i<0x10;i++)
	{
		Ht[i]=tmp[i];
	}
}
/*---------------------------------------------------------------------*/
void sub_cal0()//0AFE
{
	uint8_t i;
	uint8_t Biao_a[0x04]={0x50,0xA2,0x8B,0xE6};
	uint8_t TP[0x04];
	for(i=0;i<0x04;i++)
	{
		TP[i]=((Ht[0x00+i]^Ht[0x04+i])&Ht[0x0C+i])^Ht[0x04+i];
	}
	sub_add_4B(TP);
	if(F_calsel!=0)
	{
		sub_add_4B(Biao_a);
	}
}
/*---------------------------------------------------------------------*/
void sub_cal1(uint8_t s)//0CDF
{
	uint8_t i;
	uint8_t T[0x04];
	s=s&0x04;
	for(i=0;i<0x04;i++)
	{
		T[0x03-i]=lcyHashIn[i+s];
	}
	sub_add_4B(T);
}
/*---------------------------------------------------------------------*/
void sub_cal2()//0B4B
{
	uint8_t i;
	uint8_t Biao_b[0x04]={0x5A,0x82,0x79,0x99};
	uint8_t TP[0x04];
	uint8_t m,n;

	for(i=0;i<0x04;i++)
	{
		m=Ht[0x00+i]&Ht[0x04+i];
		n=(Ht[0x00+i]|Ht[0x04+i])&Ht[0x0C+i];
		TP[i]=m|n;
	}
	//--
	sub_add_4B(TP);
	if(0==F_calsel)
	{
		sub_add_4B(Biao_b);
	}
}
/*---------------------------------------------------------------------*/
void sub_cal3()//0BD9
{
	uint8_t i;
	uint8_t Biao_c[0x04]={0x6E,0xD9,0xEB,0xA1};
	uint8_t Biao_d[0x04]={0x5C,0x4D,0xD1,0x24};
	uint8_t TP[0x04];

	for(i=0;i<0x04;i++)
	{
		TP[i]=Ht[0x00+i]^Ht[0x04+i]^Ht[0x0C+i];
	}
	//--
	sub_add_4B(TP);
	if(0==F_calsel)
	{
		sub_add_4B(Biao_c);
	}
	else
	{
		sub_add_4B(Biao_d);
	}
}
/*---------------------------------------------------------------------*/
void sub_cal_L_A(uint8_t x)//
{
	sub_Shift_L(x);
	sub_Mixed_A();
}
/*---------------------------------------------------------------------*/
void sub_cal_L_B(uint8_t x)//
{
	sub_Shift_L(x);
	sub_Mixed_B();
}
/*---------------------------------------------------------------------*/
void sub_cal_R_A(uint8_t x)//
{
	sub_Shift_R(x);
	sub_Mixed_A();
}
/*---------------------------------------------------------------------*/
void sub_cal_R_B(uint8_t x)//
{
	sub_Shift_R(x);
	sub_Mixed_B();
}
void loadTab()
{
	const uint8_t TAB0[0x10]={
		0x45,0x03,0x11,0x4F,0x85,0x4C,0x7A,0x31,
		0xF6,0x7C,0xCB,0xB8,0x15,0xA4,0xD0,0x42};
	const uint8_t TAB1[0x10]={
		0x51,0x9B,0x49,0x14,0xB1,0x2E,0x8F,0xB5,
		0x95,0xDE,0x62,0x7A,0xD8,0x0D,0x44,0x1C};

	int i;
	for(i=0;i<0x10;i++)
	{
		if(0==F_calsel)
		{
			Ht[i]=TAB0[i];
		}
		else
		{
			Ht[i]=TAB1[i];
		}
	}
}
void sub_half()
{
	uint8_t n,m;
	loadTab();
	sub_cal0();//0AFE
	n=0x00;
	sub_cal1(n);//0CDF
	m=1;
	sub_cal_L_A(m);//0A9C
	sub_cal0();//0AFE
	n=0x04;
	sub_cal1(n);//0CDF
	sub_Mixed_A();
	//00
	sub_cal2();//0B4B
	m=1;
	sub_cal_R_A(m);//0A95
	//01
	sub_cal2();//0B4B
	m=2;
	sub_cal_R_A(m);//
	//02
	sub_cal2();//0B4B
	sub_Mixed_A();
	//03
	sub_cal2();//0B4B
	m=3;
	sub_cal_R_B(m);
	//04
	sub_cal2();//0B4B
	m=3;
	sub_cal_L_A(m);
	//05
	sub_cal2();//0B4B
	m=1;
	sub_cal_L_A(m);
	//06
	sub_cal2();//0B4B
	n=0x04;
	sub_cal1(n);//0CDF
	m=1;
	sub_cal_R_A(m);//
	//07
	sub_cal2();//0B4B
	m=1;
	sub_cal_R_B(m);
	//08
	sub_cal2();//0B4B
	m=1;
	sub_cal_R_A(m);//
	//09
	sub_cal2();//0B4B
	m=4;
	sub_cal_L_A(m);
	//0A
	sub_cal2();//0B4B
	m=1;
	sub_cal_R_B(m);
	//0B
	sub_cal2();//0B4B
	m=1;
	sub_cal_L_A(m);
	//0C
	sub_cal2();//0B4B
	n=0x00;
	sub_cal1(n);//0CDF
	m=1;
	sub_cal_R_A(m);//
	//0D
	sub_cal2();//0B4B
	m=3;
	sub_cal_L_A(m);
	//0E
	sub_cal2();//0B4B
	m=3;
	sub_cal_R_B(m);//
	//0F
	sub_cal2();//0B4B
	m=4;
	sub_cal_L_A(m);
	//10
	sub_cal3();//0BD9
	m=3;
	sub_cal_L_A(m);
	//11
	sub_cal3();//0BD9
	m=3;
	sub_cal_R_B(m);
	//12
	sub_cal3();//0BD9
	m=2;
	sub_cal_R_B(m);
	//13
	sub_cal3();//0BD9
	m=1;
	sub_cal_R_A(m);
	//14
	sub_cal3();//0BD9
	m=2;
	sub_cal_R_B(m);
	//15
	sub_cal3();//0BD9
	n=0x04;
	sub_cal1(n);//0CDF
	m=1;
	sub_cal_L_A(m);
	//16
	sub_cal3();//0BD9
	m=3;
	sub_cal_R_B(m);
	//17
	sub_cal3();//0BD9
	m=1;
	sub_cal_R_B(m);
	//18
	sub_cal3();//0BD9
	n=0x00;
	sub_cal1(n);//0CDF
	m=2;
	sub_cal_R_A(m);
	//19
	sub_cal3();//0BD9
	sub_Mixed_A();
	//1A
	sub_cal3();//0BD9
	m=3;
	sub_cal_R_B(m);
	//1B
	sub_cal3();//0BD9
	m=2;
	sub_cal_R_A(m);
	//1C
	sub_cal3();//0BD9
	m=4;
	sub_cal_L_A(m);
	//1D
	sub_cal3();//0BD9
	m=3;
	sub_cal_R_A(m);
	//1E
	sub_cal3();//0BD9
	m=1;
	sub_cal_R_A(m);
	//1F
	sub_cal3();//0BD9
	m=3;
	sub_cal_R_A(m);
}
void sub_add(uint8_t *p,uint8_t*s)
{
	uint8_t i,C;
	uint16_t Sum;
	const uint8_t B[0x08]={0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98};
	//--
	C=0;
	for(i=0;i<0x04;i++)
	{
		Sum=p[0x03-i]+s[0x03-i]+C;
		lcyHashOut[0x00+i]=p[0x03-i]+s[0x03-i]+C;
		if(Sum>0xFF)
		{
			C=0x01;
		}
		else
		{
			C=0x00;
		}
	}
	//
	C=0;
	for(i=0;i<0x04;i++)
	{
		Sum=lcyHashOut[0x00+i]+B[i]+C;
		lcyHashOut[0x00+i]=lcyHashOut[0x00+i]+B[i]+C;
		if(Sum>0xFF)
		{
			C=0x01;
		}
		else
		{
			C=0x00;
		}
	}
	//--
	C=0;
	for(i=0;i<0x04;i++)
	{
		Sum=p[0x07-i]+s[0x07-i]+C;
		lcyHashOut[0x04+i]=p[0x07-i]+s[0x07-i]+C;
		if(Sum>0xFF)
		{
			C=0x01;
		}
		else
		{
			C=0x00;
		}
	}
	//
	C=0;
	for(i=0;i<0x04;i++)
	{
		Sum=lcyHashOut[0x04+i]+B[0x04+i]+C;
		lcyHashOut[0x04+i]=lcyHashOut[0x04+i]+B[0x04+i]+C;
		if(Sum>0xFF)
		{
			C=0x01;
		}
		else
		{
			C=0x00;
		}
	}
	//--
}
void lcyHashInit(uint8_t* pBuf)
{
	uint8_t i;
	for(i=0;i<8;i++)
		lcyHashIn[i]=pBuf[i];
}
void lcyHashRead(uint8_t* pBuf)
{
	uint8_t i;
	for(i=0;i<8;i++)
		pBuf[i]=lcyHashOut[i];
}
void GetlcyHashOnce(uint8_t* pIn,uint8_t* pOut)
{
	uint8_t i;
	for(i=0;i<8;i++)
		lcyHashIn[i]=pIn[i];
	lcyHashOnce();
	for(i=0;i<8;i++)
		pOut[i]=lcyHashOut[i];
}
void GetlcyHashN(uint8_t* pIn,uint8_t* pOut,uint8_t n)
{
	uint8_t i;
	for(i=0;i<8;i++)
		lcyHashIn[i]=pIn[i];
	lcyHashCalc(n);
	for(i=0;i<8;i++)
		pOut[i]=lcyHashOut[i];
}
void lcyHashOnce(void)
{
	uint8_t i;
	uint8_t Sa[0x08];
	uint8_t Sb[0x08];
	//--
	F_calsel=0;
	sub_half();
	for(i=0;i<8;i++)
	{
		Sa[i]=Ht[i];
	}
	F_calsel=1;
	sub_half();
	for(i=0;i<8;i++)
	{
		Sb[i]=Ht[i+0x04];
	}
	sub_add(Sa,Sb);
}
void lcyHashCalc(uint8_t n)
{
	uint8_t i,j;
	for(i=0;i<n;i++)
	{
		lcyHashOnce();
		for(j=0;j<8;j++)
		{
			lcyHashIn[j]=lcyHashOut[j];
		}
	}
}
