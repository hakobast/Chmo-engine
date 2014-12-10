
#ifdef _WIN32
#include <GL\glut.h>
#else
#include <GLUT/GLUT.h>
#endif

#include <chrono>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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


#include "Mesh.h"
#include "Color.h"
#include "MeshRenderer.h"
#include "ModelLoader.h"

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
	glutTimerFunc(1000 / 60, TimerFunc, 0);
}

void loadObj(const char* filename, std::vector<float>& outVerts, std::vector<float>& outUvs, std::vector<float>& outNormals, std::vector<unsigned int>& outIndices);

class MyClass : public RemovableObject
{
public:
	int a;
	MyClass(int z)
	{
		std::cout << "Created " << std::endl;
		a = z;
	}

	~MyClass()
	{
		std::cout << "GOOD BYE BABY I'm GONNA DIE: " << a << std::endl;
	}
};

void createMyClass()
{
	MyClass* cl = new MyClass(10);

	smart_pointer<MyClass> a(cl);
	smart_pointer<MyClass> b(cl);

	MyClass d(1);
	MyClass c(2);

	(*a) = d;
	(*b) = c;

	//a = &d;
	//b = &c;
}

#define RUN_LANG_TEST
//#define RUN_ENGINE_TEST

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
	glutTimerFunc(1000 / 60, TimerFunc, 0);
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

	smart_pointer<Texture2D> txt(new TextureTiled("vtr.bmp", 2, 2, 4));
	smart_pointer<Material> mainMat(new Material("diffuse"));

	srand(time(0));
	for (int i = 0; i < 1000; i++)
	{
		GameObject* obj = new GameObject("FirstGameObject");
		obj->addComponent<SpriteRenderer>()->setMainMaterial(mainMat,false);
		obj->getComponent<SpriteRenderer>()->setMainTexture(txt);
		obj->getComponent<SpriteRenderer>()->setTextureFrame(rand() % 4);
		//obj->getComponent<SpriteRenderer>()->setSortingLayer(SortingLayer::Default,2);
		obj->getTransform()->Location.set(-10.0f + rand() % 20, -10.0f + rand() % 20, -20.0f);
	}

	/*GameObject* obj = new GameObject("FirstGameObject");
	obj->getTransform()->Location.set(0.0f, 0.0f, -8.0f);
	obj->getTransform()->RotateX(45.0f);
	obj->getTransform()->RotateY(25.0f);
	obj->getTransform()->RotateZ(75.0f);

	GameObject* obj2 = new GameObject("SecondGameObject");
	obj2->getTransform()->Location.set(3.0f, 0.0f, -8.0f);
	obj2->getTransform()->RotateX(45.0f);
	obj2->getTransform()->RotateY(25.0f);
	obj2->getTransform()->RotateZ(75.0f);

	//obj->addComponent<GLTestComponent>();
	MeshRenderer* meshRenderer = obj->addComponent<MeshRenderer>();
	MeshRenderer* meshRenderer2 = obj2->addComponent<MeshRenderer>();

	char* matPath = "C:/Users/user/Dropbox/Scripts/OBJ Loader/test.mtl";

	std::vector<smart_pointer<Material>> materials = ModelLoader::LoadMtl(matPath);
	printf("COUNT: %d\n", materials.size());
	
	std::vector<smart_pointer<Material>> rendMats = meshRenderer->getMaterials();
	rendMats.insert(rendMats.begin(), materials.begin(), materials.end());

	for (smart_pointer<Material> mat : materials)
	{
		std::cout << "NAME: " << mat->name << ", Diffuse color: " << mat->color_diffuse << std::endl;
		std::cout << "Ambient texture name: " << mat->ambient_texture_path.size() << std::endl;
		if (mat->ambient_texture_path.size() > 0)
			mat->texture_ambient = smart_pointer<Texture2D>(new Texture2D(mat->ambient_texture_path.c_str()));
	}

	char* path = "C:/Users/user/Dropbox/Scripts/OBJ Loader/cube.obj";
	smart_pointer<Mesh> mesh(new Mesh);
	ModelLoader::LoadObj(path, mesh);

	meshRenderer->setSharedMesh(mesh);
	meshRenderer2->setSharedMesh(mesh);

	std::cout << &(meshRenderer->getMesh()) << std::endl;
	std::cout << &(meshRenderer2->getMesh()) << std::endl;*/

	glutMainLoop();

#endif
	return 0;
}