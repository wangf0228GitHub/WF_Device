#ifndef GPS_GPRMC_h__
#define GPS_GPRMC_h__

typedef union   
{
	struct
	{		
		char Header[6];
		char UTCTime[10];
		char AV;
		char Latitude[9];//纬度
		char NS;
		char Longitude[10];//经度
		char EW;
		char GPSSpeed[5];
		char Course[5];//航向
		char UTCDate[6];
		char CPJ[5];
		char CPJFX;
		char Model;
	};
	unsigned char GPS_GPRMC_Data[61];
}_GPS_GPRMC;
extern _GPS_GPRMC GPS_GPRMC;
unsigned char GPS_GPRMC_DataProc(char* data);
#endif // GPS_GPRMC_h__
