#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

#include <time.h>
#include <stdlib.h>


struct constructor;

class Math
{
public:
	static const float Pi;
	static const float Pi2;
	static const float DegToRad;
	static const float RadToDeg;

	static float Random(float from, float to);
	static int Random(int from, int to);
private:
	static constructor stat_constructor;
};

inline float Math::Random(float from, float to)
{
	return from + ((float)rand() / RAND_MAX) * (to-from);
}

inline int Math::Random(int from, int to)
{
	return from + rand() % (to - from + 1);
}

#endif