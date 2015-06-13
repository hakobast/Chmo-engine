

#ifndef EngineTesting_GameObject_h
#define EngineTesting_GameObject_h

#include <vector>
#include <string>

#include "Engine.h"
#include "Transform.h"
#include "ActiveComponent.h"

class Transform;

class GameObject
{
friend class Component;
friend class Engine;
friend class ActiveComponent;

protected:
	~GameObject();
public:
    std::string name;
	std::string tag;
	GameObject(std::string name);
    
	template<class T>
	T* addComponent();
	template<class T>
	T* getComponent(bool enabledOnly = false) const;
	template<class T>
	std::vector<T*> getComponents(bool enabledOnly = false) const;

	//statics
	static GameObject* FindGameObjectByName(std::string name);
	template<class T> static T* FindComponent();
	template<class T> static std::vector<T*> FindComponents();

	void sendAction(std::string action, void*const data);
	Transform*const getTransform();
    void setActive(bool toogle);
    bool isActive() const;
    void destroy();
    
private:
	bool destroyState_ = false;
    bool isActive_ = true;
	Transform* transform_;
    std::vector<Component*> components_;
	void removeComponent(Component *);

	friend std::ostream& operator << (std::ostream& stream, const GameObject& obj);
};

inline std::ostream& operator << (std::ostream& stream, const GameObject& obj)
{
	return stream << obj.name << " GameObject(" << obj.components_.size() << ")" << std::endl;
}

inline bool GameObject::isActive()const
{
    return isActive_;
}

inline Transform*const GameObject::getTransform()
{
	return transform_;
}

template<class T>
T* GameObject::addComponent()
{
	if (std::is_base_of<Component, T>::value && !std::is_base_of<Transform, T>::value)
	{
		T *t = new T();
		Component* baseType = t;
		baseType->gameObject_ = this;
		baseType->transform_ = dynamic_cast<Transform*>(components_[0]); // first component of each gameobject is GameTransform

		components_.push_back(baseType);
		Engine::GetInstance().addComponent(*baseType, baseType->priority);

		//if the gameobject is in destroy state added component must be destroyed
		if (destroyState_)
		{
			ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(baseType);
			if (activeComp != NULL)
			{
				activeComp->destroy();
			}
			else
				Engine::GetInstance().removeComponent(*baseType);
		}

		return t;
	}

	return NULL;
}

template<class T>
T* GameObject::getComponent(bool enabledOnly) const
{
	for (size_t i = 0,len = components_.size(); i < len; i++)
	{
		if (dynamic_cast<T*>(components_[i]) && (!enabledOnly || components_[i]->isEnabled()))
		{
			return (T*)components_[i];
		}
	}

	return NULL;
}

template<class T>
std::vector<T*> GameObject::getComponents(bool enabledOnly)  const
{
	std::vector<T*const> comps;
	for (int i = 0; i < components_.size(); i++)
	{
		if (dynamic_cast<T*>(components_[i]) && (!enabledOnly || components_[i]->isEnabled()))
		{
			comps.push_back((T*)components_[i]);
		}
	}

	return comps;
}

//**********STATICS********
template<class T>
T* GameObject::FindComponent()
{
	return Engine::GetInstance().FindComponent<T>();
}

template<class T>
std::vector<T*> GameObject::FindComponents()
{
	return Engine::GetInstance().FindComponents<T>();
}

#endif
