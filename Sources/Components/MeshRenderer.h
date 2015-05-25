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
	if (m.isEmpty() || m == mesh_)
		return;

	mesh_ = m;
	mesh_->sharesCount_++;
}

inline smart_pointer<Mesh>& MeshRenderer::getMesh()
{
	if (!mesh_.isEmpty())
	{
		if (mesh_->sharesCount_ > 1)
		{
			mesh_->sharesCount_--;
			mesh_ = mesh_.clone();
			mesh_->sharesCount_ = 1;
		}

		return mesh_;
	}

	return smart_pointer<Mesh>::null();
}

inline smart_pointer<Mesh>& MeshRenderer::getSharedMesh()
{
	if (!mesh_.isEmpty())
	{
		return mesh_;
	}

	return smart_pointer<Mesh>::null();
}

#endif