
#ifdef _WIN32
#include <GL\glut.h>
#else
#include <GLUT/GLUT.h>
#endif

#include <chrono>

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

int main(int argc, char **argv)
{
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

	Texture2D* txt = new TextureTiled("vtr.bmp",2,2,4);

	/*GameObject* obj = new GameObject("FirstGameObject");
	obj->addComponent<SecondComponent>();
	obj->addComponent<GLTestComponent>();*/

	//for (int i = 0; i < 2; i++)
	{
		GameObject* obj = new GameObject("FirstGameObject");
		obj->addComponent<GLTestComponent>();
		obj->addComponent<SpriteRenderer>()->setTexture(txt);
		obj->getComponent<SpriteRenderer>()->setSortingLayer(SortingLayer::Default,2);
		obj->getTransform()->Location.set(0.0f,0.0f,-5.0f);

		GameObject* obj2 = new GameObject("SecondGameObject");
		obj2->addComponent<SpriteRenderer>()->setTexture(txt,2);
		obj2->getComponent<SpriteRenderer>()->color.set(1.0f, 0.1f, 0.3f, 0.7f);
		obj2->getComponent<SpriteRenderer>()->setSortingLayer(SortingLayer::Default,4);
		obj2->getTransform()->Location.set(0.5f, 0.0f, -5.0f);
	}

	//obj->getTransform()->ScaleLocal.set(1.0f, 1.0f, 1.0f);
	/*//creating game logics
	GameObject* obj2 = new GameObject("SecondGameObject");
	obj2->addComponent<Renderer>()->color.set(0.0f, 0.3f, 1.0f,1.0f);
	obj2->addComponent<GLTestComponent>();

	obj2->getTransform()->RotateZ(180);
	obj->getTransform()->Location.set(0.0f, 0.0f, 1.0f);*/

	/*GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f };

	Test a;
	a.addVertices(1, vertices);
	a.addVertices(1, vertices);

	a.addVertices(2, vertices);*/

	glutMainLoop();

	return 0;
}