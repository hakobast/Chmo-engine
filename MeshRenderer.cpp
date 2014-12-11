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

void MeshRenderer::Update()
{
	if (mesh.isEmpty())
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

	smart_pointer<Texture2D>& mainTexture = getMainTexture();

	if (!mainTexture.isEmpty())
	{
		glEnable(GL_TEXTURE_2D);
		mainTexture->bindTexture();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	if (!mainTexture.isEmpty())glTexCoordPointer(2, GL_FLOAT, 0, &uvs[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	if (!mainTexture.isEmpty())
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
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