#include "HardwareProfile.h"
#include "PID.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void PID_Init(void)
{
	PIDParam.PreErrorSum=0;
	PIDParam.PreError=0;
}
uint8_t PIDCalc(void) 
{
#ifdef PID_Debug
	char PIDDebug[20];
#endif
	signed int ek,d_error,p,i,d;  
	ek = PIDParam.Ref - PIDParam.FeedBack;	
#ifdef PID_Debug
	sprintf(PIDDebug,"#%d,",PIDParam.Ref);
	PIDDebug_PutString(PIDDebug);
	sprintf(PIDDebug,"%d,",PIDParam.FeedBack);
	PIDDebug_PutString(PIDDebug);
#endif	
	if(abs(ek)>=PIDParam.DeltaRef) 
	{		
		p=PIDParam.Kp *ek;
		p=p>>PID_PShift;
		// 遇限削弱积分法 
		if(abs(ek)<PIDParam.BigError) 
		{
			PIDParam.PreErrorSum+=ek;
			i=PIDParam.Ki*PIDParam.PreErrorSum;
			i=i>>PID_IShift;
		}
		else
			i=0;

		d_error = ek - PIDParam.PreError;// 本次误差与前次误差之差 
		PIDParam.PreError=ek;
		d=PIDParam.Kd*d_error;
		d=d>>PID_DShift;	

		PIDParam.Out=p+i+d;
#ifdef PID_Debug
		sprintf(PIDDebug,"%d,",p);
		PIDDebug_PutString(PIDDebug);
		sprintf(PIDDebug,"%d,",i);
		PIDDebug_PutString(PIDDebug);
		sprintf(PIDDebug,"%d,",d);
		PIDDebug_PutString(PIDDebug);
		sprintf(PIDDebug,"%d@",PIDParam.Out);
		PIDDebug_PutString(PIDDebug);
#endif	
		return 1;
	} 
	else
	{
		PIDParam.PreErrorSum=0;
		PIDParam.PreError=0;
#ifdef PID_Debug
		sprintf(PIDDebug,"0,0,0,0@",PIDParam.Out);
		PIDDebug_PutString(PIDDebug);
#endif	
		return 0;
	}
} 
#ifdef PID2
void PID2_Init(void)
{
	PID2Param.PreErrorSum=0;
	PID2Param.PreError=0;
}
uint8_t PID2Calc(void) 
{
#ifdef PID2_Debug
	char PID2Debug[20];
#endif
	signed int ek,d_error,p,i,d;  
	ek = PID2Param.Ref - PID2Param.FeedBack;	
#ifdef PID2_Debug
	sprintf(PID2Debug,"#%d,",PID2Param.Ref);
	PID2Debug_PutString(PID2Debug);
	sprintf(PID2Debug,"%d,",PID2Param.FeedBack);
	PID2Debug_PutString(PID2Debug);
#endif
	if(abs(ek)>=PID2Param.DeltaRef) 
	{		
		p=PID2Param.Kp *ek;
		p=p>>PID2_PShift;
		// 遇限削弱积分法 
		if  (abs(ek)<PID2Param.BigError) 
		{
			PID2Param.PreErrorSum+=ek;
			i=PID2Param.Ki*PID2Param.PreErrorSum;
			i=i>>PID2_IShift;
		}
		else
			i=0;

		d_error = ek - PID2Param.PreError;// 本次误差与前次误差之差 
		PID2Param.PreError=ek;
		d=PID2Param.Kd*d_error;
		d=d>>PID2_DShift;	

		PID2Param.Out=p+i+d;
#ifdef PID2_Debug
		sprintf(PID2Debug,"%d,",p);
		PID2Debug_PutString(PID2Debug);
		sprintf(PID2Debug,"%d,",i);
		PID2Debug_PutString(PID2Debug);
		sprintf(PID2Debug,"%d,",d);
		PID2Debug_PutString(PID2Debug);
		sprintf(PID2Debug,"%d@",PID2Param.Out);
		PID2Debug_PutString(PID2Debug);
#endif	
		return 1;
	} 
	else
	{
		PID2Param.PreErrorSum=0;
		PID2Param.PreError=0;
#ifdef PID2_Debug
		sprintf(PID2Debug,"0,0,0,0@",PID2Param.Out);
		PID2Debug_PutString(PID2Debug);
#endif
		return 0;
	}
} 
#endif
