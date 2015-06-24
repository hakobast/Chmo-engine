#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "EngineInclude.h"

enum SpaceshipType
{
	STANDART,
	COOL
};

class EnemyManager;
class CollisionManager;

class GameController : public GameLogic
{
public:
	SpaceshipType spaceShipType = STANDART;

	virtual void Init();
	virtual void Update();

	void startGame();
	void endGame();
	void restartGame();
private:
	EnemyManager* enemyManager_;
	CollisionManager* collisionManager_;
	bool isGameStarted_ = false;

	void createCoolSpaceship();
	void createStandartSpaceship();
};
#endif