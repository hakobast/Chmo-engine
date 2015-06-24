#ifndef SIMPLE_POOL_H
#define SIMPLE_POOL_H

#include <queue>

template<class T>
class SimplePool
{
public:
	virtual T*		get();
	virtual void	release(T* obj);
	int size();
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
inline void SimplePool<T>::release(T* obj)
{
	if (obj != NULL)
	{
		queue_.push(obj);
	}
}

template<class T>
inline int SimplePool<T>::size()
{
	return queue_.size();
}

#endif