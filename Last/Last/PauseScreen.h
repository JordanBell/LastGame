#pragma once
#include "entitycontainer.h"

class Game;

class PauseScreen :
	public EntityContainer
{
	friend class Game;

	//ImageTarget m_transparentBlack;

	PauseScreen(void);
	
	// Open this screen
	void Open(void);
	// Close this screen
	void Close(void);
};

