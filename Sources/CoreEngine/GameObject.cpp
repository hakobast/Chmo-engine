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
	trComp->gameObject_ = this;
	trComp->transform_ = trComp;

	transform_ = trComp;
	components_.push_back(trComp);

	//std::cout << "GameObject() " << name << std::endl;

	Engine::GetInstance().addComponent(*trComp, trComp->priority);
	Engine::GetInstance().addGameObject(*this);
}

GameObject::~GameObject()
{
	components_.clear();
	//cout << "GameObject ~~~~deleted " << name << " ~GameObject()" << endl;
}

void GameObject::sendAction(string action, void*const data)
{
	for (size_t i = 0; i < components_.size(); i++)
		if (dynamic_cast<GameLogic*>(components_[i]))
			((GameLogic*)components_[i])->OnAction(action, data);
}

void GameObject::setActive(bool toogle)
{
	if (isActive_ == toogle)
		return;

	for (Component* comp : components_)
	{
		ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(comp);
		if (activeComp != NULL && activeComp->enabled)
		{
			activeComp->setEnabled(toogle);
			activeComp->enabled = true; // keeping component's real state
		}
	}

	isActive_ = toogle;
}

void GameObject::removeComponent(Component* comp)
{
	vectorRemove<Component>(components_, comp);
	Engine::GetInstance().removeComponent(*comp);
}

void GameObject::destroy()
{
	if (destroyState_)
		return;

	destroyState_ = true;

	for (size_t i = 1, len = components_.size(); i < len; i++)
	{
		ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(components_[i]);
		if (activeComp != NULL)
		{
			activeComp->OnDisable();
			activeComp->_destroy();
		}
		Engine::GetInstance().removeComponent(*components_[i]);
	}
	components_.erase(components_.begin() + 1, components_.end());

	Engine::GetInstance().removeGameObject(*this);
}

//******static*****
GameObject* GameObject::FindGameObjectByName(std::string name)
{
	return Engine::GetInstance().FindGameObjectByName(name);
}