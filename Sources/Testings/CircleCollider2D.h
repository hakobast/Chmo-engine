#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "EngineInclude.h"
#include "Collider2D.h"

class CircleCollider2D : public Collider2D
{
public:
	Vector2 center;
	float radius;
	virtual void Update();
	virtual bool hasCollision(Collider2D* other);
};

#endif