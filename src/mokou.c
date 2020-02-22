#include "kbase.h"
#include "mokou.h"

/*	--	main funcs	--	*/
void mokou_init(mokou *fujiwara,u32 w,u32 h) // init empty framebuffer
{
	fujiwara->w = w;
	fujiwara->h = h;
	fujiwara->fillp = 0xFFFF;
	size_t fb_size = sizeof(u8)*(w*h);
	fujiwara->fb = malloc(fb_size);
}
void mokou_free(mokou *fuji) // free framebuffer
{ free(fuji->fb); }
void mokou_clear(mokou *fuji,u32 pix) // clear framebuffer
{ memset(fuji->fb,pix&0xFF,sizeof(u8)*(fuji->w*fuji->h)); }

/*	--	loading funcs	--	*/
void mokou_loadimg(mokou *fuji,SDL_Surface *sdl_fb,char *fname)
{
	// loading, convertin
	SDL_Surface *fimg = NULL;
	fimg = IMG_Load(fname);
	printf("loaded image '%s'! (%d)\n",fname,fimg==NULL);
	u32 w = fimg->w;
	u32 h = fimg->h;
	fimg = SDL_ConvertSurface(fimg,sdl_fb->format,0);
	// copying, freeing
	mokou_init(fuji,w,h); // fuji framebuffer setup
	memcpy(fuji->fb,fimg->pixels,sizeof(pix8)*(w*h)); // image copyin
	SDL_FreeSurface(fimg);
}

/*	--	pixel funcs	--	*/
pix8 *mokou_pread(mokou *fuji,u32 x,u32 y)
{	return fuji->fb + (x+(y*fuji->w)); }
pix8 mokou_pget(mokou *fuji,u32 x,u32 y)
{ return *mokou_pread(fuji,x,y); }
void mokou_pset(mokou *fuji,u32 x,u32 y,u8 pix)
{
	u32 ind = (x&3)+((y&3)*4);
	u32 pat_pix = (fuji->fillp>>ind)&1;
	if((pix!=0) && in_range(x,0,fuji->w-1) && in_range(y,0,fuji->h-1))
		if(pat_pix) (*mokou_pread(fuji,x,y)) = pix;
}

/*	--	rect funcs	--	*/
void mokou_rect(mokou *fuji,s32 x,s32 y,s32 w,s32 h,u32 pix)
{
	for(s32 ly=y; ly<(y+h); ly++)
		for(s32 lx=x; lx<(x+w); lx++)
			mokou_pset(fuji,lx,ly,pix);
}

/*	--	img funcs	--	*/
void mokou_blit(mokou *src,SDL_Rect *srcrect,mokou *dst,u32 dx,u32 dy)
{
	u32 x,y,w,h;
	SDL_Rect blitrect = { 0,0,src->w,src->h };
	if(srcrect == NULL) srcrect = &blitrect;
	x = srcrect->x; y = srcrect->y;
	w = srcrect->w; h = srcrect->h;

	for(u32 oy=0; oy<h; oy++)

	{
		u32 ly = oy+dy;
		for(u32 ox=0; ox<w; ox++)
		{
			u32 lx = ox+dx;
			mokou_pset(dst,dx+ox,dy+oy,mokou_pget(src,ox+x,oy+y));
			if(lx>dst->w) break;
		}
		if(ly>dst->h) break;
	}
}


