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
		_verts = new Vector2[4]
		{
			Vector2(-1.0f, -1.0f),
			Vector2( 1.0f, -1.0f),
			Vector2( 1.0f,  1.0f),
			Vector2(-1.0f,  1.0f)
		};

		_normals = new Vector3[4]
		{
			Vector3(0.0f, 0.0f, -1.0f),
			Vector3(0.0f, 0.0f, -1.0f),
			Vector3(0.0f, 0.0f, -1.0f),
			Vector3(0.0f, 0.0f, -1.0f)
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

		smart_pointer<Material> mat = Material::Unlit();
		setMainMaterial(mat);
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
	getSharedMaterial()->setColor(c);
}

inline Color SpriteRenderer::getColor()
{
	return getSharedMaterial()->getColor();
}

#endif