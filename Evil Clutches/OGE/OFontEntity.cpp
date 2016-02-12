#include "OFontEntity.h"

std::vector<OFontEntity*> OFontEntity::sFontEntityList;

OFontEntity::OFontEntity()
{
	fontTexture = new OTexture();

	font = NULL;

	demensions = { 0,0,0,0 };

	sFontEntityList.push_back(this);
}

OFontEntity::~OFontEntity()
{ //Pure Virtual
}

bool OFontEntity::onLoad(const char* ttf_file, int font_size, SDL_Color font_color, int wrapLength)
{
	//Set font's renderer
	fontTexture->setRenderer(OWindow::sGameWindow.getRenderer());
	//Check to see if font is already loaded if so unload to load in new font
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}

	color = &font_color;
	size = font_size;
	font = TTF_OpenFont(ttf_file, font_size);
	if (!font)
	{
		SDL_Log("Failed to load font %s! SDL_ttf Error: %s\n", ttf_file, TTF_GetError());
		return false;
	}

	if (wrapLength > 0)
	{
		lineWidth = wrapLength;
		lineWrap = true;
	}
	else
	{
		lineWrap = false;
	}

	return true;
}

void OFontEntity::onLoop()
{
	if (font == NULL || text.empty()) return;

	//Get rid of preexisting texture
	fontTexture->free();

	SDL_Surface* textSurface;

	//Render text surface
	if (lineWrap) textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), *color, lineWidth);
	else textSurface = TTF_RenderText_Solid(font, text.c_str(), *color);

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		fontTexture->setTexture(SDL_CreateTextureFromSurface(fontTexture->getRenderer(), textSurface));
		if (fontTexture->getTexture() == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			fontTexture->setWidth(demensions.w = textSurface->w);
			fontTexture->setHeight(demensions.h = textSurface->h);
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
}

void OFontEntity::onRender()
{
	if (fontTexture == NULL || text.empty()) { return; }

	fontTexture->render(demensions.x, demensions.y);
}

void OFontEntity::onCleanup()
{
	fontTexture->free();
	fontTexture = NULL;

	TTF_CloseFont(font);
	font = NULL;
}

SDL_Rect* OFontEntity::getDemensions()
{
	return &demensions;
}

void OFontEntity::setText(std::string text)
{
	this->text = text;
}