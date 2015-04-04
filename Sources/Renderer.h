//
//  Transform.h
//  OpenGLTesting
//
//  Created by Hakob on 11/7/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef OpenGLTesting_Renderer_h
#define OpenGLTesting_Renderer_h

#include <assert.h>

#include "GL_LIBS.h"

#include "ActiveComponent.h"
#include "RenderSystem.h"
#include "Material.h"
#include "smart_pointer.h"

enum SortingLayer
{
	Background = 0,
	Default = 1,
	Player = 2
};

class Renderer : public ActiveComponent
{
friend class RenderSystem;
protected:
	int sortingLayer = Default;
	int layerOrder = 0;
	std::vector<smart_pointer<Material>> materials;
public:
	virtual ~Renderer()
	{
		for (int i = 0; i < materials.size(); i++)
			materials[i]->_sharesCount--;
	};

	int getSortingLayer() const;
	int getLayerOrder() const;
	void setSortingLayer(int layer, int order = 0);
	void setLayerOrder(int order);
	std::vector<smart_pointer<Material>>& getMaterials();
	std::vector<smart_pointer<Material>>& getSharedMaterials();
	smart_pointer<Material>& getMaterial(int index = 0);
	smart_pointer<Material>& getSharedMaterial(int index = 0);
	smart_pointer<Texture2D>& getMainTexture();

	void addMaterial(smart_pointer<Material>& mat);
	void setMaterial(smart_pointer<Material>& mat, int index);
	void setMainMaterial(smart_pointer<Material>& mat);
	void setMainTexture(smart_pointer<Texture2D>& texture); 
};

inline int Renderer::getLayerOrder() const
{
	return layerOrder;
}

inline int Renderer::getSortingLayer() const
{
	return sortingLayer;
}

inline void Renderer::setSortingLayer(int layer, int order)
{
	sortingLayer = layer;
	layerOrder = order;
	if (isEnabled())
		dynamic_cast<RenderSystem*>(system)->sortComponents();
}

inline void Renderer::setLayerOrder(int order)
{
	layerOrder = order;
	if (isEnabled())
		dynamic_cast<RenderSystem*>(system)->sortComponents();
}

inline std::vector<smart_pointer<Material>>& Renderer::getSharedMaterials()
{
	return materials;
}

inline std::vector<smart_pointer<Material>>& Renderer::getMaterials()
{
	for (int i = 0; i < materials.size(); i++)
	{
		if (materials[i]->_sharesCount > 1)
		{
			printf("get AllMaterials:: unsharing material\n");
			materials[i] = materials[i].clone();
			materials[i]->_sharesCount = 1;
		}
	}

	return materials;
}

inline smart_pointer<Material>& Renderer::getSharedMaterial(int index)
{
	if (index < materials.size())
	{
		return materials[index];
	}

	std::cout << "There is no material at index: " << index << std::endl;
	return smart_pointer<Material>::null();
}

inline smart_pointer<Material>& Renderer::getMaterial(int index)
{
	if (index < materials.size())
	{
		if (materials[index]->_sharesCount > 1)
		{
			printf("getMaterial:: unsharing material\n");
			materials[index] = materials[index].clone();
			materials[index]->_sharesCount = 1;
		}

		return materials[index];
	}

	std::cout << "There is no material at index: " << index << std::endl;
	return smart_pointer<Material>::null();
}

inline void Renderer::addMaterial(smart_pointer<Material>& mat)
{
	if (mat.isEmpty())
		return;

	materials.push_back(mat);
	mat->_sharesCount++;
}

inline void Renderer::setMaterial(smart_pointer<Material>& mat, int index)
{
	if (mat.isEmpty())
		return;

	if (index < materials.size())
	{
		materials[index]->_sharesCount--;
		materials[index] = mat;
	}
	else
	{
		materials.push_back(mat);
	}

	mat->_sharesCount++;
}

inline void Renderer::setMainMaterial(smart_pointer<Material>& mat)
{
	setMaterial(mat, 0);
}

inline void Renderer::setMainTexture(smart_pointer<Texture2D>& texture)
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

inline smart_pointer<Texture2D>& Renderer::getMainTexture()
{
	if (materials.size() > 0)
		return materials[0]->getMainTexture();

	return smart_pointer<Texture2D>::null();
}

#endif