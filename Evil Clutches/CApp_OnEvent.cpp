#include "CApp.h"

void CApp::OnEvent(SDL_Event* event)
{
	OEvent::OnEvent(event);
}

void CApp::OnExit() 
{
	mRunning = false;
}

void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 unicode)
{
	if (isPaused) return;

	switch (sym)
	{
	case SDLK_UP:
		player.moveUp = true;
		break;
	case SDLK_DOWN:
		player.moveDown = true;
		break;
	}
}

void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 unicode)
{
	if (isPaused)
	{
		switch (sym)
		{
		case SDLK_RETURN:
			//Call restart of game
			isPaused = false;
			OnReset();
			break;
		}
		return;
	}
	//If game is not paused
	switch (sym)
	{
	case SDLK_UP:
		player.moveUp = false;
		break;
	case SDLK_DOWN:
		player.moveDown = false;
		break;
	case SDLK_SPACE:
		player.fire = true;
		break;
	}
}