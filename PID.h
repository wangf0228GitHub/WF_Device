#ifndef __PID_h__
#define __PID_h__

//#define PID_PShift 1
//#define PID_IShift 1
//#define PID_DShift 1
//
//#define PID_DeltaRef 5
//#define PID_BigError 50
// #ifdef PID_Debug
// uint8_t PIDDebug[100];
// #endif
typedef union
{	
	uint8_t AllChar[13];
	struct
	{
		uint16_t Ref;
		uint16_t FeedBack;
		signed int PreError;//前一次误差, Ref - FeedBack 
		signed int PreErrorSum;//之前的误差和;
		signed char Kp;			//速度PID，Ka = Kp 
		signed char Ki;			//速度PID，Kb = ( T / Ti ) 
		signed char Kd;			//速度PID，kc =  ( Td / T ) 
		signed int Out;		//转速电机控制输出值 
		uint16_t DeltaRef;//允许偏差范围
		uint16_t BigError;//遇限削弱积分参数
	};	
}_PIDParam;
_PIDParam PIDParam;
uint8_t PIDCalc(void);
void PID_Init(void);

#ifdef PID2
_PIDParam PID2Param;
uint8_t PID2Calc(void);
void PID2_Init(void);
#endif
#endif
