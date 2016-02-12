#include "OArea.h"

OArea OArea::sAreaControl;

OArea::OArea()
{
	mTilesetTexture = new OTexture();

	mAreaSize = 0;
}

std::vector<OMap> OArea::getMapList()
{
	return mMapList;
}

void OArea::setMapList(std::vector<OMap> list)
{
	mMapList = list;
}

int OArea::getTileSize()
{
	return mTileSize;
}

OMap* OArea::getMap(int x, int y)
{
	int mapWidth = mMapWidth * mTileSize;
	int mapHeight = mMapHeight * mTileSize;

	int id = x / mapWidth;
	id += ((y / mapHeight) * mAreaSize);

	if (id < 0 || id >= mMapList.size()) return NULL;

	return &mMapList[id];
}

OTile* OArea::getTile(int x, int y)
{
	int mapWidth = mMapWidth * mTileSize;
	int mapHeight = mMapHeight * mTileSize;

	OMap* map = getMap(x, y);

	if (map == NULL) return NULL;

	x %= mapWidth;
	y %= mapHeight;

	return map->getTile(x, y);
}

bool OArea::onLoad(char* areaFile, int mapW, int mapH, int tileSize)
{
	mTileSize = tileSize;

	mMapHeight = mapH;
	mMapWidth = mapW;

	mMapList.clear();
	//Load Area File into hanlder
	FILE* tFileHandler = fopen(areaFile, "r");

	if (tFileHandler == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load %s!\n", areaFile);
		return false;
	}
	//Pull and load tileset file into texture
	char tTilesetFile[255];

	fscanf(tFileHandler, "%s\n", tTilesetFile);

	mTilesetTexture->setRenderer(OWindow::sGameWindow.getRenderer());

	if (!mTilesetTexture->loadFromFile(tTilesetFile))
	{
		fclose(tFileHandler);

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load %s from area file %s\n", tTilesetFile, areaFile);

		return false;
	}

	fscanf(tFileHandler, "%d\n", &mAreaSize);

	//TODO might add in a fscanf to pull mapW and mapH from the area file as to allow dynamic map sizes

	//Loop though and load all map files into map list
	for (int x = 0; x < mAreaSize; ++x)
	{
		for (int y = 0; y < mAreaSize; ++y)
		{
			char tMapFile[255];

			fscanf(tFileHandler, "%s ", tMapFile);

			OMap tMap;
			if (!tMap.onLoad(tMapFile, mMapWidth, mMapHeight, mTileSize))
			{
				fclose(tFileHandler);

				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
					"Failed to load map %s from area file %s at location X:%d Y:%d\n", 
					tMapFile, areaFile, x, y);

				return false;
			}//if failed to load map

			tMap.setTilesetTexture(mTilesetTexture);

			mMapList.push_back(tMap);
		}//end y < area size
		fscanf(tFileHandler, "\n");
	}//end x < area size

	fclose(tFileHandler);

	return true;
}//end onLoad method

void OArea::onRender(int cameraX, int cameraY)
{
	int tMapWidth = mMapWidth * mTileSize;
	int tMapHeight = mMapHeight * mTileSize;

	int tFirstId = -cameraX / tMapWidth;
	tFirstId += (-cameraY / tMapHeight) * mAreaSize;

	for (int i = 0; i < 4; ++i)
	{
		int tId = tFirstId = ((i / 2) * mAreaSize) + (i % 2);

		if (tId < 0 || tId >= mMapList.size()) continue;

		int x = ((tId % mAreaSize) * mMapWidth) + cameraX;
		int y = ((tId / mAreaSize) * mMapHeight) + cameraY;

		mMapList[tId].onRender(x, y);
	}//for i < 4
}//end onRender method

void OArea::onCleanup()
{
	if(mTilesetTexture != NULL) mTilesetTexture->free();
	mTilesetTexture = NULL;

	mMapList.clear();
}