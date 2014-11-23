
//****STATICS*****
template<class T>
T* Engine::FindComponent() const
{
	for (Component* comp : components)
		if (dynamic_cast<T*>(comp))
			return (T*)comp;

	return NULL;
}

template<class T>
std::vector<T*> Engine::FindComponents() const
{
	std::vector<T*> comps;
	for (Component* comp : components)
		if (dynamic_cast<T*>(comp))
			comps.push_back((T*)comp);

	return comps;
}