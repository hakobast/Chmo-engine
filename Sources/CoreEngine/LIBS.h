
#ifndef LIBS_H
#define LIBS_H


#ifdef _WIN32
#define GLEW_STATIC 
#include <GL\glew.h>
#include <GL\glut.h>

#elif __APPLE__
#define GLEW_STATIC 
#include <GL\glew.h>
#include <GLUT/GLUT.h>

#elif __ANDROID__ 
#include <GLES2/gl2.h>

#endif

#endif