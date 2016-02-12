#ifndef _OGE_FONT_ENTITY_H_
#define _OGE_FONT_ENTITY_H_

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

#include "OWindow.h"
#include "OTexture.h"

class OFontEntity
{
public:

	static std::vector<OFontEntity*> sFontEntityList;

	OFontEntity();
	virtual ~OFontEntity();

	virtual bool onLoad(const char* ttf_file, int font_size = 18, SDL_Color font_color = { 255,255,255 }, int wrapLength = 0);
	virtual void onLoop();
	virtual void onRender();
	virtual void onCleanup();

	SDL_Rect* getDemensions();

	void setText(std::string text);

protected:

	OTexture* fontTexture;
	TTF_Font* font;
	SDL_Color* color;
	std::string text;
	int size;
	SDL_Rect demensions;

private:

	int lineWidth;
	bool lineWrap;

};
#endif // !_OGE_FONT_ENTITY_H_
