#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "../Extras/FileUtils.h"

#include "WinAssetLoader.h"

using namespace std;

AssetFile WinAssetLoader::loadAsset(const char* relativePath)
{
	if (relativePath != NULL)
	{
		ifstream file(relativePath, ios::in | ios::binary | ios::ate);
		if (file.is_open())
		{
			file.seekg(0, ios::end);
			long length = file.tellg();
			char *contents = new char[length];
			file.seekg(0, ios::beg);
			file.read(contents, length);
			file.close();
			
			return AssetFile(length, contents, NULL);
		}
	}

	return AssetFile();
}

void WinAssetLoader::releaseAsset(const AssetFile* asset)
{
	if (asset != NULL && asset->data != NULL)
	{
		delete[] asset->data;
	}
}