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

	void adoptAlpha ();

	SDL_Surface * setSurf (SDL_Surface * surf);

	operator SDL_Surface * ();

	Image & operator = (SDL_Surface * surf);

	Image & operator = (const Image & surf);

	Image();

	Image (SDL_Surface * surf);

	virtual ~Image();
};
