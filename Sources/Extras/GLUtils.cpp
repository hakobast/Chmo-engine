
#include <stdio.h>
#include <algorithm>

#include "GLUtils.h"
#include "../Debug/Logger.h"

void _check_gl_error(const char *file, int line) {
	GLenum err(glGetError());

	while (err != GL_NO_ERROR) {
		const char* error = NULL;

		switch (err)
		{
		case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}
		Logger::PrintError("GL_%s - %s:%d\n", error, file, line);
		err = glGetError();
	}
}

bool isExtensionSupported(const char* extension)
{
	const GLubyte* exts = glGetString(GL_EXTENSIONS);
	char* extToken = strtok((char*)exts, " ");

	while (extToken != NULL)
	{
		int res = strcmp(extToken, extension);

		if (res == 0)
			return true;

		extToken = strtok(NULL, " ");
	}

	return false;
}

bool isVBOSupported()
{
	static bool flag = true;
	static bool hasVBO;
	if (flag)
	{
		hasVBO = isExtensionSupported("GL_ARB_vertex_buffer_object");
		flag = false;
	}

	return hasVBO;
}