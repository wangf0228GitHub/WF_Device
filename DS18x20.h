#ifndef DS18X20_H_
#define DS18X20_H_

//#define MAXSENSORS 10
// enable DS18x20 EERPROM support
//#define DS18X20_EEPROMSUPPORT

// enable extended output via UART by defining:
//#define DS18X20_VERBOSE

#ifndef  DS18X20_SensorIDLength
	#define DS18X20_SensorIDLength 8
#endif

#define ErrDS18X20_T 0xf000
/* return values */
#define DS18X20_OK          0x00
#define DS18X20_ERROR       0x01
#define DS18X20_START_FAIL  0x02
#define DS18X20_ERROR_CRC   0x03

#define DS18X20_POWER_PARASITE 0x00
#define DS18X20_POWER_EXTERN   0x01

/* DS18X20 specific values (see datasheet) */
#define DS18S20_ID 0x10
#define DS18B20_ID 0x28

#define DS18X20_CONVERT_T	0x44
#define DS18X20_READ		0xBE
#define DS18X20_WRITE		0x4E
#define DS18X20_EE_WRITE	0x48
#define DS18X20_EE_RECALL	0xB8
#define DS18X20_READ_POWER_SUPPLY 0xB4

#define DS18B20_CONF_REG    4
#define DS18B20_9_BIT       0
#define DS18B20_10_BIT      (1<<5)
#define DS18B20_11_BIT      (1<<6)
#define DS18B20_12_BIT      ((1<<6)|(1<<5))

// indefined bits in LSB if 18B20 != 12bit
#define DS18B20_9_BIT_UNDF       ((1<<0)|(1<<1)|(1<<2))
#define DS18B20_10_BIT_UNDF      ((1<<0)|(1<<1))
#define DS18B20_11_BIT_UNDF      ((1<<0))
#define DS18B20_12_BIT_UNDF      0

// conversion times in ms
#define DS18B20_TCONV_12BIT      750
#define DS18B20_TCONV_11BIT      DS18B20_TCONV_12_BIT/2
#define DS18B20_TCONV_10BIT      DS18B20_TCONV_12_BIT/4
#define DS18B20_TCONV_9BIT       DS18B20_TCONV_12_BIT/8
#define DS18S20_TCONV            DS18B20_TCONV_12_BIT

// constant to convert the fraction bits to cel*(10^-4)
#define DS18X20_FRACCONV         625

#define DS18X20_SP_SIZE  9

// DS18X20 EEPROM-Support
#define DS18X20_WRITE_SCRATCHPAD  0x4E
#define DS18X20_COPY_SCRATCHPAD   0x48
#define DS18X20_RECALL_E2         0xB8
#define DS18X20_COPYSP_DELAY      10 /* ms */
#define DS18X20_TH_REG      2
#define DS18X20_TL_REG      3

const unsigned char DS18X20_ToDecicel[16]={
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
unsigned char DS18X20_Scratchpad[9];

#ifdef OneWire_MAXSENSORS
	void DS18X20_FindSensor(unsigned char* diff, unsigned char* id);

	unsigned char DS18X20_StartMeas(unsigned char* id);
	unsigned char DS18X20_SearchSensors(unsigned char* id);
	unsigned char DS18X20_ReadMeas(unsigned char* id,unsigned char bVerify);

	#ifdef DS18X20_EEPROMSUPPORT
		// write th, tl and config-register to scratchpad (config ignored on S20)
		unsigned char DS18X20_WriteScratchpad(unsigned char* id, unsigned char th, unsigned char tl, unsigned char conf);
		// read scratchpad into array SP
		unsigned char DS18X20_ReadScratchpad(unsigned char* id,unsigned char bVerify);
		// copy values th,tl (config) from scratchpad to DS18x20 eeprom
		unsigned char DS18X20_CopyScratchpad(unsigned char* id);
		// copy values from DS18x20 eeprom to scratchpad
		unsigned char DS18X20_RecallE2(unsigned char* id);
	#endif
#else

	unsigned char DS18X20_StartMeas();
	unsigned char DS18X20_ReadMeas(unsigned char bVerify);

	#ifdef DS18X20_EEPROMSUPPORT
		// write th, tl and config-register to scratchpad (config ignored on S20)
		#ifdef DS18B20
			unsigned char DS18X20_WriteScratchpad(unsigned char th, unsigned char tl, unsigned char conf);
		#else
			unsigned char DS18X20_WriteScratchpad(unsigned char th, unsigned char tl);
		#endif
		// read scratchpad into array SP
		unsigned char DS18X20_ReadScratchpad(unsigned char bVerify);
		// copy values th,tl (config) from scratchpad to DS18x20 eeprom
		unsigned char DS18X20_CopyScratchpad();
		// copy values from DS18x20 eeprom to scratchpad
		unsigned char DS18X20_RecallE2();
	#endif
#endif


/* for description of functions see ds18x20.c */




#endif
