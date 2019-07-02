#include "SimSPI.h"
// #define SimSPI_SCL_DIR	TRISA1
// #define SimSPI_SDI_DIR	TRISA2
// #define SimSPI_SDO_DIR	TRISA0
// 
// #define SimSPI_SCL_W	RA1
// #define SIMSPI_SDI_Read()	RA2	
// #define SimSPI_SDO_W	RA0

//Mode 0	CPOL=0, CPHA=0
//Mode 1	CPOL=0, CPHA=1
//Mode 2	CPOL=1, CPHA=0
//Mode 3	CPOL=1, CPHA=1

void SimSPI_Init(void)
{	
#if defined(SimSPI_SPI0) || defined(SimSPI_SPI1) 
	SIMSPI_SCL_Low();	//拉低时钟信号
#elif defined(SimSPI_SPI2) || defined(SimSPI_SPI3) 
	SIMSPI_SCL_High();	//拉高时钟信号
#endif
}
#ifdef SimSPI_LSB//低位在前
	uint8_t SimSPI_Proc(uint8_t c)
	{
		uint8_t i,ret;
		ret=0;
	#if defined(SimSPI_SPI0)
		for(i=0;i<8;i++)
		{
			SIMSPI_SCL_Low();	//下降沿接收数据
			ret=ret>>1;
			SimSPI_Delay();
			if(SIMSPI_SDI_Read()==1)
				ret|=0x80;
			SIMSPI_SDO_Low();
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SIMSPI_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SIMSPI_SCL_High();//上升沿发送					
		}
		SIMSPI_SCL_Low();	//空闲为低电平
	#elif defined(SimSPI_SPI1) 
		for(i=0;i<8;i++)
		{		
			SIMSPI_SCL_High();	//上升沿接收数据
			ret=ret>>1;
			SimSPI_Delay();
			if(SIMSPI_SDI_Read()==1)
				ret|=0x80;
			SIMSPI_SDO_Low();
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SIMSPI_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SIMSPI_SCL_Low();//下降沿发送					
		}
	#elif defined(SimSPI_SPI2) 
		for(i=0;i<8;i++)
		{
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SIMSPI_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SIMSPI_SCL_Low();//下降沿发送	
			SimSPI_Delay();
			SIMSPI_SCL_High();	//上升沿接收数据
			ret=ret>>1;
			SimSPI_Delay();
			if(SIMSPI_SDI_Read()==1)
				ret|=0x80;					
		}
	#elif defined(SimSPI_SPI3) 
		for(i=0;i<8;i++)
		{
			SIMSPI_SCL_Low();	//下降沿接收数据
			ret=ret>>1;
			SimSPI_Delay();
			if(SIMSPI_SDI_Read()==1)
				ret|=0x80;
			SIMSPI_SDO_Low();
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SIMSPI_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI_Delay();
			SIMSPI_SCL_High();//上升沿发送	
			SimSPI_Delay();
		}
	#endif
		return ret;
	}
