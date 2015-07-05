#include "Font.h"

Font::~Font()
{
	for (std::map<int, CharacterInfo*>::iterator it = characters.begin(); it != characters.end(); ++it)
		delete it->second;

	if (pages		!= NULL)	delete pages;
	if (kernings	!= NULL)	delete kernings;
}