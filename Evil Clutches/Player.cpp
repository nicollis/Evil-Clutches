#include "Player.h"

Player::Player()
{
	//Set Entity Type
	mType = ENTITY_TYPE_PLAYER;
	typeId = ENTITY_TYPE_ID_PLAYER;
	//Set Entity Speed
	speed = 16;
}

bool Player::onLoad(int id, int maxFrames)
{
	if (!OEntity::onLoad(id, maxFrames))
		return false;

	//Set starting location
	int x = 16;
	int y = ((OWindow::sGameWindow.getHeight() / 2) - getDimensions()->h / 2);

	getDimensions()->x = x;
	getDimensions()->y = y;

	moveDown = moveUp = fire = false;


	return true;
}

void Player::onReset()
{
	isDeadFlag = moveDown = moveUp = fire = false;

	getDimensions()->y = ((OWindow::sGameWindow.getHeight() / 2) - getDimensions()->h / 2);
}

void Player::onLoop()
{
	if (fire)
	{
		Fireball* fireball = new Fireball();
		fireball->onLoad(SPRITE_FIREBALL);
		fireball->onCreate((getDimensions()->x + 100), (getDimensions()->y + 10));
		fire = false;
	}
	
	//test directional movement and move
	int speed = 0;
	if (moveUp)
		speed = -this->speed;
	if (moveDown)
		speed = this->speed;

	onMove(0, speed);
}

bool Player::onCollision(OEntity* entity)
{
	if (isDeadFlag) return false;

	if (entity->getTypeId() == ENTITY_TYPE_ID_DEMON)
	{
		isDeadFlag = true;
		return true;
	}

	return false;
}

void Player::onMove(float moveX, float moveY)
{
	int y = getDimensions()->y; //Move Toon and set int y for reference
	int maxY = OWindow::sGameWindow.getHeight();

	//Calculate actual speed based on frame rate
	moveY *= OFPS::sFPSController.getSpeedFactor();

	//Test if move is valid
	y += (int) moveY;

	checkForCollisions();

	//Make sure dragon is in bounds
	if ((y < 0) || ((y + getDimensions()->h) > maxY))
		y -= (int) moveY; //move back if hitting border
	//Set y to new y
	getDimensions()->y = y;
}