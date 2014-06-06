#include "MenuItem.h"
#include "ToolKit.h"

TTF_Font* MenuItem::s_font = TTF_OpenFont( "joystix monospace.ttf", 28 );

MenuItem::MenuItem(const Coordinates& _pos, const string& text) 
	: Button(_pos, ComputeBoundingBox(text)), m_text(text)
{
	// Create this graphic's text from the text argument.
	SDL_Color white = { 255, 255, 255 };
	s_font = TTF_OpenFont( "joystix monospace.ttf", 28 );
	m_image = Image(text, s_font, white);
	m_boundingBox = RectFromXY(Coordinates(0), m_image.Size());
}

SDL_Rect MenuItem::ComputeBoundingBox(const string& text)
{
	// Create its size based on the number of characters in the text
	SDL_Rect r_rect = {0, 0,
					   text.size()*10, 32};
	
	return r_rect;
}


void MenuItem::OnHoverOver(void)
{
	printf("Hovering OVER.\n");
	//SetColorModulation(hoverOverColor);
}

void MenuItem::OnHoverOff(void)
{
	printf("Hovering OFF.\n");
	//SetColorModulation(hoverOffColor);
}