
#include "Terrain.h"
#include "Input.h"


Terrain::~Terrain()
{
	//for (int i = 0; i < length; i++)
	//{
	//	delete[] map[i];
	//	delete[] normals[i];
	//}

	//delete[] map;
	//delete[] normals;

	if (verts != NULL)
		delete[] verts;
	if (norms != NULL)
		delete[] verts;
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
	
	for (int z = 0; z < length; z++)
	{
		for (int x = 0; x < width; x++)
		{
			unsigned char color = (unsigned char)pixels[3 * (z*width + x)];
			GLfloat h = height * (color / 255.0f - 0.5f);
			setHeight(x, z, h);

			//verts[index++].set(x - width / 2, h, z - length / 2);
			//if (z + 1 < length)
			//{
			//	int z_plus = z + 1;
			//	unsigned char color = (unsigned char)pixels[3 * (z_plus*width + x)];
			//	GLfloat h = height * (color / 255.0f - 0.5f);
			//	verts[index++].set(x - width / 2, h, z_plus - length / 2);
			//}

			//printf("Height %f\n", h);
		}
	}

	computeNormals();

	verts = new Vector3[getVertsCount()];
	norms = new Vector3[getVertsCount()];
	textures = new Vector2[getVertsCount()];

	int index = 0;
	for (int z = 0; z < length; z++)
	{
		for (int x = 0; x < width; x++)
		{
			verts[index].set(x - width / 2, getHeight(x, z), z - length / 2);
			textures[index].set((GLfloat)x / width, (GLfloat)z / width);
			norms[index] = normals[z][x];
			index++;
			if (z + 1 < length)
			{
				int z_plus = z + 1;
				verts[index] = Vector3(x - width / 2, getHeight(x, z_plus), z_plus - length / 2);
				textures[index].set((GLfloat)x / width, (GLfloat)z_plus / width);
				norms[index] = normals[z_plus][x];
				index++;
			}
		}
	}

	if (glewGetExtension("GL_ARB_vertex_buffer_object"))
	{
		glGenBuffersARB(1, &vertex_vbo_id);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertex_vbo_id);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(Vector3)*getVertsCount(), verts, GL_STATIC_DRAW_ARB);
		delete[] verts;

		glGenBuffersARB(1, &normal_vbo_id);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, normal_vbo_id);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(Vector3)*getVertsCount(), norms, GL_STATIC_DRAW_ARB);
		delete[] norms;

		glGenBuffersARB(1, &texture_vbo_id);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, texture_vbo_id);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(Vector2)*getVertsCount(), textures, GL_STATIC_DRAW_ARB);
		delete[] textures;
	}

	for (int i = 0; i < length; i++)
	{
		delete[] map[i];
		delete[] normals[i];
	}

	delete[] map;
	delete[] normals;

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
			if (x < width - 1) {
				sum += normals2[z][x + 1] * FALLOUT_RATIO;
			}
			if (z > 0) {
				sum += normals2[z - 1][x] * FALLOUT_RATIO;
			}
			if (z < length-1) {
				sum += normals2[z + 1][x] * FALLOUT_RATIO;
			}

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

	smart_pointer<Texture2D>& mainTexture = getMainTexture();
	if (!mainTexture.isEmpty())
		getMainMaterial()->bind();

	//glColor3f(0.3f, 0.9f, 1.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (glewGetExtension("GL_ARB_vertex_buffer_object"))
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertex_vbo_id);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, normal_vbo_id);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, texture_vbo_id);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, getVertsCount());

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	}
	else
	{
		glVertexPointer(3, GL_FLOAT, 0, verts);
		glNormalPointer(GL_FLOAT, 0, norms);
		glTexCoordPointer(2, GL_FLOAT, 0, textures);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, getVertsCount());
	}

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	if (!mainTexture.isEmpty())
		getMainMaterial()->unbind();

	/*glBegin(GL_TRIANGLE_STRIP);
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
	glEnd();*/
}