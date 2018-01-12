#include "HardwareProfile.h"
#include "SPIROM.h"
_SPIROM_Status SPIROM_Status;
// #define SPIROM_CS_DIR _TRISB10
// #define SPIROM_W_DIR  _TRISB11
// #define SPIROM_D_DIR  SimSPI_SDO_DIR
// #define SPIROM_Q_DIR  SimSPI_SDI_DIR
// #define SPIROM_CLK_DIR  SimSPI_SCL_DIR
// 
// #define SPIROM_CS_W _LATB10
// #define SPIROM_W_W  _LATB11
// #define SPIROM_D_W  SimSPI_SDO_W
// #define SPIROM_Q_R  SimSPI_SDI_R
// #define SPIROM_CLK_W  SimSPI_SCL_W
void SPIROM_WriteEnable(void)
{
	SPIROM_CS_W=0;
	SPIROM_SPIProc(SPIROM_CMD_WREN);
	SPIROM_CS_W=1;
}
void SPIROM_WriteDisable(void)
{
	SPIROM_CS_W=0;
	SPIROM_SPIProc(SPIROM_CMD_WRDI);
	SPIROM_CS_W=1;
}
void SPIROM_Init(void)
{
	SPIROM_CS_W=1;
	SPIROM_CS_DIR=0;
	SPIROM_W_W=1;
	SPIROM_W_DIR=0;	
	SPIROM_SPIInit();
}
#ifdef SPIROM_Addr24
void SPIROM_WriteByte(unsigned long address,unsigned char data)
#else
void SPIROM_WriteByte(unsigned int address,unsigned char data)
#endif
{
#ifdef SPIROM_Addr24
	ulong Addr;
	Addr.u32=address;	
#else
	uint Addr;
	Addr.u16=address;
#endif	
	SPIROM_WriteEnable();
    SPIROM_CS_W=0;

    SPIROM_SPIProc(SPIROM_CMD_WRITE);
#ifdef SPIROM_Addr24
	SPIROM_SPIProc(Addr.u8s[2]);
#endif
    SPIROM_SPIProc(Addr.u8s[1]);

	SPIROM_SPIProc(Addr.u8s[0]);

    SPIROM_SPIProc(data); 
	
    SPIROM_CS_W=1;
#ifdef SPIROM_NeedWIP
	while(1)
	{
		SPIROM_ReadStatus();
		if(SPIROM_Status.WIP==0)
			break;
	}
#endif	
	SPIROM_WriteDisable();
}

#ifdef SPIROM_Addr24
unsigned char SPIROM_ReadByte(unsigned long address)
#else
unsigned char SPIROM_ReadByte(unsigned int address)
#endif
{
    unsigned char ret;
#ifdef SPIROM_Addr24
	ulong Addr;
	Addr.u32=address;
#else
	uint Addr;
	Addr.u16=address;
#endif
    SPIROM_CS_W=0;
    SPIROM_SPIProc(SPIROM_CMD_READ);

#ifdef SPIROM_Addr24
	SPIROM_SPIProc(Addr.u8s[2]);
#endif
	SPIROM_SPIProc(Addr.u8s[1]);

	SPIROM_SPIProc(Addr.u8s[0]);

	ret=SPIROM_SPIProc(0);

    SPIROM_CS_W=1;

    return (ret);
}



