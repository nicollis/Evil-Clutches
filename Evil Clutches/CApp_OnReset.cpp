#include "CApp.h"

void CApp::OnReset()
{
	//Reset entities and remove objects like Fireball and Demons
	for (int i = 0; i < OEntity::sEntityList.size(); ++i)
	{
		if (!OEntity::sEntityList[i]) continue;

		OEntity::sEntityList[i]->onReset();
	}
	//Remove all collisions and reset list
	for (int i = 0; i < OEntityCollision::sCollisionList.size(); ++i)
	{
		OEntityCollision::sCollisionList[i]->onCleanup();
		delete OEntityCollision::sCollisionList[i];
		OEntityCollision::sCollisionList[i] = NULL;
	}

	OEntityCollision::sCollisionList.clear();

	score.onReset(); //Save score
}