#include "Component.h"
#include "GameObject.h"

Component::~Component()
{
	delete node_; node_ = NULL;
}

Component::Component()
{
	node_ = new Node<Component>(this);
}

void Component::setName(std::string newName)
{
	getGameObject()->setName(newName);
}

void Component::setTag(std::string newTag)
{
	getGameObject()->setTag(newTag);
}

std::string Component::getName()
{
	return getGameObject()->getName();
}

std::string Component::getTag()
{
	return getGameObject()->getTag();
}