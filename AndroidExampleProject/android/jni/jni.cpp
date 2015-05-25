#include <jni.h>

#include <android/log.h>
#include <android/asset_manager_jni.h>

#include "../../../Sources/CoreEngine/AndroidDisplayModule.h"
#include "../../../Sources/CoreEngine/AndroidAssetLoader.h"
#include "../../../Sources/CoreEngine/Engine.h"
#include "../../../Sources/Debug/Logger.h"
#include "../../game/Main.cpp"

extern "C" {

AndroidDisplayModule* displayModule;
AndroidAssetLoader* assetLoader;

JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_init_1asset_1manager
	(JNIEnv * env, jclass cls, jobject assetManager)
{
	assetLoader = new AndroidAssetLoader(AAssetManager_fromJava(env, assetManager));
}

JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1surface_1created
	(JNIEnv * env, jclass cls) 
{
	displayModule = new	AndroidDisplayModule;

	Engine::getInstance().displayModule = displayModule;
	Engine::getInstance().assetLoader = assetLoader;
	Engine::getInstance().Create();
	Main();
}

JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1surface_1changed
	(JNIEnv * env, jclass cls, jint width, jint height)
{
	displayModule->change(width, height);
}

JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1draw_1frame
	(JNIEnv * env, jclass cls)
{
	displayModule->draw();
}
}
