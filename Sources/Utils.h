
#ifndef UTILS_H
#define UTILS_H

#include <vector>

template<typename T>
void free_vector(std::vector<T*> &v)
{
	while (!v.empty()) {
		delete v.back();
		v.pop_back();
	}
}

template<class T>
inline void vectorRemove(std::vector<T*>& vector, T* item)
{
	std::vector<T*>::iterator iter = std::remove(vector.begin(), vector.end(), item);
	vector.erase(iter, vector.end());
}

template<class T>
inline void vectorRemove(std::vector<T*>& vector, bool (*pred)(T*))
{
	std::vector<T*>::iterator iter = std::remove_if(vector.begin(), vector.end(), pred);
	vector.erase(iter, vector.end());
}

unsigned long long timeInMilliseconds();

#endif