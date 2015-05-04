#include "Renderer.h"

std::vector<smart_pointer<Material>>& Renderer::getMaterials()
{
	for (size_t i = 0, len = materials.size(); i < len; i++)
	{
		if (getRenderSystem()->getMaterialSharesCount(materials[i]) > 1)
		{
			printf("get AllMaterials:: unsharing material\n");
			materials[i] = materials[i].clone();
			getRenderSystem()->addMaterialForRenderer(materials[i], this, i);
		}
	}

	return materials;
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

smart_pointer<Material>& Renderer::getMaterial(int index)
{
	if (index < (int)materials.size())
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
	return smart_pointer<Material>::null();
}

void Renderer::addMaterial(smart_pointer<Material> mat)
{
	if (mat.isEmpty())
		return;

	materials.push_back(mat);
	getRenderSystem()->addMaterialForRenderer(mat, this, materials.size() - 1);
	bindShaderAttributes(materials.size() - 1);
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
		bindShaderAttributes(index);
	}
	else
	{
		materials.push_back(mat);
		getRenderSystem()->addMaterialForRenderer(mat, this, materials.size() - 1);
		bindShaderAttributes(materials.size() - 1);
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

void Renderer::bindShaderAttributes(int materialIndex)
{
	if ((int)materials.size() <= materialIndex)
		return;

	smart_pointer<ShaderProgram>& shader = materials[materialIndex]->getShader();

	shader->bindAttribLocation(vertexAttribLocation, vertexAttribName);
	shader->bindAttribLocation(texCoordAttribLocation, texCoordAttribName);
	shader->bindAttribLocation(normalAttribLocation, normalAttribName);
	shader->bindAttribLocation(tangAttribLocation, tangentAttribName);
	shader->bindAttribLocation(bitangAttribLocation, bitangentAttribName);
}