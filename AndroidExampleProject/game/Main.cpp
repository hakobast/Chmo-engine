
#include "Logic/EngineInclude.h"
#include "Logic/HelloEngine.cpp"

void Main()
{
	GameObject* helloAndroidObj = new GameObject("HelloAndroid");
	helloAndroidObj->addComponent<HelloEngine>();
}