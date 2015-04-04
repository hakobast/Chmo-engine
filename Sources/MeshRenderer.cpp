#include "MeshRenderer.h"
#include "Input.h"
#include "GameTime.h"

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

}

void  MeshRenderer::Update()
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

	getTransform()->applyTransformation();

	if (mesh.isEmpty())
		return;

	std::vector<smart_pointer<Material>>& mats = getSharedMaterials();
	int mats_count = mats.size();

	for (int i = 0; i < mesh->getSubMeshCount(); i++)
	{
		//TODO implement mult materials
		if (i < mats_count)
		{
			mats[i]->bind();
			mesh->draw(i);
			mats[i]->unbind();
		}
		else
		{
			if (mats_count > 0)
			{
				mats.back()->bind();
				mesh->draw(i);
				mats.back()->unbind();
			}
			else
			{
				mesh->draw(i);
			}
		}
	}
}