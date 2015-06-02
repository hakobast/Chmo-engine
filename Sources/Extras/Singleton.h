#ifndef SINGLETON_H
#define SINGLETON_H

#include <assert.h>
#include <typeinfo>
#include "../Debug/Logger.h"

template<class T>
class Singleton
{
public:
	static T& GetInstance()
	{
		return *instance_;
	}
protected:
	static T* instance_;
	Singleton()
	{
		if (instance_ != NULL)
		{
			Logger::PrintError("Singleton pattern violation <%s>\n", typeid(instance_).name());
			assert(false);
		}

		instance_ = (T*)this;
	}
};

template<class T>
T* Singleton<T>::instance_ = NULL;

#endif