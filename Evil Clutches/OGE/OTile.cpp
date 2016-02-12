#include "OTile.h"

OTile::OTile()
{
	mTileId = 0;
	mTileType = TILE_TYPE_NONE;
}

int OTile::getTileType()
{
	return mTileType;
}

void OTile::setTileType(int type)
{
	mTileType = type;
}

int OTile::getTileId()
{
	return mTileId;
}

void OTile::setTileId(int id)
{
	mTileId = id;
}