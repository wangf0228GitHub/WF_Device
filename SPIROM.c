#include "SPIROM.h"
#include "TypeDefine.h"
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
	SPIROM_CS_Low();
	SPIROM_SPIProc(SPIROM_CMD_WREN);
	SPIROM_CS_High();
}
void SPIROM_WriteDisable(void)
{
	SPIROM_CS_Low();
	SPIROM_SPIProc(SPIROM_CMD_WRDI);
	SPIROM_CS_High();
}
void SPIROM_Init(void)
{
	SPIROM_CS_High();
}
#ifdef SPIROM_Addr24
void SPIROM_WriteByte(uint32_t address,uint8_t data)
#else
void SPIROM_WriteByte(uint16_t address,uint8_t data)
#endif
{
#ifdef SPIROM_Addr24
	u32_wf Addr;
	Addr.u32=address;	
#else
	u16_wf Addr;
	Addr.u16=address;
#endif	
	SPIROM_WriteEnable();
    SPIROM_CS_Low();

    SPIROM_SPIProc(SPIROM_CMD_WRITE);
#ifdef SPIROM_Addr24
	SPIROM_SPIProc(Addr.u8s[2]);
#endif
    SPIROM_SPIProc(Addr.u8s[1]);

	SPIROM_SPIProc(Addr.u8s[0]);

    SPIROM_SPIProc(data); 
	
    SPIROM_CS_High();
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
uint8_t SPIROM_ReadByte(uint32_t address)
#else
uint8_t SPIROM_ReadByte(uint16_t address)
#endif
{
    uint8_t ret;
#ifdef SPIROM_Addr24
	u32_wf Addr;
	Addr.u32=address;
#else
	u16_wf Addr;
	Addr.u16=address;
#endif
    SPIROM_CS_Low();
    SPIROM_SPIProc(SPIROM_CMD_READ);

#ifdef SPIROM_Addr24
	SPIROM_SPIProc(Addr.u8s[2]);
#endif
	SPIROM_SPIProc(Addr.u8s[1]);

	SPIROM_SPIProc(Addr.u8s[0]);

	ret=SPIROM_SPIProc(0);

    SPIROM_CS_High();

    return (ret);
}



void SPIROM_ReadStatus(void)
{
    SPIROM_CS_Low();
    SPIROM_SPIProc(SPIROM_CMD_RDSR);
    SPIROM_Status.All=SPIROM_SPIProc(0x55);
    SPIROM_CS_High();
}
#ifdef SPIROM_Addr24
void SPIROM_WriteArray(uint32_t address, uint8_t* pData,uint16_t nCount)
#else
void SPIROM_WriteArray(uint16_t address, uint8_t* pData,uint16_t nCount)
#endif
{
#ifdef SPIROM_Addr24
	//uint32_t counter;
	u32_wf Addr;
	Addr.u32=address;
#else
	u16_wf Addr;
	Addr.u16=address;
#endif
    // WRITE
    SPIROM_WriteEnable();
    SPIROM_CS_Low();

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
			SPIROM_CS_High();

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
			SPIROM_CS_Low();

			SPIROM_SPIProc(SPIROM_CMD_WRITE);

#ifdef SPIROM_Addr24
			SPIROM_SPIProc(Addr.u8s[2]);
#endif
			SPIROM_SPIProc(Addr.u8s[1]);

			SPIROM_SPIProc(Addr.u8s[0]);
		}
#endif        
    }
    SPIROM_CS_High();   
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
void SPIROM_Fill(uint32_t address, uint8_t Data,uint32_t nCount)
#else
void SPIROM_Fill(uint16_t address, uint8_t Data,uint16_t nCount)
#endif
{    
#ifdef SPIROM_Addr24
	u32_wf Addr;
	Addr.u32=address;
#else
	u16_wf Addr;
	Addr.u16=address;
#endif 
	// WRITE
	SPIROM_WriteEnable();
	SPIROM_CS_Low();

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
			SPIROM_CS_High();;

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
			SPIROM_CS_Low();

			SPIROM_SPIProc(SPIROM_CMD_WRITE);

#ifdef SPIROM_Addr24
			SPIROM_SPIProc(Addr.u8s[2]);
#endif
			SPIROM_SPIProc(Addr.u8s[1]);

			SPIROM_SPIProc(Addr.u8s[0]);
		}
#endif        
	}
	SPIROM_CS_High();   
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
void SPIROM_ReadArray(uint32_t address, uint8_t* pData,uint16_t nCount)
#else
void SPIROM_ReadArray(uint16_t address, uint8_t* pData,uint16_t nCount)
#endif
{
#ifdef SPIROM_Addr24
	u32_wf Addr;
	Addr.u32=address;
#else
	u16_wf Addr;
	Addr.u16=address;
#endif
    SPIROM_CS_Low();

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
			SPIROM_CS_High();;

			// Wait for completion of the write operation
			SPIROM_CS_Low();

			SPIROM_SPIProc(SPIROM_CMD_READ);

#ifdef SPIROM_Addr24
			SPIROM_SPIProc(Addr.u8s[2]);
#endif
			SPIROM_SPIProc(Addr.u8s[1]);

			SPIROM_SPIProc(Addr.u8s[0]);
		}
#endif
    }
    SPIROM_CS_High();;
}


