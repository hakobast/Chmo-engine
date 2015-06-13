#include "Math.h"

struct constructor
{
	constructor()
	{
		srand((unsigned)time(NULL));
	}
};

constructor Math::stat_constructor;