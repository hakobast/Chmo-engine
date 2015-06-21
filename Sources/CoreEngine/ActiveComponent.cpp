
#include "ActiveComponent.h"

#include "System.h"
#include "GameObject.h"

bool ActiveComponent::isEnabled() const
{
	return isEnabled_ && getGameObject()->isActive();
}

void ActiveComponent::setEnabled(bool toogle)
{
	if (isEnabled_ == toogle)
		return;

	isEnabled_ = toogle;
	if (isEnabled())
		OnEnable();
	else
		OnDisable();
}

void ActiveComponent::destroy()
{
	getGameObject()->removeComponent(this);
}