#include "stdafx.h"
#include "image.h"
#include "config.h"


Image::Image() : m_surf(NULL) {
}

Image::~Image() {
}

void Image::loadBmp(const std::string &path) {
	//m_surf = SDL_LoadBMP (path.c_str());

	m_surf = IMG_Load(path.c_str());
	if (!m_surf) {
		throw std::runtime_error("Can't load texture");
	}
}

SDL_Surface *Image::getSurf() {
	return m_surf;
}

void Image::draw(SDL_Surface *scrn) {
	if (m_surf) {
		SDL_BlitSurface(m_surf, NULL, scrn, NULL);
	}
}

void Image::draw(SDL_Surface *scrn, int x, int y) {
	if (m_surf) {
		SDL_Rect dstRect;
		dstRect.h = dstRect.w = SQUARE_SZ;
		dstRect.x = x;
		dstRect.y = y;
		SDL_BlitSurface(m_surf, NULL, scrn, &dstRect);
	}
}

size_t Image::getHeight() {
	return (size_t) m_surf->h;
}

size_t Image::getWidth() {
	return (size_t) m_surf->w;
}

SDL_Surface * Image::setSurf(SDL_Surface *surf) {
	return m_surf = surf;
}