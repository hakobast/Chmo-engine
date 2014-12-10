//
//  Transform.h
//  OpenGLTesting
//
//  Created by Hakob on 11/7/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef OpenGLTesting_Renderer_h
#define OpenGLTesting_Renderer_h


#include <GL\glut.h>
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
	RenderSystem* renderSystem;
	std::vector<smart_pointer<Material>> materials;
public:
	int getSortingLayer() const;
	int getLayerOrder() const;
	void setSortingLayer(int layer, int order = 0);
	void setLayerOrder(int order);
	std::vector<smart_pointer<Material>>const getMaterials();
	smart_pointer<Material>& getMaterial(int index);
	smart_pointer<Material>& getMainMaterial();
	smart_pointer<Texture2D>& getMainTexture();
	void setMaterial(smart_pointer<Material>& mat, int index, bool copy = true);
	void setMainMaterial(smart_pointer<Material>& mat, bool copy = true);
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
	renderSystem->sortComponents();
}

inline void Renderer::setLayerOrder(int order)
{
	layerOrder = order;
	renderSystem->sortComponents();
}

inline std::vector<smart_pointer<Material>>const Renderer::getMaterials()
{
	return materials;
}

inline smart_pointer<Material>& Renderer::getMaterial(int index)
{
	return materials[index];
}

inline smart_pointer<Material>& Renderer::getMainMaterial()
{
	return materials[0];
}

inline void Renderer::setMaterial(smart_pointer<Material>& mat, int index, bool copy)
{
	if (materials.size() <= index)
	{
		std::cout << "There is no material at index";
		return;
	}

	if (copy)
	{
		materials[index] = mat.clone();
	}
	else
	{
		materials[index] = mat;
	}
}

inline void Renderer::setMainMaterial(smart_pointer<Material>& mat, bool copy)
{
	if (copy)
	{
		if (materials.size() > 0)
			materials[0] = mat.clone();
		else
			materials.push_back(mat.clone());
	}
	else
	{
		if (materials.size() > 0)
			materials[0] = mat;
		else
			materials.push_back(mat);
	}
}

inline void Renderer::setMainTexture(smart_pointer<Texture2D>& texture)
{
	materials[0]->texture_diffuse = texture;
}

inline smart_pointer<Texture2D>& Renderer::getMainTexture()
{
	return materials[0]->texture_diffuse;
}

#endif