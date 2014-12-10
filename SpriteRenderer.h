#ifndef EngineTesting_SpriteRenderer_h
#define EngineTesting_SpriteRenderer_h


#include "Renderer.h"
#include "Texture2D.h"
#include "Color.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer()
	{
		/*smart_pointer<Material> diffuseMaterial(new Material("diffuse_sprite"));

		diffuseMaterial->color_diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
		setMainMaterial(diffuseMaterial,false);*/
	}

	~SpriteRenderer();
	void Create();
	void Init();
	void Update();
	void setTextureFrame(int frame);
	void setColor(Color c);
	Color getColor();
private:
	int frame;
};

inline void SpriteRenderer::setColor(Color c)
{
	getMainMaterial()->color_diffuse = c;
}

inline Color SpriteRenderer::getColor()
{
	return getMainMaterial()->color_diffuse;
}

#endif