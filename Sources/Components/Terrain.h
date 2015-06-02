#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Extras/Vectors.h"
#include "../CoreEngine/LIBS.h"
#include "Renderer.h"

class Terrain : public Renderer
{
private:
	GLint width;
	GLint length;
	GLfloat** map;
	Vector3** normals;
	Vector3* verts;
	Vector3* norms;
	Vector2* textures;
	GLuint vertex_vbo_id;
	GLuint normal_vbo_id;
	GLuint texture_vbo_id;

	bool isNormalsComputed = false;
	void computeNormals();
	GLuint getVertsCount();
public:
	void build(smart_pointer<Texture2D> heightMap, GLfloat height);
	GLint getWidth();
	GLint getLength();
	Vector3 getNormal(GLint x, GLint z);
	GLfloat getHeight(GLint x, GLint z);
	void setHeight(GLint x, GLint z, GLfloat h);
	
	// **Component**
	~Terrain();
	virtual void Create();
	virtual void Init();
	virtual void Update();
	virtual void Render(int materialIndex = 0);
};

inline GLint Terrain::getWidth()
{
	return width;
}

inline GLint Terrain::getLength()
{
	return length;
}

inline GLuint Terrain::getVertsCount()
{
	return getWidth()*getLength() + (getLength() - 1)*getWidth();
}

inline Vector3 Terrain::getNormal(GLint x, GLint z)
{
	if (!isNormalsComputed)
		computeNormals();

	return normals[z][x];
}

inline GLfloat Terrain::getHeight(GLint x, GLint z)
{
	return map[z][x];
}

inline void Terrain::setHeight(GLint x, GLint z, GLfloat h)
{
	map[z][x] = h;
	isNormalsComputed = false;
}

#endif