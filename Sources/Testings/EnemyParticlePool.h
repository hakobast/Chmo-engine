#ifndef ENEMY_PARTICLE_POOL_H
#define ENEMY_PARTICLE_POOL_H

#include "SimplePool.h"

class EnemyParticle;

class EnemyParticlePool : public SimplePool<EnemyParticle>
{
public:
	EnemyParticlePool(int initialSize);
	virtual EnemyParticle* get();
	virtual void release(EnemyParticle* obj);
private:
	EnemyParticle* createParticle();
};
#endif