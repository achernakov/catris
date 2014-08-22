#include "stdafx.h"
#include "image.h"

static SDL_Surface *Screen;
static Image Background;

//lock and unlock surface on drawing
void slock() {
	if (SDL_MUSTLOCK(Screen)) {
		if (SDL_LockSurface(Screen) < 0) {
			return;
		}
	}
}

void sulock() {
	if (SDL_MUSTLOCK(Screen)) {
		SDL_UnlockSurface(Screen);
	}
}

int main(int argc, char **argv) {
	bool quitState = false;

	Background.loadBmp("bg.bmp");

	SDL_Init(SDL_INIT_VIDEO);
	Screen = SDL_SetVideoMode(Background.getWidth(), Background.getHeight(), 24, SDL_HWSURFACE | SDL_DOUBLEBUF);


	SDL_Event ev;

	while (!quitState) {
		slock();
		//Draw here
		Background.draw(Screen);
		SDL_Flip(Screen);
		sulock();

		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_KEYDOWN:
					switch (ev.key.keysym.sym) {
						case SDLK_ESCAPE:
							quitState = true;
							break;
					}
					break;
			}
		}
	}

	SDL_Quit();
	return 0;
}

