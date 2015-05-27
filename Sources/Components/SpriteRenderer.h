#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H


#include "../Components/Renderer.h"
#include "../CoreEngine/Texture2D.h"
#include "../CoreEngine/Material.h"
#include "../Extras/Color.h"

class GLMeshDrawer;

class SpriteRenderer : public Renderer
{
public:
	~SpriteRenderer();
	SpriteRenderer();
	void Create();
	void Init();
	void Update();
	void Render(int subRenderers = 0);

	void setTextureFrame(int frame);
	void setColor(Color c);
	Color getColor();
private:
	int frame_ = 0;
	GLfloat meterPerPixel_ = 0;

	GLMeshDrawer* drawer = 0;
	Vector2* verts_;
	Vector2* texcoords_;
	Vector3* normals_;
	Vector3* tangent_;
	Vector3* bitangent_;
	unsigned int* indices_;
};

inline void SpriteRenderer::setColor(Color c)
{
	getSharedMaterial()->setColor(c);
}

inline Color SpriteRenderer::getColor()
{
	return getSharedMaterial()->getColor();
}

#endif