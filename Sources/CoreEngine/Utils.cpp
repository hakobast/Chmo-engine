#include <chrono>

#include "Utils.h"

unsigned long long timeInMilliseconds()
{
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

wchar_t* charToWChar(const char* text)
{
	size_t size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs(wa, text, size);
	return wa;
}

char* loadFile(const char* filename)
{
	if (filename == NULL)
		return NULL;

	FILE* file = fopen(filename, "r");
	if (file == NULL)
		return NULL;

	unsigned int sLength = 0;
	char* text = NULL;

	while (fgetc(file) != EOF)
	{
		sLength++;
	}
	text = (char *)malloc(sLength + 1);

	rewind(file);
	if (text != NULL)
	{
		fread(text, 1, sLength, file);
	}

	text[sLength] = '\0';
	fclose(file);

	return text;
}

// calculates tangents for simple Triangle rendering
void calcTangent(std::vector<Vector3>& verts, std::vector<Vector2>& texcoords, std::vector<Vector3>&normals, Vector3* tangent, Vector3* bitangent)
{
	for (size_t t = 0, len = verts.size()/3; t < len; t++)
	{
		Vector3& V0 = verts[t]; // (verts[t * 3], verts[t * 3 + 1], verts[t * 3 + 2]);
		Vector3& V1 = verts[t + 1]; // (verts[t * 3 + 3], verts[t * 3 + 4], verts[t * 3 + 5]);
		Vector3& V2 = verts[t+ 2]; // (verts[t * 3 + 6], verts[t * 3 + 7], verts[t * 3 + 8]);

		Vector2& UV0 = texcoords[t];// (texcoords[t * 2], texcoords[t * 2 + 1]);
		Vector2& UV1 = texcoords[t + 1]; // (texcoords[t * 2 + 2], texcoords[t * 2 + 3]);
		Vector2& UV2 = texcoords[t + 2]; // (texcoords[t * 2 + 4], texcoords[t * 2 + 5]);

		Vector3 E1 = V1 - V0;
		Vector3 E2 = V2 - V0;

		Vector2 DUV1 = UV1 - UV0;
		Vector2 DUV2 = UV2 - UV0;

		GLfloat r = 1.0f / (DUV1.x*DUV2.y - DUV2.x*DUV1.y);

		tangent[t * 3]     += (E1*DUV2.y - E2*DUV1.y)*r;
		tangent[t * 3 + 1] += (E1*DUV2.y - E2*DUV1.y)*r;
		tangent[t * 3 + 2] += (E1*DUV2.y - E2*DUV1.y)*r;

		bitangent[t * 3]     += (E2*DUV1.x - E1*DUV2.x)*r;
		bitangent[t * 3 + 1] += (E2*DUV1.x - E1*DUV2.x)*r;
		bitangent[t * 3 + 2] += (E2*DUV1.x - E1*DUV2.x)*r;
	}

	for (int i = 0; i < 4; i++)
	{
		Vector3& normal = normals[i]; // (normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
		Vector3& tang = tangent[i];

		//Gram-Schmidt Orthogonalization
		tangent[i] = (tang - normal*(normal.dot(tang))).normalize();

		//fixing handedness
		if (normal.cross(tang).dot(bitangent[i]) < 0.0f)
			tangent[i] = tangent[i] * -1.0f;
	}
}

GLboolean isExtensionSupported(const char* extension)
{
	const GLubyte* exts = glGetString(GL_EXTENSIONS);
	char* extToken = strtok((char*)exts, " ");

	while (extToken != NULL)
	{
		int res = strcmp(extToken, extension);

		if (res == 0)
			return true;

		extToken = strtok(NULL, " ");
	}

	return false;
}

GLboolean isVBOSupported()
{
	static bool first = true;
	static GLboolean hasVBO;
	if (first)
	{
		hasVBO = isExtensionSupported("GL_ARB_vertex_buffer_object");
		first = false;
	}

	return hasVBO;
}
