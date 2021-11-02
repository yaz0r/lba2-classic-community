//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_ANIM
#define	LIB_ANIM

#define STATUS_FRAME 1
#define STATUS_LAST 2
#define STATUS_CHANGE 4
#define STATUS_BODY 8

typedef	unsigned	char		U8	;
typedef	signed		char		S8	;
typedef	unsigned	short		U16	;
typedef	signed		short		S16	;
typedef	unsigned	long		U32	;
typedef	signed		long		S32	;

extern "C" {
	extern void* (*TransFctAnim)(S32 index);
};

//──────────────────────────────────────────────────────────────────────────
#ifndef	_BUILDING_LIB

#ifdef	YAZ_WIN32

#ifdef	__SW_3R
#pragma library ("NT_ANIR.LIB")
#else//	__SW_3R
#pragma library ("NT_ANIS.LIB")
#endif//__SW_3R

#else//	YAZ_WIN32

#ifdef	__SW_3R
#pragma library ("DOS_ANIR.LIB")
#else//	__SW_3R
#pragma library ("DOS_ANIS.LIB")
#endif//__SW_3R

#endif//YAZ_WIN32

#endif//_BUILDING_LIB

//──────────────────────────────────────────────────────────────────────────
#define	FLAG_FRAME		1
#define	FLAG_LAST_FRAME		2
#define	FLAG_CHANGE		4
#define	FLAG_BODY		8

//──────────────────────────────────────────────────────────────────────────
#define	INFO_ANIM		2	// ??????

//──────────────────────────────────────────────────────────────────────────
#include	<OBJECT.H>

//──────────────────────────────────────────────────────────────────────────
#include	<ANIM\ANIM.H>
#include	<ANIM\BODY.H>
#include	<ANIM\CLEAR.H>
#include	<ANIM\FRAME.H>
#include	<ANIM\INTANIM.H>
#include	<ANIM\INTERDEP.H>
#include	<ANIM\INTFRAME.H>
#include	<ANIM\LIBINIT.H>
#include	<ANIM\STOFRAME.H>
#include	<ANIM\TEXTURE.H>

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_ANIM

//──────────────────────────────────────────────────────────────────────────
