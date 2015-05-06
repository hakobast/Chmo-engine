
#include <android/log.h>
#include "../../Sources/CoreEngine/ChmoEngine.h"
#include "HelloEngine.cpp"

#define APPNAME "MyApp"

void Main()
{
	__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "The value of 1 + 1 is %d", 1 + 1);

	GameObject* helloAndroidObj = new GameObject("HelloAndroid");
	helloAndroidObj->addComponent<HelloEngine>();
}