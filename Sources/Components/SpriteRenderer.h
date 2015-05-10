#ifndef EngineTesting_SpriteRenderer_h
#define EngineTesting_SpriteRenderer_h


#include "../Components/Renderer.h"
#include "../CoreEngine/Texture2D.h"
#include "../CoreEngine/Material.h"
#include "../Extras/Color.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer()
	{
		verts_ = new Vector2[4]
		{
			Vector2(-1.0f, -1.0f),
			Vector2( 1.0f, -1.0f),
			Vector2( 1.0f,  1.0f),
			Vector2(-1.0f,  1.0f)
		};

		normals_ = new Vector3[4]
		{
			Vector3(0.0f, 0.0f, 1.0f),
			Vector3(0.0f, 0.0f, 1.0f),
			Vector3(0.0f, 0.0f, 1.0f),
			Vector3(0.0f, 0.0f, 1.0f)
		};

		tangent_ = new Vector3[4]
		{
			Vector3::RIGHT,
			Vector3::RIGHT,
			Vector3::RIGHT,
			Vector3::RIGHT
		};

		bitangent_ = new Vector3[4]
		{
			Vector3::UP,
			Vector3::UP,
			Vector3::UP,
			Vector3::UP
		};

		indices_ = new unsigned int[6]{ 0, 1, 2, 3, 0, 2 };
	}

	~SpriteRenderer();
	void Create();
	void Init();
	void Update();
	void Render(int subRenderers = 0);

	void setTextureFrame(int frame);
	void setColor(Color c);
	Color getColor();
private:
	int frame_ = 0;
	GLfloat meterPerPixel_;
	GLfloat wRange_ = 1;
	GLfloat hRange_ = 1;

	Vector2* verts_;
	Vector3* normals_;
	GLfloat* texcoords_;
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