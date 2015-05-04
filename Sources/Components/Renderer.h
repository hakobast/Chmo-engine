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

#include "../CoreEngine/LIBS.h"
#include "../CoreEngine/ActiveComponent.h"
#include "../Systems/RenderSystem.h"
#include "../CoreEngine/Material.h"
#include "../Extras/smart_pointer.h"

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

	/* SHADER ATTRIBUTES */
	GLint vertexAttribLocation = 0;
	GLint texCoordAttribLocation = 1;
	GLint normalAttribLocation = 2;
	GLint tangAttribLocation = 3;
	GLint bitangAttribLocation = 4;
	const char* vertexAttribName = "InVertex";
	const char* texCoordAttribName = "InTexCoord0";
	const char* normalAttribName = "InNormal";
	const char* tangentAttribName = "InTangent";
	const char* bitangentAttribName = "InBitangent";
	/* */

	std::vector<smart_pointer<Material>> materials;
	void bindShaderAttributes(int materialIndex);
	RenderSystem* getRenderSystem();
public:
	virtual ~Renderer()
	{
		for (size_t i = 0, len = materials.size(); i < len; i++)
			getRenderSystem()->removeMaterialForRenderer(materials[i], this, i);
	};

	virtual void Render(int materialIndex = 0) = 0;
	int getSortingLayer() const;
	int getLayerOrder() const;
	void setSortingLayer(int layer, int order = 0);
	void setLayerOrder(int order);
	std::vector<smart_pointer<Material>>& getMaterials();
	std::vector<smart_pointer<Material>>& getSharedMaterials();
	smart_pointer<Material>& getMaterial(int index = 0);
	smart_pointer<Material>& getSharedMaterial(int index = 0);
	smart_pointer<Texture2D>& getMainTexture();

	void addMaterial(smart_pointer<Material> mat);
	void setMaterial(smart_pointer<Material> mat, int index);
	void setMainMaterial(smart_pointer<Material> mat);
	void setMainTexture(smart_pointer<Texture2D> texture); 
};

inline RenderSystem* Renderer::getRenderSystem()
{
	static RenderSystem* rendSystem = dynamic_cast<RenderSystem*>(system);

	return rendSystem;
}

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

#endif