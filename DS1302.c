#include "HardwareProfile.h"
//#include "TypeDefine.h"
#include "DS1302.h"

DS1302_TIME DS1302_Time;//秒;分;时;日;月;星期;年;
void DS1302_WriteCommand(uint8_t cmd,uint8_t data);
void DS1302_WriteByte(uint8_t tx);
uint8_t DS1302_ReadByte(void);
//DS1302初始化函数
void DS1302_Init()
{
// 	DS1302_DATA_OUT();// = 0;
// 	DS1302_CLK_IO=0;
// 	DS1302_CE_IO=0;
	DS1302_CLK_Low();// = 0;	//拉低时钟信号
	__delay_us(1);
	DS1302_CE_Low();// = 0;	//复位DS1302
	__delay_us(1);	
}
//写保护切换
void DS1302_WP(uint8_t bWP)
{
	if(bWP==0)//可写
	{
		DS1302_WriteCommand(0x8e,0x00);
	}
	else
	{
		DS1302_WriteCommand(0x8e,0x80);
	}
}
//时钟开关切换
void DS1302_Switch(uint8_t bStart)
{
	uint8_t s;
	DS1302_CE_High();// = 1;//使能DS1302
	DS1302_WriteByte(0x81);
	s=DS1302_ReadByte();
	DS1302_CE_Low();//=0;	//复位
	DS1302_WP(0);//关闭写保护
	if(bStart==1)//启动
	{
		s=s&0x7f;
	}
	else
	{
		s=s|0x80;	
	}
	DS1302_WriteCommand(0x80,s);
	DS1302_WP(1);//写保护
}
//---------------------------------------------
//设置时间函数
void DS1302_SetTime()
{
	uint8_t i;	//定义循环变量
	DS1302_Time.Hour &= 0x7f;//强行为24小时模式
	DS1302_WP(0);//关闭写保护
	DS1302_CE_High();//=1;	//使能DS1302
	DS1302_WriteByte(0xbe);	//时钟多字节写命令
	for(i=0;i<7;i++)	//连续写8个字节数据
	{
		DS1302_WriteByte(DS1302_Time.Times[i]);	//调用写一个字节函数
	}
	DS1302_WP(0);//关闭写保护
	DS1302_CE_Low();//=0;	//复位
	DS1302_WP(1);//写保护
}
void DS1302_SetHour24(uint8_t b24)
{
	DS1302_GetTime();
	if(b24==0x01)
		DS1302_Time.Hour &= 0x7f;//强行为24小时模式
	else
		DS1302_Time.Hour |= 0x80;
	DS1302_WP(0);//关闭写保护
	DS1302_CE_High();//=1;	//使能DS1302
	DS1302_WriteByte(0x84);	//时钟多字节写命令
	DS1302_WriteByte(DS1302_Time.Hour);	//调用写一个字节函数
	DS1302_WP(0);//关闭写保护
	DS1302_CE_Low();//=0;	//复位
	DS1302_WP(1);//写保护
}
//---------------------------------------------
//读取时间函数
//秒;分;时;日;月;星期;年;
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void DS1302_GetTime()
{
	uint8_t i;//设置循环变量
	DS1302_CE_High();//=1;	//使能DS1302
	DS1302_WriteByte(0xbf);//发送多字节读取命令
	for(i=0;i<7;i++)//连续读取7个字节数据
	{
		DS1302_Time.Times[i]=DS1302_ReadByte();//调用读取1个字节数据的函数
	}
	DS1302_CE_Low();//=0;	//复位
}
void DS1302_ReadTime(DS1302_TIME* t)
{
	uint8_t i;//设置循环变量
	DS1302_CE_High();//=1;	//使能DS1302
	DS1302_WriteByte(0xbf);//发送多字节读取命令
	for(i=0;i<7;i++)//连续读取7个字节数据
	{
		(*t).Times[i]=DS1302_ReadByte();//调用读取1个字节数据的函数
	}
	DS1302_CE_Low();//=0;	//复位
}
//--------------------------------------------
//写一个字节数据函数
void DS1302_WriteCommand(uint8_t cmd,uint8_t data)
{
	DS1302_CE_High();//=1;	//使能DS1302
	__delay_us(1);
	DS1302_WriteByte(cmd);	//发控制命令
	DS1302_WriteByte(data);	//发送命令内容
	__delay_us(1);
	DS1302_CE_Low();//=0;	//复位
}
//--------------------------------------------
//写一个字节数据函数
void DS1302_WriteByte(uint8_t tx)
{
	uint8_t i;	//设置循环变量
	for(i=0;i<8;i++)	//连续写8bit
	{
		__delay_us(1);
		DS1302_DATA_Low();//=0;	//先设置数据为0
		DS1302_CLK_Low();//=0;	//时钟信号拉低		
		if(tx&0x01)	//判断待发送的数据位是0或1
		{
			DS1302_DATA_High();//=1;	//待发送数据位是1
		}
		__delay_us(1);
		tx=tx>>1;	//待发送的数据右移1位
		DS1302_CLK_High();//=1;	//拉高时钟信号
	}
	DS1302_CLK_Low();//W=0;	//写完一个字节，拉低时钟信号
}
//---------------------------------------------
//读一个字节函数
uint8_t DS1302_ReadByte(void)
{
	uint8_t i,rx=0;//设置循环变量
	DS1302_DATA_SetInput();//设置数据口方向为输入
	for(i=0;i<8;i++)//连续读取8bit
	{
		DS1302_CLK_Low();//拉低时钟信号
		__delay_us(1);
		rx=rx>>1;//接收寄存器右移1位
		if(DS1302_DATA_Read())
			rx=rx|0x80;//把接收到的数据放到接收寄存器的最高位
		DS1302_CLK_High();//拉高时钟信号
		__delay_us(1);
	}
	DS1302_DATA_SetOutput();// = 0;//恢复数据口方向为输出
	DS1302_CLK_Low();//拉低时钟信号
	return(rx);//返回读取到的数据
}
uint8_t DS1302_GetMonth( void )
{
	uint8_t M;	
	M=DS1302_Time.Month&0x0f;
	if(DS1302_Time.Month>0x0f)
		M=M+10;
	return M;
}
uint8_t DS1302_GetDay( void )
{
	uint8_t D;
	D=DS1302_Time.Day>>4;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	case 0x03:
		D=30;
		break;
	}
	D=D+(DS1302_Time.Day&0x0f);
	return D;
}

