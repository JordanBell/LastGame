#pragma once
#include "entity.h"

class Text : public Entity
{
public:
	Text(string text, TTF_Font* font, SDL_Color color, int* pixelWrap = nullptr) 
		: Entity(Coordinates(0), Coordinates(0), TEXT_FRMT), 
		m_text(text), 
		m_font(font), 
		m_color(color),
		m_pixelWrap(pixelWrap)
	{ UpdateImage(); }

	~Text(void) { TTF_CloseFont(m_font); }
	
	void SetText(string text);
	void SetFont(TTF_Font* font);
	void SetColor(SDL_Color color);
	void SetWrap(int* pixelWrap);

private:
	string	  m_text;
	TTF_Font* m_font;
	SDL_Color m_color;
	int* m_pixelWrap;

	void UpdateImage(void)
	{
		Image* textImage = new Image( m_text, m_font, m_color, m_pixelWrap );
		SetImage( *textImage );
	}
};

