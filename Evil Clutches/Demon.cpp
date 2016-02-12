#include "Demon.h"

Demon::Demon() : OEntity()
{
	mType = ENTITY_TYPE_ENEMY;
	typeId = ENTITY_TYPE_ID_DEMON;

	speed = -12;

	switch (rand() % 3)
	{
	case up_left:
		speedY = -12;
		break;
	case left:
		speedY = 0;
		break;
	case down_left:
		speedY = 12;
		break;
	}
}

bool Demon::onCreate(int id, int x, int y)
{
	if (!OEntity::onLoad(id))
		return false;

	getDimensions()->x = x;
	getDimensions()->y = y;

	return true;
}

void Demon::onLoop()
{
	if (isDeadFlag)
	{
		onDistroy();
		return;
	}
	onMove(speed, speedY);
}

void Demon::onReset()
{
	onDistroy();
}

bool Demon::onCollision(OEntity* entity)
{
	if (isDeadFlag) return false;

	if (entity->getTypeId() == ENTITY_TYPE_ID_FIREBALL)
	{
 		isDeadFlag = true;
		Score::sCurrentScore += score;
		OSound::sSoundController.onPlaySoundEffect(SOUND_ID_DEMON);
		return true;
	}
	return false;
}

void Demon::onMove(float moveX, float moveY)
{
	int x = getDimensions()->x;
	int minX = 0 - getDimensions()->w;
	int y = getDimensions()->y;
	int minY = 0;
	int maxY = OWindow::sGameWindow.getHeight() - getDimensions()->h;

	//Calculate speed based on fps
	moveX *= OFPS::sFPSController.getSpeedFactor();
	moveY *= OFPS::sFPSController.getSpeedFactor();

	//Update temp location 
	x += (int)moveX;
	y += (int)moveY;

	//Check for collisions
	checkForCollisions();

	//If outsize screen distroy object
	if (x <= minX)
	{
		isDeadFlag = true;
	}
	else if (y <= minY || y >= maxY)
	{
		y -= ((int)moveY * 2);
		speedY = -speedY;
		getDimensions()->x = x;
		getDimensions()->y = y;
	}
	else
	{
		getDimensions()->x = x;
		getDimensions()->y = y;
	}
}