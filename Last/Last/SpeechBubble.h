#pragma once
#include "Text.h"
#include <memory>

#define s_maxWidth 3
#define s_textSize 10

class SpeechBubble : public Entity
{
public:
	SpeechBubble(const Coordinates& _pos, const string phrase);

private:
	unique_ptr<Text> m_text;

	// Initialise the text object
	void InitText(const string phrase);
};

