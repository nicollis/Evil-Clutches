#pragma once
#ifndef _OGE_Window_H_
#define _OGE_Window_H_

#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class OWindow
{
public:
	static OWindow sGameWindow;

	OWindow();

	//Creates window
	bool init(std::string windowName, int screenWidth = 640, int screenHeight = 480);

	//Handles window events
	void handleEvent(SDL_Event& e);

	//Focuses on window
	void focus();

	//Clear window contents
	void clear();

	//Shows windows contents
	void render();

	//Deallocates internals
	void free();

	//Window dimensions
	int getWidth();
	int getHeight();

	//Window foci
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();

	//Getters
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

private:
	//Window data
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	int mWindowID;

	//Window dimensions
	int mWidth;
	int mHeight;

	//Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
	bool mShown;
};
#endif