#else//MSB,高位在前
	uint8_t SimSPI_Proc(uint8_t c)
	{
		uint8_t i,ret;
		ret=0x00;
	#if defined(SimSPI_SPI0)
		for(i=0;i<8;i++)
		{
			SimSPI_Delay();
			SIMSPI_SCL_Low();	//下降沿接收数据
			ret=ret<<1;
			SimSPI_Delay();
			if(SIMSPI_SDI_Read()==1)
				ret|=0x01;
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SIMSPI_SDO_High();	//待发送数据位是1
			}
			else
			{
				SIMSPI_SDO_Low();	//待发送数据位是0
			}
			c=c<<1;	//判断待发送的数据位是0或1			
			SIMSPI_SCL_High();//上升沿发送
		}
		SimSPI_Delay();
		SIMSPI_SCL_Low();	//空闲为低电平
	#elif defined(SimSPI_SPI1) 
		for(i=0;i<8;i++)
		{	
			SimSPI_Delay();	
			SIMSPI_SCL_High();	//上升沿接收数据
			ret=ret<<1;
			SimSPI_Delay();
			if(SIMSPI_SDI_Read()==1)
				ret|=0x01;
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SIMSPI_SDO_High();	//待发送数据位是1
			}
			else
			{
				SIMSPI_SDO_Low();	//待发送数据位是0
			}
			c=c<<1;	//判断待发送的数据位是0或1			
			SIMSPI_SCL_Low();//下降沿发送					
		}
	#elif defined(SimSPI_SPI2) 
		for(i=0;i<8;i++)
		{
			SimSPI_Delay();
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SIMSPI_SDO_High();	//待发送数据位是1
			}	
			else
			{
				SIMSPI_SDO_Low();	//待发送数据位是0
			}
			c=c<<1;	//判断待发送的数据位是0或1				
			SIMSPI_SCL_Low();//下降沿发送
			SimSPI_Delay();
			SIMSPI_SCL_High();	//上升沿接收数据
			ret=ret<<1;
			SimSPI_Delay();
			if(SIMSPI_SDI_Read()==1)
				ret|=0x01;					
		}
	#elif defined(SimSPI_SPI3) 
		for(i=0;i<8;i++)
		{
			SimSPI_Delay();
			SIMSPI_SCL_Low();	//下降沿接收数据
			ret=ret<<1;
			SimSPI_Delay();
			if(SIMSPI_SDI_Read()==1)
				ret|=0x01;			
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SIMSPI_SDO_High();	//待发送数据位是1
			}	
			else
			{
				SIMSPI_SDO_Low();
			}
			c=c<<1;	//判断待发送的数据位是0或1			
			SIMSPI_SCL_High();//上升沿发送			
		}
	#endif
		SimSPI_Delay();
		return ret;
	}
#endif

#ifdef SimSPI2
	void SimSPI2_Init(void)
	{	
	#if defined(SimSPI2_SPI0) || defined(SimSPI2_SPI1) 
		SIMSPI2_SCL_Low();	//拉低时钟信号
	#elif defined(SimSPI2_SPI2) || defined(SimSPI2_SPI3) 
		SIMSPI2_SCL_High();	//拉高时钟信号
	#endif
// 		SimSPI2_SCL_DIR=0;
// 		SimSPI2_SDI_DIR=1;
// 		SimSPI2_SDO_DIR=0;	
	}
#ifdef SimSPI2_LSB//低位在前
	uint8_t SimSPI2_Proc(uint8_t c)
	{
		uint8_t i,ret;
		ret=0;
	#if defined(SimSPI2_SPI0)
		for(i=0;i<8;i++)
		{
			SIMSPI2_SCL_Low();	//下降沿接收数据
			ret=ret>>1;
			SimSPI2_Delay();
			if(SIMSPI2_SDI_Read()==1)
				ret|=0x80;
			SIMSPI2_SDO_Low();
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SIMSPI2_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI2_Delay();
			SIMSPI2_SCL_High();//上升沿发送					
		}
		SIMSPI2_SCL_Low();	//空闲为低电平
	#elif defined(SimSPI2_SPI1) 
		for(i=0;i<8;i++)
		{		
			SIMSPI2_SCL_High();	//上升沿接收数据
			ret=ret>>1;
			SimSPI2_Delay();
			if(SIMSPI2_SDI_Read()==1)
				ret|=0x80;
			SIMSPI2_SDO_Low();
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SIMSPI2_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI2_Delay();
			SIMSPI2_SCL_Low();//下降沿发送					
		}
	#elif defined(SimSPI2_SPI2) 
		for(i=0;i<8;i++)
		{
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SIMSPI2_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI2_Delay();
			SIMSPI2_SCL_Low();//下降沿发送	
			SimSPI2_Delay();
			SIMSPI2_SCL_High();	//上升沿接收数据
			ret=ret>>1;
			SimSPI2_Delay();
			if(SIMSPI2_SDI_Read()==1)
				ret|=0x80;					
		}
	#elif defined(SimSPI2_SPI3) 
		for(i=0;i<8;i++)
		{
			SIMSPI2_SCL_Low();	//下降沿接收数据
			ret=ret>>1;
			SimSPI2_Delay();
			if(SIMSPI2_SDI_Read()==1)
				ret|=0x80;
			SIMSPI2_SDO_Low();
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SIMSPI2_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI2_Delay();
			SIMSPI2_SCL_High();//上升沿发送	
			SimSPI2_Delay();
		}
	#endif
		return ret;
	}
