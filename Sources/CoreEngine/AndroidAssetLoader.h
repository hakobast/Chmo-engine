#ifndef ANDROID_ASSET_LOADER_H
#define ANDROID_ASSET_LOADER_H

#include "AssetLoader.h"

class AAssetManager;

class AndroidAssetLoader : public AssetLoader
{
public:
	AndroidAssetLoader(AAssetManager* assetMngr);
	virtual AssetFile loadAsset(const char* relativePath);
	virtual void releaseAsset(const AssetFile* asset);
private:
	AAssetManager* assetManager_;
};
#endif