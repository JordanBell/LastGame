#pragma once
#include "entitycontainer.h"

class Text : public Entity
{
public:
	Text(string text, TTF_Font* font, SDL_Color color) 
		: Entity(Coordinates(0), Coordinates(0), TEXT_FRMT), m_text(text), m_font(font), m_color(color)
	{
		UpdateImage();
	}

	~Text(void) 
	{ TTF_CloseFont(m_font); }
	
	void SetText(string text);
	void SetFont(TTF_Font* font);
	void SetColor(SDL_Color color);


private:
	string m_text;
	TTF_Font* m_font;
	SDL_Color m_color;

	void UpdateImage(void)
	{
		Image* textImage = new Image( m_text, m_font, m_color );
		SetImage( *textImage );
	}
};

class LoadingScreen :
	public EntityContainer
{
public:
	LoadingScreen(void);
	~LoadingScreen(void);
	
	void SetMessage(string message);
	void Add(int val) { 
		m_percentage += val; 
		UpdateLoaderSize(); 
	}
	
	void E_Update(const int delta) override final;
	void E_Render(void) override final;

private:
	static const int m_outlineThickness; // Thickness of the outline on the bar
	static const Dimensions m_barProportion; // The proportion of the screen size that the bar's size takes up

	ImageTarget* m_barGraphic; // The static image behind the growing bar
	ImageTarget* m_barLoader;  // The growing bar
	Dimensions m_loaderSize;
	Dimensions m_barSize;
	Dimensions m_barPos;
	int m_percentage;
	Text* m_text;
	
	void InitBar(void);
	void InitText(void);

	// Visibly updates the size of the loader bar based on the percentage
	void UpdateLoaderSize(void);
};
