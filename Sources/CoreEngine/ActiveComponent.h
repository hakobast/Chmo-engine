

#ifndef EngineTesting_ActiveComponent_h
#define EngineTesting_ActiveComponent_h

#include <string>

#include "Component.h"

class GameObject;

class ActiveComponent :public Component
{
	friend class GameObject;
protected:
	~ActiveComponent();
private:
	bool enabled = true;
	bool destroyState = false;
	void _destroy();
public:
	virtual void OnEnable(){/* std::cout << "ActiveComponent: OnEnable" << std::endl;*/ };
	virtual void OnDisable(){ /*std::cout << "ActiveComponent: OnDisable" << std::endl;*/ };
	virtual void OnDestroy(){};
	bool isEnabled() const;
	void destroy();
	void setEnabled(bool toogle);
};

#endif
