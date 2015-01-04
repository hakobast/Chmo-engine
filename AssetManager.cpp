
#include <math.h>
#include <sstream>
#include <queue>

#include "MeshRenderer.h"
#include "AssetManager.h"

std::vector<GameObject*> LoadModel(const char* modelfile, const char* materialfile)
{
	vector<GameObject*> gameObjects;

	//ModelDescriptor descriptor;
	std::vector<smart_pointer<Mesh>>& meshes = LoadMesh(modelfile);

	/*for (std::string mesh : descriptor.meshNames)
		std::cout << "g " << mesh << " mat " << descriptor.meshMaterials[mesh] << std::endl;*/

	std::vector<smart_pointer<Material>>& materials = LoadMtl(materialfile);
	std::queue<smart_pointer<Material>> matQueue;
	for (smart_pointer<Material> mat : materials)
		matQueue.push(mat);

	GameObject* obj;
	for (int i = 0; i < meshes.size(); i++)
	{
		std::stringstream stream;
		if (meshes[i]->getSubMeshCount() > 1)
			stream << "Obj" << i;
		else
			stream << "Mesh Name";

		obj = new GameObject(stream.str());
		MeshRenderer* meshRenderer = obj->addComponent<MeshRenderer>();
		meshRenderer->setSharedMesh(meshes[i]);
		
		//attaching materials
		for (int j = 0; j < meshes[i]->getSubMeshCount() && matQueue.size() > 0; j++)
		{
			meshRenderer->addMaterial(matQueue.front());
			matQueue.pop();
		}

		gameObjects.push_back(obj);
	}

	std::cout << "***********************************" << std::endl;
	for (GameObject* obj : gameObjects)
	{
		std::cout << "Name: " << obj->name << std::endl;
		std::cout << "Submeshes: " << obj->getComponent<MeshRenderer>()->getMesh()->getSubMeshCount() << std::endl;
		std::cout << "Materials: " << obj->getComponent<MeshRenderer>()->getMaterials().size() << std::endl;
	}
	std::cout << "***********************************" << std::endl;

	return gameObjects;
}

