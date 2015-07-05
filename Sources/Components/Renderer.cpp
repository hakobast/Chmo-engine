#include <map>

#include "../Debug/Logger.h"
#include "Renderer.h"

void Renderer::OnDestroy()
{
 	for (size_t i = 0, len = materials.size(); i < len; i++)
 		renderSystem_->removeMaterialForRenderer(materials[i], this, i);
}

std::vector<smart_pointer<Material>>& Renderer::getMaterials()
{
 	for (size_t i = 0, len = materials.size(); i < len; i++)
 	{
 		if (renderSystem_->getMaterialSharesCount(materials[i]) > 1)
 		{
			renderSystem_->removeMaterialForRenderer(materials[i], this, i);
 			materials[i] = materials[i].clone();
			renderSystem_->addMaterialForRenderer(materials[i], this, i);
 		}
 	}
 
 	return materials;

	//return getSharedMaterials();
}

smart_pointer<Material>& Renderer::getSharedMaterial(int index)
{
	if (index < (int)materials.size())
	{
		return materials[index];
	}

	Logger::PrintError("There is no material at index: %d\n", index);
	return smart_pointer<Material>::null();
}

smart_pointer<Material>& Renderer::getMaterial(int index)
{
	if (index < (int)materials.size())
	{
		if (renderSystem_->getMaterialSharesCount(materials[index]) > 1)
		{
			Logger::Print("getMaterial:: unsharing material\n");
			renderSystem_->removeMaterialForRenderer(materials[index], this, index);
			materials[index] = materials[index].clone();
			renderSystem_->addMaterialForRenderer(materials[index], this, index);
		}

		return materials[index];
	}

	std::cout << "There is no material at index: " << index << std::endl;
	return smart_pointer<Material>::null();

	//return getSharedMaterial(index);
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