#include "Si4463.h"
//#define Si4463_NSEL_DIR	TRISA1
//#define Si4463_SCL_DIR	TRISA1
//#define Si4463_SDI_DIR	TRISA2
//#define Si4463_SDO_DIR	TRISA0
//
//#define Si4463_NSEL	RA1
//#define Si4463_SCL	RA1
//#define Si4463_SDI	RA0 //芯片的输入
//#define Si4463_SDO	RA2	//芯片的输出


void Si4463_WAIT_CTS( void );

void Si4463_Init(void)
{	
	Si4463_NSEL_High();
	Si4463_SPIInit();
// 	Si4463_SCL_DIR=0;
// 	Si4463_SDO_DIR=1;
// 	Si4463_SDI_DIR=0;	
// 	Si4463_SCL_W=1;	//拉低时钟信号
}

/*
=================================================================================
Si4463_CMD( );
Function : Send a command to the device
INTPUT   : cmd, the buffer stores the command array
           cmdsize, the size of the command array
OUTPUT   : NONE
=================================================================================
*/
void Si4463_CMD(uint8_t *cmd, uint8_t cmdsize )
{
    Si4463_WAIT_CTS( );
    Si4463_NSEL_Low();
    while( cmdsize -- )
    {
        Si4463_SPIProc( *cmd++ );
    }
    Si4463_NSEL_High();
}
/*
=================================================================================
Si4463_POWER_UP( );
Function : Power up the device
INTPUT   : f_xtal, the frequency of the external high-speed crystal
OUTPUT   : NONE
=================================================================================
*/
void Si4463_POWER_UP(uint32_t f_xtal )
{
    uint8_t cmd[7];
    cmd[0] = POWER_UP;
    cmd[1] = 0x01;
    cmd[2] = 0x00;
    cmd[3] = f_xtal>>24;
    cmd[4] = f_xtal>>16;
    cmd[5] = f_xtal>>8;
    cmd[6] = f_xtal;
    Si4463_CMD( cmd, 7 );
}
/*
=================================================================================
Si4463_READ_RESPONSE( );
Function : read a array of command response
INTPUT   : buffer,  a buffer, stores the data responsed
           size,    How many bytes should be read
OUTPUT   : NONE
=================================================================================
*/
void Si4463_READ_RESPONSE( uint8_t *buffer, uint8_t size )
{
    Si4463_WAIT_CTS( );
    Si4463_NSEL_Low();
	Si4463_SPIProc( READ_CMD_BUFF );
	while( size -- )
    {
        *buffer++ = Si4463_SPIProc( 0xFF );
    }
    Si4463_NSEL_High();

}
/*
=================================================================================
Si4463_WAIT_CTS( );
Function : wait the device ready to response a command
INTPUT   : NONE
OUTPUT   : NONE
=================================================================================
*/
void Si4463_WAIT_CTS( void )
{
    uint8_t cts;
    do
    {
		cts=0;
        Si4463_NSEL_Low();
        Si4463_SPIProc( READ_CMD_BUFF );
        cts = Si4463_SPIProc( 0xFF );
        Si4463_NSEL_High();
    }while( cts != 0xFF );
}
/*
=================================================================================
Si4463_NOP( );
Function : NO Operation command
INTPUT   : NONE
OUTPUT   : NONE
=================================================================================
*/
uint8_t Si4463_NOP( void )
{
    uint8_t cts;
    Si4463_NSEL_Low();
    cts = Si4463_SPIProc( NOP );
    Si4463_NSEL_High();
	return cts;
}

