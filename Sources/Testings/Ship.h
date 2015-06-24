#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <utility>
#include "EngineInclude.h"

class Weapon;

class Ship : public GameLogic
{
public:
	float speed = 2;

	virtual void Init();
	virtual void Update();
	virtual void OnDisable();

	Weapon* getWeapon		(int index);
	void	addWeapon		(Weapon* weapon, Vector3 localPosition, Vector3 direction);
	int		getWeaponsCount	();
	void	fire			(int weaponIndex);
	void	moveTo			(Vector3 dest);
private:
	std::vector<std::pair<Weapon*,Vector3>> weapons_;
	Transform* transform_ = 0;
	Vector3 dest_;
	Matrix4 weaponTransformation_;
	bool hasDestination_ = false;
};

#endif