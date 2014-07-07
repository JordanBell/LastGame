#pragma once
#include "GameState.h"
#include "SpeechBubble.h"
#include "PauseScreen.h"

class Game : public GameState
{	
public:
	Game() 
		: widthCounter(15), isPaused(false), testSpeech(Coordinates(227, 93), "Blah Blah Blah") {}
	//"I know you're expecting something interesting by reading this, but frankly I'm just trying to fit a lot of text in one place."
	
	// Unpause the game, close the pause screen
	void Unpause(void); // Public, so that the menu button, "Resume", can call it.
	
protected:
	// Initialise all of the objects in the game.
	void OnStart();
	// Delete all of the objects in the game.
	void OnEnd();
	
	// Update the entities
	void OnUpdate(const int delta);

	// Render the entities
	void Render(void);
	
	void TogglePause(void);
	// Pause the game, open the pause screen
	void Pause(void);

private:
	PauseScreen* m_pauseScreen;
	bool isPaused;
	int widthCounter; // A counter to keep track of the zoom level, for manual zooming controls
	SpeechBubble testSpeech;

	// Respond to the keystates at this moment
	void OnKeys(const Uint8* keystates); 
	
	// Regulate the framerate, and return the delta time.
	int RegulateFrameRate();


};