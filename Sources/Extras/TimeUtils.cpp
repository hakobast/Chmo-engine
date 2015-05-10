#include "TimeUtils.h"

long TimeUtils::Now_Ms()
{
#if defined(_WIN32)
	return Now_Ms_Win();
#elif defined(__APPLE__)
	return Now_Ms_OSX();
#elif defined(__ANDROID__)
	return Now_Ms_Android();
#else
	return 0;
#endif
}

long TimeUtils::Now_Ms_Win()
{
	return 0;
}

long TimeUtils::Now_Ms_OSX()
{
	return 0;
}

long TimeUtils::Now_Ms_Android()
{
	return 0;
}