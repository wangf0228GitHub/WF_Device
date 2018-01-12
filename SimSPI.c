#include "HardwareProfile.h"
#include "SimSPI.h"
// #define SimSPI_SCL_DIR	TRISA1
// #define SimSPI_SDI_DIR	TRISA2
// #define SimSPI_SDO_DIR	TRISA0
// 
// #define SimSPI_SCL_W	RA1
// #define SimSPI_SDI_R	RA2	
// #define SimSPI_SDO_W	RA0

//Mode 0	CPOL=0, CPHA=0
//Mode 1	CPOL=0, CPHA=1
//Mode 2	CPOL=1, CPHA=0
//Mode 3	CPOL=1, CPHA=1
void SimSPI_Init(void)
{	
#if defined(SimSPI_SPI0) || defined(SimSPI_SPI1) 
	SimSPI_SCL_W=0;	//拉低时钟信号
#elif defined(SimSPI_SPI2) || defined(SimSPI_SPI3) 
	SimSPI_SCL_W=1;	//拉高时钟信号
#endif
	SimSPI_SCL_DIR=0;
	SimSPI_SDI_DIR=1;
	SimSPI_SDO_DIR=0;	
}
#ifdef SimSPI_LSB//低位在前
	unsigned char SimSPI_Proc(unsigned char c)
	{
		unsigned char i,ret;
		ret=0;
	#if defined(SimSPI_SPI0)
		for(i=0;i<8;i++)
		{
			SimSPI_SCL_W=0;	//下降沿接收数据
			ret=ret>>1;
			SimSPI_Delay();
			if(SimSPI_SDI_R==1)
				ret|=0x80;
			SimSPI_SDO_W=0;
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SimSPI_SDO_W=1;	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SimSPI_SCL_W=1;//上升沿发送					
		}
		SimSPI_SCL_W=0;	//空闲为低电平
	#elif defined(SimSPI_SPI1) 
		for(i=0;i<8;i++)
		{		
			SimSPI_SCL_W=1;	//上升沿接收数据
			ret=ret>>1;
			SimSPI_Delay();
			if(SimSPI_SDI_R==1)
				ret|=0x80;
			SimSPI_SDO_W=0;
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SimSPI_SDO_W=1;	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SimSPI_SCL_W=0;//下降沿发送					
		}
	#elif defined(SimSPI_SPI2) 
		for(i=0;i<8;i++)
		{
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SimSPI_SDO_W=1;	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SimSPI_SCL_W=0;//下降沿发送	
			SimSPI_Delay();
			SimSPI_SCL_W=1;	//上升沿接收数据
			ret=ret>>1;
			SimSPI_Delay();
			if(SimSPI_SDI_R==1)
				ret|=0x80;					
		}
	#elif defined(SimSPI_SPI3) 
		for(i=0;i<8;i++)
		{
			SimSPI_SCL_W=0;	//下降沿接收数据
			ret=ret>>1;
			SimSPI_Delay();
			if(SimSPI_SDI_R==1)
				ret|=0x80;
			SimSPI_SDO_W=0;
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SimSPI_SDO_W=1;	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SimSPI_SCL_W=1;//上升沿发送	
			SimSPI_Delay();
		}
	#endif
		return ret;
	}
