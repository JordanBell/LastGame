#include "SoundSource.h"
#include "ToolKit.h"
#include "Camera.h"

SoundSource::SoundSource(Entity* parent) 
	: EntityContainer(Dimensions(200, 200)),
	m_timeoutCountdown(0), 
	m_sourceEntity(parent), 
	m_sourcePos(nullptr)
{
	//m_speechBubble = new SpeechBubble(0);
	//AddChild(m_speechBubble);
}

SoundSource::SoundSource(Coordinates* sourcePos) 
	: EntityContainer(Dimensions(200, 200)),
	m_timeoutCountdown(0), 
	m_sourceEntity(nullptr)
{
	Coordinates normalisedPos = *sourcePos + g_camera->pos;
	m_sourcePos = new Coordinates(normalisedPos);
	//m_speechBubble = new SpeechBubble(0);
	//AddChild(m_speechBubble);
}

void SoundSource::Say(const string phrase, const int timeout)
{
	printf("Traveller says, '%s'.\n", phrase.c_str()); 
	m_timeoutCountdown = timeout;
	
	// Set a speechbubble's text to that of the phrase being said
	//m_speechBubble.SetText(phrase);
}

void SoundSource::E_Update(const int delta)
{
	// Decrement the timeout countdown
	if (m_timeoutCountdown > 0) m_timeoutCountdown--;

	// Follow the source
		 if (m_sourceEntity) pos = m_sourceEntity->pos;
	else if (m_sourcePos)	 pos = *m_sourcePos - g_camera->pos; // Adjust the coordinates based on the camera's position
	else throw runtime_error("A sound source must come from somewhere.");
}

void SoundSource::E_Render(void)
{
	// Only render if the speech is still in effect
	if (m_timeoutCountdown > 0)
	{
		// Render this and the speech
		EntityContainer::E_Render(); 
	}
}

