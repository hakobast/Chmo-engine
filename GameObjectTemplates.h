

template<class T>
T* GameObject::addComponent()
{
	if (std::is_base_of<Component, T>::value)
	{
		T *t = new T();
		Component* baseType = t;
		baseType->gameObject = this; 
		baseType->transform = (Transform*)components[0]; // first component of each gameobject is GameTransform

		components.push_back(baseType);
		Engine::getInstance().addComponent(*baseType,baseType->priority);
		return t;
	}

	return NULL;
}

template<class T>
T* GameObject::getComponent(bool enabledOnly) const
{
	for (int i = 0; i < components.size(); i++)
	{
		if (dynamic_cast<T*>(components[i]) && (!enabledOnly || components[i]->isEnabled()))
		{
			return (T*)components[i];
		}
	}	

	return NULL;
}

template<class T>
std::vector<T*> GameObject::getComponents(bool enabledOnly)  const
{
	std::vector<T*const> comps;
	for (int i = 0; i < components.size(); i++)
	{
		if (dynamic_cast<T*>(components[i]) && (!enabledOnly || components[i]->isEnabled()))
		{
			comps.push_back((T*)components[i]);
		}
	}

	return comps;
}

//**********STATICS********
template<class T>
T* GameObject::FindComponent()
{
	return Engine::getInstance().FindComponent<T>();
}

template<class T>
std::vector<T*> GameObject::FindComponents()
{
	return Engine::getInstance().FindComponents<T>();
}