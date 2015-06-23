
#include "ParticleRenderer.h"
#include "../CoreEngine/Transform.h"
#include "../CoreEngine/GLDrawer.h"
#include "../Systems/GameTime.h"

ParticleRenderer::~ParticleRenderer()
{
	delete drawer_;
}

ParticleRenderer::ParticleRenderer()
{
	drawer_ = new GLDrawer(GL_POINTS, VBO);
	drawer_->setVertexIndex(0);
	drawer_->setTexCoordIndex(1);
	drawer_->setNormalIndex(2);
	drawer_->setTangentIndex(3);
	drawer_->setBitangentIndex(4);
}

void ParticleRenderer::Render(int materialIndex /* = 0 */)
{
	getSharedMaterial()->getShader()->setUniform1i("count", particleCount_);
	getSharedMaterial()->getShader()->setUniform1f("time", time_);
	drawer_->draw();

	time_ += GameTime::DeltaTime();
}

void ParticleRenderer::setParticleCount(int count)
{
	if (particleCount_ >= 0)
	{
		particleCount_ = count;
		if (particleCount_ > 0)
			drawer_->setVertexData(3, false, particleCount_, NULL);
		else
			drawer_->setVertexData(3, false, 0, NULL);

		particleIndices_.resize(particleCount_);
		for (int i = 0; i < particleCount_; i++)
			particleIndices_[i] = (float)i;

		drawer_->setAttributeData(0, 1, 1, 15, sizeof(float), GL_FLOAT, particleIndices_.data());
	}
}