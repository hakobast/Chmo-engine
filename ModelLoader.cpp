
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>

#include "Color.h"

#include "ModelLoader.h"

void ModelLoader::LoadObj(const char* filename, smart_pointer<Mesh>& mesh)
{
	std::vector<unsigned int> vertexIndices, normalIndices, uvIndices;
	std::vector<Vector3> vertexArray, normalArray;
	std::vector<Vector2> uvArray;

	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Imposible to open the file");
		return;
	}

	bool hasUV = false, hasN = false;
	while (1)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			Vector3 vertex;
			fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);
		//	printf("v\t%f, %f, %f\n", vertex[0], vertex[1], vertex[2]);
			
			vertexArray.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			Vector2 uv;
			fscanf(file, "%f %f\n", &uv[0], &uv[1]);
		//	printf("vt\t%f, %f\n", uv[0], uv[1]);

			uvArray.push_back(uv);
			hasUV = true;
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			Vector3 normal;
			fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
		//	printf("vn\t%f, %f %f\n", normal[0], normal[1], normal[2]);

			normalArray.push_back(normal);
			hasN = true;
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int verts[3];
			unsigned int uvs[3];
			unsigned int normals[3];

			if (!hasUV && !hasN)
			{
				fscanf(file, "%d %d %d\n",
					verts, verts + 1, verts + 2);
			}
			else if (hasUV && !hasN)
			{
				fscanf(file, "%d/%d %d/%d %d/%d\n",
					verts, uvs, verts + 1, uvs + 1, verts + 2, uvs + 2);
			}
			else if (hasN && !hasUV)
			{
				fscanf(file, "%d//%d %d//%d %d//%d\n",
					verts, normals, verts + 1, normals + 1, verts + 2, normals + 2);
			}
			else
			{
				fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
					verts, uvs, normals, verts + 1, uvs + 1, normals + 1, verts + 2, uvs + 2, normals + 2);
			}

			vertexIndices.push_back(verts[0]);
			vertexIndices.push_back(verts[1]);
			vertexIndices.push_back(verts[2]);

			if (hasUV)
			{
				uvIndices.push_back(uvs[0]);
				uvIndices.push_back(uvs[1]);
				uvIndices.push_back(uvs[2]);
			}
			if (hasN)
			{
				normalIndices.push_back(normals[0]);
				normalIndices.push_back(normals[1]);
				normalIndices.push_back(normals[2]);
			}
		}

		std::vector<Vector3>& vertices = mesh->getVertices();
		std::vector<Vector2>& uvs = mesh->getUVs();
		std::vector<Vector3>& normals = mesh->getNormals();
		std::vector<unsigned int>& indices = mesh->getIndices();

		//TODO fill indices
		for (int i = 0; i < vertexIndices.size(); i++)
		{
			vertices.push_back(vertexArray[vertexIndices[i]-1]);
			uvs.push_back(uvArray[uvIndices[i]-1]);
			normals.push_back(normalArray[normalIndices[i]-1]);
		}
	}
}

std::vector<smart_pointer<Material>> ModelLoader::LoadMtl(const char* filename)
{
	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Imposible to open the file");
		return vector<smart_pointer<Material>>();
	}

	std::vector<smart_pointer<Material>> materials;
	smart_pointer<Material> mat;

	char name[128], texture_A[128], texture_D[128], texture_S[128], texture_Alpha[128], texture_Bump[128];
	GLfloat ambient[3], diffuse[3], specular[3];

	while (1)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		char line[128];

		if (strcmp(lineHeader, "newmtl") == 0)
		{
			fscanf(file, "%s", name);
			//std::cout << "NAME: " << name << std::endl;

			mat = smart_pointer<Material>(new Material(name));
			materials.push_back(mat);
		}
		else if (strcmp(lineHeader, "map_Ka") == 0)
		{
			fscanf(file, "%s", texture_A);
			mat->ambient_texture_path = texture_A;

			//std::cout << "Ambient Texture: " << texture_A << std::endl;
		}
		else if (strcmp(lineHeader, "map_Kd") == 0)
		{
			fscanf(file, "%s", texture_D);
			mat->diffuse_texture_path = texture_D;

			//std::cout << "Diffuse Texture: " << texture_D << std::endl;
		}
		else if (strcmp(lineHeader, "map_Ks") == 0)
		{
			fscanf(file, "%s", texture_S);
			mat->specular_texture_path = texture_S;

			//std::cout << "Specular Texture: " << texture_S << std::endl;
		}
		else if (strcmp(lineHeader, "map_d") == 0)
		{
			fscanf(file, "%s", texture_Alpha);
			mat->alpha_texture_path = texture_Alpha;

			//std::cout << "Alpha Texture: " << texture_Alpha << std::endl;
		}
		else if (strcmp(lineHeader, "map_bump") == 0)
		{
			fscanf(file, "%s", texture_Bump);
			mat->bump_texture_path = texture_Bump;

			//std::cout << "Bumb Texture: " << texture_Bump << std::endl;
		}
		else if (strcmp(lineHeader, "Ns") == 0)
		{
			fscanf(file, "%f", &mat->shininess);

			//std::cout << "Shiness: " << shininess << std::endl;
		}
		else if (strcmp(lineHeader, "illum") == 0)
		{
			fscanf(file, "%d", &mat->illum);

			//std::cout << "Illum: " << illum << std::endl;
		}
		else if (strcmp(lineHeader, "d") == 0)
		{
			fscanf(file, "%f", &mat->transparency);

			//std::cout << "Transparency: " << transparency << std::endl;
		}
		else if (strcmp(lineHeader, "Ka") == 0)
		{
			fscanf(file, "%f %f %f", ambient, ambient + 1, ambient + 2);
			mat->color_ambient.set(ambient[0], ambient[1], ambient[2]);

			//printf("Ka\t%f, %f, %f\n", ambient[0], ambient[1], ambient[2]);
		}
		else if (strcmp(lineHeader, "Kd") == 0)
		{
			fscanf(file, "%f %f %f", diffuse, diffuse + 1, diffuse + 2);
			mat->color_diffuse.set(diffuse[0], diffuse[1], diffuse[2]);

			//printf("Kd\t%f, %f, %f\n", diffuse[0], diffuse[1], diffuse[2]);
		}
		else if (strcmp(lineHeader, "Ks") == 0)
		{
			fscanf(file, "%f %f %f", specular, specular + 1, specular + 2);
			mat->color_specular.set(specular[0], specular[1], specular[2]);

			//printf("Ks\t%f, %f, %f\n", specular[0], specular[1], specular[2]);
		}
	}

	return materials;
}