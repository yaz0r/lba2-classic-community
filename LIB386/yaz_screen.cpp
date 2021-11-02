#include <svga.h>
#include <system.h>
#include <SDL.h>

SDL_Surface *sdlScreen;
SDL_Window *sdlWindow;
U32 g_pal[256];

S32 InitVESA()
{
	SDL_VideoInit(NULL);
	return 1;
}

S32	DetectInitVESAMode(U32 ResX, U32 ResY, U32 Depth, U32 Memory)
{
	SDL_ShowCursor(false);
    sdlWindow = SDL_CreateWindow("LBA2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ResX, ResY, SDL_WINDOW_SHOWN);
    if ( sdlWindow == NULL ) {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(1);
    }

	sdlScreen = SDL_GetWindowSurface(sdlWindow);
	/*
//    ScreenX = 640;
//    ScreenY = 480;*/

    //ModeX = 640;
    //ModeY = 480;
	/*
    for(U32 i=0; i<480; i++)
    {
        TabOffLine[i] = (U32)(640 * i);
    }*/

	ModeResX	= ResX	;
	ModeResY	= ResY;
	BytesScanLine	= ResX	;

	Phys = malloc(640*480);

	SetPaletteVESA= &SetPaletteVESA1;

	ProcessorSignature.FPU = 1;
	ProcessorSignature.Family = 5;
	ProcessorSignature.Manufacturer = 1;

	return 1;
}

void	CopyBoxF(void *dst, void *src, U32 *TabOffDst, T_BOX *box) 
{
	if(dst == Phys)
	{
		SDL_LockSurface(sdlScreen);

		for(int x=box->x0; x<box->x1; x++)
		{
			for(int y=box->y0; y<box->y1; y++)
			{
				U32* pOut = (U32*)((U8*)sdlScreen->pixels + y*sdlScreen->pitch + x * 4);
				U8 color= *(((U8*)src) + TabOffDst[y] + x);
				
				*pOut = g_pal[color];
			}
		}

		SDL_UnlockSurface(sdlScreen);

		//SDL_UpdateRect(sdlScreen, 0, 0, 639, 479);
		SDL_Rect updateRect;
		updateRect.x = box->x0;
		updateRect.y = box->y0;
		updateRect.w = box->x1-box->x0;
		updateRect.h = box->y1-box->y0;
		SDL_UpdateWindowSurfaceRects(sdlWindow, &updateRect, 1);
	}
	else
	{
		for(int x=box->x0; x<box->x1; x++)
		{
			for(int y=box->y0; y<box->y1; y++)
			{
				*(((U8*)dst) + TabOffDst[y] + x) = *(((U8*)src) + TabOffDst[y] + x);
			}
		}
	}
}

extern "C" {

void VblVESA(void)
{

}

void SetPaletteVESA2(void *pal, S32 start, S32 n)
{

}

void SetPaletteVESA1(void *pal, S32 start, S32 n)
{
	U8 *palette = (U8*)pal;

	for(U32 i=start;i<start+n; i++)
	{
		PalOne(i, palette[i*3+0], palette[i*3+1], palette[i*3+2]);
	}
}

void (*SetPaletteVESA)(void *pal, S32 start, S32 n) = 0;

void	SetPaletteOneVESA(S32 col, S32 red, S32 green, S32 blue)
{
	U32 color = ((U32)0xFF << 24) | ((U32)red << 16) | ((U32)green << 8) | ((U32)blue << 0);

	g_pal[col] = color;
}

void SetPaletteDirect(void *pal, S32 start, S32 n)
{

}

void	PaletteSync( U8 *palette ) 
{
	for(U32 i=0;i<256; i++)
	{
		PalOne(i, palette[i*3+0], palette[i*3+1], palette[i*3+2]);
	}

	SDL_LockSurface(sdlScreen);

	for(U32 x=0; x<640; x++)
	{
		for(U32 y=0; y<480; y++)
		{
			unsigned char color = ((unsigned char*)Log)[y*640 + x];

			U32* pOut = (U32*)((U8*)sdlScreen->pixels + y*sdlScreen->pitch + x * 4);

			*pOut = g_pal[color];
		}
	}

	SDL_UnlockSurface(sdlScreen);

	SDL_UpdateWindowSurface(sdlWindow);
}

void SavePCX(char *,unsigned char *,unsigned long,unsigned long,unsigned char *)
{

}

}