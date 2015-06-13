#ifndef ENEMY_H
#define ENEMY_H

#include "EngineInclude.h"

#include "SimplePool.h"

class Enemy : public GameLogic
{
	friend class EnemySpawner;
public:
	float speed = 0.5f;

	virtual void Init();
	virtual void Update();

	void setDirection(Vector3 dir);
private:
	Transform* transform_;
	SimplePool<Enemy>* pool_;
	Vector3 pos_;
	Vector3 camPos_;
	bool isMoving_;
};
#endif