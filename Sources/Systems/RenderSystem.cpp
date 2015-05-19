//
//  GameLogicSystem.cpp
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <algorithm>

#include <iostream>

#include "RenderSystem.h"
#include "../CoreEngine/Transform.h"
#include "../Components/Renderer.h"
#include "../Components/Camera.h"
#include "../CoreEngine/Utils.h"

static bool sortRenderers(const Renderer* lhs, const Renderer* rhs)
{
	if (lhs->getSortingLayer() < rhs->getSortingLayer()){return true;}
	if (lhs->getSortingLayer() == rhs->getSortingLayer() && lhs->getLayerOrder() < rhs->getLayerOrder()){ return true; };

	return false;
}

RenderSystem::RenderSystem()
{	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
	//glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
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
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//TODO apply multiple cameras
	if (Camera::main == NULL)
		return;

	static Matrix4 ModelMatrix, ViewMatrix, ModelViewMatrix, ModelViewProjectionMatrix;

	Matrix4& ProjectionMatrix = Camera::main->getProjectionMatrix();
	Camera::main->getViewMatrix(ViewMatrix);

	//std::cout << "MATERIALS " << Material::allMaterials.size() << std::endl;

 	for (size_t i = 0, len = Material::allMaterials.size(); i < len; i++)
 	{
 		Material* mat = Material::allMaterials[i];
 
 		//std::cout << "SHARINGS " << mat->sharingInfo.size() << std::endl;
		//printf("Batching:::::::\n");
		mat->bind();
		{
 			for (size_t r = 0, rlen = mat->sharingInfo.size(); r < rlen; r++)
 			{
				Renderer* rend = mat->sharingInfo[r].rend;
				Transform* transform = rend->getTransform();

				transform->getMatrix(ModelMatrix, true);
				Matrix4::MultiplyMatrices(ViewMatrix, ModelMatrix, ModelViewMatrix);
				Matrix4::MultiplyMatrices(ProjectionMatrix, ModelViewMatrix, ModelViewProjectionMatrix);

				//TEMPPPPPPPPPP
				GLint loc = mat->getShader()->getUniformLocation("ModelViewProjectionMatrix");
				glUniformMatrix4fv(loc, 1, false, &ModelViewProjectionMatrix[0]);

				rend->Render(mat->sharingInfo[r].materialIndex);
 			}
		}
 		mat->unbind();
 	}

	//Checking if renderer inited performing sharing
	if (componentsToShare.size() > 0)
	{
		std::vector<std::pair< smart_pointer<Material>, MaterialShareInfo>>::iterator iter = std::remove_if(componentsToShare.begin(), componentsToShare.end(), pred_ShareMaterial);
		componentsToShare.erase(iter, componentsToShare.end());
	}

// 	Renderer* r = NULL;
// 
// 	for (size_t i = 0, len = components.size(); i < len; i++)
// 	{
// 		if (r != NULL)
// 		{
// 			if (r->getSortingLayer() != components[i]->getSortingLayer() ||
// 				r->getLayerOrder() != components[i]->getLayerOrder())
// 			{
// 				glClear(GL_DEPTH_BUFFER_BIT);
// 			}
// 		}
// 
// 		glPushMatrix();
// 		components[i]->Render();
// 		glPopMatrix();
// 		r = components[i];
// 	}

	glDisable(GL_BLEND);
}

void RenderSystem::addComponent(Component &c)
{
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

void RenderSystem::addMaterialForRenderer(smart_pointer<Material> mat, Renderer* rend, int materialIndex)
{
	if (rend->isInited())
	{
		mat->share(MaterialShareInfo(rend, materialIndex));
	}
	else
	{
		componentsToShare.push_back(std::pair< smart_pointer<Material>, MaterialShareInfo>(mat, MaterialShareInfo(rend, materialIndex)));
	}
}

void RenderSystem::removeMaterialForRenderer(smart_pointer<Material> mat, Renderer* rend, int materialIndex)
{
	if (rend->isInited())
	{
		mat->unshare(MaterialShareInfo(rend, materialIndex));
	}
	else
	{
		std::vector<std::pair< smart_pointer<Material>, MaterialShareInfo>>::iterator iter;
		for (iter = componentsToShare.begin(); iter != componentsToShare.end(); iter++)
		{
			if (iter->first == mat && iter->second.rend == rend && iter->second.materialIndex == materialIndex)
			{
				componentsToShare.erase(iter);
				break;
			}
		}
	}
}

int RenderSystem::getMaterialSharesCount(smart_pointer<Material> mat)
{
	return mat->getSharesCount();
}

bool RenderSystem::pred_ShareMaterial(std::pair< smart_pointer<Material>, MaterialShareInfo> info)
{
	if (info.second.rend->isInited())
	{
		info.second.rend->getRenderSystem()->addMaterialForRenderer(info.first, info.second.rend, info.second.materialIndex);
		return true;
	}

	return false;
}