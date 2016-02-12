#ifndef _OGE_SOUND_H_
#define _OGE_SOUND_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <map>

class OSound
{
public:

	static OSound sSoundController;

	OSound();

	bool onLoadMusic(int id, char* file);
	bool onLoadSoundEffect(int id, char* file);
	void onCleanup();

	void onPlaySoundEffect(int id, int loop = 0);
	
	void onPlayMusic(int id, int loop = -1); //Default is to play music on loop
	void onPauseMusic();
	void onResumeMusic();
	void onStopMusic();

	bool isMusicPlaying();
	bool isMusicPaused();


private:

	static std::map<int, Mix_Music*> sMusicMap;
	static std::map<int, Mix_Chunk*> sSoundEffectMap;

};
#endif // !_OGE_SOUND_H_
