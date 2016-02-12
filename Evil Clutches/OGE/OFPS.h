#ifndef _OGE_FPS_H_
#define	_OGE_FPS_H_

#include <SDL.h>

#include "OFontEntity.h"

class OFPS
{
public:
	static OFPS sFPSController;

public:

	OFPS();

	void onLoop();

	int getFPS();

	float getSpeedFactor();

	void setBaseRate(float baseRate);

	void showFPS(int x, int y);

	void hideFPS();

private:

	int mOldTime;
	int mLastTime;

	float mSpeedFactor;

	int mNumFrames;
	int mFrames;

	bool fpsShowing;
	OFontEntity* fpsText;

	float baseRate = 30; //rate used to 
	//figure out how many frames per seconds are used
	//Set to a base of 30 encase its not set
};
#endif