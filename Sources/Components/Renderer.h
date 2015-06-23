#ifndef RENDERER_H
#define RENDERER_H

#include "../CoreEngine/LIBS.h"
#include "../CoreEngine/ActiveComponent.h"
#include "../Systems/RenderSystem.h"
#include "../CoreEngine/Material.h"
#include "../Extras/smart_pointer.h"
#include "../Extras/DoubleLinkedList.h"

enum SortingLayer
{
	Background = 0,
	Default = 1,
	Player = 2
};

class Renderer : public ActiveComponent
{
friend class RenderSystem;
private:
	Node<Renderer>* renderSystemNode_;
protected:
	RenderSystem* renderSystem_;
	int sortingLayer = Default;
	int layerOrder = 0;

	std::vector<smart_pointer<Material>> materials;
public:

	Renderer(){ renderSystemNode_ = new Node<Renderer>(this); }
	~Renderer(){ delete renderSystemNode_; renderSystemNode_ = NULL; }
	virtual void OnDestroy();
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

	virtual void addMaterial(smart_pointer<Material> mat);
	virtual void setMaterial(smart_pointer<Material> mat, int index);
	void setMainMaterial(smart_pointer<Material> mat);
	void setMainTexture(smart_pointer<Texture2D> texture); 
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
		renderSystem_->sortComponents();
}

inline void Renderer::setLayerOrder(int order)
{
	layerOrder = order;
	if (isEnabled())
		renderSystem_->sortComponents();
}

inline std::vector<smart_pointer<Material>>& Renderer::getSharedMaterials()
{
	return materials;
}

#endif