#include "stdafx.h"
#include "brick.h"
#include "helpers.h"

static Image g_textures[Brick::BT_MAX][Brick::BR_MAX][BRICK_SZ * BRICK_SZ];

static const int g_brickShapes[Brick::BT_MAX][BRICK_SZ * BRICK_SZ] = {
		{0, 0, 0, 0,
				0, 0, 0, 0,
				1, 1, 1, 1,
				0, 0, 0, 0},

		{0, 0, 0, 0,
				0, 1, 1, 0,
				1, 1, 0, 0,
				0, 0, 0, 0},

		{0, 0, 0, 0,
				0, 1, 1, 0,
				0, 0, 1, 1,
				0, 0, 0, 0},

		{0, 0, 0, 0,
				0, 1, 0, 0,
				1, 1, 1, 0,
				0, 0, 0, 0},

		{0, 0, 0, 0,
				0, 1, 1, 0,
				0, 1, 1, 0,
				0, 0, 0, 0},

		{0, 0, 0, 0,
				0, 1, 0, 0,
				0, 1, 1, 1,
				0, 0, 0, 0},

		{0, 0, 0, 0,
				0, 0, 1, 0,
				1, 1, 1, 0,
				0, 0, 0, 0}
};

Brick::Brick() {
	m_nextRot = randRot();
	m_nextType = randType();
	m_rot = randRot();
	m_type = randType();
}

Brick::~Brick() {
}

Brick::Type Brick::randType() {
	int r = rand();
	return (Brick::Type) (r % BT_MAX);
}

Brick::Rot Brick::randRot() {
	int r = rand();
	//r = BR_UP;
	return (Brick::Rot) (r % BR_MAX);
}

bool Brick::checkCollision(const Field &field, int x, int y) {
	for (int bx = 0; bx < BRICK_SZ; bx++) {
		for (int by = 0; by < BRICK_SZ; by++) {
			if (m_brick[bx + BRICK_SZ * by].getSurf()) {
				if (	(bx + x < 0) || (bx + x >= FIELD_W) ||
						(by + y < 0) || (by + y >= FIELD_H) ||
						!field.isEmpty(x + bx, y + by)) {
					return true; //has collision
				}
			}
		}
	}
	return false;
}

void Brick::moveLeft(const Field &field) {
	if (!checkCollision(field, m_x - 1, m_y)) {
		m_x--;
	}
}

void Brick::moveRight(const Field &field) {
	if (!checkCollision(field, m_x + 1, m_y)) {
		m_x++;
	}
}

void Brick::fall(Field &field) {
	if (!checkCollision(field, m_x, m_y + 1)) {
		m_y++;
	} else {
		clipBrick(field);
		spawnBrick(field);
	}
}

void Brick::rotate(const Field &field) {
	static Image oldBrick[BRICK_SZ * BRICK_SZ];
	memcpy(oldBrick, m_brick, sizeof(Image) * BRICK_SZ * BRICK_SZ);
	//continue here
	loadBrick(m_type, (Brick::Rot)((m_rot + 1) % BR_MAX));
	if (checkCollision(field, m_x, m_y)) {
		memcpy(m_brick, oldBrick, sizeof(Image) * BRICK_SZ * BRICK_SZ);
	} else {
		m_rot = (Brick::Rot)((m_rot + 1) % BR_MAX);
	}
}

void Brick::clipBrick(Field &field) {
	for (int bx = 0; bx < BRICK_SZ; bx++) {
		for (int by = 0; by < BRICK_SZ; by++) {
			if (m_brick[bx + by * BRICK_SZ].getSurf()) {
				field.clipBrick(m_x + bx, m_y + by, &g_textures[m_type][m_rot][bx + by * BRICK_SZ]);
			}
		}
	}
}

void Brick::spawnBrick(const Field &field) {
	m_type = m_nextType;
	m_rot = m_nextRot;
	m_nextType = randType();
	m_nextRot = randRot();

	loadBrick(m_type, m_rot);

	int firstLine = -1;
	for (int by = 0; by < BRICK_SZ; by++) {
		for (int bx = 0; bx < BRICK_SZ; bx++) {
			if (m_brick[bx + by * BRICK_SZ].getSurf()) {
				firstLine = by;
				break;
			}
		}
		if (firstLine != -1) {
			break;
		}
	}

	bool placeFound = false;
	int xpos;
	for (xpos = FIELD_W / 2;
		 	xpos >= 0 && xpos < FIELD_W;
			xpos = (xpos >= FIELD_W) ? (2 * FIELD_W - (xpos + 1)) : (2 * FIELD_W - xpos)) {
		if (!checkCollision(field, xpos, -(firstLine))) {
			placeFound = true;
			break;
		}
	}

	if (placeFound) {
		m_x = xpos;
		m_y = -firstLine;
	} else {
		//LOOSE!
	}
}

