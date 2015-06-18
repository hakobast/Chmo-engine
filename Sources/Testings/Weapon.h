
#ifndef WEAPON_H
#define WEAPON_H

#include <vector>
#include "EngineInclude.h"
#include "SimplePool.h"

class Bullet;

class Weapon : private SimplePool<Bullet>
{
public:
	Vector3 currentDirection;
	Vector3 direction;
	Vector3 position;

	~Weapon();
	Weapon(Color bulletColor = Color::RED, float bulletSpeed = 10);
	void fire();
private:
	int poolInitialSize_ = 30;
	float bulletSpeed_ = 0;
	Color bulletColor_;
	smart_pointer<Material> bulletMat_;
	std::vector<Bullet*> bullets_;

	///////////// pool functions //////////////
	virtual void	release(Bullet* bullet);
	virtual Bullet* get();
	////////////////////////////////////////////

	Bullet* createBullet();
};

#endif