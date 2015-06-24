//
//  GameLogicSystem.cpp
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>
#include <algorithm>

#include "../CoreEngine/System.h"
#include "GameTime.h"
#include "GameLogicSystem.h"

GameLogicSystem::~GameLogicSystem()
{
	std::cout << "GameLogicSystem:: ~~~deleted~~~" << std::endl;
}

void GameLogicSystem::OnCreate()
{
	std::cout << "GameLogicSystem:: Init()" << std::endl;
}

void GameLogicSystem::Update()
{
	//std::cout << "GameLogicSystem:: Update()" << std::endl;

	DoubleLinkedList<GameLogic>::iterator iter = componentsList_.getIterator();
	while (iter.hasNext())
	{
		Node<GameLogic>* node = iter.next();
		if (node->data->isEnabled())
			node->data->Update();
	}
}

void GameLogicSystem::addComponent(Component &c)
{
	if (isSystemComponent(c))
	{
		addToBuffer(&c);
	}
}

void GameLogicSystem::removeComponent(Component &c)
{
	if (isSystemComponent(c))
	{
		componentsList_.remove(dynamic_cast<GameLogic*>(&c)->logicSystemNode_);
		removeFromBuffer(&c);
	}
}

bool GameLogicSystem::isSystemComponent(Component &c)
{
	return dynamic_cast<GameLogic*>(&c) != NULL;
}

void GameLogicSystem::OnBufferChange(std::vector<Component*>& components)
{
	for (Component* component : components)
	{
		component->Init();
		componentsList_.addToBack(dynamic_cast<GameLogic*>(component)->logicSystemNode_);
	}
}

std::vector<Component*> GameLogicSystem::getComponents()
{
	vector<Component*> components;

	DoubleLinkedList<GameLogic>::iterator iter = componentsList_.getIterator();
	while (iter.hasNext())
		components.push_back(iter.next()->data);

	return components;
}