#ifndef _OGE_CAMERA_H_
#define _OGE_CAMERA_H_

#include "OWindow.h"

enum {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class OCamera
{
public:

	static OCamera sCameraControl;

	OCamera();

	int getTargetMode();
	void setTargetMode(int mode);

	int getX();
	int getY();

	void onMove(int moveX, int moveY);

	void setPosition(int x, int y);

	void setTarget(int* x, int* y);

private:
	int mX;
	int mY;

	int* mTargetX;
	int* mTargetY;

	int mTargetMode;
};
#endif