void SPIROM_ReadStatus(void)
{
    SPIROM_CS_W=0;
    SPIROM_SPIProc(SPIROM_CMD_RDSR);
    SPIROM_Status.All=SPIROM_SPIProc(0x55);
    SPIROM_CS_W=1;
}
#ifdef SPIROM_Addr24
void SPIROM_WriteArray(unsigned long address, unsigned char* pData,unsigned int nCount)
#else
void SPIROM_WriteArray(unsigned int address, unsigned char* pData,unsigned int nCount)
#endif
{
#ifdef SPIROM_Addr24
	//unsigned long counter;
	ulong Addr;
	Addr.u32=address;
#else
	uint Addr;
	Addr.u16=address;
#endif
    // WRITE
    SPIROM_WriteEnable();
    SPIROM_CS_W=0;

    SPIROM_SPIProc(SPIROM_CMD_WRITE);

#ifdef SPIROM_Addr24
	SPIROM_SPIProc(Addr.u8s[2]);
#endif
	SPIROM_SPIProc(Addr.u8s[1]);

	SPIROM_SPIProc(Addr.u8s[0]);

    while(nCount!=0)
    {
		nCount--;
		SPIROM_SPIProc(*pData++);
#ifdef SPIROM_PageRollover
#ifdef SPIROM_Addr24
		Addr.u32++;
		if((Addr.u32 & SPIROM_PageRollover) == 0)
#else
		Addr.u16++;
		if((Addr.u16 & SPIROM_PageRollover) == 0)
#endif
		{
			SPIROM_CS_W=1;

			// Wait for completion of the write operation
#ifdef SPIROM_NeedWIP
			while(1)
			{
				SPIROM_ReadStatus();
				if(SPIROM_Status.WIP==0)
					break;
			}
#endif
			// Start writing of the next page
			SPIROM_WriteEnable();
			SPIROM_CS_W=0;

			SPIROM_SPIProc(SPIROM_CMD_WRITE);

#ifdef SPIROM_Addr24
			SPIROM_SPIProc(Addr.u8s[2]);
#endif
			SPIROM_SPIProc(Addr.u8s[1]);

			SPIROM_SPIProc(Addr.u8s[0]);
		}
#endif        
    }
    SPIROM_CS_W=1;   
#ifdef SPIROM_NeedWIP
	while(1)
	{
		SPIROM_ReadStatus();
		if(SPIROM_Status.WIP==0)
			break;
	}
#endif   
	SPIROM_WriteDisable();
}
#ifdef SPIROM_Addr24
void SPIROM_Fill(unsigned long address, unsigned char Data,unsigned long nCount)
#else
void SPIROM_Fill(unsigned int address, unsigned char Data,unsigned int nCount)
#endif
{    
#ifdef SPIROM_Addr24
	ulong Addr;
	Addr.u32=address;
#else
	uint Addr;
	Addr.u16=address;
#endif 
	// WRITE
	SPIROM_WriteEnable();
	SPIROM_CS_W=0;

	SPIROM_SPIProc(SPIROM_CMD_WRITE);

#ifdef SPIROM_Addr24
	SPIROM_SPIProc(Addr.u8s[2]);
#endif
	SPIROM_SPIProc(Addr.u8s[1]);

	SPIROM_SPIProc(Addr.u8s[0]);

	while(nCount!=0)
	{
		nCount--;
		SPIROM_SPIProc(Data);
#ifdef SPIROM_PageRollover
#ifdef SPIROM_Addr24
		Addr.u32++;
		if((Addr.u32 & SPIROM_PageRollover) == 0)
#else
		Addr.u16++;
		if((Addr.u16 & SPIROM_PageRollover) == 0)
#endif	
		{
			SPIROM_CS_W=1;;

			// Wait for completion of the write operation
#ifdef SPIROM_NeedWIP
			while(1)
			{
				SPIROM_ReadStatus();
				if(SPIROM_Status.WIP==0)
					break;
			}
#endif
			// Start writing of the next page
			SPIROM_WriteEnable();
			SPIROM_CS_W=0;

			SPIROM_SPIProc(SPIROM_CMD_WRITE);

#ifdef SPIROM_Addr24
			SPIROM_SPIProc(Addr.u8s[2]);
#endif
			SPIROM_SPIProc(Addr.u8s[1]);

			SPIROM_SPIProc(Addr.u8s[0]);
		}
#endif        
	}
	SPIROM_CS_W=1;   
#ifdef SPIROM_NeedWIP
	// Wait for write end
	while(1)
	{
		SPIROM_ReadStatus();
		if(SPIROM_Status.WIP==0)
			break;
	}
#endif   
	SPIROM_WriteDisable();
}
#ifdef SPIROM_Addr24
void SPIROM_ReadArray(unsigned long address, unsigned char* pData,unsigned int nCount)
#else
void SPIROM_ReadArray(unsigned int address, unsigned char* pData,unsigned int nCount)
#endif
{
#ifdef SPIROM_Addr24
	ulong Addr;
	Addr.u32=address;
#else
	uint Addr;
	Addr.u16=address;
#endif
    SPIROM_CS_W=0;

    SPIROM_SPIProc(SPIROM_CMD_READ);

#ifdef SPIROM_Addr24
	SPIROM_SPIProc(Addr.u8s[2]);
#endif
	SPIROM_SPIProc(Addr.u8s[1]);

	SPIROM_SPIProc(Addr.u8s[0]);
	//nCount=nCount*size;
    while(nCount!=0)
    {
		nCount--;
		*pData=SPIROM_SPIProc(0);
        pData++;
#ifdef SPIROM_PageRollover
#ifdef SPIROM_Addr24
		Addr.u32++;
		if((Addr.u32 & SPIROM_PageRollover) == 0)
#else
		Addr.u16++;
		if((Addr.u16 & SPIROM_PageRollover) == 0)
#endif		
		{
			SPIROM_CS_W=1;;

			// Wait for completion of the write operation
			SPIROM_CS_W=0;

			SPIROM_SPIProc(SPIROM_CMD_READ);

#ifdef SPIROM_Addr24
			SPIROM_SPIProc(Addr.u8s[2]);
#endif
			SPIROM_SPIProc(Addr.u8s[1]);

			SPIROM_SPIProc(Addr.u8s[0]);
		}
#endif
    }
    SPIROM_CS_W=1;;
}


