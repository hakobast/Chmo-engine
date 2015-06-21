#ifndef SCREEN_SYSTEM_H
#define SCREEN_SYSTEM_H

#include "../CoreEngine/System.h"
#include "../Extras/Singleton.h"
#include "../Extras/DoubleLinkedList.h"

class Camera;

class ScreenSystem : public System, private Singleton<ScreenSystem>
{
private:
	DoubleLinkedList<Camera> componentsList_;
	int width;
	int height;
public:
	virtual void OnScreenChange(int width, int height);
	virtual void addComponent(Component &c);
	virtual void removeComponent(Component &c);
	virtual bool isSystemComponent(Component &c);
	virtual std::vector<Component*> getComponents();
	static int getHeight();
	static int getWidth();
protected:
	virtual void OnBufferChange(std::vector<Component*>& components);
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