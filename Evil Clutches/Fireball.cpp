#include "Fireball.h"

Fireball::Fireball() : OEntity()
{
	mType = ENTITY_TYPE_FRIEND;
	typeId = ENTITY_TYPE_ID_FIREBALL;

	speed = 32;

	id = sEntityList.size()-1;
}

bool Fireball::onLoad(int id, int maxFrames)
{
	if (!OEntity::onLoad(id, maxFrames))
		return false;

	return true;
}

void Fireball::onReset()
{
	onDistroy();
}

void Fireball::onCreate(int x, int y)
{
	getDimensions()->x = x;
	getDimensions()->y = y;
}

void Fireball::onLoop()
{
	if (isDeadFlag)
	{
		onDistroy();
		return;
	}
	onMove(speed, 0);
}

bool Fireball::onCollision(OEntity* entity)
{
	if (entity->getTypeId() > ENTITY_TYPE_ID_FIREBALL)
	{ 
		isDeadFlag = true;
		return true;
	}
	return false;
}

void Fireball::onMove(float moveX, float moveY)
{
	int x = getDimensions()->x;
	int maxX = OWindow::sGameWindow.getWidth() + getDimensions()->w;

	//Calculate speed based on fps
	moveX *= OFPS::sFPSController.getSpeedFactor();

	//Update temp location 
	x += (int)moveX;

	//Check for collisions
	checkForCollisions();

	//If outsize screen distroy object
	if (x >= maxX)
	{
		isDeadFlag = true;
	}
	else
	{
		getDimensions()->x = x;
	}

}