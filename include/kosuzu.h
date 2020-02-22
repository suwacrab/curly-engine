#include "kbase.h"
#include "mokou.h"

#ifndef KOSUZU_H
#define KOSUZU_H

/*	--	structs	--	*/
typedef struct
{
	u32 w,h;
	mokou *fb;
	char *fname;
} kosuzu;

/*	--	init funcs	--	*/
void kosuzu_init(kosuzu *moto,SDL_Surface *sdl_fb,char *fname,u32 w,u32 h);

/*	--	blit funcs	--	*/
void kosuzu_blit(kosuzu *moto,char *text,mokou *dst,u32 x,u32 y,u32 len);

#endif
