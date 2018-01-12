#include "HardwareProfile.h"
#include "SimSPI.h"
#include "X5045.h"

//#define X5045_CS_DIR	TRISA2
//#define X5045_WP_DIR	TRISA0
//
//#define X5045_CS	RA1
//#define X5045_WP	RA2
//写允许
void X5045_WREN()
{
	X5045_WP=1;//关闭写保护
	X5045_CS=0;
	SimSPI_Proc(0b00000110);
	X5045_CS=1;
}
//写禁止
void X5045_WRDI()
{
	X5045_WP=0;//启动写保护
	X5045_CS=0;
	SimSPI_Proc(0b00000100);
	X5045_CS=1;
}
void X5045_Init()
{
	X5045_CS_DIR=0;
	X5045_WP_DIR=0;
	SimSPI_Init();
	X5045_WP=0;//启动写保护
	X5045_CS=0;
	NOP();
	X5045_CS=1;
}
//复位看门狗
void X5045_RstWDT()
{
	if(X5045_CS==0)//当前处于工作状态
		return;
	X5045_CS=0;
	NOP();
	X5045_CS=1;
}
//5045状态寄存器读出程序
//等待X5045结束内部写周期
void X5045_WIPCheck()
{
	unsigned char dat;
	do
	{
		dat=X5045_RDSR();
		dat&=0x01;		
	}
	while(dat);
}
unsigned char X5045_RDSR()
{
	unsigned char x;
	X5045_CS=0;
	SimSPI_Proc(0b00000101);
	x=SimSPI_Proc(0);
	X5045_CS=1;
	return (x);
}
//5045状态寄存器写入程序
void X5045_WRSR(unsigned char x)
{
	X5045_WREN();
	X5045_CS=0;
	SimSPI_Proc(0b00000001);
	SimSPI_Proc(x);
	X5045_CS=1;
	X5045_WIPCheck();	
	X5045_WRDI();
}
//向X5045写入单字节数据,输入：x,待写数据,address,写入数据的地址
#ifndef X5045_MorePage
void X5045_WriteByte(unsigned char address,unsigned char x)
{
    X5045_WREN();
    X5045_CS=0;
    SimSPI_Proc(0b00000010);
    SimSPI_Proc(address);
    SimSPI_Proc(x);
    X5045_CS=1;
    X5045_WIPCheck();	
    X5045_WRDI();
}
void X5045_WriteBytes(unsigned char address,unsigned char* pW,unsigned char wCount)
{
    unsigned char i,x;
    X5045_WREN();
    X5045_CS=0;
    SimSPI_Proc(0b00000010);
    SimSPI_Proc(address);
    for(i=0;i<wCount;i++)
    {
        x=pW[i];
        SimSPI_Proc(x);
    }	
    X5045_CS=1;
    X5045_WIPCheck();	
    X5045_WRDI();
}
//从X5045读入单字节数据,输入：address,待读数据地址,返回：读出的数据
unsigned char X5045_ReadByte(unsigned char address)
{
    unsigned char x;
    X5045_CS=0;
    SimSPI_Proc(0b00000011);
    SimSPI_Proc(address);
    x=SimSPI_Proc(0);
    X5045_CS=1;
    return (x);
}
void X5045_ReadBytes(unsigned char address,unsigned char* pR,unsigned char rCount)
{
    unsigned char i,x;
    X5045_CS=0;
    SimSPI_Proc(0b00000011);
    SimSPI_Proc(address);
    for(i=0;i<rCount;i++)
    {
        x=SimSPI_Proc(0);
        pR[i]=x;
    }	
    X5045_CS=1;
}
#else
void X5045_WriteByte(unsigned char address,unsigned char x,unsigned char page)
{
    X5045_WREN();
    X5045_CS=0;
    if(page!=0)
        SimSPI_Proc(0b00001010);
    else
        SimSPI_Proc(0b00000010);
    SimSPI_Proc(address);
    SimSPI_Proc(x);
    X5045_CS=1;
    X5045_WIPCheck();	
    X5045_WRDI();
}
void X5045_WriteBytes(unsigned char address,unsigned char* pW,unsigned char wCount,unsigned char page)
{
    unsigned char i,x;
    X5045_WREN();
    X5045_CS=0;
    if(page!=0)
        SimSPI_Proc(0b00001010);
    else
        SimSPI_Proc(0b00000010);
    SimSPI_Proc(address);
    for(i=0;i<wCount;i++)
    {
        x=pW[i];
        SimSPI_Proc(x);
    }	
    X5045_CS=1;
    X5045_WIPCheck();	
    X5045_WRDI();
}
//从X5045读入单字节数据,输入：address,待读数据地址,返回：读出的数据
unsigned char X5045_ReadByte(unsigned char address,unsigned char page)
{
    unsigned char x;
    X5045_CS=0;
    if(page!=0)
        SimSPI_Proc(0b00001011);
    else
        SimSPI_Proc(0b00000011);
    SimSPI_Proc(address);
    x=SimSPI_Proc(0);
    X5045_CS=1;
    return (x);
}
void X5045_ReadBytes(unsigned char address,unsigned char* pR,unsigned char rCount,unsigned char page)
{
    unsigned char i,x;
    X5045_CS=0;
    if(page!=0)
        SimSPI_Proc(0b00001011);
    else
        SimSPI_Proc(0b00000011);
    SimSPI_Proc(address);
    for(i=0;i<rCount;i++)
    {
        x=SimSPI_Proc(0);
        pR[i]=x;
    }	
    X5045_CS=1;
}
#endif
