;*══════════════════════════════════════════════════════════════════════════*
		.386p

		.model SMALL, C

;*══════════════════════════════════════════════════════════════════════════*
		.DATA

;*══════════════════════════════════════════════════════════════════════════*
		public	C LongProjectList
LongProjectList	dd	offset LongProjectListInit

ASSUME ds:SEG temp

;*══════════════════════════════════════════════════════════════════════════*
temp		dd	?

;*══════════════════════════════════════════════════════════════════════════*
		extrn	C	LongProjectList3D:DWORD

;*══════════════════════════════════════════════════════════════════════════*
		.CODE

;*══════════════════════════════════════════════════════════════════════════*

		public	C	LongProjectListInit

;*══════════════════════════════════════════════════════════════════════════*
LongProjectListInit proc

		mov	[temp], eax	; save eax
		pop	eax		; get return address

		xchg	[temp], eax	; restore eax and save return address

		call	[LongProjectList3D]

		push	eax
		mov	eax, [LongProjectList3D]

		mov	[LongProjectList], eax
		pop	eax

		jmp	[temp]		; return

LongProjectListInit endp

;*══════════════════════════════════════════════════════════════════════════*
;		The
		END
