#ifndef FREEIMAGE_IMAGE_READER
#define FREEIMAGE_IMAGE_READER

#include "ImageReader.h"

struct FIBITMAP;
enum FREE_IMAGE_FORMAT;

class FreeImageImageReader : public ImageReader // funny class name :)
{
public:
	~FreeImageImageReader();
	FreeImageImageReader(const void* data, unsigned int size);
protected:
	void freeData();
private:
	void parseFormat(FREE_IMAGE_FORMAT fif);
	FIBITMAP* dib;
};

#endif