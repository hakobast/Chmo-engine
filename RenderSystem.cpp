//
//  GameLogicSystem.cpp
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>
#include "System.h"
#include "Renderer.h"

class RenderSystem : public System
{
protected:
	RenderSystem::~RenderSystem()
	{
		std::cout << "RenderSystem:: ~~~deleted~~~" << std::endl;
	}

	void RenderSystem::Init()
	{
		std::cout << "RenderSystem:: Init()" << std::endl;
	}

	void RenderSystem::Update()
	{
		//std::cout << "RenderSystem:: Update()" << std::endl;

		for (int i = 0; i < components.size(); i++)
		{
			if (components[i]->isEnabled() && components[i]->getGameObject()->isActive())
				components[i]->Update();
		}
	}

	void RenderSystem::addComponent(Component &c)
	{
		//implement component checking
		if (dynamic_cast<Renderer*>(&c))
			System::addComponent(c);
	}

	void RenderSystem::removeComponent(Component &c)
	{
		//implement component checking
		if (dynamic_cast<Renderer*>(&c))
			System::removeComponent(c);
	}
};