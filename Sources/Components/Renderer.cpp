#include <map>

#include "../Debug/Logger.h"
#include "Renderer.h"

void Renderer::OnDestroy()
{
 	for (size_t i = 0, len = materials.size(); i < len; i++)
 		renderSystem_->removeMaterialForRenderer(materials[i], this, i);
}

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
	renderSystem_->addMaterialForRenderer(mat, this, materials.size() - 1);
}

void Renderer::setMaterial(smart_pointer<Material> mat, int index)
{
	if (mat.isEmpty())
		return;

	if (index < (int)materials.size())
	{
		materials[index] = mat;
		renderSystem_->removeMaterialForRenderer(materials[index], this, index);
		renderSystem_->addMaterialForRenderer(mat, this, index);
	}
	else
	{
		materials.push_back(mat);
		renderSystem_->addMaterialForRenderer(mat, this, materials.size() - 1);
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