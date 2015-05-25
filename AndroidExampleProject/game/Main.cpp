
#include "../../Sources/CoreEngine/ChmoEngine.h"
#include "HelloEngine.cpp"

void Main()
{
	GameObject* helloAndroidObj = new GameObject("HelloAndroid");
	helloAndroidObj->addComponent<HelloEngine>();
}