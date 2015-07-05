
#include "../CoreEngine/LIBS.h"
#include "../Components/Camera.h"
#include "ScreenSystem.h"

void ScreenSystem::OnScreenChange(int width, int height)
{
	this->width = width;
	this->height = height;

	DoubleLinkedList<Camera>::iterator iter = componentsList_.getIterator();
	while (iter.hasNext())
		iter.next()->data->ApplyCameraChanges();
}

void ScreenSystem::addComponent(Component &c)
{
	if (isSystemComponent(c))
	{
		addToBuffer(&c);
	}
}

void ScreenSystem::removeComponent(Component &c)
{
	if (isSystemComponent(c))
	{
		componentsList_.remove(static_cast<Camera*>(&c)->screenSystemNode_);
		removeFromBuffer(&c);
	}
}

bool ScreenSystem::isSystemComponent(Component &c)
{
	return dynamic_cast<Camera*>(&c) != NULL;
}

void ScreenSystem::OnBufferChange(std::vector<Component*>& components)
{
	for (Component* component : components)
	{
		component->Init();
		componentsList_.addToBack(static_cast<Camera*>(component)->screenSystemNode_);
	}
}

std::vector<Component*> ScreenSystem::getComponents()
{
	vector<Component*> components;

	DoubleLinkedList<Camera>::iterator iter = componentsList_.getIterator();
	while (iter.hasNext())
		components.push_back(iter.next()->data);

	return components;
}