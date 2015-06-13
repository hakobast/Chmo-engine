#ifndef SHIP_CONTROLLER_H
#define SHIP_CONTROLLER_H

#include "EngineInclude.h"

class Ship;

class ShipController : public GameLogic
{
public:
	virtual void Init();
	virtual void Update();
private:
	float t_;
	float fireInterval_ = 0.2f;
	Ship* ship_;
};

#endif