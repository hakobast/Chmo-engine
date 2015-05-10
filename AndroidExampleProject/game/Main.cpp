
#include "../../Sources/CoreEngine/ChmoEngine.h"
#include "HelloEngine.cpp"

void Main()
{
	Logger::PrintError("The value of 1 + 1 is %d", 1 + 1);

	GameObject* helloAndroidObj = new GameObject("HelloAndroid");
	helloAndroidObj->addComponent<HelloEngine>();
}