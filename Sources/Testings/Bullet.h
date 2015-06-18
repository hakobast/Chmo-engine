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
	virtual void OnAction(std::string action, void*const data);

	void setDirection(Vector3 dir);
private:
	Transform* transform_ = 0;
	SimplePool<Bullet>* pool_ = 0;
	Vector3 pos_;
	Vector3 camPos_;
	bool isMoving_;
};
#endif