#include "DS18x20.h"
#include "OneWire.h"
#include "Verify.h"

const uint8_t DS18X20_ToDecicel[16]={
	0,
	1,
	1,
	2,
	3,
	3,
	4,
	4,
	5,
	6,
	6,
	7,
	8,
	8,
	9,
	9
};
uint8_t DS18X20_Scratchpad[9];
//uint8_t DS18X20_Scratchpad[9];
//#define DS18X20_Init() OneWire_Init()
#ifdef OneWire_MAXSENSORS
uint8_t DS18X20_SearchSensors(uint8_t* id)
{
	uint8_t i;
	uint8_t diff;
	uint8_t xx[8];
	uint8_t Count = 0;
	for(diff = ONEWIRE_SEARCH_FIRST;diff != ONEWIRE_LAST_DEVICE && Count < OneWire_MAXSENSORS ; )
	{
		DS18X20_FindSensor(&diff,xx);
		if( diff == ONEWIRE_PRESENCE_ERR ) 
			break;
		if( diff == ONEWIRE_DATA_ERR ) 		
			break;
		for(i=0;i<8;i++)
			id[i]=xx[i];
		id += DS18X20_SensorIDLength;		
		Count++;
	}
	return Count;
}
void DS18X20_FindSensor(uint8_t* diff, uint8_t* id)
{
	while(1) 
	{ 
		*diff = OneWire_RomSearch(*diff, id);
		if ( *diff==ONEWIRE_PRESENCE_ERR || *diff==ONEWIRE_DATA_ERR ||*diff == ONEWIRE_LAST_DEVICE ) return;
		if ( id[0] == DS18B20_ID || id[0] == DS18S20_ID ) return;
	}
}
/* start measurement (CONVERT_T) for all sensors if input id==NULL 
   or for single sensor. then id is the rom-code */
uint8_t DS18X20_StartMeas(uint8_t* id)
{ 
	if(OneWire_Reset()) //**
		return DS18X20_ERROR;
	return OneWire_Command( DS18X20_CONVERT_T, id );
}

/* reads temperature (scratchpad) of sensor with rom-code id
   output: subzero==1 if temp.<0, cel: full celsius, mcel: frac 
   in millicelsius*0.1
   i.e.: subzero=1, cel=18, millicel=5000 = -18,5000癈 */
uint8_t DS18X20_ReadMeas(uint8_t* id,uint8_t bVerify)
{ 
	uint8_t i;
	if(OneWire_Reset()) //**
		return DS18X20_ERROR;
	if(OneWire_Command(DS18X20_READ, id))
		return DS18X20_ERROR;
	if(bVerify!=0x00)
	{
		for ( i=0 ; i< DS18X20_SP_SIZE; i++ ) 
			DS18X20_Scratchpad[i]=OneWire_ReadByte();
		if ( GetVerify_CRC8( DS18X20_Scratchpad, DS18X20_SP_SIZE-1 )!=DS18X20_Scratchpad[DS18X20_SP_SIZE-1] ) 
			return DS18X20_ERROR_CRC;	
		return DS18X20_OK;
	}
	else
	{
		DS18X20_Scratchpad[0]=OneWire_ReadByte();
		DS18X20_Scratchpad[1]=OneWire_ReadByte();
		return DS18X20_OK;
	}
	
}

#ifdef DS18X20_EEPROMSUPPORT

uint8_t DS18X20_WriteScratchpad(uint8_t* id,uint8_t th, uint8_t tl, uint8_t conf)
{ 
	if(OneWire_Reset()) //**
		return DS18X20_ERROR;	
	if(OneWire_Command(DS18X20_WRITE_SCRATCHPAD,id))
		return DS18X20_ERROR;	
	OneWire_WriteByte(th);
	OneWire_WriteByte(tl);
	if (id[0] == DS18B20_ID) 
		OneWire_WriteByte(conf); // config avail. on B20 only
	return DS18X20_OK;	
}

uint8_t DS18X20_ReadScratchpad(uint8_t* id,uint8_t bVerify)
{ 
	uint8_t i;
	if(bVerify!=0x00)
		return DS18X20_ReadMeas(id,bVerify);
	else
	{
		OneWire_Command(DS18X20_READ, id);
		for(i=0;i<5;i++)
			DS18X20_Scratchpad[i]=OneWire_ReadByte();
		return DS18X20_OK;
	}
}

uint8_t DS18X20_CopyScratchpad(uint8_t* id)
{ 
	if(OneWire_Reset()) //**3
		return DS18X20_ERROR;	
	if(OneWire_Command( DS18X20_COPY_SCRATCHPAD, id ))
		return DS18X20_ERROR;	
	while(OneWire_ReadBit()==0);
	return DS18X20_OK;	
}

