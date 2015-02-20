

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
#include "ScreenSystem.h"
#include "Renderer.h"
#include "SpriteRenderer.h"
#include "TextureAnimator.h"
#include "Terrain.h"
#include "TextureAnimationClip.h"
#include "TextureAtlas.h"
#include "TextureTiled.h"

#include "TestComponent.cpp"
#include "SecondComponent.cpp"
#include "Ship.h"
#include "GLTestComponent.cpp"
#include "FPSCounter.cpp"
#include "Utils.h"


#include "Mesh.h"
#include "Color.h"
#include "MeshRenderer.h"
#include "Camera.h"
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

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambient[] = { 1.5f, 1.5f, 1.5f, 1.0f };
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat pos[] = { 0.0f, 0.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, pos);

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
}

void HandleResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / TARGET_FPS, TimerFunc, 0);
}

class Data : public RemovableObject
{
public:
	int a = 5;

	~Data()
	{
		std::cout << "DATA deleted " << a << std::endl;
	}

	void print()
	{
		std::cout << "A= " << a << std::endl;
	}
};

/*template< std::size_t N >
void f(char(&arr)[N])
{
	std::cout << "N=" << N << std::endl;
	std::cout << sizeof(arr) << '\n';
}*/

void createMyClass()
{
	Data* myObj = new Data;

	smart_pointer<Data> ptr1(myObj);

	smart_pointer<Data> ptr2(myObj);

	/*MyClass* cl = new MyClass(10);

	smart_pointer<MyClass> a(cl);
	smart_pointer<MyClass> b(cl);

	MyClass d(1);
	MyClass c(2);
	
	(*a) = d;
	(*b) = c;*/

	//a = &d;
	//b = &c;


	/*char text[] = "0123456789";
	f(text);*/
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
	glutReshapeFunc(HandleResize);
	glutDisplayFunc(Render);
	glutTimerFunc(1000 / TARGET_FPS, TimerFunc, 0);
	SetupRendering();
	
	//creating engine
	Engine::getInstance().Init();

	RenderSystem* renderSystem = new RenderSystem; //renderer system
	GameLogicSystem* gameLogicSystem = new GameLogicSystem;	//gamelogic system
	ScreenSystem* screenSystem = new ScreenSystem;
	Input* inputSystem = new Input;
	GameTime* timeSystem = new GameTime;

	Engine::getInstance().addSystem(*timeSystem, 0);
	Engine::getInstance().addSystem(*gameLogicSystem, 1);
	Engine::getInstance().addSystem(*screenSystem, 2);
	Engine::getInstance().addSystem(*renderSystem, 3);
	Engine::getInstance().addSystem(*inputSystem, 4);

	//creating game logics
	GameObject* fpsObj = new GameObject("FPSGameObject");
	fpsObj->addComponent<FPSCounter>();
	fpsObj->addComponent<GLTestComponent>();
	fpsObj->getTransform()->Location.set(0.0f, 0.0f, 10.0f);

	Camera* camera = fpsObj->addComponent<Camera>();
	camera->setProjectionMode(ProjectionMode::Perspective);
	camera->setOrthoSize(5.0f);
	camera->setFOVY(60.0f);

	//smart_pointer<Texture2D> shipTexture = LoadTexture("bin/shipgame/ship.png");

	//GameObject* ship = new GameObject("ship");
	//ship->addComponent<SpriteRenderer>()->setMainTexture(shipTexture);
	//ship->addComponent<Ship>();

	int regions[4] = { 0, 0, 128, 128 };
	//smart_pointer<Texture2D> texture = LoadTextureTiled("bin/alizee_tga_final.jpg", 3, 4, 12);
	smart_pointer<Texture2D> texture = LoadTexture("bin/minimap.bmp");
	smart_pointer<Texture2D> grassTexture = LoadTexture("bin/minimap.bmp");

	//smart_pointer<TextureAnimationClip> clip(new TextureAnimationClip("gagoAnim", texture, 10));

	smart_pointer<Material> spriteMat(new Material("my mat"));
	spriteMat->color_ambient.set(1.0f, 1.0f, 1.0f, 1.0);

	srand(time(0));
	for (int i = 0; i < 1; i++)
	{
		GameObject* obj = new GameObject("FirstGameObject");
		obj->addComponent<Terrain>()->setMainTexture(grassTexture);
		obj->getComponent<Terrain>()->build(texture, 20.0f);
		//obj->addComponent<TextureAnimator>()->addClip(clip);
		//obj->getComponent<TextureAnimator>()->playClip(0);
		//obj->addComponent<SpriteRenderer>();// ->setMainMaterial(spriteMat);
		//obj->getComponent<SpriteRenderer>()->setMainTexture(texture);
		//obj->getComponent<SpriteRenderer>()->setTextureFrame(rand() % 6);
		//obj->getComponent<SpriteRenderer>()->setSortingLayer(SortingLayer::Default, 2);
		//obj->getTransform()->Location.set(-10.0f + rand() % 20, -10.0f + rand() % 20, -20.0f);

		float scale = 2;
		obj->getTransform()->Location.set(0.0f, 0.0f, -1.0f);
		//obj->getTransform()->RotateX(90);
		obj->getTransform()->ScaleLocal *= scale;
	}

	//char* mesh_path = "C:/Users/user/Desktop/untitled2.obj";
	//char* mat_path = "C:/Users/user/Desktop/untitled2.mtl";
	//char* mat_path = "C:/Users/user/Desktop/Luke_skywalkers_landspeeder/Luke Skywalkers landspeeder.mtl";

	//char* mesh_path = "C:/Users/user/Dropbox/Scripts/OBJ Loader/cube.obj";
	//char* mat_path = "C:/Users/user/Dropbox/Scripts/OBJ Loader/cube.mtl";

	//std::vector<GameObject*> objects = LoadModel(mesh_path, mat_path);

	//for (GameObject* obj : objects)
	//{
	//	obj->getTransform()->Location.set(0.0f, 0.0f, 5.0f);
	//	obj->getTransform()->RotateX(25);
	//	obj->getTransform()->RotateY(25.0f);
	//	obj->getTransform()->RotateZ(75.0f);
	//}

	/*std::vector<smart_pointer<Material>> mats = objects[0]->getComponent<MeshRenderer>()->getMaterials();
hakopik
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