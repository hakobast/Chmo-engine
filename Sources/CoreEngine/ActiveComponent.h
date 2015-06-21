

#ifndef ACTIVE_COMPONENT_h
#define ACTIVE_COMPONENT_h

#include <string>

#include "Component.h"

class GameObject;

class ActiveComponent :public Component
{
	friend class GameObject;
private:
	bool isEnabled_ = true;
public:
	virtual void OnEnable(){/* std::cout << "ActiveComponent: OnEnable" << std::endl;*/ };
	virtual void OnDisable(){ /*std::cout << "ActiveComponent: OnDisable" << std::endl;*/ };
	virtual void OnDestroy(){};
	virtual bool isEnabled() const; 
	void setEnabled(bool toogle);
	void destroy();
};

#endif
