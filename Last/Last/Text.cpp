#include "Text.h"

void Text::SetText(string text)
{
	m_text = text;

	// Update the image with the new info
	UpdateImage();
}

void Text::SetFont(TTF_Font* font)
{
	// Free the old font
	TTF_CloseFont(m_font);
	// Set the new font
	m_font = font;

	// Update the image with the new info
	UpdateImage();
}

void Text::SetColor(SDL_Color color)
{
	m_color = color;

	// Update the image with the new info
	UpdateImage();
}

void Text::SetWrap(int* pixelWrap)
{
	if (m_pixelWrap) delete m_pixelWrap;
	m_pixelWrap = pixelWrap;

	// Update the image with the new info
	UpdateImage();
}