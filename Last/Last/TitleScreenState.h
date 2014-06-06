#pragma once
#include "gamestate.h"
#include "TitleMenuScreen.h"
#include <iostream>

class TitleScreenState : public GameState
{
public:
	TitleScreenState(void) : m_start(false) {}

protected:
	void OnStart(void) { printf("Press ENTER to begin.\n"); }
	void OnEnd(void) {}

	void OnUpdate(const int delta);
	void Render(void) { m_menuScreen.Render(); }

	void OnKeys(const Uint8* keystates) { if (keystates[SDL_SCANCODE_RETURN]) m_start = true; }

private:
	TitleMenuScreen m_menuScreen;
	bool m_start;
};

