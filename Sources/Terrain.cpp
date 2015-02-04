
#include "Terrain.h"
#include "Input.h"


Terrain::~Terrain()
{
	for (int i = 0; i < length; i++)
	{
		delete[] map[i];
		delete[] normals[i];
	}

	delete[] map;
	delete[] normals;
}

void Terrain::build(smart_pointer<Texture2D> heightMap, GLfloat height)
{
	width = heightMap->width;
	length = heightMap->height;

	map = new GLfloat*[length];
	for (int i = 0; i < length; i++)
		map[i] = new GLfloat[width];

	normals = new Vector3*[length];
	for (int i = 0; i < length; i++)
		normals[i] = new Vector3[width];

	char* pixels = heightMap->getPixels();

	for (int y = 0; y < length; y++)
	{
		for (int x = 0; x < width; x++)
		{
			unsigned char color = (unsigned char)pixels[3 * (y*width + x)];
			GLfloat h = height * (color / 255.0f - 0.5f);
			setHeight(x, y, h);

			//printf("Height %f\n", h);
		}
	}

	isNormalsComputed = false;
}

void Terrain::computeNormals()
{
	Vector3** normals2 = new Vector3*[length];
	for (int i = 0; i < length; i++)
		normals2[i] = new Vector3[width];

	Vector3 normal_average;
	Vector3 left, right, front, back;
	for (int z = 0; z < length; z++)
	{
		for (int x = 0; x < width; x++)
		{
			normal_average.set(0.0f, 0.0f, 0.0f);

			if (x > 0){
				left.set(-1.0f, map[z][x - 1] - map[z][x], 0.0f);
			}
			if (x < width - 1){
				right.set(1.0f, map[z][x + 1] - map[z][x], 0.0f);
			}
			if (z > 0){
				back.set(0.0f, map[z - 1][x] - map[z][x], -1.0f);
			}
			if (z < length - 1){
				front.set(0.0f, map[z + 1][x] - map[z][x], 1.0f);
			}

			if (x > 0 && z > 0){
				normal_average += back.cross(left).normalize();
			}
			if (x < width - 1 && z > 0){
				normal_average += right.cross(back).normalize();
			}
			if (x < width - 1 && z < length - 1){
				normal_average += front.cross(right).normalize();
			}
			if (x > 0 && z < length - 1){
				normal_average += left.cross(front).normalize();
			}

			normals2[z][x] = normal_average;
		}
	}

	Vector3 sum;
	const float FALLOUT_RATIO = 0.5f;
	for (int z = 0; z < length; z++)
	{
		for (int x = 0; x < width; x++)
		{
			Vector3 sum = normals2[z][x];

			if (x > 0) {
				sum += normals2[z][x - 1] * FALLOUT_RATIO;
			}
			if (x < w - 1) {
				sum += normals2[z][x + 1] * FALLOUT_RATIO;
			}
			if (z > 0) {
				sum += normals2[z - 1][x] * FALLOUT_RATIO;
			}
			//if (z < 0) {
			//	printf("WTF?");
			//	sum += normals2[z + 1][x];
			//}

			if (sum.magnitude() == 0) {
				sum = Vector3(0.0f, 1.0f, 0.0f);
			}

			normals[z][x] = sum.normalize();
		}
	}


	for (int i = 0; i < length; i++)
		delete[] normals2[i];
	delete[] normals2;

	isNormalsComputed = true;
}

void Terrain::Create()
{

}

void Terrain::Init()
{

}

void Terrain::Update()
{
	getTransform()->applyTransformation();

	glColor3f(0.3f, 0.9f, 1.0f);	

	glBegin(GL_TRIANGLE_STRIP);
	for (int z = 0; z < length - 1; z++)
	{
		for (int x = 0; x < width; x++)
		{
			Vector3 norm = getNormal(x, z);
			glNormal3f(norm[0], norm[1], norm[2]); glVertex3f(x-width/2, getHeight(x, z), z-length/2);
			
			norm = getNormal(x, z + 1);
			glNormal3f(norm[0], norm[1], norm[2]); glVertex3f(x-width/2, getHeight(x, z+1), z+1 - length/2);
		}
	}
	glEnd();
}