#include "OWindow.h"

OWindow OWindow::sGameWindow;

OWindow::OWindow()
{
	//Initalize non-existant window 
	mWindow = NULL;
	mRenderer = NULL;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth = 0;
	mHeight = 0;
}

bool OWindow::init(std::string windowName, int screenWidth, int screenHeight)
{
	//Create window
	mWindow = SDL_CreateWindow(windowName.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN);

	if (mWindow != NULL)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = screenWidth;
		mHeight = screenHeight;

		//Create renderer for window
		mRenderer = SDL_CreateRenderer(mWindow, -1, 
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (mRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s \n", SDL_GetError());
			SDL_DestroyWindow(mWindow);
			mWindow = NULL;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Grab window identifier
			mWindowID = SDL_GetWindowID(mWindow);

			//Flag as opened
			mShown = true;

			//initialize PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags)& imageFlags))
			{
				printf("SDL_image could not initialize! SDL_Image Error: %s\n", IMG_GetError());
			}//end image init else

			 //Initialize SDL_ttf
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			}

			//Initalize Audio
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_Mixer could not be initalized! SDL_mixer Error: %s\n", Mix_GetError());
			}
		}
	}// if window isnt NULL
	else
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}// is window is NULL

	return mWindow != NULL;
}
//pending delete; OEvent is handling all of this now
void OWindow::handleEvent(SDL_Event& e)
{
	//Window event occured
	//If an event is detected for this window
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID)
	{
		switch (e.window.event)
		{
			//Window appeard
		case SDL_WINDOWEVENT_SHOWN:
			mShown = true;
			break;

			//Window disappeared
		case SDL_WINDOWEVENT_HIDDEN:
			mShown = false;
			break;

			//Get new dimensions and repaint
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			SDL_RenderPresent(mRenderer);
			break;

			//Repaint on expose
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(mRenderer);
			break;

			//Mouse enter
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = false;
			break;

			//Mouse exit
		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			break;

			//Keyboard focus grained
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;

			//Hide on close
		case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow(mWindow);
			break;
		}
	}//if window event matches window id
}//end methond handle event

void OWindow::focus()
{
	//Restore window if needed
	if (!mShown)
	{
		SDL_ShowWindow(mWindow);
	}

	//Move window forward
	SDL_RaiseWindow(mWindow);
}

void OWindow::clear()
{
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);
}

void OWindow::render()
{
	SDL_RenderPresent(mRenderer);
}

void OWindow::free()
{
	
	if (mRenderer != NULL)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = NULL;
	}
	if (mWindow != NULL)
	{
		SDL_DestroyWindow(mWindow);
		mWindow = NULL;
	}
	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
}

int OWindow::getWidth()
{
	return mWidth;
}

int OWindow::getHeight()
{
	return mHeight;
}

bool OWindow::hasMouseFocus()
{
	return mMouseFocus;
}

bool OWindow::hasKeyboardFocus()
{
	return mKeyboardFocus;
}

bool OWindow::isMinimized()
{
	return mMinimized;
}

bool OWindow::isShown()
{
	return mShown;
}

SDL_Renderer* OWindow::getRenderer()
{
	return mRenderer;
}

SDL_Window* OWindow::getWindow()
{
	return mWindow;
}