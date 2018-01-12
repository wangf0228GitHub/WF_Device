#ifndef __TLV5623_h__
#define __TLV5623_h__

// #define TLV5623_FS TRISB1  //片选
// #define TLV5623_CLK RB1      //时钟
// #define TLV5623_DIO   RB1   //数据输入/输出
// 
// #define TLV5623_FS_IO TRISB1
// #define TLV5623_CLK_IO RB1
// #define TLV5623_DIO_IO   RB1  
typedef union   
{
	struct
	{
		unsigned PWR:1;
		unsigned SPD:1;
	};
	unsigned char AllFlag;
} _TLV5623State;        // general flags
_TLV5623State TLV5623State;
void TLV5623_Init(void);
void TLV5623_WriteData(unsigned char d);
#endif // __TLV5623_h__

