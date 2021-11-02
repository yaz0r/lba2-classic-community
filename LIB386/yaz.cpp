#pragma pack(8)
#include <Windows.h>
#pragma pack(1)
#include "system.h"
#include "svga.h"
#include <sdl.h>
#include <math.h>


void 	*Phys			;
void	*Log			;
void	*Screen			;
U32	ModeResX		;
U32	ModeResY		;
U32	ModeMemory		;
U32	BytesScanLine		;
U32	TabOffLine[MAX_SCREEN_Y_RES]		;
U32	TabOffPhysLine[MAX_SCREEN_Y_RES]	;

extern S32	LibMouseXDep, LibMouseYDep;

extern "C" {

	void Old_PM15_Sel()
	{

	}

S32	AdjustSpeedAngle(S32 speed, S32 start, S32 end)
{
	S32 returnValue;
	__asm {
		pusha
		mov ebx, speed
		mov ecx, start
		mov edx, end

		xor eax, eax
		and	ecx, 4095
		and	edx, 4095
		sub	edx, ecx
		jz	ok
		mov	eax, ebx
		jns	skip	
		neg	edx
		neg	eax
		skip:	cmp	edx, 2048
		jl      ok
		chg:	neg	eax
ok:
		mov returnValue, eax
		popa
	}
	return returnValue;
	/*
#pragma aux AdjustSpeedAngle	=       	\
	"	xor	eax, eax	"		\
	"	and	ecx, 4095	"		\
	"	and	edx, 4095	"		\
	"	sub	edx, ecx	"		\
	"	jz	ok		"		\
	"	mov	eax, ebx	"		\
	"	jns	skip		"		\
	"	neg	edx		"		\
	"	neg	eax		"		\
	"skip:	cmp	edx, 2048	"		\
	"	jl      ok		"		\
	"chg:	neg	eax		"		\
	"ok:				"		\
	parm    caller  [ebx] [ecx] [edx]	\
	modify	exact	[ecx edx]		\
	value		[eax]
	*/
}

void VirtualLinearFirst()
{

}

U32 VESAMode;

S32   cdecl AIL_vmm_lock         (void  *start, U32 size)
{
	return 0;
}
S32   cdecl AIL_vmm_unlock       (void  *start, U32 size)
{
	return 0;
}

int OpenCD(char* name)
{
	return 'D';
}

int PlayCD(int)
{
	return 0;
}

int StopCD()
{
	return 0;
}

int PauseCD()
{
	return 0;
}

int ResumeCD()
{
	return 0;
}

int GetVolumeCD()
{
	return 0;
}

void ChangeVolumeCD(int)
{

}

void	*SmartMalloc(S32 size)
{
	return malloc(size);
}


bool IsCDPlaying()
{
	return false;
}

void AIL_shutdown                  (void)
{

}


void EndVESA()
{

}

extern "C" {
int _VirtualProtect(LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD flNewProtect,
	PDWORD lpflOldProtect,
	DWORD dummy)
{
	DWORD oldProtect = 0;
	VirtualProtect(lpAddress, dwSize, flNewProtect, &oldProtect);

	return 0;
}
}

S32		INV64(S32 a)
{
	S32 result;

	__asm{
		pusha
		mov ebx, a
		mov eax, 80000000h
		xor edx, edx
		idiv ebx
		mov result, eax
		popa
	}
	return result;
}

void	InitKeyboard()
{

}

int GetHDFreeSize()
{
	return 10000;
}

void    ManageEvents()
{
	SDL_PumpEvents();
	{
		SDL_Event event;

		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
			case SDL_MOUSEMOTION:
				MouseX = event.motion.x;
				MouseY = event.motion.y;

				LibMouseXDep = event.motion.xrel;
				LibMouseYDep = event.motion.yrel;

				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == 1)
				{
					Click |= 1;
				}
				if(event.button.button == 3)
				{
					Click |= 2;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == 1)
				{
					Click &= ~1;
				}
				if(event.button.button == 3)
				{
					Click &= ~2;
				}
				break;
			case SDL_QUIT:
				exit(0);
			}
		}
	}

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	Key = 0;
	for(int keyIndex=0; keyIndex<SDL_NUM_SCANCODES; keyIndex++)
	{
		if(keystate[keyIndex])
		{
			Key = keyIndex;
			break;
		}
	}

	memset(TabKeys, 0, 256);

	for(int keyIndex=0; keyIndex<SDL_NUM_SCANCODES; keyIndex++)
	{
		if(keystate[keyIndex])
		{
			TabKeys[KeyIndex(keyIndex)] |= KeyBit(keyIndex);
		}
	}

	//GetKeyboardState(TabKeys);
}

U32 Delete(char* name)
{
	return 0;
}

U32	AvailableMem()
{
	return 1000000;
}

S32 GetDeltaAccMove(S32 *acc)
{
	S32 returnValue;

	__asm {
		pusha
		mov ebx, acc
		mov     ecx, 1000
		mov     eax, [ebx]
		cmp	eax, ecx
		jge	ok
		cmp	eax, -1000
		jg	skip
ok:    mov     edx, eax
	   sar     edx, 31
	   idiv    ecx
	   mov     [ebx], edx
	   jmp	end
skip:	xor	eax, eax
end:	
		mov returnValue, eax
			popa
	}

	return returnValue;
}

#undef Switch_Fillers
extern	void	Switch_Fillers(U32 Bank)	;

