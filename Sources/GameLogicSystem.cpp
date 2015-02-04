//
//  GameLogicSystem.cpp
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>
#include "System.h"
#include "GameLogicSystem.h"

static bool sortComponents(const GameLogic* lhs, const GameLogic* rhs) { return lhs->priority < rhs->priority; }

GameLogicSystem::~GameLogicSystem()
{
	std::cout << "GameLogicSystem:: ~~~deleted~~~" << std::endl;
}

void GameLogicSystem::Init()
{
	std::cout << "GameLogicSystem:: Init()" << std::endl;
}

void GameLogicSystem::Update()
{
	//std::cout << "GameLogicSystem:: Update()" << std::endl;

	for (GameLogic* logic : components)
	{
		logic->Update();
	}
}

void GameLogicSystem::addComponent(Component &c)
{
	if (isSystemComponent(c))
	{
		GameLogic* gm = dynamic_cast<GameLogic*>(&c);
		gm->system = this;
		components.push_back(gm);
		std::sort(components.begin(), components.end(), sortComponents);
	}
}

void GameLogicSystem::removeComponent(Component &c)
{
	if (isSystemComponent(c))
	{
		GameLogic* gm = dynamic_cast<GameLogic*>(&c);
		vectorRemove<GameLogic>(components, gm);
	}
}

bool GameLogicSystem::isSystemComponent(Component &c)
{
	GameLogic* gm = dynamic_cast<GameLogic*>(&c);
	return gm != NULL;
}