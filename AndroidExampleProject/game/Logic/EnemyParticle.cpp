#include "EnemyParticle.h"

void EnemyParticle::Create()
{
	smart_pointer<Material> mat =
		AssetManager::LoadMaterial("Particle", "Resources/Shaders/SimpleParticle.vert", "Resources/Shaders/SimpleParticle.frag");

	mat->setFloat(10.0f, "speed");

	particleRenderer = getGameObject()->addComponent<ParticleRenderer>();
	particleRenderer->setMainMaterial(mat);
	particleRenderer->setParticleCount(8);
	particleRenderer->setParticleSize(5.0f);
}

void EnemyParticle::Update()
{
	time_ += GameTime::DeltaTime();

	if (time_ >= duration)
	{
		pool_->release(this);
	}
}

void EnemyParticle::reset()
{
	time_ = 0;
	particleRenderer->reset();
}

void EnemyParticle::setColor(Color color)
{
	if (!particleRenderer->getSharedMaterial().isEmpty())
	{
		particleRenderer->getSharedMaterial()->setColor(color);
	}
}