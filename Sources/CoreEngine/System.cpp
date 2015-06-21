
#include "System.h"

#include "../Debug/Logger.h"

void System::OnStartFrame()
{
	if (componentsToInit.size() > 0)
	{
		OnBufferChange(componentsToInit);
		componentsToInit.clear();
	}
}

void System::OnEndFrame()
{
	if (waitForInit.size() > 0)
	{
		componentsToInit.insert(componentsToInit.begin(), waitForInit.begin(), waitForInit.end());
		waitForInit.clear();
	}
}

void System::addToBuffer(Component* component)
{
	waitForInit.push_back(component);
}

void System::removeFromBuffer(Component* component)
{
	vectorRemove<Component>(waitForInit, component);
}