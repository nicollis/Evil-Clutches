#ifndef _EC_BOSS_H_
#define _EC_BOSS_H_

#include "Define.h"
#include "OGE\OEntity.h"
#include "Demon.h"
#include "BabyDragon.h"

class Boss : public OEntity
{
public:
	Boss();

	bool onLoad(int id, int maxFrames = 0);
	void onReset();
	void onLoop();
	bool onCollision(OEntity* entity);
	void onMove(float moveX, float moveY);

private:
	int speed;
};
#endif // !_EC_BOSS_H_
