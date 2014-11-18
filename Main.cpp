
#ifdef _WIN32
#include <GL\glut.h>
#else
#include <GLUT/GLUT.h>
#endif

#include <ctime>

#include "Engine.h"
#include "GameLogicSystem.cpp"
#include "RenderSystem.cpp"
#include "Renderer.h"

#include "TestComponent.cpp"
#include "SecondComponent.cpp"
#include "GLTestComponent.cpp"

static float prevTime;

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Engine::getInstance().Update(time(0)*1000 - prevTime);
	prevTime = time(0)*1000;

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

void SpecialKeys(int key, int x, int y)
{

}

void Keys(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27: exit(0); break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("ENGINE TESTING");
	glutReshapeFunc(Resize);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(Keys);
	glutDisplayFunc(Render);
	SetupRendering();
	
	prevTime = time(0)*1000;

	//creating engine
	Engine::getInstance().Init();

	RenderSystem* renderSystem = new RenderSystem(); //renderer system
	GameLogicSystem* gameLogicSystem = new GameLogicSystem();	//gamelogic system

	Engine::getInstance().addSystem(*gameLogicSystem, 0);
	Engine::getInstance().addSystem(*renderSystem, 1);

	//creating game logics
	GameObject* obj = new GameObject("FirstGameObject");
	obj->addComponent<GLTestComponent>();
	obj->addComponent<Renderer>();

	glutMainLoop();

	return 0;
}