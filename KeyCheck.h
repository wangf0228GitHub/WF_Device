#ifndef __KeyCheck_h__
#define __KeyCheck_h__

typedef union   
{
	struct
	{
		unsigned bReKey:1;
	};
	uint8_t AllFlag;
} _KeyCheckFlags;        // general flags

_KeyCheckFlags KeyCheckFlags;

//用于在检测到按键后，外部程序加入特殊处理
#ifndef KeyCheckExFun
#define KeyCheck_ExFun()
#endif

//#define KeyCheck_ReadKey(x) x=Key1_R;x|=(Key2_R<<1)
#ifndef KeyCheck_ReKeyTick
#define KeyCheck_ReKeyTick 5
#endif
uint8_t KeyTimes;
uint16_t KeyTick;

#ifdef MatrixKeys
extern uint8_t RowKeyValue;
extern uint8_t ColKeyValue;
#define NoKey 0
#define IsKey 1
//#define ReKey 2
#endif
#ifdef BigKeys
extern uint16_t OldKey;
uint16_t KeyCheck(void);
#else
extern uint8_t OldKey;
uint8_t KeyCheck(void);
#endif
#endif // __Key_h__
