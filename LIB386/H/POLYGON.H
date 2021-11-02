//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_POLYGON
#define	LIB_POLYGON

//──────────────────────────────────────────────────────────────────────────
#ifndef	_BUILDING_LIB

#ifdef	YAZ_WIN32

#ifdef	cedric
#pragma library ("F:\PROJET\LIB386\POL_WORK\NT_POLY.LIB")
#else
#pragma library ("NT_POLY.LIB")
#endif



#else//	YAZ_WIN32

#ifdef	cedric
#pragma library ("F:\PROJET\LIB386\POL_WORK\DOS_POLY.LIB")
#else
#pragma library ("DOS_POLY.LIB")
#endif

#endif//YAZ_WIN32

#endif//_BUILDING_LIB

//──────────────────────────────────────────────────────────────────────────
#include <SYSTEM\ADELINE.H>

//──────────────────────────────────────────────────────────────────────────
#include <POLYGON\POLY.H>
#include <POLYGON\TESTVUE.H>
#include <POLYGON\CLIPPERZ.H>

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_POLYGON

//──────────────────────────────────────────────────────────────────────────