std::vector<smart_pointer<Mesh>> LoadMesh(const char* filename, ModelDescriptor* descriptor)
{
	std::vector<std::string> meshNames;
	std::vector<smart_pointer<Mesh>> meshes;
	std::vector<unsigned int> vertexIndices, normalIndices, uvIndices;
	std::vector<Vector3> vertexArray, normalArray;
	std::vector<Vector2> uvArray;

	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Imposible to open the file\n");
		return meshes;
	}

	char lineHeader[128];
	char line[128];
	while (1)
	{
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "g") == 0)
		{
			fscanf(file, "%s\n", line);
			meshNames.push_back(line);

			if (meshes.size() > 0)
			{
				setVertexAttributes(meshes.back(), 0,
					vertexArray, uvArray, normalArray,
					vertexIndices, uvIndices, normalIndices);

				vertexIndices.clear();
				uvIndices.clear();
				normalIndices.clear();
			}

			meshes.push_back(smart_pointer<Mesh>(new Mesh()));
		}
		else if (strcmp(lineHeader, "o") == 0)
		{
			fscanf(file, "%s\n", line);
			meshNames.push_back(line);

			if (meshes.size() == 0) //first time, create mesh and one submesh in constructor
			{
				meshes.push_back(smart_pointer<Mesh>(new Mesh()));
			}
			else if (meshes.back()->getSubMeshCount() > 0) // other times, setVertexAttributes and add new submesh
			{
				setVertexAttributes(meshes.back(), meshes.back()->getSubMeshCount()-1,
					vertexArray, uvArray, normalArray,
					vertexIndices, uvIndices, normalIndices);

				vertexIndices.clear();
				uvIndices.clear();
				normalIndices.clear();

				meshes.back()->setSubMeshCount(meshes.back()->getSubMeshCount() + 1);
			}

		}
		else if (strcmp(lineHeader, "mtllib") == 0)
		{
			if (descriptor != NULL)
			{
				fscanf(file, "%s\n", descriptor->matfile);
			}
		}
		else if (strcmp(lineHeader, "usemtl") == 0) //TODO support material for faces
		{
			if (descriptor != NULL)
			{
				fscanf(file, "%s\n", line);
				descriptor->meshMaterials[meshNames.back()] = line;
			}
		}
		else if (strcmp(lineHeader, "v") == 0)
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
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			Vector3 normal;
			fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
			//	printf("vn\t%f, %f %f\n", normal[0], normal[1], normal[2]);

			normalArray.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) //parsing faces
		{
			int v = 0, u = 0, n = 0;
			std::vector<unsigned int> verts;
			std::vector<unsigned int> uvs;
			std::vector<unsigned int> normals;

			char line[128];
			fgets(line, sizeof(line), file);

			char* vertexToken = strtok(line, " ");

			if (uvArray.size() == 0 && normalArray.size() == 0)			// only vertex attribute
			{
				while (vertexToken != NULL)
				{
					sscanf(vertexToken, "%d", &v);

					if (v < 0)
						v += vertexArray.size() + 1;
					verts.push_back(v);
					vertexToken = strtok(NULL, " ");
				}

				/*fscanf(file, " %d %d %d\n",
				verts, verts + 1, verts + 2);*/
			}
			else if (uvArray.size() > 0 && normalArray.size() == 0)			// vertex and uv attributes
			{
				while (vertexToken != NULL)
				{
					sscanf(vertexToken, "%d/%d", &v, &u);

					if (v < 0)
						v += vertexArray.size() + 1;
					if (u < 0)
						u += uvArray.size() + 1;
					verts.push_back(v);	uvs.push_back(u);
					vertexToken = strtok(NULL, " ");
				}

				/*fscanf(file, "%d/%d %d/%d %d/%d\n",
				verts, uvs, verts + 1, uvs + 1, verts + 2, uvs + 2);*/
			}
			else if (normalArray.size() > 0 && uvArray.size() == 0)		// vertex and normal attributes
			{
				while (vertexToken != NULL)
				{
					sscanf(vertexToken, "%d//%d", &v, &n);

					if (v < 0)
						v += vertexArray.size() + 1;
					if (n < 0)
						n += normalArray.size() + 1;
					verts.push_back(v);	normals.push_back(n);
					vertexToken = strtok(NULL, " ");
				}

				/*fscanf(file, "%d//%d %d//%d %d//%d\n",
				verts, normals, verts + 1, normals + 1, verts + 2, normals + 2);*/
			}
			else			// vertex,uv and normal attributes
			{
				while (vertexToken != NULL)
				{
					sscanf(vertexToken, "%d/%d/%d", &v, &u, &n);

					if (v < 0)
						v += vertexArray.size() + 1;
					if (u < 0)
						u += uvArray.size() + 1;
					if (n < 0)
						n += normalArray.size() + 1;
					verts.push_back(v);	uvs.push_back(u);	normals.push_back(n);
					vertexToken = strtok(NULL, " ");
				}

				//fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				//verts, uvs, normals, verts + 1, uvs + 1, normals + 1, verts + 2, uvs + 2, normals + 2);
			}

			for (int i = 1; i < verts.size() - 1; i++)
			{
				vertexIndices.push_back(verts[0]);
				vertexIndices.push_back(verts[i]);
				vertexIndices.push_back(verts[i + 1]);

				if (uvs.size() > 0)
				{
					uvIndices.push_back(uvs[0]);
					uvIndices.push_back(uvs[i]);
					uvIndices.push_back(uvs[i + 1]);
				}
				if (normals.size() > 0)
				{
					normalIndices.push_back(normals[0]);
					normalIndices.push_back(normals[i]);
					normalIndices.push_back(normals[i + 1]);
				}
			}
		} //if face

	}//while

	if (vertexArray.size() > 0)
	{
		//check when file doesn't contain g or o attributes
		if (meshes.size() == 0)
		{
			smart_pointer<Mesh> mesh(new Mesh());
			meshes.push_back(mesh);
		}

		setVertexAttributes(meshes.back(), meshes.back()->getSubMeshCount()-1,
			vertexArray, uvArray, normalArray,
			vertexIndices, uvIndices, normalIndices);
	}

	if (descriptor != NULL)
		descriptor->meshNames = meshNames;

	return meshes;
}

void setVertexAttributes(smart_pointer<Mesh>& mesh, int subMesh,
	std::vector<Vector3>& v,
	std::vector<Vector2>& u,
	std::vector<Vector3>& n,
	std::vector<unsigned int>& vIndices,
	std::vector<unsigned int>& uIndices,
	std::vector<unsigned int>& nIndices)

{
	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
	std::vector<unsigned int> indices;

	//TODO make indexing
	for (int i = 0; i < vIndices.size(); i++)
	{
		//std::cout << "V " << v.size() << " Index " << (vIndices[i] - 1) << std::endl;
		vertices.push_back(v[vIndices[i] - 1]);

		if (uIndices.size()>0)
			uvs.push_back(u[uIndices[i] - 1]);
		if (nIndices.size()>0)
			normals.push_back(n[nIndices[i] - 1]);
	}

	mesh->setVertices(vertices, subMesh);
	mesh->setUVs(uvs, subMesh);
	mesh->setNormals(normals, subMesh);
}

