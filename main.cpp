#include "stdafx.h"
#include "image.h"
#include "helpers.h"
#include "field.h"
#include "brick.h"

static SDL_Surface *Screen;
static Image Background;
static Field GameField;
static Brick FallingBrick;
static SDL_Event EventFall;
static SDL_TimerID TimerFall;

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

void loadResources () {
	Background.loadBmp("art/back.png");
	LoadBrickImage(Brick::BT_LINE, "art/line.png");
	LoadBrickImage(Brick::BT_CUBE, "art/sq.png");
	LoadBrickImage(Brick::BT_LGAMMA, "art/G-right.png");
	LoadBrickImage(Brick::BT_RGAMMA, "art/G-left.png");
	LoadBrickImage(Brick::BT_SNL, "art/E.png");
	LoadBrickImage(Brick::BT_SNR, "art/L.png");
	LoadBrickImage(Brick::BT_T, "art/i.png");
	FallingBrick.spawnBrick(GameField);
}

Uint32 SDLCALL FallCallback (Uint32 interval, void *param) {
	EventFall.type = SDL_USEREVENT;
	SDL_PushEvent(&EventFall);
}

int main(int argc, char **argv) {
	bool quitState = false;


	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		throw std::runtime_error("Can't init PNG loading");
	}
	srand(time(NULL));

	Screen = SDL_SetVideoMode(FIELD_IMG_W, FIELD_IMG_H, 32, SDL_SWSURFACE);
	loadResources();
	TimerFall = SDL_AddTimer(500, FallCallback, NULL);

	SDL_Event ev;

	while (!quitState && SDL_WaitEvent(&ev)) {
		slock();

		//Draw here
		Background.draw(Screen);
		GameField.draw(Screen);
		FallingBrick.draw(Screen);

		SDL_Flip(Screen);
		sulock();


		switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.sym) {
					case SDLK_ESCAPE:
						quitState = true;
						break;
					case SDLK_r:
						FallingBrick.rotate(GameField);
						break;
					case SDLK_RIGHT:
						FallingBrick.moveRight(GameField);
						break;
					case SDLK_LEFT:
						FallingBrick.moveLeft(GameField);
						break;
					case SDLK_DOWN:
						FallingBrick.fall(GameField);
						break;
				}
				break;
			case SDL_QUIT:
				quitState = true;
				break;
			case SDL_USEREVENT:
				FallingBrick.fall(GameField);
				TimerFall = SDL_AddTimer(500, FallCallback, NULL);
				break;
		}
	}

	SDL_Quit();
	return 0;
}

