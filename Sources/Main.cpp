

#include <iostream>
#include <chrono>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>

#include "CoreEngine/ChmoEngine.h"

#include "Testings/Ship.h"
#include "Testings/FPSCounter.cpp"
#include "Testings/GLTestComponent.cpp"
#include "Testings/SecondComponent.cpp"
#include "Testings/TestComponent.cpp"


#define TARGET_FPS 60

void CreateGame();

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
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);

	//glEnable(GL_LIGHTING);
	/*glEnable(GL_LIGHT0);

	GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat pos[] = { 0.0f, 0.0f, -8, 1.0f };
	GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15.0f);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);

	//glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);*/

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
}

void HandleResize(int width, int height)
{
	Engine::getInstance().ScreenChange(width, height);

// 	glViewport(0, 0, width, height);
// 
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 
// 	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
// 
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / TARGET_FPS, TimerFunc, 0);
}

int main(int argc, char **argv)
{
	using namespace std::chrono;

	typedef high_resolution_clock Clock;
	high_resolution_clock::time_point t1 = Clock::now();
	for (int i = 0; i < 1000; i++)
		printf("*");
	high_resolution_clock::time_point t2 = Clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	auto time = t2.time_since_epoch();
	long long t = duration_cast<seconds>(time).count();

	std::cout << "\n" << t << std::endl;

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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

	CreateGame();

	glutMainLoop();

	return 0;
}

void CreateGame()
{
	//creating game logics
// 	GameObject* lightObj = new GameObject("FPSGameObject");
// 
// 	Light* light = lightObj->addComponent<Light>();
// 	light->setLight(0);
// 	light->setAmbient(Color(0.0f, 0.0f, 0.0f));
// 	light->setDiffuse(Color(1.0f, 0.0f, 0.0f));
// 	light->setSpecular(Color(0.0f, 0.0f, 0.0f));
// 	light->setLightType(POSITIONAL);
	//light->setLinearAttenuation(0.1f);
	//light->setSpotCutoff(15.0f);

	GameObject* camerObj = new GameObject("Camera");
	camerObj->addComponent<GLTestComponent>();
	camerObj->addComponent<FPSCounter>();
	camerObj->getTransform()->Location.set(0.0f, 0.0f, 10.0f);

	Camera* camera = camerObj->addComponent<Camera>();
	camera->setProjectionMode(ProjectionMode::PERSPECTIVE);
	camera->setOrthoSize(5.0f);
	camera->setFOVY(60.0f);

	int regions[4] = { 0, 0, 128, 128 };
	smart_pointer<Texture2D> texture = LoadTexture("Resources/heightmap2.bmp");
	smart_pointer<Texture2D> textureTransparent = LoadTexture("Resources/vtr.bmp");

	smart_pointer<Material> mat = Material::Unlit();
	mat->addTexture(textureTransparent);
	mat->setColor(Color::GREEN);

	for (int i = 0; i < 1; i++)
	{
		GameObject* obj = new GameObject("FirstGameObject");
// 		obj->addComponent<Terrain>();
// 		obj->getComponent<Terrain>()->setMainMaterial(mat);
// 		obj->getComponent<Terrain>()->build(texture, 1.0f);
		//obj->addComponent<TextureAnimator>()->addClip(clip); 
		//obj->getComponent<TextureAnimator>()->playClip(0);
		//obj->addComponent<GLTestComponent>();
		obj->addComponent<SpriteRenderer>()->setMainMaterial(mat);
		//obj->getComponent<SpriteRenderer>()->addMaterial(mat);
		//obj->getComponent<SpriteRenderer>()->setMainTexture(textureTransparent);
	//	obj->getComponent<SpriteRenderer>()->setColor(Color(1.0f,1.0f,1.0f,0.5f));
		//obj->getComponent<SpriteRenderer>()->setTextureFrame(rand() % 6);
		//obj->getComponent<SpriteRenderer>()->setSortingLayer(SortingLayer::Default, 2);
		//obj->getTransform()->Location.set(-10.0f + rand() % 20, -10.0f + rand() % 20, -20.0f);

		float scale = 1.0f;
		obj->getTransform()->Location.set(0.0f, 0.0f, -2.0f);
		//obj->getTransform()->RotateX(90);
		obj->getTransform()->ScaleLocal *= scale;
	}

	Logger::Print("mer gagona %d %s\n", 12, "HAKOB");
	Logger::PrintError("mer gagona %d %s\n", 12, "HAKOB");
	Logger::PrintWarning("mer gagona %d %s\n", 12, "HAKOB");

	// **************** MODEL ****************
	// 	char* mesh_path = "C:/Users/user/Dropbox/Scripts/OBJ Loader/cube.obj";
	// 	char* mat_path = "C:/Users/user/Dropbox/Scripts/OBJ Loader/cube.mtl";
	// 
	// 	std::vector<GameObject*> objects = LoadModel(mesh_path, mat_path);
	// 
	// 	for (GameObject* obj : objects)
	// 	{
	// 		obj->getTransform()->Location.set(0.0f, 0.0f, 5.0f);
	// 		obj->getTransform()->RotateX(25);
	// 		obj->getTransform()->RotateY(25.0f);
	// 		obj->getTransform()->RotateZ(75.0f);
	// 	}
	// 
	// 	smart_pointer<Mesh>& mesh = objects[0]->getComponent<MeshRenderer>()->getSharedMesh();

	std::vector<unsigned int> indices{ 0, 1, 2, 3, 0, 2 };
	std::vector<Vector3> verts{ Vector3(-1.0f, -1.0f, 0.0f), Vector3(1.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector3(-1.0f, 1.0f, 0.0f) };
	std::vector<Vector2> texcoords{ Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2(0.0f, 1.0f) };

	smart_pointer<Mesh> mesh(new Mesh);
	mesh->setSubMeshCount(1);
	mesh->setVertices(verts);
	mesh->setUVs(texcoords);
	mesh->setIndices(indices);

	for (int i = 0; i < 0; i++)
	{
		GameObject* obj = new GameObject("MY OBJ");
		MeshRenderer* meshRend = obj->addComponent<MeshRenderer>();
		meshRend->setMainMaterial(mat);
		meshRend->setMesh(mesh);

		obj->getTransform()->Location.set(0.0f, 0.0f, -2.0f);
	}
}