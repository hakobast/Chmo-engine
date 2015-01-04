#include "MeshRenderer.h"

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Create()
{
	renderSystem->sortComponents();
}

void MeshRenderer::Init()
{

}

void  MeshRenderer::Update()
{
	getTransform()->applyTransformation();

	if (mesh.isEmpty())
		return;

	for (int i = 0; i < mesh->getSubMeshCount(); i++)
	{
		std::vector<Vector3>& vertices = mesh->getVertices(i);
		std::vector<Vector2>& uvs = mesh->getUVs(i);
		std::vector<Vector3>& normals = mesh->getNormals(i);

		//TEMP
		if (vertices.size() == 0 || i >= materials.size())
			continue;
		
		//TODO use VBO to render models
		//TODO fix this sheet
		smart_pointer<Material>& material = getMaterial(i);

		material->bind();

		if (uvs.size() > 0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, &uvs[0]);
		}

		if (normals.size() > 0)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 0, &normals[0]);
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		material->unbind();
	}
}

void MeshRenderer::setSharedMesh(smart_pointer<Mesh>& m)
{
	mesh = m;
}

void MeshRenderer::setMesh(smart_pointer<Mesh>& m)
{
	mesh = m.clone();
}

smart_pointer<Mesh>& MeshRenderer::getMesh()
{
	return mesh;
}