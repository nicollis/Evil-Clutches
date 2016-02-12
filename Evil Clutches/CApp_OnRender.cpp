#include "CApp.h"

void CApp::OnRender()
{
	OWindow::sGameWindow.clear();
	//Render background
	background.render(0, 0);

	//Render teach Entity
	for (int i = 0; i < OEntity::sEntityList.size(); ++i)
	{
		if (!OEntity::sEntityList[i]) continue;

		OEntity::sEntityList[i]->onRender();
	}

	//If Paused add a black back drop to screen behind score
	if (isPaused)
	{
		SDL_Rect fillRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
		SDL_SetRenderDrawBlendMode(OWindow::sGameWindow.getRenderer(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(OWindow::sGameWindow.getRenderer(), 0x00, 0X00, 0X00, 0XBE);
		SDL_RenderFillRect(OWindow::sGameWindow.getRenderer(), &fillRect);
	}

	//Render all needed font
	for each (OFontEntity* text in OFontEntity::sFontEntityList)
	{
		if (!text) continue;

		text->onRender();
	}
	

	OWindow::sGameWindow.render();
}