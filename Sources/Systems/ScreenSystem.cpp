
#include "../CoreEngine/LIBS.h"
#include "ScreenSystem.h"

ScreenSystem* ScreenSystem::s_instance = NULL;

ScreenSystem::ScreenSystem()
{
	s_instance = this;

	//glutReshapeFunc(fr_ScreenResize);
}

ScreenSystem::~ScreenSystem()
{
	std::cout << "ScreenSystem:: ~~~deleted~~~" << std::endl;
}

void ScreenSystem::Init()
{

}

void ScreenSystem::Update()
{
	
}

void fr_ScreenResize(int width, int height)
{
	ScreenSystem::s_instance->ScreenResize(width, height);
}

void ScreenSystem::ScreenResize(int width, int height)
{
	this->width = width;
	this->height = height;

	for (Camera* cam : components)
		cam->ApplyCameraChanges();
}

void ScreenSystem::addComponent(Component &c)
{
	if (isSystemComponent(c))
	{
		Camera* gm = dynamic_cast<Camera*>(&c);
		gm->system = this;
		components.push_back(gm);
	}
}

void ScreenSystem::removeComponent(Component &c)
{
	if (isSystemComponent(c))
	{
		Camera* gm = dynamic_cast<Camera*>(&c);
		vectorRemove<Camera>(components, gm);
	}
}

bool ScreenSystem::isSystemComponent(Component &c)
{
	Camera* gm = dynamic_cast<Camera*>(&c);
	return gm != NULL;
}