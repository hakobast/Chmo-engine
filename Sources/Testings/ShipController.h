#ifndef SHIP_CONTROLLER_H
#define SHIP_CONTROLLER_H

#include <vector>
#include "EngineInclude.h"

class Ship;
class Collider2D;

class ShipController : public GameLogic
{
public:
	virtual void Init();
	virtual void Update();
	virtual void OnAction(std::string action, void*const data);
private:
	Ship* ship_;
	float t_;
	float fireInterval_ = 0.2f;
	std::vector<Collider2D*> otherColliders_;
};

#endif