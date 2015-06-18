#include "Math.h"

const float Math::Pi = 3.14159265359f;
const float Math::Pi2 = 6.28318530718f;
const float Math::DegToRad = 0.0174532925f;
const float Math::RadToDeg = 57.2957795f;

struct constructor
{
	constructor()
	{
		srand((unsigned)time(NULL));
	}
};
constructor Math::stat_constructor;
