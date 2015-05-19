#ifndef WIN_ASSET_LOADER_H
#define WIN_ASSET_LOADER_H

#include "AssetLoader.h"

class WinAssetLoader : public AssetLoader
{
public:
	virtual AssetFile loadAsset(const char* relativePath);
	virtual void releaseAsset(const AssetFile* asset);
};

#endif