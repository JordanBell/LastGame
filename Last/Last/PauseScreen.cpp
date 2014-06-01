#include "PauseScreen.h"
#include "ToolKit.h"

PauseScreen::PauseScreen(void) 
	: EntityContainer(LOGICAL_SIZE), m_transparentBlack(LOGICAL_SIZE, true), m_active(false)
{
	// Initialise the semi-transparent background rectangle
	SDL_Rect backgroundRect = {0, 0, LOGICAL_SIZE.x, LOGICAL_SIZE.y};
	RenderRectToTexture( m_transparentBlack.GetTexture(),
						 &backgroundRect,
						 0x00, 0x00, 0x00, 0xEE);

	m_transparentBlack.SetTarget(&m_imageTarget);
}


void PauseScreen::Open(void)
{
	// Make entities visible
	m_active = true;
}


void PauseScreen::Close(void)
{
	// Hide entities
	m_active = false;
}

void PauseScreen::E_Render(void)
{
	if (m_active)
	{
		// Render background texture
		m_transparentBlack.RenderToTarget(Coordinates(0));

		// Render entities
		EntityContainer::E_Render();
	}
}
