#ifdef __ANDROID__

#include <android/asset_manager_jni.h>

#include "AndroidAssetLoader.h"

AndroidAssetLoader::AndroidAssetLoader(AAssetManager* assetMngr)
{
	assetManager_ = assetMngr;
}

AssetFile AndroidAssetLoader::loadAsset(const char* relativePath)
{
	if(relativePath != NULL)
	{
		AAsset* asset = AAssetManager_open(assetManager_,relativePath, AASSET_MODE_STREAMING);
		if(asset != NULL)
		{
			return AssetFile(AAsset_getLength(asset), AAsset_getBuffer(asset), asset);
		}
	}

	return AssetFile();
}

void AndroidAssetLoader::releaseAsset(const AssetFile* asset)
{
	if(asset != NULL && asset->handler != nullptr)
	{
		AAsset_close((AAsset*)asset->handler);
	}
}

#endif