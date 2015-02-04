#ifndef TERRAIN_H
#define TERRAIN_H

#include "smart_pointer.h"
#include "Texture2D.h"
#include "GameLogic.h" //TEMP

class Terrain : public Renderer
{
private:
	GLint width;
	GLint length;
	GLfloat** map;
	Vector3** normals;
	bool isNormalsComputed = false;
	void computeNormals();
public:
	void build(smart_pointer<Texture2D> heightMap, GLfloat height);
	GLint getWidth();
	GLint getLength();
	Vector3 getNormal(GLint x, GLint z);
	GLfloat getHeight(GLint x, GLint z);
	void setHeight(GLint x, GLint z, GLfloat h);
	
	// **Component**
	~Terrain();
	void Create();
	void Init();
	void Update();
};

inline GLint Terrain::getWidth()
{
	return width;
}

inline GLint Terrain::getLength()
{
	return length;
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