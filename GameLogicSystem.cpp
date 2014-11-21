//
//  GameLogicSystem.cpp
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>
#include "System.h"
#include "GameLogic.h"

class GameLogicSystem:  public System
{
protected:
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

		for (int i = 0; i < components.size(); i++)
		{
			if (components[i]->isEnabled() && components[i]->getGameObject()->isActive())
				components[i]->Update();
		}
	}

	void GameLogicSystem::addComponent(Component &c)
	{
		//implement component checking
		if (dynamic_cast<GameLogic*>(&c))
			System::addComponent(c);
	}

	void GameLogicSystem::removeComponent(Component &c)
	{
		//implement component checking
		if (dynamic_cast<GameLogic*>(&c))
			System::removeComponent(c);
	}
};