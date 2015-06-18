#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "EngineInclude.h"

enum SpaceshipType
{
	STANDART,
	COOL
};

class EnemyManager;
class CollisionSystem;

class GameController : public GameLogic
{
public:
	SpaceshipType spaceShipType = STANDART;

	virtual void Create();
	virtual void Update();

	void startGame();
	void endGame();
private:
	EnemyManager* enemyManager;
	CollisionSystem* collisionSystem;

	void createCoolSpaceship();
	void createStandartSpaceship();
};
#endif