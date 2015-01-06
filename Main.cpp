
#ifdef _WIN32
#include <GL\glut.h>
#else
#include <GLUT/GLUT.h>
#endif

#include <chrono>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>

#include "Engine.h"
#include "Input.h"
#include "GameTime.h"
#include "GameLogicSystem.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include "SpriteRenderer.h"
#include "TextureAtlas.h"
#include "TextureTiled.h"

#include "TestComponent.cpp"
#include "SecondComponent.cpp"
#include "GLTestComponent.cpp"
#include "FPSCounter.cpp"
#include "Utils.h"


#include "Mesh.h"
#include "Color.h"
#include "MeshRenderer.h"
#include "AssetManager.h"

#define TARGET_FPS 160

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Engine::getInstance().Update();

	glutSwapBuffers();
	//glutPostRedisplay();
}

void SetupRendering(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
}

void Resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat) w/(GLfloat)h, 1.0f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / TARGET_FPS, TimerFunc, 0);
}

class BaseClass;

class Data
{
public:
	BaseClass* object;
};

class ChildData :public Data
{

};

class BaseClass
{
public:
	BaseClass()
	{
		std::cout << "BaseClass Created " << std::endl;
	}

	virtual void pure() = 0;

	virtual void addComponent(Data& obj)
	{
		obj.object = this;
	}

	virtual void print()
	{
		std::cout << "PARENT PRINTED " << std::endl;
	}
};

class ChildClass:public BaseClass
{
public:
	ChildClass()
	{
		std::cout << "ChildClass Created " << std::endl;
	}

	void pure()
	{

	}

	void addComponent(Data& obj)
	{
		std::cout << "OVERRRIDE " << std::endl;
		BaseClass::addComponent(obj);
	}

	void print()
	{
		std::cout << "CHILD PRINTED " << std::endl;
	}

	int result;
	int getResult()
	{
		return result;
	}
};

void createMyClass()
{
	ChildData myObj;

	ChildClass cl;
	cl.addComponent(myObj);

	dynamic_cast<ChildClass*>(myObj.object)->print();


	/*MyClass* cl = new MyClass(10);

	smart_pointer<MyClass> a(cl);
	smart_pointer<MyClass> b(cl);

	MyClass d(1);
	MyClass c(2);
	
	(*a) = d;
	(*b) = c;*/

	//a = &d;
	//b = &c;
}

//#define RUN_LANG_TEST
#define RUN_ENGINE_TEST

int main(int argc, char **argv)
{
#ifdef RUN_LANG_TEST
	createMyClass();
#endif
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#ifdef RUN_ENGINE_TEST

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("ENGINE TESTING");
	glutReshapeFunc(Resize);
	glutDisplayFunc(Render);
	glutTimerFunc(1000 / TARGET_FPS, TimerFunc, 0);
	SetupRendering();
	
	//creating engine
	Engine::getInstance().Init();

	RenderSystem* renderSystem = new RenderSystem; //renderer system
	GameLogicSystem* gameLogicSystem = new GameLogicSystem;	//gamelogic system
	Input* inputSystem = new Input;
	GameTime* timeSystem = new GameTime;

	Engine::getInstance().addSystem(*timeSystem, 0);
	Engine::getInstance().addSystem(*gameLogicSystem, 1);
	Engine::getInstance().addSystem(*renderSystem, 2);
	Engine::getInstance().addSystem(*inputSystem, 3);


	//creating game logics
	GameObject* fpsObj = new GameObject("FPSGameObject");
	fpsObj->addComponent<FPSCounter>();
	fpsObj->addComponent<GLTestComponent>();

	smart_pointer<Texture2D> texture(new TextureTiled("vtr.bmp", 2, 2, 4));
	smart_pointer<Material> spriteMat(new Material("my mat"));
	spriteMat->color_ambient.set(1.0f, 1.0f, 1.0f, 1.0);

	srand(time(0));
	for (int i = 0; i < 0; i++)
	{
		GameObject* obj = new GameObject("FirstGameObject");
		obj->addComponent<SpriteRenderer>()->setMainMaterial(spriteMat);
		obj->getComponent<SpriteRenderer>()->setMainTexture(texture);
		obj->getComponent<SpriteRenderer>()->setTextureFrame(rand() % 1);
		obj->getComponent<SpriteRenderer>()->setSortingLayer(SortingLayer::Default, 2);
		obj->getComponent<SpriteRenderer>()->setTextureFrame(rand() % 1);
		obj->getTransform()->Location.set(-10.0f + rand() % 20, -10.0f + rand() % 20, -20.0f);
		//obj->getTransform()->Location.set(0.0f,0.0f, -2.0f);
	}

	//char* mesh_path = "C:/Users/user/Desktop/untitled2.obj";
	//char* mat_path = "C:/Users/user/Desktop/untitled2.mtl";
	//char* mat_path = "C:/Users/user/Desktop/Luke_skywalkers_landspeeder/Luke Skywalkers landspeeder.mtl";
	/*char* mesh_path = "C:/Users/user/Dropbox/Scripts/OBJ Loader/cube.obj";
	char* mat_path = "C:/Users/user/Dropbox/Scripts/OBJ Loader/cube.mtl";

	std::vector<GameObject*> objects = LoadModel(mesh_path, mat_path);

	for (GameObject* obj : objects)
	{
		obj->getTransform()->Location.set(0.0f, 0.0f, -8.0f);
		obj->getTransform()->RotateX(25);
		obj->getTransform()->RotateY(25.0f);
		obj->getTransform()->RotateZ(75.0f);
	}*/

	/*std::vector<smart_pointer<Material>> mats = objects[0]->getComponent<MeshRenderer>()->getMaterials();

	for (int i = 0; i < 1000; i++)
	{
		GameObject* obj = new GameObject("APEE");
		MeshRenderer* meshRend = obj->addComponent<MeshRenderer>();
		meshRend->setSharedMesh(objects[0]->getComponent<MeshRenderer>()->getMesh());
		
		for (smart_pointer<Material> mat : mats)
			meshRend->addMaterial(mat);
		
		obj->getTransform()->Location.set(0.0f, 0.0f, -8.0f);
		obj->getTransform()->RotateX(45);
		obj->getTransform()->RotateY(25.0f);
		obj->getTransform()->RotateZ(75.0f);
	}*/

	glutMainLoop();

#endif
	return 0;
}