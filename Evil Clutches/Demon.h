#ifndef _EC_DEMON_H_
#define _EC_DEMON_H_

#include <SDL.h>
#include "OGE\OTexture.h"
#include "OGE\OEntity.h"
#include "OGE\OSound.h"
#include "Score.h"

class Demon : public OEntity
{
public:

	Demon();

	bool onCreate(int id, int x, int y);
	void onReset();
	void onLoop();
	bool onCollision(OEntity* entity);
	void onMove(float moveX, float moveY);

private:

	int speed;
	int speedY;

	int score = 100;

	enum direction
	{
		up_left = 0,
		left,
		down_left
	};
};
#endif // !_EC_DEMON_H_
