#include "PauseScreen.h"
#include "ToolKit.h"

PauseScreen::PauseScreen(void) 
	: EntityContainer(LOGICAL_SIZE)/*, m_transparentBlack(LOGICAL_SIZE, true)*/
{
	// Initialise the transparent background rectangle
	/*SDL_Rect backgroundRect = {0, 0, LOGICAL_SIZE.x, LOGICAL_SIZE.y};
	RenderRectToTexture( m_transparentBlack.GetTexture(),
						 &backgroundRect,
						 0x00, 0x00, 0x00, 0x88);

	m_transparentBlack.SetTarget(&m_imageTarget);*/
}

void PauseScreen::Open(void)
{
	// Make entities visible
}


void PauseScreen::Close(void)
{
	// Hide entities
}
