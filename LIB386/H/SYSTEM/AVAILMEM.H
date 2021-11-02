//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_SYSTEM_AVAILMEM
#define LIB_SYSTEM_AVAILMEM

//──────────────────────────────────────────────────────────────────────────
#ifdef	__cplusplus
extern	"C"	{
#endif

//──────────────────────────────────────────────────────────────────────────
extern	U32	AvailableMem()	;

#ifndef	YAZ_WIN32

#pragma aux	AvailableMem		\
	modify	[ebx ecx edx esi edi]

#endif//YAZ_WIN32

//──────────────────────────────────────────────────────────────────────────

#ifdef	__cplusplus
}
#endif

#endif//LIB_SYSTEM_AVAILMEM

//──────────────────────────────────────────────────────────────────────────
