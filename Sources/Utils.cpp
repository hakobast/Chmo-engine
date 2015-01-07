#include <chrono>

#include "Utils.h"

unsigned long long timeInMilliseconds()
{
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}