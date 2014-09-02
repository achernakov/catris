#include "stdafx.h"
#include "field.h"
#include "config.h"

Field::Field () {
	for (int x = 0; x < FIELD_W; x++) {
		for (int y = 0; y < FIELD_H; y++) {
			m_field[x + y * FIELD_W] = NULL;
		}
	}
}

Field::~Field () {
}

void Field::draw(SDL_Surface *screen) {
	for (int x = 0; x < FIELD_W; x++) {
		for (int y = 0; y < FIELD_H; y++) {
			if (m_field[x + y * FIELD_W]) {
				m_field[x + y * FIELD_W]->draw(screen, x  * SQUARE_SZ + FIELD_OFFSET_X, y * SQUARE_SZ + FIELD_OFFSET_Y);
			}
		}
	}
}

bool Field::isEmpty(int x, int y) const {
	if (m_field[x + y * FIELD_W])
		return false;
	else
		return true;
}

void Field::clipBrick(int x, int y, Image *image) {
	m_field[x + y * FIELD_W] = image;
}