#else//MSB,高位在前
	uint8_t SimSPI2_Proc(uint8_t c)
	{
		uint8_t i,ret;
		ret=0x00;
	#if defined(SimSPI2_SPI0)
		for(i=0;i<8;i++)
		{
			SIMSPI2_SCL_Low();	//下降沿接收数据
			ret=ret<<1;
			SimSPI2_Delay();
			if(SIMSPI2_SDI_Read()==1)
				ret|=0x01;
			SIMSPI2_SDO_Low();
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SIMSPI2_SDO_High();	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1	
			SimSPI2_Delay();
			SIMSPI2_SCL_High();//上升沿发送					
		}
		SIMSPI2_SCL_Low();	//空闲为低电平
	#elif defined(SimSPI2_SPI1) 
		for(i=0;i<8;i++)
		{		
			SIMSPI2_SCL_High();	//上升沿接收数据
			ret=ret<<1;
			SimSPI2_Delay();
			if(SIMSPI2_SDI_Read()==1)
				ret|=0x01;
			SIMSPI2_SDO_Low();
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SIMSPI2_SDO_High();	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1
			SimSPI2_Delay();
			SIMSPI2_SCL_Low();//下降沿发送					
		}
	#elif defined(SimSPI2_SPI2) 
		for(i=0;i<8;i++)
		{
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SIMSPI2_SDO_High();	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1	
			SimSPI2_Delay();
			SIMSPI2_SCL_Low();//下降沿发送
			SimSPI2_Delay();
			SIMSPI2_SCL_High();	//上升沿接收数据
			ret=ret<<1;
			SimSPI2_Delay();
			if(SIMSPI2_SDI_Read()==1)
				ret|=0x01;					
		}
	#elif defined(SimSPI2_SPI3) 
		for(i=0;i<8;i++)
		{
			SIMSPI2_SCL_Low();	//下降沿接收数据
			ret=ret<<1;
			SimSPI2_Delay();
			if(SIMSPI2_SDI_Read()==1)
				ret|=0x01;
			SIMSPI2_SDO_Low();
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SIMSPI2_SDO_High();	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1	
			SimSPI2_Delay();
			SIMSPI2_SCL_High();//上升沿发送			
			SimSPI2_Delay();
		}
	#endif
		return ret;
	}
#endif
#endif

#ifdef SimSPI3
	void SimSPI3_Init(void)
	{	
	#if defined(SimSPI3_SPI0) || defined(SimSPI3_SPI1) 
		SimSPI3_SCL_Low();	//拉低时钟信号
	#elif defined(SimSPI3_SPI2) || defined(SimSPI3_SPI3) 
		SimSPI3_SCL_High();	//拉高时钟信号
	#endif
		// 		SimSPI3_SCL_DIR=0;
		// 		SimSPI3_SDI_DIR=1;
		// 		SimSPI3_SDO_DIR=0;	
	}
