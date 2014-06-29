#pragma once
#include "EntityContainer.h"

/*
A sound source is an entityContainer than manages and handles 
a SpeechBubble. This is instantiates in any other entity that 
may make a sound or say something. This class updates that
SpeechBubble with a position (following a source entity, or
sticking to a world-relative position.
*/
class SoundSource : public EntityContainer
{
public:
	SoundSource(Entity* parent);
	SoundSource(Coordinates* sourcePos); // Note: sourcePos is relative to the camera, not the window.
	
	// Set a new phrase for the speech bubble, and set a new timeout
	void Say(const string phrase, const int timeout = 50);
	void Stop(void) { m_timeoutCountdown = 0; }

	// Return whether or not this source is still making a sound
	bool IsActive(void) { return m_timeoutCountdown > 0; }

protected:
	void E_Update(const int delta) override final;
	void E_Render(void) override final;

private:
	int m_timeoutCountdown; // The number of seconds until the sound disappears.
	Coordinates* m_sourcePos;
	Entity* m_sourceEntity;
};

