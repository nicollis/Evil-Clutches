#include "Boss.h"

Boss::Boss()
{
	//Set entity type
	mType = ENTITY_TYPE_ENEMY;
	typeId = ENTITY_TYPE_ID_BOSS;

	//Set entity speed
	speed = 8;
}

bool Boss::onLoad(int id, int maxFrames)
{
	if (!OEntity::onLoad(id, maxFrames))
		return false;

	//Set starting location
	int x = (OWindow::sGameWindow.getWidth() - getDimensions()->w - 16);
	int y = ((OWindow::sGameWindow.getHeight() / 2) - getDimensions()->h / 2);

	getDimensions()->x = x;
	getDimensions()->y = y;


	return true;
}

void Boss::onReset()
{
	int y = ((OWindow::sGameWindow.getHeight() / 2) - getDimensions()->h / 2);
	getDimensions()->y = y;
}

void Boss::onLoop()
{
	//Has a 1 in 100 chance in generating a demon
	if ((rand() % 100) == 50)
	{
		Demon* demon = new Demon();
		demon->onCreate(SPRITE_DEMON, getDimensions()->x, getDimensions()->y);
	}
	//Has a 1 in 200 chance of generating a baby dragon
	if ((rand() % 200) == 89)
	{
		BabyDragon* baby = new BabyDragon();
		baby->onLoad(SPRITE_BABY_DRAGON);
		baby->onCreate(getDimensions()->x, getDimensions()->y);
	}


	onMove(0, speed);
}

bool Boss::onCollision(OEntity* entity)
{
	return false;
}

void Boss::onMove(float moveX, float moveY)
{
	int y = getDimensions()->y; //Move Toon and set int y for reference
	int maxY = OWindow::sGameWindow.getHeight();

	//Calculate actual speed based on frame rate
	moveY *= OFPS::sFPSController.getSpeedFactor();

	//Test if move is valid
	y += (int)moveY;

	//Make sure dragon is in bounds if hits bounds switch direction
	if ((y < 0) || ((y + getDimensions()->h) > maxY))
	{
		y -= (int)moveY; //move back if hitting border
						 //Set y to new y
		speed = -speed;
	}
	getDimensions()->y = y;
}