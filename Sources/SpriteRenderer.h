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
		_normals = new Vector3[4]
		{
			Vector3(0.0f, 0.0f, 1.0f),
			Vector3(0.0f, 0.0f, 1.0f),
			Vector3(0.0f, 0.0f, 1.0f),
			Vector3(0.0f, 0.0f, 1.0f)
		};

		_tangent = new Vector3[4]
		{
			Vector3::RIGHT,
			Vector3::RIGHT,
			Vector3::RIGHT,
			Vector3::RIGHT
		};

		_bitangent = new Vector3[4]
		{
			Vector3::UP,
			Vector3::UP,
			Vector3::UP,
			Vector3::UP
		};

		setMainMaterial(Material::Unlit());
	}

	~SpriteRenderer();
	void Create();
	void Init();
	void Update();

	void setTextureFrame(int frame);
	void setColor(Color c);
	Color getColor();
private:
	int _frame = 0;
	GLfloat _meterPerPixel;
	GLfloat _wRange = 1;
	GLfloat _hRange = 1;

	Vector2* _verts;
	Vector3* _normals;
	GLfloat* _texcoords;
	Vector3* _tangent;
	Vector3* _bitangent;
	GLuint _tangAttribLocation;
	GLuint _bitangAttribLocation;
};

inline void SpriteRenderer::setColor(Color c)
{
	getMaterial()->color_diffuse = c;
}

inline Color SpriteRenderer::getColor()
{
	return getSharedMaterial()->color_diffuse;
}

#endif