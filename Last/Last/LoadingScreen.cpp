#include "LoadingScreen.h"
#include "ToolKit.h"
#include "Text.h"

const Dimensions LoadingScreen::m_barProportion = Dimensions(0.6, 0.1);
const int LoadingScreen::m_outlineThickness = 4;

LoadingScreen::LoadingScreen(void) : EntityContainer(GetLogicalSize()), m_percentage(0)
{
	// Calculate the bar size based on the const proportions set
	m_barSize = m_barProportion * GetLogicalSize();
	// Place the bar in the center of the screen
	m_barPos = ScreenCenter() - (m_barSize / 2);
	//m_barPos.y *= 1.1;

	InitBar();
	InitText();
}

LoadingScreen::~LoadingScreen(void)
{
	delete m_barGraphic;
	delete m_barLoader;
}

void LoadingScreen::InitBar(void)
{
	m_barGraphic = new ImageTarget(m_barSize, true);

	// Draw the bar outline
	SDL_Rect outlineRect = RectFromXY(0, m_barSize);
	RenderRectToTexture( m_barGraphic->GetTexture(),
						 &outlineRect,
						 0xFF, 0xFF, 0xFF, 0xFF); // Outline Color

	// Draw the bar filler
	SDL_Rect fillerRect = RectFromXY(m_outlineThickness, m_barSize - (2 * m_outlineThickness));
	RenderRectToTexture( m_barGraphic->GetTexture(),
						 &fillerRect,
						 0x22, 0x22, 0x22, 0xFF); // Filler Color
	
	m_barGraphic->SetTarget(&m_imageTarget);

	// Initialise the loader bar 
	m_barLoader = new ImageTarget(m_barSize - (2 * m_outlineThickness), false);
	UpdateLoaderSize();
	m_barLoader->SetTarget(&m_imageTarget);
}

void LoadingScreen::InitText(void)
{
	// Initialise text
	TTF_Font* textFont = TTF_OpenFont("joystix monospace.ttf", 12);
	SDL_Color textColor = {200, 200, 200}; // White-ish
	m_text = new Text("Loading...", textFont, textColor);

	// Place the text right below the bar, center horizontally.
	int textWidth = m_text->GetImage().Size().x; // For centering
	m_text->pos = Coordinates(ScreenCenter().x -  - (textWidth / 2), 
							  m_barPos.y + m_barSize.y + 4);
	
	AddChild(m_text);
}

void LoadingScreen::SetMessage(string message) 
{ 
	m_text->SetText(message); 

	// Place the text right below the bar, center horizontally.
	m_text->CenterAround(ScreenCenter(), true, false); // Center X	
}

void LoadingScreen::UpdateLoaderSize()
{
	// Determine the size of the loader
	m_loaderSize = m_barSize - (2 * m_outlineThickness);

	// Calculate new width based on percentage
	m_loaderSize.x *= float(m_percentage) / 100;
}

void LoadingScreen::E_Update(const int delta)
{
	UpdateLoaderSize();

	EntityContainer::E_Update(delta);
}


void LoadingScreen::E_Render(void)
{
	// Render rect to dynamic barLoader target
	SDL_Rect loaderRect = RectFromXY(0, m_loaderSize);
	RenderRectToTexture( m_barLoader->GetTexture(),
						 &loaderRect,
						 0xFF, 0xFF, 0xFF, 0xFF); // Loader Color

	// Note: Render images to (0, 0), as the rects rendered within them are placed at the correct coordinates
	m_barGraphic->RenderToTarget( m_barPos );
	m_barLoader->RenderToTarget( m_barPos + m_outlineThickness );

	EntityContainer::E_Render();
}