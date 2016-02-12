#ifndef _OGE_ENTITY_H_
#define _OGE_ENTITY_H_

#include <vector>
#include <SDL.h>

#include "OWindow.h"
#include "OTexture.h"
#include "OAnimation.h"
#include "OFPS.h"
#include "OCamera.h"
#include "OUtil.h"

enum EntityTypes
{
	ENTITY_TYPE_GENERIC = 0,
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_FRIEND,
	ENTITY_TYPE_ENEMY
};

enum EntityFlags
{
	ENTITY_FLAG_NONE = 0,
	ENTITY_FLAG_GRAVITY = 0x00000001,
	ENTITY_FLAG_GHOST = 0x00000002,
	ENTITY_FLAG_MAP_ONLY = 0x00000004
};

class OEntity
{
public:

	static std::vector<OEntity*> sEntityList;

	OEntity();
	virtual ~OEntity();

	void setDimensions(SDL_Rect* rect);
	SDL_Rect* getDimensions();

	EntityTypes getType();

	int getTypeId();

	void setAnimationState(int state);
	int getAnimationState();

	bool isDead();

	virtual bool onLoad(int id, int maxFrames = 0);
	virtual void onReset();
	virtual void onLoop();
	virtual void onRender();
	virtual void onDistroy(); //Do not call directly use "isDead" and fire in onLoop
	virtual void onCleanup();
	virtual void onAnimate();
	virtual bool onCollision(OEntity* entity);
	virtual void onMove(float moveX, float moveY);

protected:

	bool checkForCollisions();

	OAnimation mAnimationController;

	OTexture* mEntityTexture;

	float mSpeedX;
	float mSpeedY;

	int mCurrentFrameCol;
	int mCurrentFrameRow;

	int mColX;
	int mColY;
	int mColWidth;
	int mColHeight;

	EntityTypes mType;
	EntityFlags mFlags;
	int typeId;

	bool isDeadFlag;

private:

	SDL_Rect* mEntityDimensions;

	int mAnimationState;
};

//Class used to register detected collisions so after all entity's on move
//collisions can be resolved
class OEntityCollision
{
public:
	static std::vector<OEntityCollision*> sCollisionList;

	OEntityCollision();

	void onCleanup();

	static void onRegister(OEntity* a, OEntity* b);

	OEntity* entityA;
	OEntity* entityB;
};
#endif