#include "MenuItem.h"
#include "ToolKit.h"

TTF_Font* MenuItem::s_font = nullptr;

MenuItem::MenuItem(const Coordinates& _pos, const string& text) 
	: 
	Button( _pos, ComputeBoundingBox(text) ),
	m_text(text)
{
	// Create this graphic's text from the text argument.
	if (!s_font) s_font = TTF_OpenFont("joystix monospace.ttf", 28);
	
	// Set the text image
	SDL_Color white = { 255, 255, 255 };
	Image* textImage = new Image( text, s_font, white );
	SetImage( *textImage );

	// Reset the bounding box from the new image
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
	//SetColorModulation(hoverOverColor);
	// Set this item as the selected item
}

void MenuItem::OnHoverOff(void)
{
	//SetColorModulation(hoverOffColor);
}