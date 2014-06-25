#pragma once
#include "gamestate.h"
#include "TitleMenuScreen.h"
#include <iostream>

class TitleScreenState : public GameState
{
public:
	TitleScreenState(void) : m_start(false) {}

protected:
	void OnStart(void) override final { m_menuScreen = new TitleMenuScreen(); }
	void OnEnd(void) override final { delete m_menuScreen; }

	void OnKeys(const Uint8* keystates) override final { 
		if (keystates[SDL_SCANCODE_ESCAPE]) m_menuScreen->GoBack(); 
	}

	void OnUpdate(const int delta) override final;
	void Render(void) override final { m_menuScreen->Render(); }

private:
	TitleMenuScreen* m_menuScreen;
	bool m_start;
};

