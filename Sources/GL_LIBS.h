
#ifndef GL_LIBS_H
#define GL_LIBS_H

#define GLEW_STATIC 
#include <GL\glew.h>

#ifdef _WIN32
#include <GL\glut.h>
#else
#include <GLUT/GLUT.h>
#endif

#endif