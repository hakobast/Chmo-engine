
#include <vector>

#include "MeshRenderer.h"
#include "../Systems/Input.h"
#include "../Systems/GameTime.h"
#include "../CoreEngine/Transform.h"

MeshRenderer::~MeshRenderer()
{
	cout << "MeshRenderer:: ~~~deleted~~~ " << endl;

	if (!mesh.isEmpty())
		mesh->_sharesCount--;
}

void MeshRenderer::Create()
{
	dynamic_cast<RenderSystem*>(system)->sortComponents();
}

void MeshRenderer::Init()
{
	Component::Init();
}

void MeshRenderer::Update(){}

void  MeshRenderer::Render(int materialIndex)
{
// 	GLfloat rotation = 180.0f;
// 
// 	if (Input::IsKeyDown(KeyCode::w))
// 		getTransform()->RotateY(rotation*GameTime::DeltaTime());
// 
// 	if (Input::IsKeyDown(KeyCode::s))
// 		getTransform()->RotateY(-rotation*GameTime::DeltaTime());
// 
// 	if (Input::IsKeyDown(KeyCode::a))
// 	{
// 		getTransform()->RotateX(rotation*GameTime::DeltaTime());
// 	}
// 
// 	if (Input::IsKeyDown(KeyCode::d))
// 	{
// 		getTransform()->RotateX(-rotation*GameTime::DeltaTime());
// 	}

	//getTransform()->applyTransformation();

	if (mesh.isEmpty())
		return;

	materialIndex = materialIndex < mesh->getSubMeshCount() ? materialIndex : (mesh->getSubMeshCount() - 1);
	mesh->draw(materialIndex);
}