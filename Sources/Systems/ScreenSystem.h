#ifndef SCREEN_SYSTEM_H
#define SCREEN_SYSTEM_H

#include "../CoreEngine/System.h"
#include "../Components/Camera.h"

class ScreenSystem : public System
{
private:
	std::vector<Camera*> components;
	int width;
	int height;
public:
	~ScreenSystem();
	ScreenSystem();
	virtual void OnCreate();
	virtual void Update();
	virtual void OnScreenChange(int width, int height);
	virtual void addComponent(Component &c);
	virtual void removeComponent(Component &c);
	virtual bool isSystemComponent(Component &c);
	static int getHeight();
	static int getWidth();
private:
	static ScreenSystem* s_instance;
};

inline int ScreenSystem::getWidth()
{
	return s_instance->width;
}

inline int ScreenSystem::getHeight()
{
	return s_instance->height;
}

#endif