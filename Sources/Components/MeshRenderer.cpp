
#include <vector>

#include "MeshRenderer.h"
#include "../Systems/Input.h"
#include "../Systems/GameTime.h"
#include "../CoreEngine/Transform.h"

MeshRenderer::~MeshRenderer()
{
	cout << "MeshRenderer:: ~~~deleted~~~ " << endl;

	if (!mesh_.isEmpty())
		mesh_->sharesCount_--;
}

void MeshRenderer::Create()
{
	dynamic_cast<RenderSystem*>(renderSystem_)->sortComponents();
}

void MeshRenderer::Init()
{
	Component::Init();
}

void MeshRenderer::Update(){}

void  MeshRenderer::Render(int materialIndex)
{
	if (mesh_.isEmpty())
		return;

	materialIndex = materialIndex < mesh_->getSubMeshCount() ? materialIndex : (mesh_->getSubMeshCount() - 1);
	mesh_->draw(materialIndex);
}