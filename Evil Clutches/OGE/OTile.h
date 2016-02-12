#ifndef _OGE_TILE_H_
#define _OGE_TILE_H_

enum {
	TILE_TYPE_NONE = 0,

	TILE_TYPE_NORMAL,
	TILE_TYPE_BLOCK
};

class OTile
{
public:

	OTile();

	int getTileType();
	void setTileType(int type);

	int getTileId();
	void setTileId(int id);

private:
	int mTileId;
	int mTileType;
};
#endif