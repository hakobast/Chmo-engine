
#ifndef EngineTesting_System_h
#define EngineTesting_System_h

#include <vector>
#include <list>

#include "Utils.h"
#include "Component.h"

class System
{
public:
	int priority;

	virtual ~System(){};

	virtual void Update(){};
	virtual void OnCreate(){};
	virtual void OnScreenChange(int width, int height){};
	virtual void OnStartFrame();
	virtual void OnEndFrame();
	virtual void OnResume(){};
	virtual void OnPause(){};
	virtual void OnDestroy(){};
	virtual void addComponent(Component &c){};
	virtual void removeComponent(Component &c){};
	virtual bool isSystemComponent(Component &c){ return false; };
	virtual std::vector<Component*> getComponents(){ return std::vector<Component*>(); }
private:
	std::vector<Component*> componentsToInit;
	std::vector<Component*> waitForInit;
protected:
	void addToBuffer(Component* component);
	void removeFromBuffer(Component* component);
	virtual void OnBufferChange(std::vector<Component*>& components){};
};

#endif
