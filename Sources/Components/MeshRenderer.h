#ifndef EngineTesting_MeshRenderer_h
#define EngineTesting_MeshRenderer_h


#include "Renderer.h"
#include "../CoreEngine/Mesh.h"

class MeshRenderer : public Renderer
{
public:
	~MeshRenderer();
	void Create();
	void Init();
	void Update();
	void Render(int subRenderer = 0);
	void setMesh(smart_pointer<Mesh>& m);
	smart_pointer<Mesh>& getMesh();
	smart_pointer<Mesh>& getSharedMesh();
private:
	smart_pointer<Mesh> mesh_;
};

inline void MeshRenderer::setMesh(smart_pointer<Mesh>& m)
{
	if (m.isEmpty())
		return;

	mesh_ = m;
	mesh_->sharesCount_++;

	for (int i = 0; i < mesh_->getSubMeshCount(); i++)
	{
		if(mesh_->submeshes_[i]->_updateVBO())
			mesh_->genBuffers(i);
	}
}

inline smart_pointer<Mesh>& MeshRenderer::getMesh()
{		
	if (mesh_.isEmpty())
	{
		mesh_ = smart_pointer<Mesh>(new Mesh);
		mesh_->sharesCount_ = 1;
	}
	else if (mesh_->sharesCount_ > 1)
	{
		mesh_->sharesCount_ = 1;
		mesh_ = mesh_.clone();
	}

	return mesh_;
}

inline smart_pointer<Mesh>& MeshRenderer::getSharedMesh()
{
	if (mesh_.isEmpty())
	{
		mesh_ = smart_pointer<Mesh>(new Mesh);
		mesh_->sharesCount_ = 1;
	}

	return mesh_;
}

#endif