#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H 

#include <typeinfo>

#include "../Debug/Logger.h"
#include "CircleCollider2D.h"
#include "BoxCollider2D.h"

class CollisionUtils
{
public:
	static bool CircleToCircle(CircleCollider2D* c1, CircleCollider2D* c2);
	static bool BoxToBox(BoxCollider2D* c1, BoxCollider2D* c2);
	static bool CircleToBox(CircleCollider2D* c1, BoxCollider2D* c2);
	static bool IsInersectsWithCollider(Vector2 pos, Vector2 halfSize, Collider2D* coll);
};

inline bool CollisionUtils::CircleToCircle(CircleCollider2D* c1, CircleCollider2D* c2)
{
	static Vector3 v1, v2;
	c1->getTransform()->getPosition(v1);
	c2->getTransform()->getPosition(v2);
	v1.x += c1->center.x;
	v1.y += c1->center.y;

	v2.x += c2->center.x;
	v2.y += c2->center.y;

	return (v1 - v2).sqrmagnitude() < (c1->radius + c2->radius)*(c1->radius + c2->radius);
}

inline bool CollisionUtils::BoxToBox(BoxCollider2D* c1, BoxCollider2D* c2)
{
	static Vector3 v1, v2;
	c1->getTransform()->getPosition(v1);
	c2->getTransform()->getPosition(v2);
	v1.x += c1->center.x - c1->size.x / 2;
	v1.y += c1->center.y + c1->size.y / 2;
	v1.z = 0;

	v2.x += c2->center.x - c2->size.x/2;
	v2.y += c2->center.y + c2->size.y/2;
	v2.z = 0;

	return v1.x < v2.x + c2->size.x &&
		v1.x + c1->size.x > v2.x &&
		v1.y > v2.y - c2->size.y &&
		v1.y - c1->size.y < v2.y;
}

inline bool CollisionUtils::CircleToBox(CircleCollider2D* c1, BoxCollider2D* c2)
{
	static Vector3 v1, v2;
	c1->getTransform()->getPosition(v1);
	c2->getTransform()->getPosition(v2);
	v1.x += c1->center.x;
	v1.y += c1->center.y;
	v1.z = 0;

	v2.x += c2->center.x - c2->size.x / 2;
	v2.y += c2->center.y + c2->size.y / 2;
	v2.z = 0;

	if (v1.x < v2.x) v1.x = v2.x;
	if (v1.x > v2.x + c2->size.x) v1.x = v2.x + c2->size.x;
	if (v1.y < v2.y - c2->size.y) v1.y = v2.y - c2->size.y;
	if (v1.y > v2.y) v1.y = v2.y;

	c1->getTransform()->getPosition(v2);
	v2.x += c1->center.x;
	v2.y += c1->center.y;
	v2.z = 0;
	return (v1 - v2).sqrmagnitude() < c1->radius*c1->radius;
}

inline bool CollisionUtils::IsInersectsWithCollider(Vector2 pos, Vector2 halfSize, Collider2D* coll)
{
	static Vector3 v1,v2;
	if (dynamic_cast<CircleCollider2D*>(coll))
	{
		CircleCollider2D* circleColl = (CircleCollider2D*)coll;

		circleColl->getTransform()->getPosition(v1);
		v1.x += circleColl->center.x;
		v1.y += circleColl->center.y;
		v1.z = 0;

		v2.set(pos.x, pos.y, 0);
		
		if (v1.x < v2.x - halfSize.x) v1.x = v2.x - halfSize.x;
		if (v1.x > v2.x + halfSize.x) v1.x = v2.x + halfSize.x;
		if (v1.y < v2.y - halfSize.y) v1.y = v2.y - halfSize.y;
		if (v1.y > v2.y + halfSize.y) v1.y = v2.y + halfSize.y;

		circleColl->getTransform()->getPosition(v2);
		v2.x += circleColl->center.x;
		v2.y += circleColl->center.y;
		v2.z = 0;

		return (v1 - v2).sqrmagnitude() < circleColl->radius*circleColl->radius;
	}
	else if (dynamic_cast<BoxCollider2D*>(coll))
	{
		BoxCollider2D* boxColl = (BoxCollider2D*)coll;

		boxColl->getTransform()->getPosition(v1);
		v1.x += boxColl->center.x - boxColl->size.x/2;
		v1.y += boxColl->center.y + boxColl->size.y/2;
		v1.z = 0;

		v2.set(pos.x - halfSize.x, pos.y + halfSize.y, 0);

		return v1.x < v2.x + halfSize.x * 2 && v1.x + boxColl->size.x > v2.x &&
			v1.y > v2.y - halfSize.y * 2 && v1.y - boxColl->size.y < v2.y;
	}
	else
		return false;
}

#endif