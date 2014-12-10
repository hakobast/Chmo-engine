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
	void setSharedMesh(smart_pointer<Mesh>& m);
	smart_pointer<Mesh>& getMesh();
private:
	smart_pointer<Mesh> mesh;
};

#endif