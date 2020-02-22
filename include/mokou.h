/*	fujiwara no mokou framebuffer subsystem */
/*	meant to be paired with keine kamishirasawa */
/*	suwacrab 2020-02-17 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "kbase.h"

#ifndef FUJI_H
#define FUJI_H
/*	--	structs	--	*/
typedef u8 pix8;
typedef struct
{
	pix8 *fb;
	u32 w,h;
	u16 fillp;
} mokou;

/*	--	main funcs	--	*/
extern void mokou_init(mokou *fuji,u32 w,u32 h);
extern void mokou_free(mokou *fuji);
extern void mokou_clear(mokou *fuji,u32 pix);

/*	--	loading funcs	--	*/
extern void mokou_loadimg(mokou *fuji,SDL_Surface *sdl_fb,char *fname);

/*	--	pixel funcs	--	*/
extern pix8 *mokou_pread(mokou *fuji,u32 x,u32 y);
extern pix8 mokou_pget(mokou *fuji,u32 x,u32 y);
extern void mokou_pset(mokou *fuji,u32 x,u32 y,u8 pix);
extern void mokou_pset_fillp(mokou *fuji,u32 x,u32 y,u32 pix,u16 fillp);

/*	--	rect funcs	--	*/
extern void mokou_rect(mokou *fuji,s32 x,s32 y,s32 w,s32 h,u32 pix);

/*	--	img funcs	--	*/
extern void mokou_blit(mokou *src,SDL_Rect *srcrect,mokou *dst,u32 dx,u32 dy);

#endif
