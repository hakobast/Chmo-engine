
#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "EngineInclude.h"

class TestComponent : public GameLogic
{
public:
	virtual void Create();
	virtual void Init();
	virtual void Update();
};

#endif