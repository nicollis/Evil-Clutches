#ifndef _EC_BABY_DRAGON_H_
#define _EC_BABY_DRAGON_H_

#include <SDL.h>
#include "Define.h"
#include "OGE\OEntity.h"
#include "Score.h"
#include "OGE\OSound.h"

class BabyDragon : public OEntity
{
public:

	BabyDragon();

	bool onLoad(int id, int maxFrames = 0);
	void onReset();
	void onCreate(int x, int y);
	void onLoop();
	bool onCollision(OEntity* entity);
	void onMove(float moveX, float moveY);

private:

	int speed = 8;

	int id;

	const int killScore = -300;
	const int saveScore = 500;
};
#endif // !_EC_BABY_DRAGON_H_
