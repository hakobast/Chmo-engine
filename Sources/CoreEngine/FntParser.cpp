
#include <stdio.h>
#include <string.h>

#include "Font.h"
#include "FntParser.h"
#include "../Debug/Logger.h"

//#define DEBUG
//#define DEBUG_CHARACTERS

void FntParser::parseInfo(const char* source, Font* fnt)
{
	sscanf(source, "info "
		"face = \"%[^\"]\" "
		"size=%d "
		"bold=%d "
		"italic=%d "
		"charset=\"%[^\"]\" "
		"unicode=%d "
		"stretchH=%d "
		"smooth=%d "
		"aa=%d "
		"padding=%d,%d,%d,%d "
		"spacing=%d,%d "
		"outline=%d ",
		fnt->face,
		&fnt->size,
		&fnt->bold,
		&fnt->italic,
		fnt->charset,
		&fnt->unicode,
		&fnt->stretchH,
		&fnt->smooth,
		&fnt->aa,
		fnt->padding, fnt->padding + 1, fnt->padding + 2, fnt->padding + 3,
		fnt->spacing, fnt->spacing + 1,
		&fnt->outline);

#ifdef DEBUG
	printf("----------Info----------\n");
	printf("face=%s\n", fnt->face);
	printf("size=%d\n", fnt->size);
	printf("bold=%d\n", fnt->bold);
	printf("italic=%d\n", fnt->italic);
	printf("charset=%s\n", fnt->charset);
	printf("unicode=%d\n", fnt->unicode);
	printf("stretchH=%d\n", fnt->stretchH);
	printf("smooth=%d\n", fnt->smooth);
	printf("aa=%d\n", fnt->aa);
	printf("padding=%d,%d,%d,%d\n", fnt->padding[0], fnt->padding[1], fnt->padding[2], fnt->padding[3]);
	printf("spacing=%d,%d\n", fnt->spacing[0], fnt->spacing[1]);
	printf("outline=%d\n", fnt->outline);
#endif
}

void FntParser::parseCommon(const char* source, Font* fnt)
{
	sscanf(source, "common "
		"lineHeight=%d "
		"base=%d "
		"scaleW=%d "
		"scaleH=%d "
		"pages=%d "
		"smooth=%d "
		"packed "
		"alphaChnl=%d "
		"redChnl=%d "
		"greenChnl=%d "
		"blueChnl=%d ",
		&fnt->lineHeight,
		&fnt->base,
		&fnt->scaleW,
		&fnt->scaleH,
		&fnt->pages_count,
		&fnt->packed,
		&fnt->alphaChnl,
		&fnt->redChnl,
		&fnt->greenChnl,
		&fnt->blueChnl);

#ifdef DEBUG
	printf("----------Common----------\n");
	printf("lineHeight=%d\n", fnt->lineHeight);
	printf("base=%d\n", fnt->base);
	printf("scaleW=%d\n", fnt->scaleW);
	printf("scaleH=%d\n", fnt->scaleH);
	printf("pages=%d\n", fnt->pages_count);
	printf("packed=%d\n", fnt->packed);
	printf("alphaChnl=%d\n", fnt->alphaChnl);
	printf("redChnl=%d\n", fnt->redChnl);
	printf("greenChnl=%d\n", fnt->greenChnl);
	printf("blueChnl=%d\n", fnt->blueChnl);
#endif
}

void FntParser::parsePage(const char* source, Page* page)
{
	sscanf(source, "page id=%d file=\"%[^\"]\"", &page->id, page->file);

#ifdef DEBUG
	printf("----------Page----------\n");
	printf("page id=%d file=%s\n", page->id, page->file);
#endif
}

void FntParser::parseCharacter(const char* source, CharacterInfo* charInfo)
{
	sscanf(source, "char "
		"id=%d "
		"x=%d "
		"y=%d "
		"width=%d "
		"height=%d "
		"xoffset=%d "
		"yoffset=%d "
		"xadvance=%d "
		"page=%d "
		"chnl=%d ",
		&charInfo->id,
		&charInfo->x,
		&charInfo->y,
		&charInfo->width,
		&charInfo->height,
		&charInfo->xoffset,
		&charInfo->yoffset,
		&charInfo->xadvance,
		&charInfo->page,
		&charInfo->chnl);

#ifdef DEBUG_CHARACTERS
	printf("----------Character----------\n");
	printf("char "
		"id=%d "
		"x=%d "
		"y=%d "
		"width=%d "
		"height=%d "
		"xoffset=%d "
		"yoffset=%d "
		"xadvance=%d "
		"page=%d "
		"chnl=%d \n",
		charInfo->id,
		charInfo->x,
		charInfo->y,
		charInfo->width,
		charInfo->height,
		charInfo->xoffset,
		charInfo->yoffset,
		charInfo->xadvance,
		charInfo->page,
		charInfo->chnl);
#endif
}

