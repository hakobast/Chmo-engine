#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include "Renderer.h"

class GLDrawer;

class ParticleRenderer : public Renderer
{
public:
	~ParticleRenderer();
	ParticleRenderer();

	virtual void Render(int materialIndex = 0);

	void	setParticleCount(int count);
	int		getParticleCount();
	void	setParticleSize(float size);
	float	getParticleSize();
private:
	GLDrawer* drawer_ = 0;
	int particleCount_ = 0;
	float time_;
	std::vector<float> particleIndices_;
};

inline int ParticleRenderer::getParticleCount()
{
	return particleCount_;
}

inline void ParticleRenderer::setParticleSize(float size)
{
	smart_pointer<Material>& mat = getSharedMaterial();
	if (!mat.isEmpty())
		return mat->setFloat(size, "size");
}

inline float ParticleRenderer::getParticleSize()
{
	smart_pointer<Material>& mat = getSharedMaterial();
	if (!mat.isEmpty())
		return mat->getFloat("size");

	return 1.0f;
}

#endif
