#include <map>

#include "../Debug/Logger.h"
#include "Renderer.h"

const char* Renderer::vertexAttribName = "InVertex";
const char* Renderer::texCoordAttribName = "InTexCoord0";
const char* Renderer::normalAttribName = "InNormal";
const char* Renderer::tangentAttribName = "InTangent";
const char* Renderer::bitangentAttribName = "InBitangent";

std::map<const char*, unsigned int> Renderer::AllAttributes{
	{ vertexAttribName, 0 },
	{ texCoordAttribName, 1 },
	{ normalAttribName, 2 },
	{ tangentAttribName, 3 },
	{ bitangentAttribName, 4 } 
};

std::map<const char*, unsigned int> Renderer::StandartAttributes{
	{ vertexAttribName, 0 },
	{ texCoordAttribName, 1 },
	{ normalAttribName, 2 },
};

std::map<const char*, unsigned int> Renderer::SmallAttributes{
	{ vertexAttribName, 0 },
	{ texCoordAttribName, 1 },
};

//TODO implement material and shader copy constructor to remove comment
std::vector<smart_pointer<Material>>& Renderer::getMaterials()
{
	/*for (size_t i = 0, len = materials.size(); i < len; i++)
	{
		if (getRenderSystem()->getMaterialSharesCount(materials[i]) > 1)
		{
			materials[i] = materials[i].clone();
			getRenderSystem()->addMaterialForRenderer(materials[i], this, i);
		}
	}

	return materials;*/

	return getSharedMaterials();
}

smart_pointer<Material>& Renderer::getSharedMaterial(int index)
{
	if (index < (int)materials.size())
	{
		return materials[index];
	}

	std::cout << "There is no material at index: " << index << std::endl;
	return smart_pointer<Material>::null();
}

//TODO implement material and shader copy constructor to remove comment
smart_pointer<Material>& Renderer::getMaterial(int index)
{
	/*if (index < (int)materials.size())
	{
		if (getRenderSystem()->getMaterialSharesCount(materials[index]) > 1)
		{
			printf("getMaterial:: unsharing material\n");
			materials[index] = materials[index].clone();
			getRenderSystem()->addMaterialForRenderer(materials[index], this, index);
		}

		return materials[index];
	}

	std::cout << "There is no material at index: " << index << std::endl;
	return smart_pointer<Material>::null();*/

	return getSharedMaterial(index);
}

void Renderer::addMaterial(smart_pointer<Material> mat)
{
	if (mat.isEmpty())
		return;

	materials.push_back(mat);
	getRenderSystem()->addMaterialForRenderer(mat, this, materials.size() - 1);
	initAttributes(materials.size() - 1);
}

void Renderer::setMaterial(smart_pointer<Material> mat, int index)
{
	if (mat.isEmpty())
		return;

	if (index < (int)materials.size())
	{
		materials[index] = mat;
		getRenderSystem()->removeMaterialForRenderer(materials[index], this, index);
		getRenderSystem()->addMaterialForRenderer(mat, this, index);
		initAttributes(index);
	}
	else
	{
		materials.push_back(mat);
		getRenderSystem()->addMaterialForRenderer(mat, this, materials.size() - 1);
		initAttributes(materials.size() - 1);
	}
}

void Renderer::setMainMaterial(smart_pointer<Material> mat)
{
	setMaterial(mat, 0);
}

void Renderer::setMainTexture(smart_pointer<Texture2D> texture)
{
	if (texture.isEmpty())
		return;

	if (materials.size() > 0)
	{
		materials[0]->setMainTexture(texture);
		return;
	}

	std::cout << "There is no material to set texture: " << std::endl;
}

smart_pointer<Texture2D>& Renderer::getMainTexture()
{
	if (materials.size() > 0)
		return materials[0]->getMainTexture();

	return smart_pointer<Texture2D>::null();
}

void Renderer::initAttributes(int materialIndex)
{
	smart_pointer<Material>& mat = materials[materialIndex];

	std::map<const char*, unsigned int> attributes = mat->getShader()->getAttributes();

	if (materialIndex < (int)vertexAttribLocations.size())
	{
		vertexAttribLocations[materialIndex] = attributes[vertexAttribName];
		texCoordAttribLocations[materialIndex] = attributes[texCoordAttribName];
		normalAttribLocations[materialIndex] = attributes[normalAttribName];
		tangAttribLocations[materialIndex] = attributes[tangentAttribName];
		bitangAttribLocations[materialIndex] = attributes[bitangentAttribName];
	}
	else
	{
		vertexAttribLocations.push_back(attributes[vertexAttribName]);
		texCoordAttribLocations.push_back(attributes[texCoordAttribName]);
		normalAttribLocations.push_back(attributes[normalAttribName]);
		tangAttribLocations.push_back(attributes[tangentAttribName]);
		bitangAttribLocations.push_back(attributes[bitangentAttribName]);
	}
}