/*---------------------------------------------------------------------------
; FILE NAME: TypeDefine.H
; DESCRIPTION: 
;---------------------------------------------------------------------------*/
#ifndef   __TypeDefine_h__
#define   __TypeDefine_h__

#include <stdint.h>

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

//#pragma anon_unions
typedef union
{	
	uint8_t u8s[4];
	float f;
}float_wf;

typedef union
{	
	uint8_t u8;
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
}u8_wf;
typedef union
{	
	uint8_t u8s[2];
	uint16_t u16;
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
		uint8_t u8L;
		uint8_t u8H;
	};
}u16_wf;
typedef union 
{	
	uint8_t u8s[3];	
	struct
	{
		u16_wf	u16_0;
		uint8_t	u8_1;
	}byte21;
	struct
	{
		uint8_t	u8_0;
		u16_wf	u16_1;
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
}u24_wf;

typedef union 
{	
	uint8_t u8s[4];
	struct
	{
		u16_wf u16L;
		u16_wf u16H;
	}u16s;
	uint32_t u32;
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
}u32_wf;

/************************************************************************/
/* 有符号数                                                             */
/************************************************************************/
typedef union
{	
	struct
	{
		uint8_t s8_l;
		signed char	u8_h;
	}s8s;
	short s16;
	uint16_t u16;
}sshort_wf;

typedef union 
{	
	struct
	{
		uint8_t	s8_0;
		uint8_t	u8_1;
		uint8_t	u8_2;
		signed char	s8_3;
	}s8s;
	struct
	{
		u16_wf	u16_l;
		sshort_wf	s16_h;	
	}s16s;
	struct
	{
		uint16_t	u16_l;
		short	s16_h;	
	}s16s1;
	int s32;
	uint32_t u32;
}sint_wf;

#ifdef unsigned64
typedef struct
{	
	uint32_t hi, lo;
}u64;
u64 u64_Init (uint32_t hi, uint32_t lo);
/* Return a u64 value representing LO.  */
u64 u64_lo (uint32_t lo);
u64 u64_hi (uint32_t hi);
uint8_t u64_lt (u64 x, u64 y);
/* Return X & Y.  */
u64 u64_and (u64 x, u64 y);
/* Return X | Y.  */
u64 u64_or (u64 x, u64 y);
/* Return X ^ Y.  */
u64 u64_xor (u64 x, u64 y);
/* Return X + Y.  */
u64 u64_plus (u64 x, uint32_t hi,uint32_t lo);
u64 u64_decrease (u64 x, uint32_t hi,uint32_t lo);
/* Return X << N.  */
u64 u64_shl (u64 x, int n);
/* Return X >> N.  */
u64 u64_shr (u64 x, int n);
u64 u64_lmul(uint32_t multiplier, uint32_t multiplicand);
u64 u64_lmuu64(u64 multiplier, uint32_t multiplicand);
u64 u64_u64muu64(u64 multiplier, uint32_t hi,uint32_t lo);
#endif

#endif


/*-------------------------------------------------------------------------------------------------
;
;end  of  the  file
;
;-------------------------------------------------------------------------------------------------*/

  

