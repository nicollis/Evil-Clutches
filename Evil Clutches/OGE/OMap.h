#ifndef _OGE_MAP_H_
#define _OGE_MAP_H_

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <vector>
#include <SDL.h>

#include "OTile.h"
#include "OTexture.h"

class OMap
{
public:

	OMap();

	OTexture* getTilesetTexture();
	void setTilesetTexture(OTexture* texture);

	int getTileSize();
	OTile* getTile(int x, int y);

	bool onLoad(char* file, int mapW, int mapH, int tileSize);
	void onRender(int mapX, int mapY);

private:

	OTexture* mTilesetTexture;

	std::vector<OTile> mTileList;

	int mMapWidth;
	int mMapHeight;

	int mTileSize;
};
#endif