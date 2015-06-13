
#ifndef WEAPON_H
#define WEAPON_H

#include "../CoreEngine/ChmoEngine.h"
#include "SimplePool.h"

class Bullet;

class Weapon : private SimplePool<Bullet>
{
public:
	Vector3 currentDirection;
	Vector3 direction;
	Vector3 position;

	Weapon(Color bulletColor = Color::RED, float bulletSpeed = 10);
	void fire();
private:
	void	add(Bullet* bullet);
	Bullet* get();

private:
	int poolInitialSize_ = 30;
	float bulletSpeed_ = 0;
	Color bulletColor_;
	Bullet* createBullet();
};

#endif