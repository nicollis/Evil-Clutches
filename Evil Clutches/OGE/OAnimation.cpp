#include "OAnimation.h"

OAnimation::OAnimation()
{
	mCurrentFrame = 0;
	mMaxFrames = 0;
	mFrameInc = 1;

	mFrameRate = 100;
	mOldTime = 0;

	mOscillate = false;
}

void OAnimation::onAnimate()
{
	if (mOldTime + mFrameRate > SDL_GetTicks())
	{
		return;
	}

	mOldTime = SDL_GetTicks();

	mCurrentFrame += mFrameInc;

	if (mOscillate)
	{
		if (mCurrentFrame >= mMaxFrames - 1 || mCurrentFrame <= 0)
		{
			mFrameInc = -mFrameInc;
		}
	}
	else //Oscillate disabled
	{
		if (mCurrentFrame >= mMaxFrames)
		{
			mCurrentFrame = 0;
		}
	}//end if Oscillate
}//end on animate method

void OAnimation::setFrameRate(int rate)
{
	mFrameRate = rate;
}

void OAnimation::setCurrentFrame(int frame)
{
	mCurrentFrame = frame;
}

int OAnimation::getCurrentFrame()
{
	return mCurrentFrame;
}

void OAnimation::setMaxFrames(int max)
{
	mMaxFrames = max;
}

int OAnimation::getMaxFrames()
{
	return mMaxFrames;
}

void OAnimation::setOscillate(bool enable)
{
	mOscillate = enable;
}

bool OAnimation::getOscillate()
{
	return mOscillate;
}