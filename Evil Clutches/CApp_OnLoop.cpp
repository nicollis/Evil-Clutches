#include "CApp.h"

void CApp::OnLoop()
{
	//Check if player has died
	if (player.isDead())
	{
		isPaused = true;
		return;
	}

	//Run though all entity's onLoop function
	for (int i = 0; i < OEntity::sEntityList.size(); ++i)
	{
		if (!OEntity::sEntityList[i]) continue;

		OEntity::sEntityList[i]->onLoop();
	}

	//Run though all registered collision events
	for (int i = 0; i < OEntityCollision::sCollisionList.size(); ++i)
	{
		OEntity* entityA = OEntityCollision::sCollisionList[i]->entityA;
		OEntity* entityB = OEntityCollision::sCollisionList[i]->entityB;

		if (entityA == NULL || entityB == NULL) continue;

 		if (entityA->onCollision(entityB))
			entityB->onCollision(entityA);
	}

	//Clear collisions events when done
	OEntityCollision::sCollisionList.clear();

	//Update score after collisions
	score.onLoop();

	//Run though all font's onLoop funcations
	for each (OFontEntity* text in OFontEntity::sFontEntityList)
	{
		if (!text) continue;

		text->onLoop();
	}

	OFPS::sFPSController.onLoop();
}