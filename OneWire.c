#include "OneWire.h"



uint8_t OneWire_Reset(void)
{
	unsigned char r,Retry;
	r=1;
	Retry=TIMESFORRETRY_OneWire;
	while(Retry--)
	{
		ONEWIRE_SETLOW(); 
		OneWire_Delay_us(480);
		ONEWIRE_SETHIGH();//等电阻拉高总线并保持15－60us
		//di();
		OneWire_Delay_us(75);
		r=ONEWIRE_GETIN();//接受应答信号
		//ei();		
		OneWire_Delay_us(480);//延时60－240us
		if(ONEWIRE_GETIN()==0)
			r=1;
		if(r==0)
			break;
	}	
	return r;	
}
#ifdef OneWire_MAXSENSORS
uint8_t OneWire_RomSearch( uint8_t diff, uint8_t *id )
{ 
	uint8_t i, j, next_diff;
	uint8_t b,b1;

	if(OneWire_Reset())
		return ONEWIRE_PRESENCE_ERR;
	OneWire_WriteByte(ONEWIRE_SEARCH_ROM);     // ROM search command
	next_diff = ONEWIRE_LAST_DEVICE;      // unchanged on last device
	i = 64;         // 8 bytes
	do 
	{
		j = 8;                        // 8 bits
		do 
		{
			di();
			ONEWIRE_SETLOW();
			OneWire_Delay_us(2);
			//	ONEWIRE_SETLOW();
			ONEWIRE_SETHIGH();
			OneWire_Delay_us(15-3-OneWire_ReadDelayOffSet);
			b=ONEWIRE_GETIN();
			ei();
			OneWire_Delay_us(60);
			di();
			ONEWIRE_SETLOW();
			OneWire_Delay_us(2);
			//	ONEWIRE_SETLOW();
			ONEWIRE_SETHIGH();
			OneWire_Delay_us(15-3-OneWire_ReadDelayOffSet);
			b1=ONEWIRE_GETIN();
			ei();
			OneWire_Delay_us(60);
			//b = OneWire_ReadBit();			// read bit
			//if(OneWire_ReadBit()) 
			if(b1!=0x00)
			{ 
				//read complement bit
				if( b!=0x00 )                 // 11
				return ONEWIRE_DATA_ERR;  // data error
			}
			else 
			{
				if( b==0x00 ) 
				{ 
					// 00 = 2 devices
					if( diff > i || ((*id & 1) && diff != i) ) 
					{
						b = 1;// now 1
						next_diff = i;// next pass 0
					}
				}
			}
			di();
			ONEWIRE_SETLOW();
			OneWire_Delay_us(2);
			if (b!=0x00)  
			{
				ONEWIRE_SETHIGH();
			}
			OneWire_Delay_us(75);
			ONEWIRE_SETHIGH();
			ei();
			//OneWire_WriteBit(b);// write bit
			*id >>= 1;
			if( b!=0x00 ) 
				*id |= 0x80;// store bit
			i--;
		} 
		while( --j );
		id++;// next byte
	}while(i);
	return next_diff;// to continue search
}


uint8_t OneWire_Command( uint8_t command, uint8_t *id )
{
	uint8_t i;
	if(OneWire_Reset())
		return 0x01;	
	if(id) 
	{ 
		OneWire_WriteByte( ONEWIRE_MATCH_ROM );			// to a single device
		i = 8;
		do 
		{ 
			OneWire_WriteByte( *id );
			id++;
		}while( --i );
	} 
	else
		OneWire_WriteByte( ONEWIRE_SKIP_ROM );			// to all devices
	OneWire_WriteByte( command );
	return 0x00;	
}
#else
uint8_t OneWire_Command( uint8_t command)
{
	if(OneWire_Reset())
		return 0x01;	
	OneWire_WriteByte( ONEWIRE_SKIP_ROM );			// to all devices
	OneWire_WriteByte( command );
	return 0x00;	
}
#endif
// void OneWire_WriteBit( uint8_t bitval )
// {
// 	di();
// 	ONEWIRE_SETLOW();
// 	OneWire_Delay_us(2);
// 	if (bitval==1)  
// 	{
// 		ONEWIRE_SETHIGH();
// 	}
// 	OneWire_Delay_us(65);
// 	ONEWIRE_SETHIGH();
// 	ei();
// }
// 
uint8_t OneWire_ReadBit( void )
{
	uint8_t r;
	ONEWIRE_SETLOW();
	OneWire_Delay_us(2);
	//	ONEWIRE_SETLOW();
	ONEWIRE_SETHIGH();
	OneWire_Delay_us(15-3-OneWire_ReadDelayOffSet);
	r=ONEWIRE_GETIN();
	OneWire_Delay_us(60);
	if(r==0x00)
 		return 0;	
	else
 		return 1;
}

void OneWire_WriteByte( uint8_t val )
{
	uint8_t i;
	uint8_t temp;
	for (i=0;i<8;i++)
	{
		temp=val>>i;
		temp&=0x01;
		//di();
		ONEWIRE_SETLOW();
		OneWire_Delay_us(2);
		if (temp==1)  
		{
			ONEWIRE_SETHIGH();
		}
		OneWire_Delay_us(75);
		ONEWIRE_SETHIGH();
		//ei();
		//OneWire_WriteBit(temp);   //调写位函数
	}
	//OneWire_Delay_us(1);
}

uint8_t OneWire_ReadByte( void )
{
	uint8_t i;
	uint8_t b;
	uint8_t value=0;
	for(i=0;i<8;i++)
	{
		//di();
		ONEWIRE_SETLOW();
		OneWire_Delay_us(2);
		//	ONEWIRE_SETLOW();
		ONEWIRE_SETHIGH();
		OneWire_Delay_us(15-3-OneWire_ReadDelayOffSet);
		b=ONEWIRE_GETIN();
		//ei();
		OneWire_Delay_us(60);
		//b=OneWire_ReadBit();     //调读位函数
		if(b)               //如果是 1 置1
		{
			value|=(0x01<<i);  //先读低位，再读高位
			//OneWire_Delay_us(1);
		}
	}                         //否则置 0
	return(value);  
}

