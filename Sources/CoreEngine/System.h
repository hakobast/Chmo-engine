
#ifndef EngineTesting_System_h
#define EngineTesting_System_h

#include <vector>

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
	virtual void OnStartFrame(){};
	virtual void OnEndFrame(){};
	virtual void OnResume(){};
	virtual void OnPause(){};
	virtual void OnDestroy(){};
	virtual void addComponent(Component &c){};
	virtual void removeComponent(Component &c){};
	virtual bool isSystemComponent(Component &c){ return false; };
};

#endif