void FntParser::parseKerning(const char* source, Kerning* kerning, Font* font)
{
	sscanf(source, "kerning first=%d second=%d amount=%d", &kerning->first, &kerning->second, &kerning->amount);
	font->characters[kerning->first]->kernings.insert(std::pair<int, int>(kerning->second, kerning->amount));

#ifdef DEBUG
	printf("----------Kerning----------\n");
	printf("kerning first=%d second=%d amount=%d\n", kerning->first, kerning->second, kerning->amount);
#endif
}

Font* FntParser::parseTextFile(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		Logger::PrintError("FntTextParser:: error opening file at path %s\n", filename);
		return NULL;
	}

	Font* fnt = new Font;

	char line[256];
	while (fgets(line, sizeof(line), file))
	{
		if (strncmp(line, "info", 4) == 0) //parsing info tag
		{
			parseInfo(line, fnt);
		}
		else if (strncmp(line, "common", 6) == 0) //parsing common tag
		{
			parseCommon(line, fnt);
		}
		else if (strncmp(line, "page", 4) == 0) //parsing pages
		{
			fnt->pages = new Page[fnt->pages_count];
			int i = 0;
			parsePage(line, &fnt->pages[i]);
			while(i < fnt->pages_count - 1)
			{
				fgets(line, sizeof(line), file);
				parsePage(line, &fnt->pages[++i]);
			}
		}
		else if (strncmp(line, "chars", 5) == 0) //parsing chars count
		{
			sscanf(line, "chars count=%d", &fnt->chars_count);
		}
		else if (strncmp(line, "char", 4) == 0) //parsing chars
		{
			int i = 0;
			CharacterInfo* character = new CharacterInfo;
			parseCharacter(line, character);
			fnt->characters.insert(std::pair<int,CharacterInfo*>(character->id, character));

			while (i < fnt->chars_count - 1)
			{
				fgets(line, sizeof(line), file);
				character = new CharacterInfo;
				parseCharacter(line, character);
				fnt->characters.insert(std::pair<int, CharacterInfo*>(character->id, character));
			}
		}
		else if (strncmp(line, "kernings", 8) == 0) //parsing kernings count
		{
			sscanf(line, "kernings count=%d", &fnt->kernings_count);
		}
		else if (strncmp(line, "kerning", 7) == 0) //parsing kernings
		{
			fnt->kernings = new Kerning[fnt->kernings_count];
			int i = 0;
			parseKerning(line, &fnt->kernings[i], fnt);
			while (i < fnt->kernings_count - 1)
			{
				fgets(line, sizeof(line), file);
				parseKerning(line, &fnt->kernings[++i], fnt);
			}
		}
	}

	fclose(file);

	return fnt;
}

Font* FntParser::parseText(const char* source, int length)
{
	//printf("%s\n", source); 
	
	if (source == NULL && length <= 0)
	{
		Logger::PrintError("Cannot parse text \n");
		return NULL;
	}
	

	Font* fnt = new Font;

	const char* nextLine = strchr(source, '\n');
	while (nextLine != NULL)
	{
		if (strncmp(source, "info", 4) == 0) //parsing info tag
		{
			parseInfo(source, fnt);
		}
		else if (strncmp(source, "common", 6) == 0) //parsing common tag
		{
			parseCommon(source, fnt);
		}
		else if (strncmp(source, "page", 4) == 0) //parsing pages
		{
			fnt->pages = new Page[fnt->pages_count];
			int i = 0;
			parsePage(source, &fnt->pages[i]);
			while (++i < fnt->pages_count)
			{
				source = nextLine + 1;
				nextLine = strchr(source, '\n');
				parsePage(source, &fnt->pages[i]);
			}
		}
		else if (strncmp(source, "chars", 5) == 0) //parsing chars count
		{
			sscanf(source, "chars count=%d", &fnt->chars_count);
		}
		else if (strncmp(source, "char", 4) == 0) //parsing chars
		{
			CharacterInfo* character = new CharacterInfo;
			int i = 0;
			parseCharacter(source, character);
			fnt->characters.insert(std::pair<int, CharacterInfo*>(character->id, character));
			while (++i < fnt->chars_count)
			{
				source = nextLine + 1;
				nextLine = strchr(source, '\n');

				character = new CharacterInfo;
				parseCharacter(source, character);
				fnt->characters.insert(std::pair<int, CharacterInfo*>(character->id, character));
			}
		}
		else if (strncmp(source, "kernings", 8) == 0) //parsing kernings count
		{
			sscanf(source, "kernings count=%d", &fnt->kernings_count);
		}
		else if (strncmp(source, "kerning", 7) == 0) //parsing kernings
		{
			fnt->kernings = new Kerning[fnt->kernings_count];
			int i = 0;
			parseKerning(source, &fnt->kernings[i], fnt);
			while (++i < fnt->kernings_count)
			{
				source = nextLine + 1;
				nextLine = strchr(source, '\n');
				parseKerning(source, &fnt->kernings[i], fnt);
			}
		}

		if (nextLine != NULL)
		{
			source = nextLine+1;
			nextLine = strchr(source, '\n');
		}
	}

	return fnt;
}