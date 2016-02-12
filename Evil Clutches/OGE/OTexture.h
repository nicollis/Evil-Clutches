#pragma once
#ifndef _OGE_TEXTURE_H_
#define _OGE_TEXTURE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

#include "OWindow.h"

class OTexture
{
public:

	static std::map<int, OTexture*> sTextureMap;

	//de/contructor
	OTexture();
	OTexture(SDL_Renderer* renderer);
	~OTexture();

	//Loads the texter into memory for use with entites
	static bool onLoad(int id, char* file, int spriteWidth, int spriteHeight, SDL_Color* colorKey = NULL);
	
	//Release any allocated memory
	void onCleanup();

	//Load image at specified path, with color key for transparency
	bool loadFromFile(std::string path, SDL_Color* colorKey = NULL);

	//Load editable texture at specified point
	bool loadEditableFromFile(std::string path, SDL_Color* colorKey = NULL);

	//Returns true if texture has been loaded
	bool textureIsLoaded();

	//Creates blank texture
	bool createBlank(int width, int height, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);

	//Deaccocates Texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, 
		double angle = 0.0, SDL_Point* center = NULL, 
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Set self as render target
	void setAsRenderTarget();

	//Get image dimensions
	int getImageWidth();
	int getImageHeight();
	int getSpriteWidth();
	int getSpriteHeight();

	void setWidth(int w);
	void setHeight(int h);

	void setRenderer(SDL_Renderer* renderer);
	SDL_Renderer* getRenderer();

	//Pixel Manipulators
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	void copyPixels(void* pixels);
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);
	bool isEditable();

	//Textures
	void setTexture(SDL_Texture* texture);
	SDL_Texture* getTexture();

protected:
	//hardware texture
	SDL_Texture* mTexture = NULL;
	SDL_Renderer* mRenderer = NULL;

private:
	//The actual hardware texture
	void* mPixels;
	int mPitch;
	bool mEditabled;

	//Image dimensions
	int imageHeight;
	int imageWidth;

	//Sprite dimensions
	int spriteHeight;
	int spriteWidth;
};
#endif