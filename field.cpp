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

void Field::swipeLines() {
	bool removed = true;
	while (removed) {
		removed = false;
		for (int y = FIELD_H - 1; y >= 0; y--) {
			bool fullLine = true;
			for (int x = 0; x < FIELD_W; x++) {
				if (!m_field[x + y * FIELD_W]) {
					fullLine = false;
					break;
				}
			}
			if (fullLine) {
				removed = true;
				for (int line = y; line > 0; line--) {
					for (int x = 0; x < FIELD_W; x++) {
						m_field[x + line * FIELD_W] = m_field[x + (line - 1) * FIELD_W];
					}
				}
				for (int x = 0; x < FIELD_W; x++) {
					m_field[x] = NULL;
				}

			}
		}
	}
}

bool Field::checkTopLine() {
	for (int x = 0; x < FIELD_W; x++) {
		if (m_field[x]) {
			return false;
		}
	}
	return true;
}