#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include <array>

#include "../CoreEngine/ChmoEngine.h"
#include "SimplePool.h"

class Enemy;

class EnemySpawner : public GameLogic, private SimplePool<Enemy>
{
	typedef std::array<float, 2> fRange;
	typedef std::array<int, 2> iRange;

public:
	virtual void Init();
	virtual void Update();
	void setRandomParams(fRange radius, fRange step, iRange count);
private:
	float t_;
	float enemySpawnInterval_ = 0.8f;
	int poolInitialSize_ = 20;

	///////////// generation vars //////////////
	fRange radius_;
 	fRange step_;
 	iRange count_;
	////////////////////////////////////////////
	
	void	add(Enemy* bullet);
	Enemy* get();

	Enemy* createEnemy();
	void spawnEnemy();
	void randomizeEnemy(Enemy* enemy);
};

#endif