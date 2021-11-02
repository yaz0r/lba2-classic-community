//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_AIL
#define	LIB_AIL

//──────────────────────────────────────────────────────────────────────────
#ifndef	_BUILDING_LIB

#ifdef	YAZ_WIN32

#ifdef	__SW_3R
#pragma library ("NT_AILR.LIB")
#else//	__SW_3R
#pragma library ("NT_AILS.LIB")
#endif//__SW_3R

#else//	YAZ_WIN32

#ifdef	__SW_3R
#pragma library ("DOS_AILR.LIB")
#else//	__SW_3R
#pragma library ("DOS_AILS.LIB")
#endif//__SW_3R

#endif//YAZ_WIN32

#endif//_BUILDING_LIB

//──────────────────────────────────────────────────────────────────────────
#include	<AIL\TIMER.H>
#include	<AIL\COMMON.H>
#include	<AIL\MIDI.H>
#include	<AIL\SAMPLE.H>
#include	<AIL\STREAM.H>
#include	<AIL\MIDDIG.H>
#include	<AIL\CD.H>

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_AIL

//──────────────────────────────────────────────────────────────────────────
