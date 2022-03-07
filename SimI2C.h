#ifndef __SimI2C_h__
#define __SimI2C_h__

#include "HardwareProfile.h"
//#define SimI2C_CLK_IO TRISB6
//#define SimI2C_DATA_IO TRISB4
//#define SimI2C_CLK RB6
//#define SimI2C_DATA RB4
#ifndef SimI2C_Delay_Ex
#define SimI2C_Delay()
#endif


void SimI2C_Start(void);
void SimI2C_Stop(void);
uint8_t SimI2C_RecAck(void);
void SimI2C_Ack(void);
void SimI2C_NoAck(void);

void SimI2C_Init( void );
void SimI2C_SendByte(uint8_t data);//写数据
uint8_t SimI2C_ReadByte(void);//读数据

#ifdef SimI2C_2
#ifndef SimI2C_2_Delay_Ex
#define SimI2C_2_Delay()
#endif


void SimI2C_2_Start(void);
void SimI2C_2_Stop(void);
uint8_t SimI2C_2_RecAck(void);
void SimI2C_2_Ack(void);
void SimI2C_2_NoAck(void);

void SimI2C_2_Init( void );
void SimI2C_2_SendByte(uint8_t data);//写数据
uint8_t SimI2C_2_ReadByte(void);//读数据
#endif

#ifdef SimI2C_3
#ifndef SimI2C_3_Delay_Ex
#define SimI2C_3_Delay()
#endif


void SimI2C_3_Start(void);
void SimI2C_3_Stop(void);
uint8_t SimI2C_3_RecAck(void);
void SimI2C_3_Ack(void);
void SimI2C_3_NoAck(void);

void SimI2C_3_Init( void );
void SimI2C_3_SendByte(uint8_t data);//写数据
uint8_t SimI2C_3_ReadByte(void);//读数据
#endif

#ifdef SimI2C_4
#ifndef SimI2C_4_Delay_Ex
#define SimI2C_4_Delay()
#endif


void SimI2C_4_Start(void);
void SimI2C_4_Stop(void);
uint8_t SimI2C_4_RecAck(void);
void SimI2C_4_Ack(void);
void SimI2C_4_NoAck(void);

void SimI2C_4_Init(void);
void SimI2C_4_SendByte(uint8_t data);//写数据
uint8_t SimI2C_4_ReadByte(void);//读数据
#endif


#endif // __SimI2C_h__

