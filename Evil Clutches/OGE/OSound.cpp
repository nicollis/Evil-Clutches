#include "OSound.h"

OSound OSound::sSoundController;
std::map<int, Mix_Music*> OSound::sMusicMap;
std::map<int, Mix_Chunk*> OSound::sSoundEffectMap;

OSound::OSound()
{

}

bool OSound::onLoadMusic(int id, char* file)
{
	Mix_Music* music = Mix_LoadMUS(file);
	if (music == NULL)
	{
		SDL_Log("Failed to load music %s! SDL_mixer Error: %s", file, Mix_GetError());
		return false;
	}

	auto results = sMusicMap.insert({ id, music });
	if (!results.second)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR,
			"Error loading music %s with id %d into MusicMap!\n", file, id);
		return false;
	}

	return true;
}

bool OSound::onLoadSoundEffect(int id, char* file)
{
	Mix_Chunk* sound = Mix_LoadWAV(file);
	if (sound == NULL)
	{
		SDL_Log("Failed to load sound %s! SDL_mixer Error: %s", file, Mix_GetError());
		return false;
	}

	auto results = sSoundEffectMap.insert({ id, sound });
	if (!results.second)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR,
			"Error loading sound %s with id %d into SoundEffectMap!\n", file, id);
		return false;
	}

	return true;
}

void OSound::onCleanup()
{
	for (int i = 0; i < sMusicMap.size(); i++)
	{
		Mix_FreeMusic(sMusicMap[i]);
		sMusicMap[i] = NULL;
	}
	sMusicMap.clear();

	for (int i = 0; i < sSoundEffectMap.size(); i++)
	{
		Mix_FreeChunk(sSoundEffectMap[i]);
		sSoundEffectMap[i] = NULL;
	}
	sSoundEffectMap.clear();
}


void OSound::onPlaySoundEffect(int id, int loop)
{
	Mix_PlayChannel(-1, sSoundEffectMap.at(id), loop);
}


void OSound::onPlayMusic(int id, int loop)
{
	if (isMusicPlaying())
	{
		onStopMusic();
	}

	Mix_PlayMusic(sMusicMap.at(id), loop);
}

void OSound::onPauseMusic()
{
	Mix_PauseMusic();
}

void OSound::onResumeMusic()
{
	Mix_ResumeMusic();
}

void OSound::onStopMusic()
{
	Mix_HaltMusic();
}

bool OSound::isMusicPlaying()
{
	return Mix_PlayingMusic == 0;
}

bool OSound::isMusicPaused()
{
	return Mix_PausedMusic() == 1;
}
