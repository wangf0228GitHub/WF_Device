#ifndef _ONEWIRE_h_
#define _ONEWIRE_h_

#include "main.h"

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

uint8_t OneWire_Reset(void);
void OneWire_WriteBit(uint8_t bitval);
uint8_t OneWire_ReadBit( void );
void OneWire_WriteByte(uint8_t val);
uint8_t OneWire_ReadByte(void);

#ifdef OneWire_MAXSENSORS

	uint8_t OneWire_RomSearch( uint8_t diff, uint8_t *id );

	uint8_t OneWire_Command( uint8_t command, uint8_t *id );

#else
	uint8_t OneWire_Command( uint8_t command);
#endif

#endif

