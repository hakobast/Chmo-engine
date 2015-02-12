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

#include "Camera.h"

void RenderSystem::Update()
{
	//std::cout << "RenderSystem:: Update() " << std::endl;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//******************TEMP************************
	glPushMatrix();
	Camera::main->ApplyTransformation();

	Renderer* r = NULL;
	for (int i = 0; i < components.size(); i++)
	{
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

	glPopMatrix();
	glDisable(GL_BLEND);
}

void RenderSystem::addComponent(Component &c)
{
	//implement component checking
	if (isSystemComponent(c))
	{
		Renderer* r = dynamic_cast<Renderer*>(&c);
		r->system = this;
		components.push_back(r);
		sortComponents();
	}
}

void RenderSystem::removeComponent(Component &c)
{
	//implement component checking
	if (isSystemComponent(c))
	{
		vectorRemove<Renderer>(components, dynamic_cast<Renderer*>(&c));
	}
}

bool RenderSystem::isSystemComponent(Component &c)
{
	Renderer* r = dynamic_cast<Renderer*>(&c);
	return r != NULL;
}

void RenderSystem::sortComponents()
{
	std::sort(components.begin(), components.end(),sortRenderers);
}