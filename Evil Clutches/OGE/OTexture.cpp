#include "OTexture.h"

std::map<int, OTexture*> OTexture::sTextureMap;

OTexture::OTexture() {}

OTexture::OTexture(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mTexture = NULL;
	imageWidth = 0;
	imageHeight = 0;
}

OTexture::~OTexture()
{
	free();
	mRenderer = NULL;
}

bool OTexture::onLoad(int id, char* file, int spriteWidth, int spriteHeight, SDL_Color* colorKey)
{
	OTexture* temp = new OTexture();
	temp->setRenderer(OWindow::sGameWindow.getRenderer());

	if (!temp->loadFromFile(file, colorKey))
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR,
			"Error loading asset %s! SDL_Error: %s\n", file, SDL_GetError());
		return false;
	}

	temp->spriteWidth = spriteWidth;
	temp->spriteHeight = spriteHeight;

	auto results = sTextureMap.insert({ id, temp });
	if (!results.second)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR,
			"Error loading texture %s wth id %d into TextureMap!\n", file, id);
		return false;
	}

	return true;
}

void OTexture::onCleanup()
{
	free();
}

bool OTexture::loadFromFile(std::string path, SDL_Color* colorKey)
{
	//Get rid of preexisiting texture
	free();

	mEditabled = false;

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load iamge at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		if (colorKey != NULL)
		{
			SDL_SetColorKey(loadedSurface, SDL_TRUE,
				SDL_MapRGB(loadedSurface->format,
					colorKey->r, colorKey->g, colorKey->b));
		}

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//get image dimensions
			imageWidth = loadedSurface->w;
			imageHeight = loadedSurface->h;
		}//end if else newTexture created

		//Get rid of old loaded surface		
		SDL_FreeSurface(loadedSurface);
	}//end if else loadedSurface

	mTexture = newTexture;
	return mTexture != NULL;
}//end loadFromFile

bool OTexture::loadEditableFromFile(std::string path, SDL_Color *colorKey)
{
	//Get rid of preexisting texture
	free();

	mEditabled = true;

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formattedSurface == NULL)
		{
			printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Lock texture for manipulation
				SDL_LockTexture(newTexture, NULL, &mPixels, &mPitch);

				//Copy loaded/formatted surface pixels
				memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				imageWidth = formattedSurface->w;
				imageHeight = formattedSurface->h;

				//Remove background
				if (colorKey != NULL)
				{
					//Get pixel data in editable format
					Uint32* pixels = (Uint32*)mPixels;
					int pixelCount = (mPitch / 4) * imageHeight;

					//Map colors
					Uint32 tColorKey = SDL_MapRGB(formattedSurface->format,
						colorKey->r, colorKey->g, colorKey->b);
					Uint32 transparent = SDL_MapRGBA(formattedSurface->format,
						0xFF, 0xFF, 0xFF, 0x00);

					//Color key pixels
					for (int i = 0; i < pixelCount; ++i)
					{
						if (pixels[i] == tColorKey)
						{
							pixels[i] = transparent;
						}
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				mPixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool OTexture::textureIsLoaded()
{
	return mTexture != NULL;
}

bool OTexture::createBlank(int width, int height, SDL_TextureAccess access)
{
	//Texture is editable
	mEditabled = true;

	//Create uninitalized texures
	mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888,
		access, width, height);
	if (mTexture == NULL)
	{
		printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		imageWidth = width;
		imageHeight = height;
	}

	return mTexture != NULL;
}

void OTexture::free()
{
	//Free texture if it exist
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		imageWidth = 0;
		imageHeight = 0;
	}
}//end free

void OTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void OTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void OTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void OTexture::render(int x, int y, SDL_Rect* clip,
	double angle, SDL_Point* center,
	SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, imageWidth, imageHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderQuad, angle, center, flip))
	{
		printf("Error rendering texture! SDL Error %s\n", SDL_GetError());
	}
}//end render

void OTexture::setAsRenderTarget()
{
	//Make self render target
	SDL_SetRenderTarget(mRenderer, mTexture);
}

int OTexture::getImageWidth()
{
	return imageWidth;
}

int OTexture::getImageHeight()
{
	return imageHeight;
}

void OTexture::setWidth(int w)
{
	imageWidth = w;
}

void OTexture::setHeight(int h)
{
	imageHeight = h;
}

int OTexture::getSpriteWidth()
{
	return spriteWidth;
}

int OTexture::getSpriteHeight()
{
	return spriteHeight;
}

void OTexture::setRenderer(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

SDL_Renderer* OTexture::getRenderer()
{
	return mRenderer;
}

bool OTexture::lockTexture()
{
	bool success = true;

	//Texture is not editable
	if (!mEditabled)
	{
		printf("Texture is not editable!\n");
		success = false;
	}
	//Texture is already locked
	else if (mPixels != NULL)
	{
		printf("Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch) != 0)
		{
			printf("Unable to lock texture! %s\n", SDL_GetError());
			success = false;
		}
	}
	return success;
}

bool OTexture::unlockTexture()
{
	bool success = true;

	//Texture is not editable 
	if (!mEditabled)
	{
		printf("Texture is not editable!\n");
		success = false;
	}
	//Texture is not locked
	else if (mPixels == NULL)
	{
		printf("Texture is not locked!\n");
		success = false;
	}
	//Unlock Texture
	else
	{
		SDL_UnlockTexture(mTexture);
		mPixels = NULL;
		mPitch = 0;
	}

	return success;
}

void* OTexture::getPixels()
{
	return mPixels;
}

void OTexture::copyPixels(void* pixels)
{
	//Texture is locked
	if (mPixels != NULL)
	{
		//Copy to locked pixels
		memcpy(mPixels, pixels, mPitch * imageHeight);
	}
}

int OTexture::getPitch()
{
	return mPitch;
}

Uint32 OTexture::getPixel32(unsigned int x, unsigned int y)
{
	//Convert the pixels to 32bit
	Uint32 *pixels = (Uint32*)mPixels;

	//Get the pixel requested
	return pixels[(y * (mPitch / 4)) + x];
}

bool OTexture::isEditable()
{
	return mEditabled;
}

void OTexture::setTexture(SDL_Texture* texture)
{
	mTexture = texture;
}

SDL_Texture* OTexture::getTexture()
{
	return mTexture;
}