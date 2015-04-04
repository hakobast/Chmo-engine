#ifndef EngineTesting_MeshRenderer_h
#define EngineTesting_MeshRenderer_h


#include "Renderer.h"
#include "Mesh.h"

class MeshRenderer : public Renderer
{
public:
	~MeshRenderer();
	void Create();
	void Init();
	void Update();
	void setMesh(smart_pointer<Mesh>& m);
	smart_pointer<Mesh>& getMesh();
	smart_pointer<Mesh>& getSharedMesh();
private:
	smart_pointer<Mesh> mesh;
};

inline void MeshRenderer::setMesh(smart_pointer<Mesh>& m)
{
	if (m.isEmpty())
		return;

	mesh = m;
	mesh->_sharesCount++;

	for (int i = 0; i < mesh->getSubMeshCount(); i++)
	{
		if(mesh->_submeshes[i]->_updateVBO())
			mesh->genBuffers(i);
	}
}

inline smart_pointer<Mesh>& MeshRenderer::getMesh()
{		
	if (mesh.isEmpty())
	{
		mesh = smart_pointer<Mesh>(new Mesh);
		mesh->_sharesCount = 1;
	}
	else if (mesh->_sharesCount > 1)
	{
		mesh->_sharesCount = 1;
		mesh = mesh.clone();
	}

	return mesh;
}

inline smart_pointer<Mesh>& MeshRenderer::getSharedMesh()
{
	if (mesh.isEmpty())
	{
		mesh = smart_pointer<Mesh>(new Mesh);
		mesh->_sharesCount = 1;
	}

	return mesh;
}

#endif