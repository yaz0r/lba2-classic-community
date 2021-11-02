#include	<system\adeline.h>
#include	<system\exit.h>
#include	<system\initimer.h>
#include	<system\timerwin.h> //yaz

#include	<ail\timer.h>

//████████████████████████████████████████████████████████████████████████████
VOID_FUNC	ClearAIL;

//████████████████████████████████████████████████████████████████████████████
void	InitAIL()
{
	//AIL_startup()	;

	RegisterInitClear( InitAIL, ClearAIL ) ;
}

//████████████████████████████████████████████████████████████████████████████
void	ClearAIL()
{
	//AIL_shutdown()	;
}

//████████████████████████████████████████████████████████████████████████████
#ifndef	_WIN32

//████████████████████████████████████████████████████████████████████████████
S32	InitTimerAIL()
{
	HTIMER  HandleTimer ;

	LockVMMTimer();
	HandleTimer = AIL_register_timer( (AILTIMERCB)NewProc08 ) ;
	if (HandleTimer == -1)
	{
		return FALSE ;
	}

	AIL_set_timer_frequency( HandleTimer, 200 ) ;
	AIL_start_timer( HandleTimer ) ;

	RegisterInitClear( (VOID_FUNC *)InitTimerAIL, NULL ) ;

	return TRUE;
}

//████████████████████████████████████████████████████████████████████████████
#endif//_WIN32

//████████████████████████████████████████████████████████████████████████████
