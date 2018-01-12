#ifndef __PID_h__
#define __PID_h__

//#define PID_PShift 1
//#define PID_IShift 1
//#define PID_DShift 1
//
//#define PID_DeltaRef 5
//#define PID_BigError 50
// #ifdef PID_Debug
// unsigned char PIDDebug[100];
// #endif
typedef union
{	
	unsigned char AllChar[13];
	struct
	{
		unsigned int Ref;
		unsigned int FeedBack;
		signed int PreError;//前一次误差, Ref - FeedBack 
		signed int PreErrorSum;//之前的误差和;
		signed char Kp;			//速度PID，Ka = Kp 
		signed char Ki;			//速度PID，Kb = ( T / Ti ) 
		signed char Kd;			//速度PID，kc =  ( Td / T ) 
		signed int Out;		//转速电机控制输出值 
		unsigned int DeltaRef;//允许偏差范围
		unsigned int BigError;//遇限削弱积分参数
	};	
}_PIDParam;
_PIDParam PIDParam;
unsigned char PIDCalc(void);
void PID_Init(void);

#ifdef PID2
_PIDParam PID2Param;
unsigned char PID2Calc(void);
void PID2_Init(void);
#endif
#endif
