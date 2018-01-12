#ifndef __SimI2C_h__
#define __SimI2C_h__

//#define SimI2C_CLK_IO TRISB6
//#define SimI2C_DATA_IO TRISB4
//#define SimI2C_CLK RB6
//#define SimI2C_DATA RB4
#ifndef SimI2C_Delay_Ex
#define SimI2C_Delay() __delay_us(1);
#endif


void SimI2C_Start(void);
void SimI2C_Stop(void);
unsigned char SimI2C_RecAck(void);
void SimI2C_Ack(void);
void SimI2C_NoAck(void);

void SimI2C_Init( void );
void SimI2C_SendByte(unsigned char data);//写数据
unsigned char SimI2C_ReadByte(void);//读数据

#ifdef SimI2C_2
#ifndef SimI2C_Delay_2
#define SimI2C_Delay_2() __delay_us(1);
#endif
void SimI2C_Start_2(void);
void SimI2C_Stop_2(void);
unsigned char SimI2C_RecAck_2(void);
void SimI2C_Ack_2(void);
void SimI2C_NoAck_2(void);

void SimI2C_Init_2( void );
void SimI2C_SendByte_2(unsigned char data);//写数据
unsigned char SimI2C_ReadByte_2(void);//读数据
#endif

#ifdef SimI2C_3
#ifndef SimI2C_Delay_3
#define SimI2C_Delay_3() __delay_us(1);
#endif
void SimI2C_Start_3(void);
void SimI2C_Stop_3(void);
unsigned char SimI2C_RecAck_3(void);
void SimI2C_Ack_3(void);
void SimI2C_NoAck_3(void);

void SimI2C_Init_3( void );
void SimI2C_SendByte_3(unsigned char data);//写数据
unsigned char SimI2C_ReadByte_3(void);//读数据
#endif
#endif // __SimI2C_h__

