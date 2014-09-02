#pragma once

#include "image.h"
#include "config.h"



class Field {
public:
	Field();

	virtual ~Field();

	void draw (SDL_Surface * screen);
	bool isEmpty (int x, int y) const;

	void clipBrick (int x, int y, Image * image);
protected:
private:
	Image * m_field[FIELD_H * FIELD_W];
};