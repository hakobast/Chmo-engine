#include "Component.h"
#include "GameObject.h"

std::string Component::getName()
{
	return getGameObject()->name;
}

std::string Component::getTag()
{
	return getGameObject()->tag;
}