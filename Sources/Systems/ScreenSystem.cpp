
#include "../CoreEngine/LIBS.h"
#include "ScreenSystem.h"

void ScreenSystem::OnScreenChange(int width, int height)
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