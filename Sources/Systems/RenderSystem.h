
#ifndef EngineTesting_RenderSystem_h
#define EngineTesting_RenderSystem_h

#include <vector>
#include "../CoreEngine/System.h"

class Renderer;
class RenderSystem :public System
{
private:
	std::vector<Renderer*> components;
protected:
	~RenderSystem();
	void Init();
	void Update();
	void addComponent(Component &c);
	void removeComponent(Component &c);
	bool isSystemComponent(Component &c);
public:
	void sortComponents();
	RenderSystem();
};

#endif
