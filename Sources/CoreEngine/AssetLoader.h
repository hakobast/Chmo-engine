#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

struct AssetFile
{
	AssetFile(long length, const void* data, const void* handler) 
		:length(length), data(data), handler(handler){}
	AssetFile()
		:length(0), data(0), handler(0){}

	const long length;
	const void* data = 0;
	const void* handler = 0;
};

class AssetLoader
{
public:
	virtual ~AssetLoader(){}
	virtual AssetFile loadAsset(const char* relativePath) = 0;
	virtual void releaseAsset(const AssetFile* asset) = 0;
};

#endif