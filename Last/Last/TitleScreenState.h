#pragma once
#include "gamestate.h"
#include "TitleMenuScreen.h"
#include <iostream>

class TitleScreenState : public GameState
{
public:
	TitleScreenState(void) : m_start(false) {}

protected:
	void OnStart(void) { m_menuScreen = new TitleMenuScreen(); }
	void OnEnd(void) { delete m_menuScreen; }

	void OnUpdate(const int delta);
	void Render(void) { m_menuScreen->Render(); }

private:
	TitleMenuScreen* m_menuScreen;
	bool m_start;
};

