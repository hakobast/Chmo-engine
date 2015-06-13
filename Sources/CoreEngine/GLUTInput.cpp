#include "../CoreEngine/Application.h"
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_MAC)

#include <iostream>

#include "LIBS.h"
#include "GLUTInput.h"
 
 void GLUTInput::init()
 {
	 glutKeyboardFunc(OnKeyDown);
	 glutKeyboardUpFunc(OnKeyUp);
	 glutSpecialFunc(OnSpecialKeyDown);
	 glutSpecialUpFunc(OnSpecialKeyUp);
	 glutMouseFunc(MouseFunc);
	 glutMotionFunc(MouseMotionFunc);
	 glutPassiveMotionFunc(MousePassiveMotionFunc);
 }
 
// Friend functions
 void OnKeyDown(unsigned char key, int x, int y)
 {
	 if (GLUTInput::instance_->keyStates_[key] == 0)
		GLUTInput::instance_->keyStates_[key] = GLUTInput::instance_->frame_;
 }
 
 void OnKeyUp(unsigned char key, int x, int y)
 {
 	GLUTInput::instance_->keyStates_[key] = 0;
 }
 
 void OnSpecialKeyDown(int key, int x, int y)
 {
	if (GLUTInput::instance_->keyStates_[key] == 0)
		GLUTInput::instance_->specialKeyStates_[key] = GLUTInput::instance_->frame_;;
 }
 
 void OnSpecialKeyUp(int key, int x, int y)
 {
 	GLUTInput::instance_->specialKeyStates_[key] = 0;
 }
 
 void MouseFunc(int button, int state, int x, int y)
 {
 	if (state == GLUT_DOWN)
		GLUTInput::instance_->mouseStates_[button] = GLUTInput::instance_->frame_;
 	else
 		GLUTInput::instance_->mouseStates_[button] = 0;
 }
 
 void MouseMotionFunc(int x, int y)
 {
 	GLUTInput::instance_->mousePosition_[0] = x;
 	GLUTInput::instance_->mousePosition_[1] = y;
 }
 
 void MousePassiveMotionFunc(int x, int y)
 {
 	GLUTInput::instance_->mousePosition_[0] = x;
 	GLUTInput::instance_->mousePosition_[1] = y;
 }

// end

#endif