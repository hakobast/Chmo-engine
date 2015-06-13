#ifndef SIMPLE_POOL_H
#define SIMPLE_POOL_H

#include <queue>

template<class T>
class SimplePool
{
public:
	virtual T* get();
	virtual void add(T* obj);
private:
	std::queue<T*> queue_;
};

template<class T>
inline T* SimplePool<T>::get()
{
	if (queue_.size() > 0)
	{
		T* obj = queue_.front();
		queue_.pop();
		return obj;
	}

	return NULL;
}

template<class T>
inline void SimplePool<T>::add(T* obj)
{
	if (obj != NULL)
	{
		queue_.push(obj);
	}
}

#endif