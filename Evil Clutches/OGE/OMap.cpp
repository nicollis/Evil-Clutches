#include "OMap.h"

OMap::OMap()
{
	mTilesetTexture = NULL;

	mMapWidth = 0;
	mMapHeight = 0;
}

OTexture* OMap::getTilesetTexture()
{
	return mTilesetTexture;
}

void OMap::setTilesetTexture(OTexture* texture)
{
	mTilesetTexture = texture;
}

int OMap::getTileSize()
{
	return mTileSize;
}

OTile* OMap::getTile(int x, int y)
{
	int id = 0;

	id = x / mTileSize;
	id += mMapWidth * (y / mTileSize);

	if (id < 0 || id >= mTileList.size()) return NULL;

	return &mTileList[id];
}

bool OMap::onLoad(char* mapFile, int mapW, int mapH, int tileSize)
{
	mTileSize = tileSize;

	mTileList.clear();

	FILE* tFileHandler = fopen(mapFile, "r");

	if (tFileHandler == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load %s!\n", mapFile);
		return false;
	}

	mMapHeight = mapH;
	mMapWidth = mapW;

	for (int y = 0; y < mMapHeight; ++y)
	{
		for (int w = 0; w < mMapWidth; ++w)
		{
			OTile tTile;
			int id = 0;
			int type = 0;

			fscanf(tFileHandler, "%d:%d", &id, &type);

			tTile.setTileId(id);
			tTile.setTileType(type);

			mTileList.push_back(tTile);
		}//for w < mapW
		fscanf(tFileHandler, "\n");
	}//for y < mapH

	fclose(tFileHandler);

	return true;
}//end onLoad method

void OMap::onRender(int mapX, int mapY)
{
	if (mTilesetTexture == NULL) return;

	int tTilesetWidth = mTilesetTexture->getImageWidth() / mTileSize;
	int tTilesetHeight = mTilesetTexture->getImageHeight() / mTileSize;

	int tId = 0;

	for (int y = 0; y < mMapHeight; ++y)
	{
		for (int x = 0; x < mMapWidth; ++x)
		{
			if (mTileList[tId].getTileType() == TILE_TYPE_NONE)
			{
				tId++;
				continue;
			}

			int tX = mapX + (x * mTileSize);
			int tY = mapY + (y * mTileSize);

			int tTilesetX = (mTileList[tId].getTileId() % tTilesetWidth) * mTileSize;
			int tTilesetY = (mTileList[tId].getTileId() / tTilesetHeight) * mTileSize;

			SDL_Rect clip = { tTilesetX, tTilesetY, mTileSize, mTileSize };

			mTilesetTexture->render(tX, tY, &clip);

			tId++;
		}//for x < mapW
	}//for y < mapH
}//end onRender method