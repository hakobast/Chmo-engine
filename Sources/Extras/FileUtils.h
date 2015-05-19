#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

class FileUtils
{
public:
	static long GetFileLength(FILE* file);
};

#endif