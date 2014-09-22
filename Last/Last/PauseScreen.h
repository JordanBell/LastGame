#pragma once
#include "MenuScreen.h"

class Game;

class PauseScreen : public MenuScreen
{
	friend class Game;

	// Construct the pause screen
	PauseScreen(void);

	ImageTarget m_transparentBlack; // A black, transparent background
	bool m_active; // Whether or not this screen is open
	
	// Open this screen
	void Open(void);
	// Close this screen
	void Close(void);

protected:
	void E_Render(void);
};

