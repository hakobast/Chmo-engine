
#include "ActiveComponent.h"

#include "System.h"
#include "GameObject.h"

ActiveComponent::~ActiveComponent()
{
	std::cout << "~~~~~~~~~~~~~ ActiveComponent: " << getGameObject()->name << std::endl;
}

bool ActiveComponent::isEnabled() const
{
	return enabled && getGameObject()->isActive();
}

void ActiveComponent::setEnabled(bool toogle)
{
	if (toogle == isEnabled())
		return;

	enabled = toogle;
	if (enabled)
	{
		OnEnable();
// 		if (system != NULL && !destroyState)
// 			system->addComponent(*this);
	}
	else
	{
		OnDisable();
// 		if (system != NULL && !destroyState)
// 			system->removeComponent(*this);
	}
}

void ActiveComponent::destroy()
{
	if (destroyState)
		return;

	destroyState = true;
	getGameObject()->removeComponent(this);
	if (system != NULL)
		system->removeComponent(*this);
}

void ActiveComponent::_destroy()
{
	if (destroyState)
		return;

	destroyState = true;
	if (system != NULL)
		system->removeComponent(*this);
}