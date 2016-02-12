#ifndef _EC_PLAYER_H_
#define _EC_PLAYER_H_

#include "Define.h"
#include "OGE\OEntity.h"
#include "Fireball.h"

class Player : public OEntity
{
public:
	Player();

	bool onLoad(int id, int maxFrames = 0);
	void onReset();
	void onLoop();
	bool onCollision(OEntity* entity);
	void onMove(float moveX, float moveY);

	bool moveUp, moveDown;
	bool fire;

private:
	int speed;
};
#endif // !_EC_PLAYER_H_
