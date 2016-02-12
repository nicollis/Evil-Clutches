/*This source code copyrighted by Odua, LLC (2015)
and may not be redistributed without written permission.*/
#ifndef _CAPP_H_
#define _CAPP_H_

#include <iostream>
#include <SDL.h>
#include "OGE\OGE.h"

#include "Define.h"
#include "Player.h"
#include "Boss.h"
#include "Score.h"

class CApp : public OEvent {

public:

	void OnPaused();

	void OnReset();

public:
	CApp();

	int OnExecute();

	bool OnInit();

	void OnEvent(SDL_Event* event);

	void OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 unicode);

	void OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 unicode);

	void OnExit();

	void OnLoop();

	void OnRender();

	void OnCleanUp();

private:
	bool mRunning;

	bool isPaused;

	OTexture background;

	Score score;

	Player player;
	SDL_Color playerKey = { 0,0,255 };

	Boss boss;
	SDL_Color bossKey = { 81, 46, 41 };

	SDL_Color textColor = { 255, 255, 255 };

	SDL_Color fireballKey = { 97, 14, 8 };
};
#endif