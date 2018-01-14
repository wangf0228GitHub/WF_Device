#include "HardwareProfile.h"

#ifndef MatrixKeys

#ifdef BigKeys
uint16_t OldKey;
uint16_t KeyCheck(void)
#else
uint8_t OldKey;
uint8_t KeyCheck(void)
#endif
{
#ifdef BigKeys
	uint16_t x,key;
#else
	uint8_t x,key;
#endif	
	KeyCheck_ReadKey(key);	
	if(key==KeyCheck_NoKey)
	{
		OldKey=KeyCheck_NoKey;
		return KeyCheck_NoKey;
	}
	__delay_ms(20);
	KeyCheck_ReadKey(x);	
	if(x!=key)
	{
		OldKey=KeyCheck_NoKey;
		return KeyCheck_NoKey;
	}
	if(key==OldKey)//之前已经按过按键了，属于重复触发
	{
		if(!KeyCheckFlags.bReKey)//不允许重复触发
			return KeyCheck_NoKey;
			
		if(GetDeltaTick(KeyTick)>KeyCheck_ReKeyTick)//允许重复触发的需间隔600ms
		{
			KeyTick=SystemTick;
			KeyTimes++;
			return key;
		}
		else
		{
#ifdef KeyCheck_ReKey
			return KeyCheck_ReKey;
#else
			return KeyCheck_NoKey;
#endif
		}			
	}
	else
	{
		KeyTick=SystemTick;
		OldKey=key;
		KeyTimes=0;
		KeyCheckFlags.bReKey=0;
		return key;
	}
}
#else
uint8_t RowKeyValue;
uint8_t ColKeyValue;
uint8_t KeyCheck(void)
{
	uint8_t x,row,col;	
	KeyCheck_SetRow();
	__delay_ms(1);
	KeyCheck_ReadRow(row);	
	if(row==RowNoKey)
	{
		RowKeyValue=0;
		ColKeyValue=0;
		return 0;
	}
	__delay_ms(20);
	KeyCheck_ReadRow(x);	
	if(row!=x)
	{
		RowKeyValue=0;
		ColKeyValue=0;
		return 0;
	}
	KeyCheck_SetCol();
	__delay_ms(1);
	KeyCheck_ReadCol(col);
	if(col==ColNoKey)
	{
		RowKeyValue=0;
		ColKeyValue=0;
		return 0;
	}
	__delay_ms(20);		
	KeyCheck_ReadCol(x);
	if(col!=x)
	{
		RowKeyValue=0;
		ColKeyValue=0;
		return 0;
	}
	if(ColKeyValue==col && RowKeyValue==row)//之前已经按过按键了，属于重复触发
	{
		if(!KeyCheckFlags.bReKey)//不允许重复触发
			return 0;
		if(SystemTick-KeyTick>KeyCheck_ReKeyTick)//允许重复触发的需间隔600ms
		{
			KeyTick=SystemTick;
			KeyTimes++;
			KeyCheck_ExFun();
			return 1;
		}
		else 
#ifdef ReKey
			return 2;
#else
			return 0;
#endif
	}
	else
	{
		KeyTick=SystemTick;
		ColKeyValue=col;
		RowKeyValue=row;
		KeyTimes=0;
		KeyCheckFlags.bReKey=0;
		KeyCheck_ExFun();
		return 1;
	}
}
#endif



