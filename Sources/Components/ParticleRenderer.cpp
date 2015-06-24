
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
}

void ParticleRenderer::Render(int materialIndex /* = 0 */)
{
	getSharedMaterial()->getShader()->setUniform1f("count", (float)particleCount_);
	getSharedMaterial()->getShader()->setUniform1f("time", time_);
	drawer_->draw();

	time_ += GameTime::DeltaTime();
}

void ParticleRenderer::setParticleCount(int count)
{
	if (particleCount_ >= 0)
	{
		particleCount_ = count;
		particlePositions_.resize(particleCount_);
		if (particleCount_ > 0)
			drawer_->setVertexData(3, false, particleCount_, particlePositions_[0].getPointer());
		else
			drawer_->setVertexData(3, false, 0, NULL);

		particleIndices_.resize(particleCount_);
		for (int i = 0; i < particleCount_; i++)
			particleIndices_[i] = (float)i;
		
		GLint loc = getSharedMaterial()->getShader()->getAttributeLocation("index");
		drawer_->setCustomAttribute(0, loc, 1, particleCount_, sizeof(float), GL_FLOAT, particleIndices_.data());
	}
}