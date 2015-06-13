#ifndef BULLET_H
#define BULLET_H

#include "EngineInclude.h"
#include "SimplePool.h"

class Bullet : public GameLogic
{
	friend class Weapon;
public:
	float speed;

	virtual void Init();
	virtual void Update();

	void setDirection(Vector3 dir);
private:
	Transform* transform_;
	SimplePool<Bullet>* pool_;
	Vector3 pos_;
	Vector3 camPos_;
	bool isMoving_;
};
#endif