#ifndef NMEA0183_h__
#define NMEA0183_h__

typedef union   
{
	struct
	{
		unsigned bRx:1;
	};
	unsigned char AllFlag;
} _NMEA0183_Flags;        // general flags

extern _NMEA0183_Flags NMEA0183_Flags;


#ifndef NMEA0183_RxBufSize
#define NMEA0183_RxBufSize 100
#endif

extern char NMEA0183_RxBuf[NMEA0183_RxBufSize];
extern unsigned char NMEA0183_RxCount;
void NMEA0183_Init(void);
void NMEA0183_RxProc(unsigned char rx);
unsigned char NMEA0183_Verify(void);
#endif // NMEA0183_h__
