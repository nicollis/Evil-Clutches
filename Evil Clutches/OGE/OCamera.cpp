#include "OCamera.h"

OCamera OCamera::sCameraControl;

OCamera::OCamera()
{
	mX = mY = 0;

	mTargetX = mTargetY = 0;

	mTargetMode = TARGET_MODE_NORMAL;
}

int OCamera::getTargetMode()
{
	return mTargetMode;
}

void OCamera::setTargetMode(int mode)
{
	mTargetMode = mode;
}

int OCamera::getX()
{
	if (mTargetX != NULL)
	{
		if (mTargetMode == TARGET_MODE_CENTER)
		{
			return *mTargetX - (OWindow::sGameWindow.getWidth() / 2);
		}

		return *mTargetX;
	}

	return mX;
}

int OCamera::getY()
{
	if (mTargetY != NULL)
	{
		if (mTargetMode == TARGET_MODE_CENTER)
		{
			return *mTargetY - (OWindow::sGameWindow.getHeight() / 2);
		}

		return *mTargetY;
	}

	return mY;
}

void OCamera::onMove(int moveX, int moveY)
{
	mX += moveX;
	mY += moveY;
}

void OCamera::setPosition(int x, int y)
{
	mX = x;
	mY = y;
}

void OCamera::setTarget(int* x, int* y)
{
	mTargetX = x;
	mTargetY = y;
}