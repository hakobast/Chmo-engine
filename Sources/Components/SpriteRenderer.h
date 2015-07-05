#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H


#include "../Components/Renderer.h"
#include "../CoreEngine/Texture2D.h"
#include "../CoreEngine/Material.h"
#include "../Extras/Color.h"

class GLDrawer;

class SpriteRenderer : public Renderer
{
public:
	~SpriteRenderer();
	SpriteRenderer();
	virtual void Create();
	virtual void Init();
	virtual void Update();
	virtual void Render(int materialIndex = 0);

	void setTextureFrame(int frame);
	void setColor(Color c);
	Color getColor();
private:
	int frame_ = 0;
	GLfloat meterPerPixel_ = 0;

	GLDrawer* drawer_ = 0;
	Vector2* verts_;
	Vector2* texcoords_;
	Vector3* normals_;
	Vector3* tangent_;
	Vector3* bitangent_;
	unsigned int* indices_;
};

inline void SpriteRenderer::setColor(Color c)
{
	smart_pointer<Material>& mat = getSharedMaterial();
	if (!mat.isEmpty())
		mat->setColor("Color",c);
}

inline Color SpriteRenderer::getColor()
{
	smart_pointer<Material>& mat = getSharedMaterial();
	if (!mat.isEmpty())
		return mat->getColor("Color");

	return Color::BLACK();
}

#endif