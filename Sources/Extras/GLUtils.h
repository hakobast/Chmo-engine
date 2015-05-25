#ifndef GL_UTILS_H
#define GL_UTILS_H

#include "../CoreEngine/LIBS.h"

#define check_gl_error() _check_gl_error(__FILE__, __LINE__)

void _check_gl_error(const char *file, int line);
bool isVBOSupported();
bool isExtensionSupported(const char* extension);

#endif