void Brick::loadBrick(Type brType, Rot brRot) {
	for (int bx = 0; bx < BRICK_SZ; bx++) {
		for (int by = 0; by < BRICK_SZ; by++) {
			m_brick[bx + BRICK_SZ * by].setSurf(g_textures[brType][brRot][bx + BRICK_SZ * by].getSurf());
		}
	}
}

void Brick::draw(SDL_Surface *scrn) {
	SDL_Rect dst;
	dst.w = dst.h = SQUARE_SZ;
	for (int bx = 0; bx < BRICK_SZ; bx++) {
		for (int by = 0; by < BRICK_SZ; by++) {
			if (m_brick[bx + BRICK_SZ * by].getSurf()) {
				dst.x = (m_x + bx) * SQUARE_SZ + FIELD_OFFSET_X;
				dst.y = (m_y + by) * SQUARE_SZ + FIELD_OFFSET_Y;
				SDL_BlitSurface(m_brick[bx + BRICK_SZ * by].getSurf(), NULL, scrn, &dst);
			}
		}
	}
}

bool LoadBrickImage(Brick::Type brType, const std::string &file) {
	Image brImage;
	brImage.loadBmp(file);
	SDL_Rect src, dst;
	src.h = src.w = dst.h = dst.w = SQUARE_SZ;
	dst.x = dst.y = 0;

	//  UP
	for (int bx = 0; bx < BRICK_SZ; bx++) {
		for (int by = 0; by < BRICK_SZ; by++) {
			if (g_brickShapes[brType][bx + by * BRICK_SZ]) {
				src.x = bx * SQUARE_SZ;
				src.y = by * SQUARE_SZ;
				g_textures[brType][Brick::BR_UP][bx + by * BRICK_SZ].setSurf(CreateSurf(SQUARE_SZ, SQUARE_SZ));
				SDL_BlitSurface(brImage.getSurf(), &src, (g_textures[brType][Brick::BR_UP][bx + by * BRICK_SZ]).getSurf(), NULL);
			} else {
				g_textures[brType][Brick::BR_UP][bx + by * BRICK_SZ].setSurf(NULL);
			}
		}
	}

	//RIGHT
	for (int bx = 0; bx < BRICK_SZ; bx++) {
		for (int by = 0; by < BRICK_SZ; by++) {

			int tx = BRICK_SZ - by - 1;
			int ty = bx;

			if (g_brickShapes[brType][bx + by * BRICK_SZ]) {
				src.x = bx * SQUARE_SZ;
				src.y = by * SQUARE_SZ;
				g_textures[brType][Brick::BR_RIGHT][tx + ty * BRICK_SZ].setSurf(CreateSurf(SQUARE_SZ, SQUARE_SZ));
				SDL_BlitSurface(brImage.getSurf(), &src, (g_textures[brType][Brick::BR_RIGHT][tx + ty * BRICK_SZ]).getSurf(), NULL);
			} else {
				g_textures[brType][Brick::BR_RIGHT][tx + ty * BRICK_SZ].setSurf(NULL);
			}
		}
	}


	//DOWN
	for (int bx = 0; bx < BRICK_SZ; bx++) {
		for (int by = 0; by < BRICK_SZ; by++) {

			int tx = BRICK_SZ - bx - 1;
			int ty = BRICK_SZ - by - 1;

			if (g_brickShapes[brType][bx + by * BRICK_SZ]) {
				src.x = bx * SQUARE_SZ;
				src.y = by * SQUARE_SZ;
				g_textures[brType][Brick::BR_DOWN][tx + ty * BRICK_SZ].setSurf(CreateSurf(SQUARE_SZ, SQUARE_SZ));
				SDL_BlitSurface(brImage.getSurf(), &src, (g_textures[brType][Brick::BR_DOWN][tx + ty * BRICK_SZ]).getSurf(), NULL);
			} else {
				g_textures[brType][Brick::BR_DOWN][tx + ty * BRICK_SZ].setSurf(NULL);
			}
		}
	}

	//LEFT
	for (int bx = 0; bx < BRICK_SZ; bx++) {
		for (int by = 0; by < BRICK_SZ; by++) {

			int tx = by;
			int ty = BRICK_SZ - bx - 1;

			if (g_brickShapes[brType][bx + by * BRICK_SZ]) {
				src.x = bx * SQUARE_SZ;
				src.y = by * SQUARE_SZ;
				g_textures[brType][Brick::BR_LEFT][tx + ty * BRICK_SZ].setSurf(CreateSurf(SQUARE_SZ, SQUARE_SZ));
				SDL_BlitSurface(brImage.getSurf(), &src, (g_textures[brType][Brick::BR_LEFT][tx + ty * BRICK_SZ]).getSurf(), NULL);
			} else {
				g_textures[brType][Brick::BR_LEFT][tx + ty * BRICK_SZ].setSurf(NULL);
			}
		}
	}
}