#else//MSB,高位在前
	unsigned char SimSPI_Proc(unsigned char c)
	{
		unsigned char i,ret;
		ret=0x00;
	#if defined(SimSPI_SPI0)
		for(i=0;i<8;i++)
		{
			SimSPI_SCL_W=0;	//下降沿接收数据
			ret=ret<<1;
			SimSPI_Delay();
			if(SimSPI_SDI_R==1)
				ret|=0x01;
			SimSPI_SDO_W=0;
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SimSPI_SDO_W=1;	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SimSPI_SCL_W=1;//上升沿发送					
		}
		SimSPI_SCL_W=0;	//空闲为低电平
	#elif defined(SimSPI_SPI1) 
		for(i=0;i<8;i++)
		{		
			SimSPI_SCL_W=1;	//上升沿接收数据
			ret=ret<<1;
			SimSPI_Delay();
			if(SimSPI_SDI_R==1)
				ret|=0x01;
			SimSPI_SDO_W=0;
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SimSPI_SDO_W=1;	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1
			SimSPI_Delay();
			SimSPI_SCL_W=0;//下降沿发送					
		}
	#elif defined(SimSPI_SPI2) 
		for(i=0;i<8;i++)
		{
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SimSPI_SDO_W=1;	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SimSPI_SCL_W=0;//下降沿发送
			SimSPI_Delay();
			SimSPI_SCL_W=1;	//上升沿接收数据
			ret=ret<<1;
			SimSPI_Delay();
			if(SimSPI_SDI_R==1)
				ret|=0x01;					
		}
	#elif defined(SimSPI_SPI3) 
		for(i=0;i<8;i++)
		{
			SimSPI_SCL_W=0;	//下降沿接收数据
			ret=ret<<1;
			SimSPI_Delay();
			if(SimSPI_SDI_R==1)
				ret|=0x01;
			SimSPI_SDO_W=0;
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SimSPI_SDO_W=1;	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SimSPI_SCL_W=1;//上升沿发送			
			SimSPI_Delay();
		}
	#endif
		return ret;
	}
#endif

