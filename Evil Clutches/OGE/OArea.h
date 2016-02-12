#ifndef _OGE_AREA_H_
#define _OGE_AREA_H_

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <vector>

#include "OWindow.h"
#include "OMap.h"
#include "OTexture.h"

class OArea
{
public:
	static OArea sAreaControl;

	OArea();

	std::vector<OMap> getMapList();
	void setMapList(std::vector<OMap> list);

	int getTileSize();

	OMap* getMap(int x, int y);

	OTile* getTile(int x, int y);

	bool onLoad(char* areaFile, int mapW, int mapH , int tileSize);
	void onRender(int cameraX, int cameraY);
	void onCleanup();

private:

	std::vector<OMap> mMapList;

	int mAreaSize;

	OTexture* mTilesetTexture;

	int mMapWidth;
	int mMapHeight;

	int mTileSize;
};
#endif