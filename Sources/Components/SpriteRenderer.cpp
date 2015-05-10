

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
	delete[] verts_;
	delete[] normals_;
	delete[] tangent_;
	delete[] bitangent_;
	delete[] indices_;
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

	glVertexAttribPointer(vertexAttribLocation, 2, GL_FLOAT, false, 0, verts_);
	if (hasTexture)glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, false, 0, texcoords_);
	glVertexAttribPointer(normalAttribLocation, 3, GL_FLOAT, true,  0, normals_);
 	glVertexAttribPointer(tangAttribLocation, 3, GL_FLOAT, true, 0, tangent_);
 	glVertexAttribPointer(bitangAttribLocation, 3, GL_FLOAT, true, 0, bitangent_);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices_);

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
		this->frame_ = frame;

		float width = (region->u_v[2] - region->u_v[0])*txt->width;
		float height = (region->u_v[5] - region->u_v[1])*txt->height;
	
		wRange_ = meterPerPixel_*width;
		hRange_ = meterPerPixel_*height;

		if (verts_ != NULL)
			delete[] verts_;

		verts_ = new Vector2[4]
		{
			Vector2(-wRange_, -hRange_),
			Vector2(wRange_, -hRange_),
			Vector2(wRange_, hRange_),
			Vector2(-wRange_, hRange_)
		};

		 texcoords_ = region->u_v;
	}
}