#include "CApp.h"

bool CApp::OnInit()
{
	//Initalize SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL cloud not initalize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	//Create Window and Renderer
	if (!OWindow::sGameWindow.init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Window could not be created!\n");
		return false;
	}

	//Set base rate for animations
	OFPS::sFPSController.setBaseRate(ANIMATION_RATE);

	//Load Textures

	//Load Background
	if (!OTexture::onLoad(SPRITE_BACKGROUND,"media/Background.bmp", WINDOW_WIDTH, WINDOW_HEIGHT))
		return false;

	//Load Player
	if (!OTexture::onLoad(SPRITE_PLAYER,"media/Dragon.gif", 135, 150, &playerKey))
		return false;

	//Load Boss
	if (!OTexture::onLoad(SPRITE_BOSS ,"media/Boss.gif", 135, 165, &bossKey))
		return false;

	//Load Fireball
	if (!OTexture::onLoad(SPRITE_FIREBALL, "media/Fireball.gif", 50, 48, &fireballKey))
		return false;

	//Load Demon
	if (!OTexture::onLoad(SPRITE_DEMON, "media/Demon.gif", 130, 140, &bossKey))
		return false;

	//Load Baby Dragon
	if (!OTexture::onLoad(SPRITE_BABY_DRAGON, "media/Baby.gif", 53, 55, &bossKey))
		return false;

	//Initalize on screen entites

	//init background
	//if (!background.onLoad(SPRITE_BACKGROUND))
		//return false;
	background = *OTexture::sTextureMap.at(SPRITE_BACKGROUND);

	//init player
	if (!player.onLoad(SPRITE_PLAYER))
		return false;

	//init boss
	if (!boss.onLoad(SPRITE_BOSS))
		return false;

	//show FPS
	//OFPS::sFPSController.showFPS(10, 10);

	//init and show score
	score.onLoad();

	//Initalize music and sounds

	if (!OSound::sSoundController.onLoadMusic(SOUND_ID_MUSIC, "media/Music.mp3"))
		return false;

	if (!OSound::sSoundController.onLoadSoundEffect(SOUND_ID_BABY, "media/Baby.wav"))
		return false;

	if (!OSound::sSoundController.onLoadSoundEffect(SOUND_ID_DEMON, "media/Demon.wav"))
		return false;

	//Start playing music
	OSound::sSoundController.onPlayMusic(SOUND_ID_MUSIC);

	return true;
}