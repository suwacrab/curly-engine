#include "kbase.h"
#include "mokou.h"
#include "keine.h"
#include "kosuzu.h"

// standard1 is 320x240
// standard2 is 256x192
// stamdard3 is 160x144
// widescreen1 is 480x270
// widescreen2 is 424x240
// widescreen3 is 384x216
#define WIDTH (112)
#define HEIGHT (160)

// phoenix vars
mokou *fuji = NULL;
keine *kami = NULL;
// img vars
typedef struct { char *fname;mokou *img; } mokou_img;
mokou_img img_bank[] = {
	{ "gfx/testtile.png",NULL },
	{ NULL,NULL }
};
kosuzu font_bank[] = {
	{ 4,6,NULL,"gfx/borefont.png" },
	{ 8,8,NULL,"gfx/bobofont.png" },
	{ 0,0,NULL,NULL,NULL }
};
kosuzu *borefont = &font_bank[0];
kosuzu *bobofont = &font_bank[1];
// misc vars
u32 revs = 0; // revision number
	const u16 fade_p[0x10] = { // LUT for fillp fading.
	0x8000,0x8020,0xA020,0xA0A0,
	0xA4A0,0xA5A0,0xA5A4,0xA5A5,
	0xADA5,0xAFA5,0xAFAD,0xAFAF,
	0xEFAF,0xFFAF,0xFFEF,0xFFFF
};

// funcs
void init_kene();

void update();
void draw();

// main function
int main()
{
	// init
	init_kene();
	
	// main loop
	while( !(kami->do_quit) )
	{
		// updating
		update();
		// drawing
		draw();
		// final blit
		keine_mokou(kami,fuji);
	}
	// exit
	mokou_free(fuji);
	return 0;
}

void init_kene()
{
	// main mokokene setup
	kami = malloc(sizeof(keine));
	fuji = malloc(sizeof(mokou));
	keine_init(kami,"mokokene engine",NULL,WIDTH,HEIGHT);
	mokou_init(fuji,WIDTH,HEIGHT);
	// palette copying
	RGBA32 *famipal = keine_loadhexpal("pals/famicube.hex",0x40);
	keine_initpal(kami,famipal,0x40);
	free(famipal);
	// image loading
	u32 imgid = 0;
	while(img_bank[imgid].fname != NULL)
	{
		mokou_img *curimg = &img_bank[imgid]; // the current image struct
		curimg->img = malloc(sizeof(mokou)); // mallocate it's image...
		mokou_loadimg(curimg->img,kami->mainfb,curimg->fname); // then load using keine's fb.
		printf("loaded img '%s'! [ID: %02X]\n",curimg->fname,imgid);
		imgid++;
	}
	// font loading
	u32 fontid = 0;
	while(font_bank[fontid].fname != NULL)
	{
		kosuzu *curfont = &font_bank[fontid]; // current font struct
		kosuzu_init(curfont,kami->mainfb,curfont->fname,curfont->w,curfont->h);
		fontid++;
	}
}

void update()
{
	// event handlin
	while( SDL_PollEvent(&kami->inpevnt) )
	{
		keine_checkquit(kami);
	}
}

void draw()
{
	// clearing
	fuji->fillp = 0xFFFF;
	mokou_clear(fuji,7);
}
