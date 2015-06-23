#ifndef ENEMY_PARTICLE_H
#define ENEMY_PARTICLE_H

#include "EngineInclude.h"

class ParticleRenderer;

class EnemyParticle : public GameLogic
{
public:
	void Create();
	void Update();
	void setColor(Color color);
private:
	float duration = 0.5f;
	float time_ = 0;
	ParticleRenderer* particleRenderer;
};
#endif