/*
=================================================================================
Si4463_PART_INFO( );
Function : Read the PART_INFO of the device, 8 bytes needed
INTPUT   : buffer, the buffer stores the part information
OUTPUT   : NONE
=================================================================================
*/
void Si4463_PART_INFO( uint8_t *buffer )
{
    uint8_t cmd = PART_INFO;

    Si4463_CMD( &cmd, 1 );
    Si4463_READ_RESPONSE( buffer, 8 );

}
/*
=================================================================================
Si4463_FUNC_INFO( );
Function : Read the FUNC_INFO of the device, 7 bytes needed
INTPUT   : buffer, the buffer stores the FUNC information
OUTPUT   : NONE
=================================================================================
*/
void Si4463_FUNC_INFO( uint8_t *buffer )
{
    uint8_t cmd = FUNC_INFO;

    Si4463_CMD( &cmd, 1 );
    Si4463_READ_RESPONSE( buffer, 7 );
}
/*
=================================================================================
Si4463_INT_STATUS( );
Function : Read the INT status of the device, 9 bytes needed
INTPUT   : buffer, the buffer stores the int status
OUTPUT   : NONE
=================================================================================
*/
void Si4463_INT_STATUS( uint8_t *buffer )
{
    uint8_t cmd[4];
    cmd[0] = GET_INT_STATUS;
    cmd[1] = 0;
    cmd[2] = 0;
    cmd[3] = 0;

    Si4463_CMD( cmd, 4 );
    Si4463_READ_RESPONSE( buffer, 9 );

}
/*
=================================================================================
Si4463_GET_PROPERTY( );
Function : Read the PROPERTY of the device
INTPUT   : buffer, the buffer stores the PROPERTY value
           GROUP_NUM, the group and number of the parameter
           NUM_GROUP, number of the group
OUTPUT   : NONE
=================================================================================
*/
void Si4463_GET_PROPERTY_X( Si4463_PROPERTY GROUP_NUM, uint8_t NUM_PROPS, uint8_t *buffer  )
{
    uint8_t cmd[4];

    cmd[0] = GET_PROPERTY;
    cmd[1] = GROUP_NUM>>8;
    cmd[2] = NUM_PROPS;
    cmd[3] = GROUP_NUM;

    Si4463_CMD( cmd, 4 );
    Si4463_READ_RESPONSE( buffer, NUM_PROPS + 1 );
}
/*
=================================================================================
Si4463_SET_PROPERTY_X( );
Function : Set the PROPERTY of the device
INTPUT   : GROUP_NUM, the group and the number of the parameter
           NUM_GROUP, number of the group
           PAR_BUFF, buffer stores parameters
OUTPUT   : NONE
=================================================================================
*/
void Si4463_SET_PROPERTY_X( Si4463_PROPERTY GROUP_NUM, uint8_t NUM_PROPS, uint8_t *PAR_BUFF )
{
    uint8_t cmd[20], i = 0;
    if( NUM_PROPS >= 16 )   { return; }
    cmd[i++] = SET_PROPERTY;
    cmd[i++] = GROUP_NUM>>8;
    cmd[i++] = NUM_PROPS;
    cmd[i++] = GROUP_NUM;
    while( NUM_PROPS-- )
    {
        cmd[i++] = *PAR_BUFF++;
    }
    Si4463_CMD( cmd, i );
}
/*
=================================================================================
Si4463_SET_PROPERTY_1( );
Function : Set the PROPERTY of the device, only 1 byte
INTPUT   : GROUP_NUM, the group and number index
           prioriry,  the value to be set
OUTPUT   : NONE
=================================================================================
*/
void Si4463_SET_PROPERTY_1( Si4463_PROPERTY GROUP_NUM, uint8_t proirity )
{
    uint8_t cmd[5];

    cmd[0] = SET_PROPERTY;
    cmd[1] = GROUP_NUM>>8;
    cmd[2] = 1;
    cmd[3] = GROUP_NUM;
    cmd[4] = proirity;
    Si4463_CMD( cmd, 5 );
}
/*
=================================================================================
Si4463_GET_PROPERTY_1( );
Function : Get the PROPERTY of the device, only 1 byte
INTPUT   : GROUP_NUM, the group and number index
OUTPUT   : the PROPERTY value read from device
=================================================================================
*/
uint8_t Si4463_GET_PROPERTY_1( Si4463_PROPERTY GROUP_NUM )
{
    uint8_t cmd[4];

    cmd[0] = GET_PROPERTY;
    cmd[1] = GROUP_NUM>>8;
    cmd[2] = 1;
    cmd[3] = GROUP_NUM;
    Si4463_CMD( cmd, 4 );
    Si4463_READ_RESPONSE( cmd, 2 );
    return cmd[1];
}
/*
=================================================================================
Si4463_RESET( );
Function : reset the Si4463 device
INTPUT   : NONE
OUTPUT   : NONE
=================================================================================
*/
void Si4463_RESET( void )
{
    Si4463_SDN_High();
    wfDelay_ms(20);
    Si4463_SDN_Low();
    Si4463_NSEL_High();
	wfDelay_ms(2000);
}
/*
=================================================================================
Si4463_W_TX_FIFO( );
Function : write data to TX fifo
INTPUT   : txbuffer, a buffer stores TX array
           size,  how many bytes should be written
OUTPUT   : NONE
=================================================================================
*/
void Si4463_W_TX_FIFO( uint8_t *txbuffer, uint8_t size )
{
    Si4463_NSEL_Low();
    Si4463_SPIProc( WRITE_TX_FIFO );
    while( size -- )    { Si4463_SPIProc( *txbuffer++ ); }
    Si4463_NSEL_High();
}
/*
=================================================================================
Si4463_SEND_PACKET( );
Function : send a packet
INTPUT   : txbuffer, a buffer stores TX array
           size,  how many bytes should be written
           channel, tx channel
           condition, tx condition
OUTPUT   : NONE
=================================================================================
*/
void Si4463_SEND_PACKET( uint8_t *txbuffer, uint8_t size, uint8_t channel, uint8_t condition )
{
    uint8_t cmd[5];
    uint8_t tx_len = size;

    Si4463_TX_FIFO_RESET( );

    Si4463_NSEL_Low();
    Si4463_SPIProc( WRITE_TX_FIFO );
#if PACKET_LENGTH == 0
    tx_len ++;
    Si4463_SPIProc( size );
#endif
    while( size -- )    { Si4463_SPIProc( *txbuffer++ ); }
    Si4463_NSEL_High();
    cmd[0] = START_TX;
    cmd[1] = channel;
    cmd[2] = condition;
    cmd[3] = 0;
    cmd[4] = tx_len;
    Si4463_CMD( cmd, 5 );
}
/*
=================================================================================
Si4463_START_TX( );
Function : start TX command
INTPUT   : channel, tx channel
           condition, tx condition
           tx_len, how many bytes to be sent
OUTPUT   : NONE
=================================================================================
*/
void Si4463_START_TX( uint8_t channel, uint8_t condition, uint16_t tx_len )
{
    uint8_t cmd[5];

    cmd[0] = START_TX;
    cmd[1] = channel;
    cmd[2] = condition;
    cmd[3] = tx_len>>8;
    cmd[4] = tx_len;
    Si4463_CMD( cmd, 5 );
}
/*
=================================================================================
Si4463_READ_PACKET( );
Function : read RX fifo
INTPUT   : buffer, a buffer to store data read
OUTPUT   : received bytes
=================================================================================
*/
uint8_t Si4463_READ_PACKET( uint8_t *buffer )
{
    uint8_t length, i,x;
    Si4463_WAIT_CTS( );
    Si4463_NSEL_Low();

    Si4463_SPIProc( READ_RX_FIFO );
#if PACKET_LENGTH == 0
    length = Si4463_SPIProc( 0xFF );
#else
    length = PACKET_LENGTH;
#endif
    i = length;

    while( length -- )
    {
        x = Si4463_SPIProc( 0xFF );
		*buffer++=x;
    }
    Si4463_NSEL_High();
    return i;
}
/*
=================================================================================
Si4463_START_RX( );
Function : start RX state
INTPUT   : channel, receive channel
           condition, receive condition
           rx_len, how many bytes should be read
           n_state1, next state 1
           n_state2, next state 2
           n_state3, next state 3
OUTPUT   : NONE
=================================================================================
*/
void Si4463_START_RX( uint8_t channel, uint8_t condition, uint16_t rx_len,
                      uint8_t n_state1, uint8_t n_state2, uint8_t n_state3 )
{
    uint8_t cmd[8];
    Si4463_RX_FIFO_RESET( );
    Si4463_TX_FIFO_RESET( );
    cmd[0] = START_RX;
    cmd[1] = channel;
    cmd[2] = condition;
    cmd[3] = rx_len>>8;
    cmd[4] = rx_len;
    cmd[5] = n_state1;
    cmd[6] = n_state2;
    cmd[7] = n_state3;
    Si4463_CMD( cmd, 8 );
}
/*
=================================================================================
Si4463_RX_FIFO_RESET( );
Function : reset the RX FIFO of the device
INTPUT   : None
OUTPUT   : NONE
=================================================================================
*/
void Si4463_RX_FIFO_RESET( void )
{
    uint8_t cmd[2];

    cmd[0] = FIFO_INFO;
    cmd[1] = 0x02;
    Si4463_CMD( cmd, 2 );
}
/*
=================================================================================
Si4463_TX_FIFO_RESET( );
Function : reset the TX FIFO of the device
INTPUT   : None
OUTPUT   : NONE
=================================================================================
*/
void Si4463_TX_FIFO_RESET( void )
{
    uint8_t cmd[2];

    cmd[0] = FIFO_INFO;
    cmd[1] = 0x01;
    Si4463_CMD( cmd, 2 );
}
/*
=================================================================================
Si4463_PKT_INFO( );
Function : read packet information
INTPUT   : buffer, stores the read information
           FIELD, feild mask
           length, the packet length
           diff_len, diffrence packet length
OUTPUT   : NONE
=================================================================================
*/
void Si4463_PKT_INFO( uint8_t *buffer, uint8_t FIELD, uint16_t length, uint16_t diff_len )
{
    uint8_t cmd[6];
    cmd[0] = PACKET_INFO;
    cmd[1] = FIELD;
    cmd[2] = length >> 8;
    cmd[3] = length;
    cmd[4] = diff_len >> 8;
    cmd[5] = diff_len;

    Si4463_CMD( cmd, 6 );
    Si4463_READ_RESPONSE( buffer, 3 );
}
/*
=================================================================================
Si4463_FIFO_INFO( );
Function : read fifo information
INTPUT   : buffer, stores the read information
OUTPUT   : NONE
=================================================================================
*/
void Si4463_FIFO_INFO( uint8_t *buffer )
{
    uint8_t cmd[2];
    cmd[0] = FIFO_INFO;
    cmd[1] = 0x03;

    Si4463_CMD( cmd, 2 );
    Si4463_READ_RESPONSE( buffer, 3);
}
/*
=================================================================================
Si4463_GPIO_CONFIG( );
Function : config the GPIOs, IRQ, SDO
INTPUT   :
OUTPUT   : NONE
=================================================================================
*/
void Si4463_GPIO_CONFIG( uint8_t G0, uint8_t G1, uint8_t G2, uint8_t G3,
                         uint8_t IRQ, uint8_t SDO, uint8_t GEN_CONFIG )
{
    uint8_t cmd[10];
    cmd[0] = GPIO_PIN_CFG;
    cmd[1] = G0;
    cmd[2] = G1;
    cmd[3] = G2;
    cmd[4] = G3;
    cmd[5] = IRQ;
    cmd[6] = SDO;
    cmd[7] = GEN_CONFIG;
    Si4463_CMD( cmd, 8 );
    Si4463_READ_RESPONSE( cmd, 8 );
}
/*
=================================================================================
------------------------------------End of FILE----------------------------------
=================================================================================
*/

