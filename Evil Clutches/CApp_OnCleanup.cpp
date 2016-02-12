#include "CApp.h"

void CApp::OnCleanUp()
{
	//Clean up and free Entites
	for each (OEntity* entity in OEntity::sEntityList)
	{
		if (!entity) continue;

		entity->onCleanup();
	}

	OEntity::sEntityList.clear();

	for (int i = 0; i < OEntityCollision::sCollisionList.size(); ++i)
	{
		OEntityCollision::sCollisionList[i]->onCleanup();
		delete OEntityCollision::sCollisionList[i];
		OEntityCollision::sCollisionList[i] = NULL;
	}

	OEntityCollision::sCollisionList.clear();

	for each (OFontEntity* text in OFontEntity::sFontEntityList)
	{
		if (!text) continue;

		text->onCleanup();
	}

	score.onCleanup(); //Save scores

	OFontEntity::sFontEntityList.clear();

	for (int i = 0; i < OTexture::sTextureMap.size(); ++i)
	{
		if (!OTexture::sTextureMap[i]) continue;

		OTexture::sTextureMap[i]->free();
		OTexture::sTextureMap[i] = NULL;
	}

	OTexture::sTextureMap.clear();

	OWindow::sGameWindow.free();
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}