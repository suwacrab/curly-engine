# curly engine
horrible code incoming
this is a small framework for handling image drawing & font drawing with 256-color images.

## subsystems:
* mokou (mokou.h,mokou.c)
	* the main framebuffer subsystem, used for loading images & blitting.
	* features the ability to use fill patterns similar to PICO-8, which allow for custom dithering.
* keine (keine.h,keine.c)
	* SDL handler subsystem, used for simplifying the process of interfacing with SDL.
	* can load Grafx2 .hex palettes, and blit mokou framebuffers directly to SDL.
