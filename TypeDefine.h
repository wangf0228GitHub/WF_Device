/*---------------------------------------------------------------------------
; FILE NAME: TypeDefine.H
; DESCRIPTION: 
;---------------------------------------------------------------------------*/
#ifndef   __TypeDefine_h__
#define   __TypeDefine_h__



// #ifndef __GENERIC_TYPE_DEFS_H_
// typedef enum _BOOL { FALSE = 0, TRUE } BOOL;    /* Undefined size */
// #endif

// #ifndef NULL
// #define	NULL		0
// #endif
// #ifndef TRUE
// #define	TRUE  		1
// #endif
// #ifndef FALSE
// #define FALSE 		0
// #endif

//0为低位，其它顺次为高位
///---------------------------------------------------------------------------
typedef union
{	
	unsigned char u8;
	struct
	{
		unsigned b0:1;
		unsigned b1:1;
		unsigned b2:1;
		unsigned b3:1;
		unsigned b4:1;
		unsigned b5:1;
		unsigned b6:1;
		unsigned b7:1;		
	}bits;
}uchar;
typedef union
{	
	unsigned char u8s[2];
	unsigned int u16;
	struct
	{
		unsigned b0:1;
		unsigned b1:1;
		unsigned b2:1;
		unsigned b3:1;
		unsigned b4:1;
		unsigned b5:1;
		unsigned b6:1;
		unsigned b7:1;
		unsigned b8:1;
		unsigned b9:1;
		unsigned b10:1;
		unsigned b11:1;
		unsigned b12:1;
		unsigned b13:1;
		unsigned b14:1;
		unsigned b15:1;
	}bits;
	struct
	{
		unsigned char u8L;
		unsigned char u8H;
	};
}uint;
typedef union 
{	
	unsigned char u8s[3];	
	struct
	{
		uint	u16_0;
		unsigned char	u8_1;
	}byte21;
	struct
	{
		unsigned char	u8_0;
		uint	u16_1;
	}byte12;
	struct
	{
		unsigned b0:1;
		unsigned b1:1;
		unsigned b2:1;
		unsigned b3:1;
		unsigned b4:1;
		unsigned b5:1;
		unsigned b6:1;
		unsigned b7:1;
		unsigned b8:1;
		unsigned b9:1;
		unsigned b10:1;
		unsigned b11:1;
		unsigned b12:1;
		unsigned b13:1;
		unsigned b14:1;
		unsigned b15:1;
		unsigned b16:1;
		unsigned b17:1;
		unsigned b18:1;
		unsigned b19:1;
		unsigned b20:1;
		unsigned b21:1;
		unsigned b22:1;
		unsigned b23:1;
	}bits;
}uchar3;

typedef union 
{	
	unsigned char u8s[4];
	unsigned int u16s[2];
	unsigned long u32;
	struct
	{
		uint u16L;
		uint u16H;
	};
	struct
	{
		unsigned b0:1;
		unsigned b1:1;
		unsigned b2:1;
		unsigned b3:1;
		unsigned b4:1;
		unsigned b5:1;
		unsigned b6:1;
		unsigned b7:1;
		unsigned b8:1;
		unsigned b9:1;
		unsigned b10:1;
		unsigned b11:1;
		unsigned b12:1;
		unsigned b13:1;
		unsigned b14:1;
		unsigned b15:1;
		unsigned b16:1;
		unsigned b17:1;
		unsigned b18:1;
		unsigned b19:1;
		unsigned b20:1;
		unsigned b21:1;
		unsigned b22:1;
		unsigned b23:1;
		unsigned b24:1;
		unsigned b25:1;
		unsigned b26:1;
		unsigned b27:1;
		unsigned b28:1;
		unsigned b29:1;
		unsigned b30:1;
		unsigned b31:1;
	}bits;
}ulong;
typedef union 
{	
	unsigned char u8s[4];
	unsigned int u16s[2];
	double f32;
}float32;
/************************************************************************/
/* 有符号数                                                             */
/************************************************************************/
typedef union
{	
	struct
	{
		unsigned char s8_l;
		signed char	u8_h;
	}s8s;
	int s16;
	unsigned int u16;
}sint;

typedef union 
{	
	struct
	{
		unsigned char	s8_0;
		unsigned char	u8_1;
		unsigned char	u8_2;
		signed char	s8_3;
	}s8s;
	struct
	{
		uint	u16_l;
		sint	s16_h;	
	}s16s;
	struct
	{
		unsigned int	u16_l;
		int	s16_h;	
	}s16s1;
	long s32;
	unsigned long u32;
}slong;

typedef struct
{	
	unsigned long hi, lo;
}u64;
u64 u64_Init (unsigned long hi, unsigned long lo);
/* Return a u64 value representing LO.  */
u64 u64_lo (unsigned long lo);
u64 u64_hi (unsigned long hi);
unsigned char u64_lt (u64 x, u64 y);
/* Return X & Y.  */
u64 u64_and (u64 x, u64 y);
/* Return X | Y.  */
u64 u64_or (u64 x, u64 y);
/* Return X ^ Y.  */
u64 u64_xor (u64 x, u64 y);
/* Return X + Y.  */
u64 u64_plus (u64 x, unsigned long hi,unsigned long lo);
u64 u64_decrease (u64 x, unsigned long hi,unsigned long lo);
/* Return X << N.  */
u64 u64_shl (u64 x, int n);
/* Return X >> N.  */
u64 u64_shr (u64 x, int n);
u64 u64_lmul(unsigned long multiplier, unsigned long multiplicand);
u64 u64_lmuu64(u64 multiplier, unsigned long multiplicand);
u64 u64_u64muu64(u64 multiplier, unsigned long hi,unsigned long lo);
#endif


/*-------------------------------------------------------------------------------------------------
;
;end  of  the  file
;
;-------------------------------------------------------------------------------------------------*/

  

