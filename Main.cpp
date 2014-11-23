
#ifdef _WIN32
#include <GL\glut.h>
#else
#include <GLUT/GLUT.h>
#endif

#include <chrono>

#include "Engine.h"
#include "Input.h"
#include "GameTime.h"
#include "GameLogicSystem.cpp"
#include "RenderSystem.cpp"
#include "Renderer.h"

#include "TestComponent.cpp"
#include "SecondComponent.cpp"
#include "GLTestComponent.cpp"


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


}

void Resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0f, (GLfloat) w/(GLfloat)h, 1.0f, 200.0f);

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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
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
	GameObject* obj = new GameObject("FirstGameObject");
	obj->addComponent<GLTestComponent>();
	obj->addComponent<Renderer>();

	//creating game logics
	GameObject* obj2 = new GameObject("SecondGameObject");
	obj2->addComponent<Renderer>();
	obj2->addComponent<GLTestComponent>();


	obj2->getTransform()->Location = Vector3(2, 1, 0);

	glutMainLoop();

	return 0;
}