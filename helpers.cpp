#include "stdafx.h"
#include "helpers.h"

SDL_Surface *CreateSurf(int width, int height) {

	SDL_Surface *surface;
	Uint32 rmask, gmask, bmask, amask;
	SDL_Rect rct;
	rct.x = rct.y = 0;
	rct.h = height;
	rct.w = width;

/* SDL interprets each pixel as a 32-bit number, so our masks must depend
   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
			rmask, gmask, bmask, amask);
	if (surface == NULL) {
		throw std::runtime_error("Surface creation just fucked up");
	}

	//SDL_FillRect(surface, &rct, SDL_MapRGBA(surface->format, 0, 0, 0, 255));
	FormatAlpha(surface);


	return surface;
}

void FormatAlpha (SDL_Surface * & surf) {
	SDL_Surface * tmp = SDL_DisplayFormatAlpha(surf);
	if (!tmp) {
		throw std::runtime_error("Can't set alpha format");
	}
	SDL_FreeSurface(surf);
	surf = tmp;
}
