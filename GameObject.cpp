//
//  GameObject.cpp
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include "GameObject.h"
#include "ActiveComponent.h"
#include "GameLogic.h"
#include "Engine.h"
#include <iostream>

using namespace std;

GameObject::GameObject(string name)
{
	GameObject::name = name;

	cout << "GameObject: " << name << " GameObject()" << endl;

	//adding Transform component to all gameobjects
	GameTransform* trComp = new GameTransform();
	trComp->gameObject = this;
	trComp->transform = trComp;

	transform = trComp;
	components.push_back(trComp);

	Engine::getInstance().addComponent(*trComp, trComp->priority);
	Engine::getInstance().addGameObject(*this);
}

GameObject::~GameObject()
{
	for (Component *comp : components)
	{
		Engine::getInstance().removeComponent(*comp);
		delete comp;
	}
	cout << "GameObject: " << name << " ~GameObject()" << endl;
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
	_isActive = toogle;
}

void GameObject::removeComponent(Component* comp)
{
	vectorRemove(components, *comp);
	Engine::getInstance().removeComponent(*comp);
	delete comp;
}

void GameObject::destroy()
{ 
	delete this;
}

GameObject* GameObject::FindGameObjectByName(std::string name)
{
	return Engine::getInstance().FindGameObjectByName(name);
}