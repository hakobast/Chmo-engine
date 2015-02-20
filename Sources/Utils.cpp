#include <chrono>

#include "Utils.h"

unsigned long long timeInMilliseconds()
{
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

wchar_t* charToWChar(const char* text)
{
	size_t size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs(wa, text, size);
	return wa;
}

char* loadFile(const char* filename)
{
	if (filename == NULL)
		return NULL;

	FILE* file = fopen(filename, "r");
	if (file == NULL)
		return NULL;

	unsigned int sLength = 0;
	char* text = NULL;

	while (fgetc(file) != EOF)
	{
		sLength++;
	}
	text = (char *)malloc(sLength + 1);

	rewind(file);
	if (text != NULL)
	{
		fread(text, 1, sLength, file);
	}

	text[sLength] = '\0';
	fclose(file);

	return text;
}
