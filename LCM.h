#ifndef __LCM_H__
#define __LCM_H__

/*const uint8_t ZM[]={0x5f,0x50,0x3d,0x79,0x72,0x6b,0x6f,0x51,0x7f,0x7b,//0~9
							0x76,0x20,0x5e,0x37,0x29,0x00};//10:H,11:-,12:U 13:P 14:三,15:无*/
							
//送控制字   
void LCM_WriteCmd(uint8_t cmdcode);
//初始化     
void LCM_Init(void);
//送6位地址+LCM_DATALENGTH位数据
void LCM_WriteData(uint8_t address,uint8_t data);
//连续写
void LCM_WriteDatas(uint8_t address,uint8_t len,uint8_t* pData);
#endif
