#ifndef __TLV56XX_h__
#define __TLV56XX_h__

// #define TLV56XX_FS_W	LATE6 
// #define TLV56XX_CLK_W	LATE4   
// #define TLV56XX_DIO_W	LATE3  
// #define TLV56XX_CS_W	LATE5
// 
// #define TLV56XX_FS_DIR	TRISE6
// #define TLV56XX_CLK_DIR TRISE4
// #define TLV56XX_DIO_DIR TRISE3  
// #define TLV56XX_CS_DIR  TRISE5
// 
// #define TLV56XX_2
// 
// #define TLV56XX_2_FS_W	LATA3 
// #define TLV56XX_2_CLK_W	LATA5   
// #define TLV56XX_2_DIO_W	LATA4  
// #define TLV56XX_2_CS_W	LATA2
// 
// #define TLV56XX_2_FS_DIR	TRISA3
// #define TLV56XX_2_CLK_DIR	TRISA5
// #define TLV56XX_2_DIO_DIR	TRISA4  
// #define TLV56XX_2_CS_DIR	TRISA2
void TLV56XX_Init(void);
void TLV56XX_WriteData(unsigned int d);

#ifdef TLV56XX_2
void TLV56XX_2_Init(void);
void TLV56XX_2_WriteData(unsigned int d);
#endif
#endif // __TLV56XX_h__

