#include <jni.h>

#include <android/log.h>
#include <android/asset_manager_jni.h>

#include "../../../Sources/CoreEngine/AndroidDisplayModule.h"
#include "../../../Sources/CoreEngine/AndroidAssetLoader.h"
#include "../../../Sources/CoreEngine/Engine.h"
#include "../../../Sources/Debug/Logger.h"
#include "../../game/Main.cpp"

extern "C" {

Engine* engine;
AndroidDisplayModule* displayModule;
AndroidAssetLoader* assetLoader;

JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_init_1asset_1manager
	(JNIEnv * env, jclass cls, jobject assetManager)
{
	if (assetLoader == NULL)
		assetLoader = new AndroidAssetLoader(AAssetManager_fromJava(env, assetManager));
}

JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1surface_1created
	(JNIEnv * env, jclass cls) 
{
	if (engine == NULL)
	{
		engine = new Engine;
		engine->assetLoader = assetLoader;

		displayModule = new	AndroidDisplayModule(engine);
		displayModule->create();

		Main();
		return;
	}

	displayModule->create();
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

JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1resume
(JNIEnv * env, jclass cls)
{
	if (displayModule != NULL)
		displayModule->resume();
}

JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1pause
(JNIEnv * env, jclass cls)
{
	if (displayModule != NULL)
		displayModule->pause();

	//TEMP
	displayModule = NULL;
	engine = NULL;
	assetLoader = NULL;
}

JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1destroy
(JNIEnv * env, jclass cls)
{
 	if (displayModule != NULL)
 		displayModule->destroy();

	displayModule = NULL;
	engine = NULL;
	assetLoader = NULL;
}
}
