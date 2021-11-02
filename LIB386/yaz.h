#ifndef __YAZ_H__
#define __YAZ_H__
#pragma pack(8)
#include <windows.h>
#pragma pack(1)

#define _MAX_NAME (8+3)

typedef void *HANDLE;

struct find_t
{
	HANDLE _h;
	WIN32_FIND_DATA _find;
	char name[256];
	int attrib;
};

void _dos_getdrive(unsigned int*);
void _dos_setdrive(S32,unsigned int*);
U32 _dos_findfirst( char* , int, find_t* ) ;
U32 _dos_findnext(find_t* ) ;

void delay(int);

#endif // __YAZ_H__