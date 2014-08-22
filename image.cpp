#include "stdafx.h"
#include "image.h"

Image::Image() : m_surf(NULL) {
}

Image::~Image() {
}

void Image::loadBmp(const std::string &path) {
	m_surf = SDL_LoadBMP (path.c_str());
	if (!m_surf) {
		throw std::runtime_error("Can't load texture");
	}
}

SDL_Surface *Image::getSurf() {
	return m_surf;
}

void Image::draw(SDL_Surface *scrn) {
	SDL_BlitSurface(m_surf, NULL, scrn, NULL);
}

size_t Image::getHeight() {
	return (size_t) m_surf->h;
}

size_t Image::getWidth() {
	return (size_t) m_surf->w;
}