#include "kosuzu.h"

/*	--	init funcs	--	*/
void kosuzu_init(kosuzu *moto,SDL_Surface *sdl_fb,char *fname,u32 w,u32 h)
{
	// load easy vars
	moto->fname = fname;
	moto->w = w;
	moto->h = h;
	moto->fb = NULL;
	// load font image
	moto->fb = malloc(sizeof(mokou));
	mokou_loadimg(moto->fb,sdl_fb,fname);
}

/*	--	blit funcs	--	*/
void kosuzu_blit(kosuzu *moto,char *text,mokou *dst,u32 x,u32 y,u32 len)
{
	mokou *fontfb = moto->fb;
	u32 cx = 0; u32 cy = 0;
	u32 w = moto->w;
	u32 h = moto->h;
	for(u32 i=0; i<len; i++)
	{
		char c = text[i];
		// if it's a newline, reset X and increment Y.
		if(c == '\n')
		{ cx = 0; cy++; }
		// otherwise, insert a character.
		else {
			SDL_Rect textrect = { (c&15)*w,(c>>4)*h,w,h };
			mokou_blit(fontfb,&textrect,dst,x+(cx*w),y+(cy*h));
			cx++;
		}
	}
}

