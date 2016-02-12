#include "BabyDragon.h"

BabyDragon::BabyDragon()
{
	mType = ENTITY_TYPE_FRIEND;
	typeId = ENTITY_TYPE_ID_BABY_DRAGON;

	id = sEntityList.size() - 1;
}

bool BabyDragon::onLoad(int id, int maxFrames)
{
	if (!OEntity::onLoad(id, maxFrames))
		return false;
}

void BabyDragon::onReset()
{
	onDistroy();
}

void BabyDragon::onCreate(int x, int y)
{
	getDimensions()->x = x;
	getDimensions()->y = y;
}

void BabyDragon::onLoop()
{
	if (isDead())
	{
		onDistroy();
		return;
	}
	onMove(speed, 0);
}

bool BabyDragon::onCollision(OEntity* entity)
{
	if (isDead()) return false;

	if (entity->getTypeId() == ENTITY_TYPE_ID_PLAYER)
	{
		isDeadFlag = true;
		Score::sCurrentScore += saveScore;
		return true;
	}
	else if (entity->getTypeId() == ENTITY_TYPE_ID_FIREBALL)
	{
		isDeadFlag = true;
		Score::sCurrentScore += killScore;
		OSound::sSoundController.onPlaySoundEffect(SOUND_ID_BABY);
		return true;
	}

	return false;
}

void BabyDragon::onMove(float moveX, float moveY)
{
	int x = getDimensions()->x;
	int minX = -getDimensions()->w;

	//Calcuation speed based on fps
	moveX *= OFPS::sFPSController.getSpeedFactor();

	//Update temp location
	x -= (int)moveX; //-= because we are moving to the left 

	checkForCollisions();

	//If outside screen disotry the object
	if (x <= minX)
	{
		isDeadFlag = true;
	}
	else
	{
		getDimensions()->x = x;
	}
}
