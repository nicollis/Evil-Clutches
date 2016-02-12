/*This source code copyrighted by Odua, LLC (2015)
and may not be redistributed without written permission.*/

#include "CApp.h"

CApp::CApp()
{
	mRunning = true;
	isPaused = false;
}

int CApp::OnExecute()
{
	if (OnInit() == false)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initlize game!");
		return -1;
	}

	SDL_Event event;

	//Main Loop
	while (mRunning)
	{
		while (SDL_PollEvent(&event))
		{
			OnEvent(&event);
		}//end while even poll

		if(!isPaused) OnLoop();
		else OnPaused();

		OnRender();
	}//end while running

	OnCleanUp();

	return 0;
}//end method OnExecute

int main(int argc, char* argv[])
{
	CApp theApp;

	if (theApp.OnExecute() != 0)
	{
		std::cout << std::endl << "Press any key to continue...";
		getchar();
		return 1;
	}
	//system("pause");
	return 0;
}