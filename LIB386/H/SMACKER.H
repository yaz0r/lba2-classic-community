//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_SMACKER
#define	LIB_SMACKER

//──────────────────────────────────────────────────────────────────────────
#ifndef	_BUILDING_LIB

#ifdef	YAZ_WIN32

#pragma library ("SMACKW32.LIB")

#ifdef	__SW_3R
#pragma library ("NT_SMKR.LIB")
#else//	__SW_3R
#pragma library ("NT_SMKS.LIB")
#endif//__SW_3R

#else//	YAZ_WIN32

#pragma library ("SMACK.LIB")

#ifdef	__SW_3R
#pragma library ("DOS_SMKR.LIB")
#else//	__SW_3R
#pragma library ("DOS_SMKS.LIB")
#endif//__SW_3R

#endif//YAZ_WIN32

#endif//_BUILDING_LIB

//──────────────────────────────────────────────────────────────────────────
//#include	<SMACKER\SMACK.H>
// #include	<SMACKER\SMACKER.H>

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_SMACKER

//──────────────────────────────────────────────────────────────────────────
