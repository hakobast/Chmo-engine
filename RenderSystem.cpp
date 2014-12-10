//
//  GameLogicSystem.cpp
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>
#include "RenderSystem.h"
#include "Renderer.h"
#include "Libs.h"

static bool sortRenderers(const Renderer* lhs, const Renderer* rhs)
{
	if (lhs->getSortingLayer() < rhs->getSortingLayer()){return true;}
	if (lhs->getSortingLayer() == rhs->getSortingLayer() && lhs->getLayerOrder() < rhs->getLayerOrder()){ return true; };

	return false;
}

RenderSystem::RenderSystem()
{	

}

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
	//std::cout << "RenderSystem:: Update() " << std::endl;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Renderer* r = NULL;
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->isEnabled() && components[i]->getGameObject()->isActive())
		{
			//std::cout << "OBJ: " << components[i]->getGameObject()->name << std::endl;
			if (r != NULL)
			{
				if (r->getSortingLayer() != components[i]->getSortingLayer() ||
					r->getLayerOrder() != components[i]->getLayerOrder())
				{
					glClear(GL_DEPTH_BUFFER_BIT);
				}
			}
			
			glPushMatrix();
			components[i]->Update();
			glPopMatrix();
			r = components[i];
		}
	}
	glDisable(GL_BLEND);
}

void RenderSystem::addComponent(Component &c)
{
	//implement component checking
	Renderer* r = dynamic_cast<Renderer*>(&c);
	if (r)
	{
		r->renderSystem = this;
		components.push_back(r);
	}
}

void RenderSystem::removeComponent(Component &c)
{
	//implement component checking
	Renderer* r = dynamic_cast<Renderer*>(&c);
	if (r)
	{
		vectorRemove<Renderer>(components, *r);
	}
}

void RenderSystem::sortComponents()
{
	std::sort(components.begin(), components.end(),sortRenderers);
}