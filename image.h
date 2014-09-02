#pragma once

class Image {
private:
	SDL_Surface *m_surf;
public:
	SDL_Surface *getSurf();

	void loadBmp(const std::string &path);

	void draw(SDL_Surface *scrn);

	void draw(SDL_Surface *scrn, int x, int y);

	size_t getWidth();

	size_t getHeight();

	SDL_Surface * setSurf (SDL_Surface * surf);

	Image();

	virtual ~Image();
};