#ifdef SimSPI3_LSB//低位在前
	uint8_t SimSPI3_Proc(uint8_t c)
	{
		uint8_t i,ret;
		ret=0;
	#if defined(SimSPI3_SPI0)
		for(i=0;i<8;i++)
		{
			SimSPI3_SCL_Low();	//下降沿接收数据
			ret=ret>>1;
			SimSPI3_Delay();
			if(SimSPI3_SDI_Read()==1)
				ret|=0x80;
			SimSPI3_SDO_Low();
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SimSPI3_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI3_Delay();
			SimSPI3_SCL_High();//上升沿发送					
		}
		SimSPI3_SCL_Low();	//空闲为低电平
	#elif defined(SimSPI3_SPI1) 
		for(i=0;i<8;i++)
		{		
			SimSPI3_SCL_High();	//上升沿接收数据
			ret=ret>>1;
			SimSPI3_Delay();
			if(SimSPI3_SDI_Read()==1)
				ret|=0x80;
			SimSPI3_SDO_Low();
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SimSPI3_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI3_Delay();
			SimSPI3_SCL_Low();//下降沿发送					
		}
	#elif defined(SimSPI3_SPI2) 
		for(i=0;i<8;i++)
		{
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SimSPI3_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI3_Delay();
			SimSPI3_SCL_Low();//下降沿发送	
			SimSPI3_Delay();
			SimSPI3_SCL_High();	//上升沿接收数据
			ret=ret>>1;
			SimSPI3_Delay();
			if(SimSPI3_SDI_Read()==1)
				ret|=0x80;					
		}
	#elif defined(SimSPI3_SPI3) 
		for(i=0;i<8;i++)
		{
			SimSPI3_SCL_Low();	//下降沿接收数据
			ret=ret>>1;
			SimSPI3_Delay();
			if(SimSPI3_SDI_Read()==1)
				ret|=0x80;
			SimSPI3_SDO_Low();
			if((c&0x01)==0x01)	//判断待发送的数据位是0或1
			{
				SimSPI3_SDO_High();	//待发送数据位是1
			}	
			c=c>>1;	//判断待发送的数据位是0或1	
			SimSPI3_Delay();
			SimSPI3_SCL_High();//上升沿发送	
			SimSPI3_Delay();
		}
	#endif
		return ret;
	}
#else//MSB,高位在前
	uint8_t SimSPI3_Proc(uint8_t c)
	{
		uint8_t i,ret;
		ret=0x00;
	#if defined(SimSPI3_SPI0)
		for(i=0;i<8;i++)
		{
			SimSPI3_SCL_Low();	//下降沿接收数据
			ret=ret<<1;
			SimSPI3_Delay();
			if(SimSPI3_SDI_Read()==1)
				ret|=0x01;
			SimSPI3_SDO_Low();
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SimSPI3_SDO_High();	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1	
			SimSPI3_Delay();
			SimSPI3_SCL_High();//上升沿发送					
		}
		SimSPI3_SCL_Low();	//空闲为低电平
	#elif defined(SimSPI3_SPI1) 
		for(i=0;i<8;i++)
		{		
			SimSPI3_SCL_High();	//上升沿接收数据
			ret=ret<<1;
			SimSPI3_Delay();
			if(SimSPI3_SDI_Read()==1)
				ret|=0x01;
			SimSPI3_SDO_Low();
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SimSPI3_SDO_High();	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1
			SimSPI3_Delay();
			SimSPI3_SCL_Low();//下降沿发送					
		}
	#elif defined(SimSPI3_SPI2) 
		for(i=0;i<8;i++)
		{
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SimSPI3_SDO_High();	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1	
			SimSPI3_Delay();
			SimSPI3_SCL_Low();//下降沿发送
			SimSPI3_Delay();
			SimSPI3_SCL_High();	//上升沿接收数据
			ret=ret<<1;
			SimSPI3_Delay();
			if(SimSPI3_SDI_Read()==1)
				ret|=0x01;					
		}
	#elif defined(SimSPI3_SPI3) 
		for(i=0;i<8;i++)
		{
			SimSPI3_SCL_Low();	//下降沿接收数据
			ret=ret<<1;
			SimSPI3_Delay();
			if(SimSPI3_SDI_Read()==1)
				ret|=0x01;
			SimSPI3_SDO_Low();
			if((c&0x80)==0x80)	//判断待发送的数据位是0或1
			{
				SimSPI3_SDO_High();	//待发送数据位是1
			}	
			c=c<<1;	//判断待发送的数据位是0或1	
			SimSPI3_Delay();
			SimSPI3_SCL_High();//上升沿发送			
			SimSPI3_Delay();
		}
	#endif
		return ret;
	}
#endif
#endif
