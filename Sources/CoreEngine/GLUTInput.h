#ifndef GLUT_INPUT_H
#define GLUT_INPUT_H

#include "NativeInput.h"
#include "../Extras/Singleton.h"

class GLUTInput : public NativeInput, private Singleton<GLUTInput>
{
public:
	virtual void init();
private:
	friend void OnKeyDown				(unsigned char key, int x, int y);
	friend void OnKeyUp					(unsigned char key, int x, int y);
	friend void OnSpecialKeyDown		(int key, int x, int y);
	friend void OnSpecialKeyUp			(int key, int x, int y);
	friend void MouseFunc				(int button, int state, int x, int y);
	friend void MouseMotionFunc			(int x, int y);
	friend void MousePassiveMotionFunc	(int x, int y);
};

#endif