
#include "FileUtils.h"

long FileUtils::GetFileLength(FILE* file)
{
	if (file != NULL)
	{
		fseek(file, 0, SEEK_END);
		long length = ftell(file);
		fseek(file, 0, SEEK_SET);
		return length;
	}

	return 0;
}