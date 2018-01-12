#ifndef _ONEWIRE_h_
#define _ONEWIRE_h_

#ifndef TIMESFORRETRY_OneWire
	#define TIMESFORRETRY_OneWire 5
#endif

#ifndef OneWire_ReadDelayOffSet
#define OneWire_ReadDelayOffSet 0
#endif
//#define ONEWIRE_PIN RA2
//#define ONEWIRE_PIN_DIR TRISA2

#ifndef ONEWIRE_SETLOW
	#define ONEWIRE_SETLOW ONEWIRE_PIN_DIR = 0;ONEWIRE_PIN_W=0
#endif


#ifndef ONEWIRE_GETIN
	#define ONEWIRE_GETIN ONEWIRE_PIN_R
#endif

#ifndef ONEWIRE_SETHIGH
	#define ONEWIRE_SETHIGH ONEWIRE_PIN_DIR=1
#endif





/*******************************************/

// #define ONEWIRE_SHORT_CIRCUIT  0x01
#define ONEWIRE_READ_ROM	0x33
#define ONEWIRE_MATCH_ROM	0x55
#define ONEWIRE_SKIP_ROM	0xCC
#define	ONEWIRE_SEARCH_ROM	0xF0

#define	ONEWIRE_SEARCH_FIRST	0xFF		// start new search
#define	ONEWIRE_PRESENCE_ERR	0xFF
#define	ONEWIRE_DATA_ERR	    0xFE
#define ONEWIRE_LAST_DEVICE		0x00		// last device found
//			0x01 ... 0x40: continue searching

// rom-code size including CRC
#define ONEWIRE_ROMCODE_SIZE 8

//#define OneWire_Init() ONEWIRE_SETHIGH()

unsigned char OneWire_Reset(void);
void OneWire_WriteBit(unsigned char bitval);
unsigned char OneWire_ReadBit( void );
void OneWire_WriteByte(unsigned char val);
unsigned char OneWire_ReadByte(void);

#ifdef OneWire_MAXSENSORS

	unsigned char OneWire_RomSearch( unsigned char diff, unsigned char *id );

	unsigned char OneWire_Command( unsigned char command, unsigned char *id );

#else
	unsigned char OneWire_Command( unsigned char command);
#endif

#endif

