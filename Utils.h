
#ifndef UTILS_H
#define UTILS_H

#include <vector>


template<class T>
void vectorRemove(std::vector<T*>& vector, T& item)
{
	int index = -1;
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i] == &item)
		{
			index = i;
			break;
		}
	}

	if (index != -1)
		vector.erase(vector.begin() + index);
}

#endif