uint8_t DS18X20_RecallE2(uint8_t* id)
{ 
	if(OneWire_Reset()) //**
		return DS18X20_ERROR;	
	if(OneWire_Command( DS18X20_RECALL_E2, id ))
		return DS18X20_ERROR;	
	while(OneWire_ReadBit()==0);
	return DS18X20_OK;	
	// TODO: wait until status is "1" (then eeprom values
	// have been copied). here simple delay to avoid timeout 
	// handling
	//Delay1(200);
	//delay_ms(DS18X20_COPYSP_DELAY);
}
#endif
#else//只有一个18b20
/* start measurement (CONVERT_T) for all sensors if input id==NULL 
   or for single sensor. then id is the rom-code */
uint8_t DS18X20_StartMeas()
{ 
	if(OneWire_Reset()) //**
		return DS18X20_ERROR;
	return OneWire_Command( DS18X20_CONVERT_T);
}

/* reads temperature (scratchpad) of sensor with rom-code id
   output: subzero==1 if temp.<0, cel: full celsius, mcel: frac 
   in millicelsius*0.1
   i.e.: subzero=1, cel=18, millicel=5000 = -18,5000癈 */
uint8_t DS18X20_ReadMeas(uint8_t bVerify)
{ 
	uint8_t i;
	if(OneWire_Reset()) //**
		return DS18X20_ERROR;
	if(OneWire_Command(DS18X20_READ))
		return DS18X20_ERROR;
	if(bVerify)
	{
		for ( i=0 ; i< DS18X20_SP_SIZE; i++ ) 
			DS18X20_Scratchpad[i]=OneWire_ReadByte();
		if ( GetVerify_CRC8( DS18X20_Scratchpad, DS18X20_SP_SIZE-1 )!=DS18X20_Scratchpad[DS18X20_SP_SIZE-1] ) 
			return DS18X20_ERROR_CRC;	
		return DS18X20_OK;
	}
	else
	{
		DS18X20_Scratchpad[0]=OneWire_ReadByte();
		DS18X20_Scratchpad[1]=OneWire_ReadByte();
		return DS18X20_OK;
	}
	
}

#ifdef DS18X20_EEPROMSUPPORT

#ifdef DS18B20
	uint8_t DS18X20_WriteScratchpad(uint8_t th, uint8_t tl, uint8_t conf)
	{ 
		if(OneWire_Reset()) //**
			return DS18X20_ERROR;	
		if(OneWire_Command(DS18X20_WRITE_SCRATCHPAD))
			return DS18X20_ERROR;	
		OneWire_WriteByte(th);
		OneWire_WriteByte(tl);
		OneWire_WriteByte(conf); // config avail. on B20 only
		return DS18X20_OK;	
	}
#else
	uint8_t DS18X20_WriteScratchpad(uint8_t th, uint8_t tl)
	{ 
		if(OneWire_Reset()) //**
			return DS18X20_ERROR;	
		if(OneWire_Command(DS18X20_WRITE_SCRATCHPAD))
			return DS18X20_ERROR;	
		OneWire_WriteByte(th);
		OneWire_WriteByte(tl);
		return DS18X20_OK;	
	}
#endif 


uint8_t DS18X20_ReadScratchpad(uint8_t bVerify)
{ 
	uint8_t i;
	if(bVerify)
		return DS18X20_ReadMeas(bVerify);
	else
	{
		OneWire_Command(DS18X20_READ);
		for(i=0;i<5;i++)
			DS18X20_Scratchpad[i]=OneWire_ReadByte();
		return DS18X20_OK;
	}
}

uint8_t DS18X20_CopyScratchpad()
{ 
	if(OneWire_Reset()) //**3
		return DS18X20_ERROR;	
	if(OneWire_Command( DS18X20_COPY_SCRATCHPAD))
		return DS18X20_ERROR;	
	while(OneWire_ReadBit()==0);
	return DS18X20_OK;	
}

uint8_t DS18X20_RecallE2()
{ 
	if(OneWire_Reset()) //**
		return DS18X20_ERROR;	
	if(OneWire_Command( DS18X20_RECALL_E2))
		return DS18X20_ERROR;	
	while(OneWire_ReadBit()==0);
	return DS18X20_OK;	
	// TODO: wait until status is "1" (then eeprom values
	// have been copied). here simple delay to avoid timeout 
	// handling
	//Delay1(200);
	//delay_ms(DS18X20_COPYSP_DELAY);
}	
#endif
#endif