uint8_t DS1302_GetHour24( void )
{
	uint8_t D;
	D=DS1302_Time.Hour>>4;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	}
	D=D+(DS1302_Time.Hour&0x0f);
	return D;
}
uint8_t DS1302_GetMinute( void )
{
	uint8_t D;
	D=DS1302_Time.Minute>>4;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	case 0x03:
		D=30;
		break;
	case 0x04:
		D=40;
		break;
	case 0x05:
		D=50;
		break;
	}
	D=D+(DS1302_Time.Minute&0x0f);
	return D;
}

uint8_t DS1302_GetSecond( void )
{
	uint8_t D;
	D=DS1302_Time.Second>>4;
	D=D&0x07;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	case 0x03:
		D=30;
		break;
	case 0x04:
		D=40;
		break;
	case 0x05:
		D=50;
		break;
	}
	D=D+(DS1302_Time.Second&0x0f);
	return D;
}
uint8_t DS1302_GetNum(uint8_t x)
{
	uint8_t D;
	D=x>>4;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	case 0x03:
		D=30;
		break;
	case 0x04:
		D=40;
		break;
	case 0x05:
		D=50;
		break;
	}
	D=D+(x&0x0f);
	return D;
}
void DS1302_Convert2Char(void)
{
	DS1302_Time.Year=DS1302_GetNum(DS1302_Time.Year);
	DS1302_Time.Month=DS1302_GetNum(DS1302_Time.Month);
	DS1302_Time.Day=DS1302_GetNum(DS1302_Time.Day);
	DS1302_Time.Hour=DS1302_GetNum(DS1302_Time.Hour);
	DS1302_Time.Minute=DS1302_GetNum(DS1302_Time.Minute);
	DS1302_Time.Second=DS1302_GetNum(DS1302_Time.Second&0x7f);
}
