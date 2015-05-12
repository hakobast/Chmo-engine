#ifndef SCREEN_SYSTEM_H
#define SCREEN_SYSTEM_H

#include "../CoreEngine/System.h"
#include "../Components/Camera.h"
#include "../CoreEngine/DisplayModuleObserver.h"
#include "../CoreEngine/DisplayModule.h"

class ScreenSystem : public System, public DisplayModuleObserver
{
private:
	std::vector<Camera*> components;
	int width;
	int height;
public:
	~ScreenSystem();
	ScreenSystem(DisplayModule* displayModule);
	void Init();
	void Update();
	void addComponent(Component &c);
	void removeComponent(Component &c);
	bool isSystemComponent(Component &c);
	static int getHeight();
	static int getWidth();

protected:
	void change(int width, int height);
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