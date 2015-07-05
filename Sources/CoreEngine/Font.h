#ifndef FONT_H
#define FONT_H

#include <vector>
#include <map>
#include "../Extras/smart_pointer.h"

/*
This tag gives the name of a texture file. There is one for each page in the font.
*/
struct Page
{
	int		id;			// The page id.
	char	file[256];	// The texture file name.
};

/*
The kerning information is used to adjust
the distance between certain characters, e.g. some characters
should be placed closer to each other than others.
*/
struct Kerning
{
	int first;	//	The first character id.
	int second;	//	The second character id.
	int amount;	//	How much the x position should be adjusted when drawing the second character immediately following the first.
};

/*
This struct describes on character in the font. There is one for each included character in the font.
*/
struct CharacterInfo
{
	int id;			//	The character id.
	int x;			//	The left position of the character image in the texture.
	int y;			//	The top position of the character image in the texture.
	int width;		//	The width of the character image in the texture.
	int height;		//	The height of the character image in the texture.
	int xoffset;	//	How much the current position should be offset when copying the image from the texture to the screen.
	int yoffset;	//	How much the current position should be offset when copying the image from the texture to the screen.
	int xadvance;	//	How much the current position should be advanced after drawing the character.
	int page;		//	The texture page where the character image is found.
	int chnl;		//	The texture channel where the character image is found(1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels).

	std::map<int, int> kernings; // key - second character, value - amount 
};

class Font : public RemovableObject
{
public:
	///////////////////INFO/////////////////////

	char	face[256];			// This is the name of the true type font.
	int		size;			// The size of the true type font.
	bool	bold;			// the font is bold
	bool	italic;			// the font is italic
	char	charset[256];		// The name of the OEM charset used (when not unicode).
	bool	unicode;		// Set to 1 if it is the unicode charset.
	int		stretchH;		// The font height stretch in percentage. 100% means no stretch.
	bool	smooth;			// Set to 1 if smoothing was turned on.
	bool	aa;				// The supersampling level used. 1 means no supersampling was used.
	int		padding[4];		// The padding for each character (up, right, down, left).
	int		spacing[2];		// The spacing for each character (horizontal, vertical).
	bool	outline;		// The outline thickness for the characters.

	///////////////////COMMON/////////////////////

	int		lineHeight;		// This is the distance in pixels between each line of text.
	int		base;			// The number of pixels from the absolute top of the line to the base of the characters.
	int		scaleW;			// The width of the texture, normally used to scale the x pos of the character image.
	int		scaleH;			// The height of the texture, normally used to scale the y pos of the character image.
	int		pages_count;	// The number of texture pages included in the font.
	int		chars_count;	// The number of characters included in the font.
	int		kernings_count;	// The number of kernings included in the font.
	bool	packed;			// Set to 1 if the monochrome characters have been packed into each of the texture channels.In this case alphaChnl describes what is stored in each channel.
	int		alphaChnl;		// Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.
	int		redChnl;		// Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.
	int		greenChnl;		// Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.
	int		blueChnl;		// Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.

	////////////////////////////////////////

	Page* pages = 0;
	std::map<int, CharacterInfo*> characters;
	Kerning* kernings = 0;

	~Font();

};

#endif