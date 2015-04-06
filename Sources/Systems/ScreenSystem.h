#ifndef SCREEN_SYSTEM_H
#define SCREEN_SYSTEM_H

#include "CoreEngine/System.h"
#include "Components/Camera.h"

class ScreenSystem : public System
{
private:
	std::vector<Camera*> components;
	int width;
	int height;
public:
	~ScreenSystem();
	ScreenSystem();
	void Init();
	void Update();
	void addComponent(Component &c);
	void removeComponent(Component &c);
	bool isSystemComponent(Component &c);
	static int getHeight();
	static int getWidth();
private:
	static ScreenSystem* s_instance;
	friend void fr_ScreenResize(int width, int height);
	void ScreenResize(int width, int height);
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