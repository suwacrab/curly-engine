/* keine kamishirasawa SDL subsystem */
/* meant to be paired with fujiwara no mokou */
/* - suwacrab 2020-02-19 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "kbase.h"
#include "mokou.h"

#ifndef KEINE_H
#define KEINE_H

typedef struct
{
	SDL_Surface *window;
	SDL_Surface *mainfb;
	SDL_Color *palette;
	u32 w,h;
	// event vars
	SDL_Event inpevnt;
	bool do_quit;
	// misc vars
	u32 framerate;
	s16 time;
	clock_t last_frame;
} keine;

/*	--	init funcs	--	*/
void keine_init(keine *kami,char *caption,char *icon,u32 w,u32 h);
void keine_initpal(keine *kami,RGBA32 *pal,u32 pallen);

/*	--	load funcs	--	*/
RGBA32 *keine_loadhexpal(char *fname,u32 pallen);

/*	--	blit funcs	--	*/
void keine_mokou(keine *kami,mokou *fuji);

/*	--	event funcs	--	*/
void keine_checkquit(keine *kami);

#endif
