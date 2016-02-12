#ifndef _EC_FIREBALL_H_
#define _EC_FIREBALL_H_

#include <SDL.h>
#include "Define.h"
#include "OGE\OTexture.h"
#include "OGE\OEntity.h"

class Fireball : public OEntity
{
public:

	Fireball();

	bool onLoad(int id, int maxFrames = 0);
	void onReset();
	void onCreate(int x, int y);
	void onLoop();
	bool onCollision(OEntity* entity);
	void onMove(float moveX, float moveY);

private:

	int speed;

	int id;
};
#endif // !_EC_FIREBALL_H_
