#ifndef ENEMY_PARTICLE_H
#define ENEMY_PARTICLE_H

#include "EngineInclude.h"
#include "SimplePool.h"

class ParticleRenderer;

class EnemyParticle : public GameLogic
{
	friend class EnemyParticlePool;
public:
	void Create();
	void Update();
	void setColor(Color color);
	void reset();
private:
	SimplePool<EnemyParticle>* pool_ = 0;
	float duration = 0.5f;
	float time_ = 0;
	ParticleRenderer* particleRenderer;
};
#endif