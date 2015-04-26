#include "JNIBridge.h"
//#include "../../Sources/CoreEngine/Engine.h"
#include "../../Sources/CoreEngine/ChmoEngine.h"
#include "../../game/Main.cpp"

void on_surface_created()
{
	//glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
	Engine::getInstance().Init();
	//Main();
}

void on_surface_changed(int width, int height)
{
	//Engine::getInstance().ScreenChange(width, height);
}

void on_draw_frame()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	//Engine::getInstance().Update();
}