#ifdef SimSPI2
	void SimSPI2_Init(void)
	{	
	#if defined(SimSPI2_SPI0) || defined(SimSPI2_SPI1) 
		SimSPI2_SCL_W=0;	//拉低时钟信号
	#elif defined(SimSPI2_SPI2) || defined(SimSPI2_SPI3) 
		SimSPI2_SCL_W=1;	//拉高时钟信号
	#endif
		SimSPI2_SCL_DIR=0;
		SimSPI2_SDI_DIR=1;
		SimSPI2_SDO_DIR=0;	
	}
	#ifdef SimSPI2_LSB//低位在前
		unsigned char SimSPI2_Proc(unsigned char c)
		{
			unsigned char i,ret;
			ret=0;
		#if defined(SimSPI2_SPI0)
			for(i=0;i<8;i++)
			{
				SimSPI2_SCL_W=0;	//下降沿接收数据
				ret=ret>>1;
				SimSPI2_Delay();
				if(SimSPI2_SDI_R==1)
					ret|=0x80;
				SimSPI2_SDO_W=0;
				if((c&0x01)==0x01)	//判断待发送的数据位是0或1
				{
					SimSPI2_SDO_W=1;	//待发送数据位是1
				}	
				c=c>>1;	//判断待发送的数据位是0或1	
				SimSPI2_Delay();
				SimSPI2_SCL_W=1;//上升沿发送					
			}
			SimSPI2_SCL_W=0;	//空闲为低电平
		#elif defined(SimSPI2_SPI1) 
			for(i=0;i<8;i++)
			{		
				SimSPI2_SCL_W=1;	//上升沿接收数据
				ret=ret>>1;
				SimSPI2_Delay();
				if(SimSPI2_SDI_R==1)
					ret|=0x80;
				SimSPI2_SDO_W=0;
				if((c&0x01)==0x01)	//判断待发送的数据位是0或1
				{
					SimSPI2_SDO_W=1;	//待发送数据位是1
				}	
				c=c>>1;	//判断待发送的数据位是0或1	
				SimSPI2_Delay();
				SimSPI2_SCL_W=0;//下降沿发送					
			}
		#elif defined(SimSPI2_SPI2) 
			for(i=0;i<8;i++)
			{
				if((c&0x01)==0x01)	//判断待发送的数据位是0或1
				{
					SimSPI2_SDO_W=1;	//待发送数据位是1
				}	
				c=c>>1;	//判断待发送的数据位是0或1	
				SimSPI2_Delay();
				SimSPI2_SCL_W=0;//下降沿发送	
				SimSPI2_Delay();
				SimSPI2_SCL_W=1;	//上升沿接收数据
				ret=ret>>1;
				SimSPI2_Delay();
				if(SimSPI2_SDI_R==1)
					ret|=0x80;					
			}
		#elif defined(SimSPI2_SPI3) 
			for(i=0;i<8;i++)
			{
				SimSPI2_SCL_W=0;	//下降沿接收数据
				ret=ret>>1;
				SimSPI2_Delay();
				if(SimSPI2_SDI_R==1)
					ret|=0x80;
				SimSPI2_SDO_W=0;
				if((c&0x01)==0x01)	//判断待发送的数据位是0或1
				{
					SimSPI2_SDO_W=1;	//待发送数据位是1
				}	
				c=c>>1;	//判断待发送的数据位是0或1	
				SimSPI2_Delay();
				SimSPI2_SCL_W=1;//上升沿发送	
				SimSPI2_Delay();
			}
		#endif
			return ret;
		}
	#else//MSB,高位在前
		unsigned char SimSPI2_Proc(unsigned char c)
		{
			unsigned char i,ret;
			ret=0x00;
		#if defined(SimSPI2_SPI0)
			for(i=0;i<8;i++)
			{
				SimSPI2_SCL_W=0;	//下降沿接收数据
				ret=ret<<1;
				SimSPI2_Delay();
				if(SimSPI2_SDI_R==1)
					ret|=0x01;
				SimSPI2_SDO_W=0;
				if((c&0x80)==0x80)	//判断待发送的数据位是0或1
				{
					SimSPI2_SDO_W=1;	//待发送数据位是1
				}	
				c=c<<1;	//判断待发送的数据位是0或1	
				SimSPI2_Delay();
				SimSPI2_SCL_W=1;//上升沿发送					
			}
			SimSPI2_SCL_W=0;	//空闲为低电平
		#elif defined(SimSPI2_SPI1) 
			for(i=0;i<8;i++)
			{		
				SimSPI2_SCL_W=1;	//上升沿接收数据
				ret=ret<<1;
				SimSPI2_Delay();
				if(SimSPI2_SDI_R==1)
					ret|=0x01;
				SimSPI2_SDO_W=0;
				if((c&0x80)==0x80)	//判断待发送的数据位是0或1
				{
					SimSPI2_SDO_W=1;	//待发送数据位是1
				}	
				c=c<<1;	//判断待发送的数据位是0或1
				SimSPI2_Delay();
				SimSPI2_SCL_W=0;//下降沿发送					
			}
		#elif defined(SimSPI2_SPI2) 
			for(i=0;i<8;i++)
			{
				if((c&0x80)==0x80)	//判断待发送的数据位是0或1
				{
					SimSPI2_SDO_W=1;	//待发送数据位是1
				}	
				c=c<<1;	//判断待发送的数据位是0或1	
				SimSPI2_Delay();
				SimSPI2_SCL_W=0;//下降沿发送
				SimSPI2_Delay();
				SimSPI2_SCL_W=1;	//上升沿接收数据
				ret=ret<<1;
				SimSPI2_Delay();
				if(SimSPI2_SDI_R==1)
					ret|=0x01;					
			}
		#elif defined(SimSPI2_SPI3) 
			for(i=0;i<8;i++)
			{
				SimSPI2_SCL_W=0;	//下降沿接收数据
				ret=ret<<1;
				SimSPI2_Delay();
				if(SimSPI2_SDI_R==1)
					ret|=0x01;
				SimSPI2_SDO_W=0;
				if((c&0x80)==0x80)	//判断待发送的数据位是0或1
				{
					SimSPI2_SDO_W=1;	//待发送数据位是1
				}	
				c=c<<1;	//判断待发送的数据位是0或1	
				SimSPI2_Delay();
				SimSPI2_SCL_W=1;//上升沿发送			
				SimSPI2_Delay();
			}
		#endif
			return ret;
		}
	#endif
#endif
