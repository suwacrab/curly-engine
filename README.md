# curly engine
this is a small,crappy framework for handling image drawing with 256-color images.

## subsystems:
* mokou (mokou.h, mokou.c)
	* the main framebuffer subsystem, used for loading images & blitting.
	* features the ability to use fill patterns similar to PICO-8, which allow for custom dithering.
* keine (keine.h, keine.c)
	* SDL handler subsystem, used for simplifying the process of interfacing with SDL.
	* can load Grafx2 .hex palettes, and blit mokou framebuffers directly to SDL.
* kosuzu (kosuzu.h, kosuzu.c)
	* font handler subsystem, used for blitting ascii fonts loaded with mokou.
	* can load monospace fonts of varying widths and heights, as long as they are in a 16x16-character grid.

