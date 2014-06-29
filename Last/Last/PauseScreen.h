#pragma once
#include "MenuScreen.h"

class Game;

class PauseScreen : public MenuScreen
{
	friend class Game;

	// Construct the pause screen
	PauseScreen(Game* game);

	ImageTarget m_transparentBlack; // A black, transparent background
	bool m_active; // Whether or not this screen is open
	
	// Open this screen
	void Open(void);
	// Close this screen
	void Close(void);

	// Return whether or not this menu is at the root (first) menu
	bool IsAtRootMenu(void);

protected:
	void E_Render(void);
};

