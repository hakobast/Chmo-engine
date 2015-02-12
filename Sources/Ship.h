#ifndef SHIP_H
#define SHIP_H

#include "GL_LIBS.h"
#include "GameLogic.h"

class Ship : public GameLogic
{
public:
	GLfloat speed = 13.0f;
	GLfloat rotation = 180.0f;
	void Init();
	void Update();
};

#endif