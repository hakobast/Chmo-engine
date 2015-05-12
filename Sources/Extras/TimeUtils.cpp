
#include <chrono>

#include "TimeUtils.h"

using namespace std::chrono;

uint64_t TimeUtils::Now_Ms()
{
	auto time = high_resolution_clock::now().time_since_epoch();
	return duration_cast<milliseconds>(time).count();
}

/*#if defined(__APPLE__)

uint64_t TimeUtils::Now_Ms()
{
	return 0;
}

#endif*/