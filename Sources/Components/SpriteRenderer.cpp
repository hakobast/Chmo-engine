

#include <iostream>
#include "SpriteRenderer.h"

#include "../CoreEngine/LIBS.h"
#include "../CoreEngine/Transform.h"
#include "../CoreEngine/Component.h"
#include "../CoreEngine/GLMeshDrawer.h"
#include "../Systems/ScreenSystem.h"
#include "../CoreEngine/GameObject.h"
#include "../CoreEngine/ShaderProgram.h"
#include "../Systems/Input.h"
#include "../Systems/GameTime.h"


SpriteRenderer::~SpriteRenderer()
{
	cout << "SpriteRenderer:: ~~~deleted~~~ " << endl;
	delete[] verts_;
	delete[] texcoords_;
	delete[] normals_;
	delete[] tangent_;
	delete[] bitangent_;
	delete[] indices_;

	delete drawer;
}

SpriteRenderer::SpriteRenderer()
{
	verts_ = new Vector2[4]
	{
		Vector2(-1.0f, -1.0f),
		Vector2(1.0f, -1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(-1.0f, 1.0f)
	};

	texcoords_ = new Vector2[4]
	{
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Vector2(0.0f, 1.0f)
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

	drawer = new GLMeshDrawer(GL_TRIANGLES, VAO);

	//TEMP get this data from shader
	drawer->setVertexIndex(0);
	drawer->setTexCoordIndex(1);
	drawer->setNormalIndex(2);
	drawer->setTangentIndex(3);
	drawer->setBitangentIndex(4);

	drawer->setNormalData(false, 4, normals_[0].getPointer());
	drawer->setTangentData(3, false, 4, tangent_[0].getPointer());
	drawer->setBitangentData(3, false, 4, bitangent_[0].getPointer());
	drawer->setIndexData(6, indices_);
}

void SpriteRenderer::Create()
{
	meterPerPixel_ = 1.0f/100.0f;
}

void SpriteRenderer::Init()
{
	Component::Init();

	//std::cout << "SpriteRenderer: Init() " << getGameObject()->name << std::endl;

	setTextureFrame(frame_);
}

void SpriteRenderer::Update(){}

bool hasTexture;
void SpriteRenderer::Render(int material)
{
 	drawer->draw();

	float rotationSpeed = 100.0f;

	if (Input::IsKeyDown(Key::z))
		getTransform()->RotateY(rotationSpeed*GameTime::DeltaTime());
	if (Input::IsKeyDown(Key::x))
		getTransform()->RotateY(-rotationSpeed*GameTime::DeltaTime());
}

void SpriteRenderer::setTextureFrame(int frame)
{
	smart_pointer<Texture2D>& txt = getMainTexture();
	
	if (txt.isEmpty())
		return;

	TextureRegion* region = txt->getTextureRegion(frame);

	if (region != NULL)
	{
		this->frame_ = frame;

		float width = (region->uv[2] - region->uv[0])*txt->width;
		float height = (region->uv[5] - region->uv[1])*txt->height;

		float wRange_ = meterPerPixel_*width;
		float hRange_ = meterPerPixel_*height;

		verts_[0].set(-wRange_, -hRange_);
		verts_[1].set(wRange_, -hRange_);
		verts_[2].set(wRange_, hRange_);
		verts_[3].set(-wRange_, hRange_);
		
		texcoords_[0].set(region->uv[0], region->uv[1]);
		texcoords_[1].set(region->uv[2], region->uv[3]);
		texcoords_[2].set(region->uv[4], region->uv[5]);
		texcoords_[3].set(region->uv[6], region->uv[7]);

		drawer->setVertexData(2, false, 4, verts_[0].getPointer());
		drawer->setTexCoordData(2, false, 4, texcoords_[0].getPointer());
	}
}