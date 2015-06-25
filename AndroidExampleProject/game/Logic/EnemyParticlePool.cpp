#include "EnemyParticlePool.h"
#include "EnemyParticle.h"
#include "EngineInclude.h"

EnemyParticlePool::EnemyParticlePool(int initialSize)
{
	for (int i = 0; i < initialSize; i++)
	{
		release(createParticle());
	}
}

EnemyParticle* EnemyParticlePool::get()
{
	EnemyParticle* particle = SimplePool::get();
	if (particle)
	{
		particle->getGameObject()->setActive(true);
		particle->reset();
	}
	else
	{
		particle = createParticle();
		SimplePool::release(particle);
	}

	return particle;
}

void EnemyParticlePool::release(EnemyParticle* obj)
{
	if (obj != NULL)
	{
		obj->getGameObject()->setActive(false);
		SimplePool::release(obj);
	}
}

EnemyParticle* EnemyParticlePool::createParticle()
{
	GameObject* obj = new GameObject("EnemyParticle");
	EnemyParticle* particle = obj->addComponent<EnemyParticle>();
	particle->pool_ = this;

	return particle;
}
