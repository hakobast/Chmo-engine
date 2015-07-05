#ifndef FNT_TEXT_PARSER_H
#define FNT_TEXT_PARSER_H

class Font;

class FntParser
{
public:
	static Font* parseTextFile(const char* filename);
	static Font* parseText(const char* source, int length);
private:
	static void parseInfo(const char* source, Font* fnt);
	static void parseCommon(const char* source, Font* fnt);
	static void parsePage(const char* source, Page* page);
	static void parseCharacter(const char* source, CharacterInfo* charInfo);
	static void parseKerning(const char* source, Kerning* kerning, Font* font);
};
#endif