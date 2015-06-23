#include "EnemyParticle.h"

void EnemyParticle::Create()
{
	smart_pointer<Material> mat =
		AssetManager::LoadMaterial("Particle", "Resources/Shaders/SimpleParticle.vert", "Resources/Shaders/SimpleParticle.frag");

	mat->setFloat(10.0f, "speed");

	particleRenderer = getGameObject()->addComponent<ParticleRenderer>();
	particleRenderer->setMainMaterial(mat);
	particleRenderer->setParticleCount(10);
	particleRenderer->setParticleSize(1.0f);
}

void EnemyParticle::Update()
{
	time_ += GameTime::DeltaTime();

	if (time_ >= duration)
	{
		getGameObject()->destroy();
	}
}

void EnemyParticle::setColor(Color color)
{
	if (!particleRenderer->getSharedMaterial().isEmpty())
	{
		particleRenderer->getSharedMaterial()->setColor(color);
	}
}