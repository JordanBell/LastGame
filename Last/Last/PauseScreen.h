#pragma once
#include "entitycontainer.h"
#include "Tiles.h"

class Game;

class PauseScreen :
	public EntityContainer
{
	friend class Game;

	ImageTarget m_transparentBlack;
	bool m_active;

	PauseScreen(void);

	
	// Open this screen
	void Open(void);
	// Close this screen
	void Close(void);

protected:
	void E_Render(void);
};

