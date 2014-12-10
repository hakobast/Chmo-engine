#include "MeshRenderer.h"

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Create()
{
	
}

void MeshRenderer::Init()
{

}

void MeshRenderer::Update()
{
	if (mesh == NULL)
		return;

	getTransform()->applyTransformation();

	std::vector<Vector3>& vertices = mesh->getVertices();
	std::vector<Vector2>& uvs = mesh->getUVs();
	std::vector<Vector3>& normals = mesh->getNormals();

	if (vertices.size() == 0)
		return;

	/*glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i++)
	{
		//printf("v\t%f, %f, %f\n", vertices[i][0], vertices[i][1], vertices[i][2]);
		glTexCoord2fv(&uvs[i][0]);
		glNormal3fv(&normals[i][0]);
		glVertex3fv(&vertices[i][0]);
	}
	glEnd();*/

	//TODO use VBO to render models
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, &uvs[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
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