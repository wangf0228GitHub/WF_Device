#ifndef __SimSPI_h__
#define __SimSPI_h__

#ifndef SimSPI_Delay_Ex
#define SimSPI_Delay() NOP()
#endif

#if defined(SimSPI_SPI0) || defined(SimSPI_SPI1) || defined(SimSPI_SPI2) || defined(SimSPI_SPI3) 
#else
#define SimSPI_SPI0
#endif

void SimSPI_Init(void);
unsigned char SimSPI_Proc(unsigned char c);

#ifdef SimSPI2
	#ifndef SimSPI2_Delay_Ex
	#define SimSPI2_Delay() NOP()
	#endif

	#if defined(SimSPI2_SPI0) || defined(SimSPI2_SPI1) || defined(SimSPI2_SPI2) || defined(SimSPI2_SPI3) 
	#else
	#define SimSPI2_SPI0
	#endif

	void SimSPI2_Init(void);
	unsigned char SimSPI2_Proc(unsigned char c);
#endif


#endif // __SimSPI_h__
