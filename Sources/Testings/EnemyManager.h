#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <array>

#include "EngineInclude.h"
#include "SimplePool.h"

class Enemy;
class Collider2D;

class EnemyManager : public GameLogic, private SimplePool<Enemy>
{
	typedef std::array<float, 2> fRange;
	typedef std::array<int, 2> iRange;

public:
	virtual void Init();
	virtual void Update();
	
	void clearEnemies();
	void setEnemyGenParams(fRange speed, fRange radius, fRange step, iRange count);
private:
	float t_;
	float enemySpawnInterval_ = 1.5f;
	int poolInitialSize_ = 20;
	std::vector<Enemy*> enemies_;
	std::vector<Collider2D*> collisions_;

	///////////// generation vars //////////////
	fRange speed_;
	fRange radius_;
 	fRange step_;
 	iRange count_;
	////////////////////////////////////////////
	
	///////////// pool functions //////////////
	virtual void	release(Enemy* bullet);
	virtual Enemy*	get();
	////////////////////////////////////////////

	Enemy*	createEnemy	();
	Enemy*	spawnEnemy	();
	void	randomizeEnemy	(Enemy* enemy);
	void	OnEnemyCollision(Enemy* enemy, Collider2D* other);
};

#endif