std::vector<smart_pointer<Material>> LoadMtl(const char* filename)
{
	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Imposible to open the file\n");
		return vector<smart_pointer<Material>>();
	}

	std::vector<smart_pointer<Material>> materials;
	smart_pointer<Material> mat;

	GLfloat ambient[3], diffuse[3], specular[3];

	char line[128];
	char lineHeader[128];
	while (1)
	{
		int res = fscanf(file, "%s ", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "newmtl") == 0)
		{
			fscanf(file, "%s\n", line);
			//std::cout << "NAME: " << name << std::endl;

			mat = smart_pointer<Material>(new Material(line));
			materials.push_back(mat);
		}
		else if (strcmp(lineHeader, "map_Ka") == 0)
		{
			fgets(line, sizeof(line), file);
			size_t length = strlen(line) - 1;
			if (line[length] == '\n')
				line[length] = '\0';

			mat->texture_ambient = smart_pointer<Texture2D>(new Texture2D(line));

			//std::cout << "Ambient Texture: " << line << " Size " << sizeof(line) << std::endl;
		}
		else if (strcmp(lineHeader, "map_Kd") == 0)
		{
			fgets(line, sizeof(line), file);
			size_t length = strlen(line)-1;
			if (line[length] == '\n')
				line[length] = '\0';

			mat->texture_diffuse = smart_pointer<Texture2D>(new Texture2D(line));

			//std::cout << "Diffuse Texture: " << texture_D << std::endl;
		}
		else if (strcmp(lineHeader, "map_Ks") == 0)
		{
			fgets(line, sizeof(line), file);
			size_t length = strlen(line) - 1;
			if (line[length] == '\n')
				line[length] = '\0';

			mat->texture_specular = smart_pointer<Texture2D>(new Texture2D(line));

			//std::cout << "Specular Texture: " << texture_S << std::endl;
		}
		else if (strcmp(lineHeader, "map_d") == 0)
		{
			fgets(line, sizeof(line), file);
			size_t length = strlen(line) - 1;
			if (line[length] == '\n')
				line[length] = '\0';

			mat->texture_alpha = smart_pointer<Texture2D>(new Texture2D(line));

			//std::cout << "Alpha Texture: " << texture_Alpha << std::endl;
		}
		else if (strcmp(lineHeader, "map_bump") == 0)
		{
			fgets(line, sizeof(line), file);
			size_t length = strlen(line) - 1;
			if (line[length] == '\n')
				line[length] = '\0';

			mat->texture_bump = smart_pointer<Texture2D>(new Texture2D(line));

			//std::cout << "Bumb Texture: " << texture_Bump << std::endl;
		}
		else if (strcmp(lineHeader, "Ns") == 0)
		{
			fscanf(file, "%f\n", &mat->shininess);

			//std::cout << "Shiness: " << shininess << std::endl;
		}
		else if (strcmp(lineHeader, "illum") == 0)
		{
			fscanf(file, "%d\n", &mat->illum);

			//std::cout << "Illum: " << illum << std::endl;
		}
		else if (strcmp(lineHeader, "d") == 0)
		{
			float tr = 1.0f;
			fscanf(file, "%f\n", &tr);
			mat->color_diffuse.setA(tr);
			//std::cout << "Transparency: " << transparency << std::endl;
		}
		else if (strcmp(lineHeader, "Ka") == 0)
		{
			fscanf(file, "%f %f %f\n", ambient, ambient + 1, ambient + 2);
			mat->color_ambient.set(ambient[0], ambient[1], ambient[2]);

			//printf("Ka\t%f, %f, %f\n", ambient[0], ambient[1], ambient[2]);
		}
		else if (strcmp(lineHeader, "Kd") == 0)
		{
			fscanf(file, "%f %f %f\n", diffuse, diffuse + 1, diffuse + 2);
			mat->color_diffuse.set(diffuse[0], diffuse[1], diffuse[2]);

			//printf("Kd\t%f, %f, %f\n", diffuse[0], diffuse[1], diffuse[2]);
		}
		else if (strcmp(lineHeader, "Ks") == 0)
		{
			fscanf(file, "%f %f %f\n", specular, specular + 1, specular + 2);
			mat->color_specular.set(specular[0], specular[1], specular[2]);

			//printf("Ks\t%f, %f, %f\n", specular[0], specular[1], specular[2]);
		}
	}

	return materials;
}