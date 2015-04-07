
#include "CoreEngine/LIBS.h"

#include <iostream>
#include "SpriteRenderer.h"
#include "CoreEngine/Transform.h"
#include "Systems/ScreenSystem.h"
#include "CoreEngine/ShaderProgram.h"
#include "Systems/Input.h"
#include "Systems/GameTime.h"


SpriteRenderer::~SpriteRenderer()
{
	cout << "SpriteRenderer:: ~~~deleted~~~ " << endl;
	delete[] _verts;
	delete[] _normals;
	delete[] _tangent;
	delete[] _bitangent;
}

void SpriteRenderer::Create()
{
	_meterPerPixel = 1.0f/100.0f;
}

void SpriteRenderer::Init()
{
	_tangAttribLocation = getSharedMaterial()->shader->getAttributeLocation("tangent");
	_bitangAttribLocation = getSharedMaterial()->shader->getAttributeLocation("bitangent");

	setTextureFrame(_frame);
}

bool hasTexture;
void SpriteRenderer::Update()
{
	getTransform()->applyTransformation();
	
	smart_pointer<Material>& mat = getSharedMaterial();
	hasTexture = !mat->getMainTexture().isEmpty();

	mat->bind();
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		if (hasTexture) glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(2, GL_FLOAT, 0, _verts);
		glNormalPointer(GL_FLOAT, 0, _normals);
		if (hasTexture) glTexCoordPointer(2, GL_FLOAT, 0, _texcoords);

		glVertexAttribPointerARB(_tangAttribLocation, 3, GL_FLOAT, true, 0, _tangent);
		glVertexAttribPointerARB(_bitangAttribLocation, 3, GL_FLOAT, true, 0, _bitangent);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		if (hasTexture) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	mat->unbind();

	/*glBegin(GL_QUADS);
	{
		glNormal3f(0.0f, 0.0f, 1.0f);

		glTexCoord2fv((*mainTexture)[_frame][0]); glVertex3f(-_wRange, -_hRange, 0.0f);
		//mat->shader->setVertexAttrib3fv("tangent", _tangent.getPointer());
		//mat->shader->setVertexAttrib3fv("bitangent", _bitangent.getPointer());

		glTexCoord2fv((*mainTexture)[_frame][2]); glVertex3f(_wRange, -_hRange, 0.0f);
		//mat->shader->setVertexAttrib3fv("tangent", _tangent.getPointer());
		//mat->shader->setVertexAttrib3fv("bitangent", _bitangent.getPointer());

		glTexCoord2fv((*mainTexture)[_frame][4]); glVertex3f(_wRange, _hRange, 0.0f);
		//mat->shader->setVertexAttrib3fv("tangent", _tangent.getPointer());
		//mat->shader->setVertexAttrib3fv("bitangent", _bitangent.getPointer());

		glTexCoord2fv((*mainTexture)[_frame][6]); glVertex3f(-_wRange, _hRange, 0.0f);		
		//mat->shader->setVertexAttrib3fv("tangent", _tangent.getPointer());
		//mat->shader->setVertexAttrib3fv("bitangent", _bitangent.getPointer());
	}
	glEnd();*/

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