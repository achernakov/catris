#pragma once

class Image {
private:
	SDL_Surface *m_surf;
public:
	SDL_Surface *getSurf();

	void loadBmp(const std::string &path);

	void draw(SDL_Surface *scrn);

	size_t getWidth();

	size_t getHeight();

	Image();

	virtual ~Image();
};
