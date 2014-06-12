#include "TitleScreenState.h"
#include "GameStateManager.h"


void TitleScreenState::OnUpdate(const int delta)
{
	// Update the menus
	m_menuScreen->Update(delta); 

	// When the game is set to start, switch to the main game state
	if (m_start)
		g_manager->SwitchToState(GSID_MAIN);
}
