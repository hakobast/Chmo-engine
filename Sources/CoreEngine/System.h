
#ifndef EngineTesting_System_h
#define EngineTesting_System_h

#include <vector>

#include "Utils.h"
#include "Component.h"

class System
{
friend class Engine;

public:
	int priority;
protected:
	virtual ~System(){};
	virtual void Update(){};
public:
	virtual void OnCreate(){};
	virtual void OnScreenChange(int width, int height){};
	virtual void OnResume(){};
	virtual void OnPause(){};
	virtual void OnDestroy(){};
	virtual void addComponent(Component &c){};
	virtual void removeComponent(Component &c){};
	virtual bool isSystemComponent(Component &c){ return false; };
};

#endif
