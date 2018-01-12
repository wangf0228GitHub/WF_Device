#include "HardwareProfile.h"
#include "OneWire.h"


unsigned char OneWire_Reset(void)
{
	unsigned char r,Retry;
	r=1;
	Retry=TIMESFORRETRY_OneWire;
	while(Retry--)
	{
		ONEWIRE_SETLOW; 
		__delay_us(480);
		ONEWIRE_SETHIGH;//等电阻拉高总线并保持15－60us
		di();
		__delay_us(75);
		r=ONEWIRE_GETIN;//接受应答信号
		ei();		
		__delay_us(480);//延时60－240us
		if(ONEWIRE_GETIN==0)
			r=1;
		if(r==0)
			break;
	}	
	return r;	
}
#ifdef OneWire_MAXSENSORS
unsigned char OneWire_RomSearch( unsigned char diff, unsigned char *id )
{ 
	unsigned char i, j, next_diff;
	unsigned char b,b1;

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
			ONEWIRE_SETLOW;
			__delay_us(2);
			//	ONEWIRE_SETLOW();
			ONEWIRE_SETHIGH;
			__delay_us(15-3-OneWire_ReadDelayOffSet);
			b=ONEWIRE_GETIN;
			ei();
			__delay_us(60);
			di();
			ONEWIRE_SETLOW;
			__delay_us(2);
			//	ONEWIRE_SETLOW();
			ONEWIRE_SETHIGH;
			__delay_us(15-3-OneWire_ReadDelayOffSet);
			b1=ONEWIRE_GETIN;
			ei();
			__delay_us(60);
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
			ONEWIRE_SETLOW;
			__delay_us(2);
			if (b!=0x00)  
			{
				ONEWIRE_SETHIGH;
			}
			__delay_us(75);
			ONEWIRE_SETHIGH;
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


unsigned char OneWire_Command( unsigned char command, unsigned char *id )
{
	unsigned char i;
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
unsigned char OneWire_Command( unsigned char command)
{
	if(OneWire_Reset())
		return 0x01;	
	OneWire_WriteByte( ONEWIRE_SKIP_ROM );			// to all devices
	OneWire_WriteByte( command );
	return 0x00;	
}
#endif
// void OneWire_WriteBit( unsigned char bitval )
// {
// 	di();
// 	ONEWIRE_SETLOW();
// 	__delay_us(2);
// 	if (bitval==1)  
// 	{
// 		ONEWIRE_SETHIGH();
// 	}
// 	__delay_us(65);
// 	ONEWIRE_SETHIGH();
// 	ei();
// }
// 
unsigned char OneWire_ReadBit( void )
{
	unsigned char r;
	di();
	ONEWIRE_SETLOW;
	__delay_us(2);
	//	ONEWIRE_SETLOW();
	ONEWIRE_SETHIGH;
	__delay_us(15-3-OneWire_ReadDelayOffSet);
	r=ONEWIRE_GETIN;
	ei();
	__delay_us(60);
	if(r==0x00)
 		return 0;	
	else
 		return 1;
}

void OneWire_WriteByte( unsigned char val )
{
	unsigned char i;
	unsigned char temp;
	for (i=0;i<8;i++)
	{
		temp=val>>i;
		temp&=0x01;
		di();
		ONEWIRE_SETLOW;
		__delay_us(2);
		if (temp==1)  
		{
			ONEWIRE_SETHIGH;
		}
		__delay_us(75);
		ONEWIRE_SETHIGH;
		ei();
		//OneWire_WriteBit(temp);   //调写位函数
	}
	//__delay_us(1);
}

unsigned char OneWire_ReadByte( void )
{
	unsigned char i;
	unsigned char b;
	unsigned char value=0;
	for(i=0;i<8;i++)
	{
		di();
		ONEWIRE_SETLOW;
		__delay_us(2);
		//	ONEWIRE_SETLOW();
		ONEWIRE_SETHIGH;
		__delay_us(15-3-OneWire_ReadDelayOffSet);
		b=ONEWIRE_GETIN;
		ei();
		__delay_us(60);
		//b=OneWire_ReadBit();     //调读位函数
		if(b)               //如果是 1 置1
		{
			value|=(0x01<<i);  //先读低位，再读高位
			//__delay_us(1);
		}
	}                         //否则置 0
	return(value);  
}

