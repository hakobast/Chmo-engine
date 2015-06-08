#ifndef SCREEN_SYSTEM_H
#define SCREEN_SYSTEM_H

#include "../CoreEngine/System.h"
#include "../Components/Camera.h"
#include "../Extras/Singleton.h"

class ScreenSystem : public System, private Singleton<ScreenSystem>
{
private:
	std::vector<Camera*> components;
	int width;
	int height;
public:
	virtual void OnScreenChange(int width, int height);
	virtual void addComponent(Component &c);
	virtual void removeComponent(Component &c);
	virtual bool isSystemComponent(Component &c);
	static int getHeight();
	static int getWidth();
};

inline int ScreenSystem::getWidth()
{
	return instance_->width;
}

inline int ScreenSystem::getHeight()
{
	return instance_->height;
}

#endif