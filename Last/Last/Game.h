#pragma once
#include "GameState.h"
#include "PauseScreen.h"

class Game : public GameState
{	
public:
	Game() : widthCounter(16), isPaused(false), m_pauseScreen() {}
	
protected:
	// Initialise all of the objects in the game.
	void OnStart();
	// Delete all of the objects in the game.
	void OnEnd();
	
	// Update the entities
	void OnUpdate(const int delta);

	// Render the entities
	void Render(void);
	
	// Pause the game, open the pause screen
	void Pause(void);
	// Unpause the game, close the pause screen
	void Unpause(void);

private:
	PauseScreen m_pauseScreen;
	bool isPaused;
	int widthCounter; // A counter to keep track of the zoom level, for manual zooming controls

	// Respond to the keystates at this moment
	void OnKeys(const Uint8* keystates); 
	
	// Regulate the framerate, and return the delta time.
	int RegulateFrameRate();


};

extern Game* g_game;