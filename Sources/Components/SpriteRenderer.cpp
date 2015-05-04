

#include <iostream>
#include "SpriteRenderer.h"

#include "../CoreEngine/LIBS.h"
#include "../CoreEngine/Transform.h"
#include "../CoreEngine/Component.h"
#include "../Systems/ScreenSystem.h"
#include "../CoreEngine/GameObject.h"
#include "../CoreEngine/ShaderProgram.h"
#include "../Systems/Input.h"
#include "../Systems/GameTime.h"


SpriteRenderer::~SpriteRenderer()
{
	cout << "SpriteRenderer:: ~~~deleted~~~ " << endl;
	delete[] _verts;
	delete[] _normals;
	delete[] _tangent;
	delete[] _bitangent;
	delete[] indices;
}

void SpriteRenderer::Create()
{
	_meterPerPixel = 1.0f/100.0f;
}

void SpriteRenderer::Init()
{
	Component::Init();

	//std::cout << "SpriteRenderer: Init() " << getGameObject()->name << std::endl;

	setTextureFrame(_frame);
}

bool hasTexture;

void SpriteRenderer::Update(){}

/*void SpriteRenderer::Render(int material)
{
	smart_pointer<Material>& mat = getSharedMaterial(material);
	hasTexture = !mat->getMainTexture().isEmpty();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	if (hasTexture) glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, _verts);
	glNormalPointer(GL_FLOAT, 0, _normals);
	if (hasTexture) glTexCoordPointer(2, GL_FLOAT, 0, _texcoords);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	if (hasTexture) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
*/

void SpriteRenderer::Render(int material)
{
//	getTransform()->applyTransformation();
 	smart_pointer<Material>& mat = getSharedMaterial(material);
 	hasTexture = !mat->getMainTexture().isEmpty();

	//std::cout << "RENDER ME " << getGameObject()->name << " SUB " << material << " Has Texture " << hasTexture << std::endl;

	glEnableVertexAttribArray(vertexAttribLocation);
	if(hasTexture)glEnableVertexAttribArray(texCoordAttribLocation);
	glEnableVertexAttribArray(normalAttribLocation);
	glEnableVertexAttribArray(tangAttribLocation);
	glEnableVertexAttribArray(bitangAttribLocation);

	glVertexAttribPointer(vertexAttribLocation, 2, GL_FLOAT, false, 0, _verts);
	if (hasTexture)glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, false, 0, _texcoords);
	glVertexAttribPointer(normalAttribLocation, 3, GL_FLOAT, true,  0, _normals);
 	glVertexAttribPointer(tangAttribLocation, 3, GL_FLOAT, true, 0, _tangent);
 	glVertexAttribPointer(bitangAttribLocation, 3, GL_FLOAT, true, 0, _bitangent);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

	glDisableVertexAttribArray(vertexAttribLocation);
	if (hasTexture)glDisableVertexAttribArray(texCoordAttribLocation);
	glDisableVertexAttribArray(normalAttribLocation);
	glDisableVertexAttribArray(tangAttribLocation);
	glDisableVertexAttribArray(bitangAttribLocation);

	float rotationSpeed = 100.0f;

	if (Input::IsKeyDown(KeyCode::z))
		getTransform()->RotateY(rotationSpeed*GameTime::DeltaTime());
	if (Input::IsKeyDown(KeyCode::x))
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
		this->_frame = frame;

		float width = (region->u_v[2] - region->u_v[0])*txt->width;
		float height = (region->u_v[5] - region->u_v[1])*txt->height;
	
		_wRange = _meterPerPixel*width;
		_hRange = _meterPerPixel*height;

		if (_verts != NULL)
			delete[] _verts;

		_verts = new Vector2[4]
		{
			Vector2(-_wRange, -_hRange),
			Vector2(_wRange, -_hRange),
			Vector2(_wRange, _hRange),
			Vector2(-_wRange, _hRange)
		};

		 _texcoords = region->u_v;
	}
}