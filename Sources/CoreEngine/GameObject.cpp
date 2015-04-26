//
//  GameObject.cpp
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>

#include "GameObject.h"
#include "GameLogic.h"

using namespace std;

GameObject::GameObject(string name)
{
	this->name = name;

	//cout << "GameObject: " << name << " GameObject()" << endl;

	//adding Transform component to all gameobjects
	Transform* trComp = new Transform();
	trComp->gameObject = this;
	trComp->transform = trComp;

	transform = trComp;
	components.push_back(trComp);

	std::cout << "GameObject() " << name << std::endl;

	Engine::getInstance().addComponent(*trComp, trComp->priority);
	Engine::getInstance().addGameObject(*this);
}

GameObject::~GameObject()
{
	components.clear();
	cout << "GameObject ~~~~deleted " << name << " ~GameObject()" << endl;
}

void GameObject::sendAction(string action, void*const data)
{
	for (Component *c : components)
	if (dynamic_cast<GameLogic*>(c))
		((GameLogic*)c)->OnAction(action, data);
}	

void GameObject::sendMessage(string function, void *data)
{

}

void GameObject::setActive(bool toogle)
{
	if (_isActive == toogle)
		return;

	//if toogle is true we call component's setEnable which check if the 
	//gameobject is active than call his state-callbacks.
	//maybe this is bad solution but it works :)
	if (toogle)
		_isActive = toogle;

	for (Component* comp : components)
	{
		ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(comp);
		if (activeComp != NULL && activeComp->enabled)
		{
			activeComp->setEnabled(toogle);
			activeComp->enabled = true; // restoring component's real state
		}
	}

	_isActive = toogle;
}

void GameObject::removeComponent(Component* comp)
{
	vectorRemove<Component>(components, comp);
	Engine::getInstance().removeComponent(*comp);
}

void GameObject::destroy()
{
	if (destroyState)
		return;

	destroyState = true;

	for (size_t i = 1, len = components.size(); i < len; i++)
	{
		ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(components[i]);
		if (activeComp != NULL)
			activeComp->_destroy();
		Engine::getInstance().removeComponent(*components[i]);
	}
	components.erase(components.begin() + 1, components.end());

	Engine::getInstance().removeGameObject(*this);
}

//******static*****
GameObject* GameObject::FindGameObjectByName(std::string name)
{
	return Engine::getInstance().FindGameObjectByName(name);
}