
#include "../../Dependencies/freeimage/FreeImage.h"

#include "../Debug/Logger.h"
#include "FreeImageImageReader.h"

FreeImageImageReader::~FreeImageImageReader()
{
	freeData();
}

FreeImageImageReader::FreeImageImageReader(const void* data, unsigned int size)
{
 	FIMEMORY* fiStream = FreeImage_OpenMemory((BYTE*)data, size);
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(fiStream);
	if (FreeImage_FIFSupportsReading(fif))
	{
 		dib = FreeImage_LoadFromMemory(fif, fiStream, 0);
	}

	if (!dib)
		return;
	
	data_ = FreeImage_GetBits(dib);
	width_ = FreeImage_GetWidth(dib);
	height_ = FreeImage_GetHeight(dib);
	
	parseFormat(fif);
}

void FreeImageImageReader::freeData()
{
	if (!dib)
		FreeImage_Unload(dib);
}

void FreeImageImageReader::parseFormat(FREE_IMAGE_FORMAT fif)
{
	switch (fif)
	{
	case FIF_UNKNOWN:
		imgFormat_ = ImgFormat::UNKNOWN;
		break;
	case FIF_BMP:
		imgFormat_ = ImgFormat::BMP;
		break;
	case FIF_JPEG:
		imgFormat_ = ImgFormat::JPEG;
		break;
	case FIF_PNG:
		imgFormat_ = ImgFormat::PNG;
		break;
	}
}