#include "GameState.h"
#include "ToolKit.h"

void GameState::OnRender(void)
{
	//Clear screen
	ClearWindow();

	Render();

	// Update the screen
	UpdateWindow();
}
