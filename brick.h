#pragma once

#include "field.h"
#include "image.h"

class Brick {
public:
	enum Type {BT_LINE, BT_SNL, BT_SNR, BT_T, BT_CUBE, BT_LGAMMA, BT_RGAMMA, BT_MAX};
	enum Rot {BR_UP, BR_RIGHT, BR_DOWN, BR_LEFT, BR_MAX};

	Brick ();

	virtual ~Brick ();

	void fall (Field & field);

	void moveLeft (const Field & field);

	void moveRight (const Field & field);

	void rotate (const Field & field);

	void clipBrick (Field & field);

	void spawnBrick (const Field & field);

	static Type randType ();

	static Rot randRot ();

	bool checkCollision (const Field & field, int x, int y);

	void loadBrick (Type brType, Rot brRot);

	void draw (SDL_Surface * scrn);


protected:
private:

	Type m_type;
	Image m_brick [BRICK_SZ * BRICK_SZ];
	int m_x;
	int m_y;
	Rot m_rot;

	Type m_nextType;
	Rot m_nextRot;

};

bool LoadBrickImage (Brick::Type brType, const std::string & file);