void Switch_Fillers_C(U32 Bank)
{
	__asm{
		pusha
		mov eax, Bank
		call Switch_Fillers
		popa
	}
}

typedef	void (Func_LongRotatePoint)(void *Mat, S32 x, S32 y, S32 z) ;
extern	Func_LongRotatePoint	*LongRotatePoint	;

extern int MatriceWorld;

void LongWorldRotatePoint_C(S32 x, S32 y, S32 z)
{
	__asm {
		pusha
		mov esi, offset MatriceWorld
		mov eax, x
		mov ebx, y
		mov ecx, z
		call LongRotatePoint
		popa
	}
}

#undef Fill_Poly
S32	Fill_PolyMMX(S32 Type_Poly, S32 Color_Poly,
	S32 Nb_Points, Struc_Point *Ptr_Points);

S32	Fill_Poly_C(S32 Type_Poly, S32 Color_Poly,
	S32 Nb_Points, Struc_Point *Ptr_Points)
{
	S32 returnValue;
	__asm {
		pusha
		mov eax, Type_Poly
		mov ebx, Color_Poly
		mov ecx, Nb_Points
		mov esi, Ptr_Points
		call Fill_PolyMMX
		mov returnValue, eax
		popa
	}

	return returnValue;
}

#undef LongProjectPoint
typedef	S32 (Func_LongProjectPoint)(S32 x, S32 y, S32 z)	;
extern	Func_LongProjectPoint	*LongProjectPoint	;
 
S32 LongProjectPoint_C(S32 x, S32 y, S32 z)
{
	S32 result;
	__asm {
		pusha
		mov eax, x
		mov ebx, y
		mov ecx, z
		call LongProjectPoint
		mov result, eax
		popa
	}

	return result;
}

typedef	void (Func_RotatePoint)(void *Mat, S32 x, S32 y, S32 z) ;
extern	Func_RotatePoint	*RotatePoint	;

void RotatePoint_C(void *Mat, S32 x, S32 y, S32 z)
{
	__asm {
		pusha
		mov esi, Mat
		mov eax, x
		mov ebx, y
		mov ecx, z
		call RotatePoint
		popa
	}
}

} // "C"



int drive = 0;

void _dos_getdrive(unsigned int* outDriveLetter)
{
	*outDriveLetter = drive;
}

void _dos_setdrive(S32 driveLetter,unsigned int*)
{
	drive = driveLetter;
}

U32 _dos_findfirst( char* name, int, find_t* structFind)
{
	structFind->_h = FindFirstFile(name, &structFind->_find);

	if(structFind->_h != INVALID_HANDLE_VALUE)
	{
		strcpy(structFind->name, structFind->_find.cFileName);

		structFind->attrib = 0;
		if(structFind->_find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			structFind->attrib |= _A_SUBDIR;
		}

		return 0;
	}
	return -1;
}

U32 _dos_findnext(find_t* structFind)
{
	if(FindNextFile(structFind->_h, &structFind->_find))
	{
		strcpy(structFind->name, structFind->_find.cFileName);

		structFind->attrib = 0;
		if(structFind->_find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			structFind->attrib |= _A_SUBDIR;
		}

		return 0;
	}
	FindClose(structFind->_h);
	return -1;
}

void delay(int)
{

}

S32		MULDIV64( S32 x, S32 mul, S32 div ) // (x*mul)/div
{
	S32 result;
	__asm{
		pusha
		mov eax, x
		mov edx, mul
		mov ecx, div
		imul edx
		idiv ecx
		mov result, eax
		popa
	}
	return result;
	/*
#pragma	aux	MULDIV64= 				\
	"	imul	edx		"	\
	"	idiv	ecx		"	\
	parm	caller 	[eax] [edx] [ecx]	\
	modify	exact	[eax edx]
	*/
}

S32	Min3( S32 a, S32 b, S32 c )
{
	return min(min(a,b),c);
}
S32	Max3( S32 a, S32 b, S32 c )
{
	return max(max(a,b),c);
}

extern "C" {
	S32 AsciiMode;
	S32 Key;
	U8	TabKeys[256+16*8]	;

	S32 lastReturnedAscii = 0;

	S32 GetAscii(void)
	{
		S32 asciiValue = 0;
		ManageEvents();

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		for(int keyIndex=0; keyIndex<SDL_NUM_SCANCODES; keyIndex++)
		{
			if(keystate[keyIndex])
			{
				asciiValue = SDL_GetKeyFromScancode((SDL_Scancode)keyIndex);

				if(lastReturnedAscii == asciiValue)
					return 0;

				lastReturnedAscii = asciiValue;
				return asciiValue;
			}
		}

		lastReturnedAscii = 0;

		return 0;
	}

	void	ManageKeyboard()
	{
		ManageEvents()	;
	}

	U32	Distance2D(S32 x0, S32 y0, S32 x1, S32 y1)
	{
		S32 dx = x0-x1;
		S32 dy = y0-y1;

		return sqrtl(dx*dx + dy*dy);
	}

	U32	Distance3D(S32 x0, S32 y0, S32 z0, S32 x1, S32 y1, S32 z1)
	{
		S32 dx = x0-x1;
		S32 dy = y0-y1;
		S32 dz = z0-z1;

		return sqrtl(dx*dx + dy*dy + dz*dz);
	}
};

extern "C" {
	void __iob_func()
	{

	}
}

//****************************************************************************
