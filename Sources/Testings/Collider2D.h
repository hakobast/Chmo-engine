#ifndef COLLIDER_H
#define COLLIDER_H

#include "../CoreEngine/ChmoEngine.h"

//#define DEBUG_COLLISION

class CircleCollider2D;
class BoxCollider2D;

class Collider2D : public GameLogic
{
public:
	virtual bool HasCollision(Collider2D* other) = 0;
};

#endif