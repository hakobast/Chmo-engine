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
: name_(name)
{
	//cout << "GameObject: " << name << " GameObject()" << endl;

	node_ = new Node<GameObject>(this);

	//adding Transform component to all gameobjects
	Transform* trComp = new Transform();
	trComp->gameObject_ = this;
	trComp->transform_ = trComp;

	transform_ = trComp;
	componentsList_.addToBack(trComp->node_);

	Engine::GetInstance().addComponent(trComp);
	Engine::GetInstance().addGameObject(this);

	trComp->Create();
}

GameObject::~GameObject()
{
	//cout << "GameObject ~~~~deleted " << name << " ~GameObject()" << endl;
	delete node_; node_ = NULL;
}

void GameObject::sendAction(string action, void*const data)
{
	DoubleLinkedList<Component>::iterator iter = componentsList_.getIterator();

	while (iter.hasNext())
	{
		Node<Component>* node = iter.next();
		if (dynamic_cast<GameLogic*>(node->data))
			((GameLogic*)node->data)->OnAction(action, data);
	}
}

void GameObject::setActive(bool toogle)
{
	if (isActive_ == toogle)
		return;

	isActive_ = toogle;

	DoubleLinkedList<Component>::iterator iter = componentsList_.getIterator();
	while (iter.hasNext())
	{
		Node<Component>* node = iter.next();
		ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(node->data);
		if (activeComp && activeComp->isEnabled_)
		{
			if (isActive_)
				activeComp->OnEnable();
			else
				activeComp->OnDisable();
		}
	}
}

void GameObject::removeComponent(Component* comp)
{
	if (comp->node_ == NULL)
		return;

	componentsList_.remove(comp->node_);

	ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(comp);
	if (activeComp && activeComp->isEnabled())
		activeComp->OnDisable();
	 
	Engine::GetInstance().removeComponent(comp);
}

void GameObject::destroy()
{
	if (isDestroying)
		return;

	std::vector<Component*> tempList;

	DoubleLinkedList<Component>::iterator iter = componentsList_.getIterator();

	if (iter.hasNext()) //	keeping first component(Transform) to delete in last
		iter.next();

	while (iter.hasNext())
		removeComponent(iter.next()->data);

	removeComponent(transform_);

	Engine::GetInstance().removeGameObject(this);

	isDestroying = true;
}

//******static*****
GameObject* GameObject::FindGameObjectByName(std::string name)
{
	return Engine::GetInstance().FindGameObjectByName(name);
}