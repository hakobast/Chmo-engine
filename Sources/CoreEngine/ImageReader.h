#ifndef IMAGE_READER_H
#define IMAGE_READER_H

enum ImgFormat
{
	UNKNOWN,
	BMP,
	PNG,
	JPEG
};

class ImageReader
{
public:
	virtual void* getData();
	virtual ImgFormat getFormat();
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
protected:
	virtual void freeData();
	void* data_ = 0;
	ImgFormat imgFormat_ = ImgFormat::UNKNOWN;
	unsigned int width_ = 0;
	unsigned int height_ = 0;
};

inline void* ImageReader::getData()
{
	return data_;
}

inline void ImageReader::freeData()
{
	delete[] data_;
}

inline ImgFormat ImageReader::getFormat()
{
	return imgFormat_;
}

inline unsigned int ImageReader::getWidth()
{
	return width_;
}

inline unsigned int ImageReader::getHeight()
{
	return height_;
}

#endif