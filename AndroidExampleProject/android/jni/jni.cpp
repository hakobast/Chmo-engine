#include <jni.h>

#include <android/asset_manager_jni.h>

#include "../../../Sources/CoreEngine/AndroidDisplay.h"
#include "../../../Sources/CoreEngine/AndroidAssetLoader.h"
#include "../../../Sources/CoreEngine/AndroidInput.h"
#include "../../../Sources/CoreEngine/Engine.h"
#include "../../../Sources/Debug/Logger.h"
#include "../../game/Main.cpp"

extern "C" {

Engine* engine;
AndroidDisplay* displayModule;
AndroidAssetLoader* assetLoader;
AndroidInput* nativeInput;

//	InitAssetManager
JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_init_1asset_1manager
	(JNIEnv * env, jclass cls, jobject assetManager)
{
	if (assetLoader == NULL)
		assetLoader = new AndroidAssetLoader(AAssetManager_fromJava(env, assetManager));
}

//	OnSurfaceCreated
JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1surface_1created
	(JNIEnv * env, jclass cls) 
{
	if (engine == NULL)
	{
		engine = new Engine;
		engine->assetLoader = assetLoader;

		nativeInput = new AndroidInput;
		engine->nativeInput = nativeInput;

		displayModule = new	AndroidDisplay(engine);
		engine->display = displayModule;
		displayModule->create();

		Main();
		return;
	}

	displayModule->create();
}

//	OnSurfaceChanged(int width, int height)
JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1surface_1changed
	(JNIEnv * env, jclass cls, jint width, jint height)
{
	displayModule->change(width, height);
}

//	OnDrawFrame
JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1draw_1frame
	(JNIEnv * env, jclass cls)
{
	displayModule->draw();
}

//	OnResume
JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1resume
(JNIEnv * env, jclass cls)
{
	if (displayModule != NULL)
		displayModule->resume();
}

//	OnPause
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

//	OnDestroy
JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1destroy
(JNIEnv * env, jclass cls)
{
	Logger::PrintError("JNI: OnDestroy");
//  	if (displayModule != NULL)
//  		displayModule->destroy();
// 
// 	displayModule = NULL;
// 	engine = NULL;
// 	assetLoader = NULL;
}

//	OnTouchEvent(MotionEvent)
JNIEXPORT void JNICALL Java_com_example_spaceshipgame_GameLibJNIWrapper_on_1touch_1event
(JNIEnv * env, jclass cls, jobject motionEvent)
{
	nativeInput->OnTouchEvent(env, motionEvent);
}
}
