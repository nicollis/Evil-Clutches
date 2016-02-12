#ifndef _OGE_ANIMATION_H_
#define _OGE_ANIMATION_H_

#include <SDL.h>

class OAnimation
{
public:

	OAnimation();

	void onAnimate();

	void setFrameRate(int rate);

	void setCurrentFrame(int frame);

	int getCurrentFrame();

	void setMaxFrames(int max);

	int getMaxFrames();

	void setOscillate(bool enable);

	bool getOscillate();

private:

	int mCurrentFrame;

	int mFrameInc;

	int mFrameRate; //in milliseconds

	long mOldTime;

	int mMaxFrames;

	bool mOscillate;
};
#endif