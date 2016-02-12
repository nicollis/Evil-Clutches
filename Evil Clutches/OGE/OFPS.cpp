#include "OFPS.h"

OFPS OFPS::sFPSController;

OFPS::OFPS()
{
	mOldTime = 0;
	mLastTime = 0;

	mSpeedFactor = 0;

	mFrames = 0;
	mNumFrames = 0;

	fpsShowing = false; 
	fpsText = NULL;
}

void OFPS::onLoop()
{
	//Every second clear stats
	if (mOldTime + 1000 < SDL_GetTicks())
	{
		mOldTime = SDL_GetTicks();

		mNumFrames = mFrames;

		mFrames = 0;

		//if fps is showing use refresh as time to show counted frames
		if (fpsShowing)
		{
			fpsText->setText(std::to_string(mNumFrames));
		}
	}

	mSpeedFactor = ((SDL_GetTicks() - mLastTime) / 1000.0f) * baseRate;

	mLastTime = SDL_GetTicks();

	++mFrames;
}

int OFPS::getFPS()
{
	return mNumFrames;
}

float OFPS::getSpeedFactor()
{
	return mSpeedFactor;
}

void OFPS::setBaseRate(float baseRate)
{
	this->baseRate = baseRate;
}

void OFPS::showFPS(int x, int y)
{
	fpsShowing = true;
	if (!fpsText)
	{
		fpsText = new OFontEntity();
		fpsText->onLoad("OGE/OpenSans-Bold.ttf");
	}
	fpsText->setText("0");
	fpsText->getDemensions()->x = x;
	fpsText->getDemensions()->y = y;
}

void OFPS::hideFPS()
{
	fpsShowing = false;
}