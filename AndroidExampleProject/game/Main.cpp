
#include "Logic/EngineInclude.h"
#include "Logic/TestComponent.h"

void Main()
{
	TestComponent* test = (new GameObject("Test"))->addComponent<TestComponent>();
}