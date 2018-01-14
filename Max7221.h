#ifndef __Max7221_h__
#define __Max7221_h__

#ifndef Max7221_LEDNumCode
const uint8_t Max7221_LEDNumCode[]=
{
	//DP A B C D E F G
	0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x77,0x1F,0x4E,0x3D,0x4F,0x47,0x01,0x00//0-9,A-F,-
};
#endif
void Max7221_Init(void);
//送6位地址+Max7221_DATALENGTH位数据
void Max7221_WriteData(uint8_t addr,uint8_t data);

#ifdef Max7221_2
void Max7221_Init_2(void);
//送6位地址+Max7221_DATALENGTH位数据
void Max7221_WriteData_2(uint8_t addr,uint8_t data);
#endif

#ifdef Max7221_3
void Max7221_Init_3(void);
//送6位地址+Max7221_DATALENGTH位数据
void Max7221_WriteData_3(uint8_t addr,uint8_t data);
#endif
#endif
