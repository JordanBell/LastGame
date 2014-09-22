#include "KeyTools.h"
#include <iostream>

Uint8* KeyTools::s_keyStates = const_cast<Uint8*>( SDL_GetKeyboardState(nullptr) );
int KeyTools::s_cooldowns[ SDL_NUM_SCANCODES ];

void KeyTools::UpdateStates(void)
{
	s_keyStates = const_cast<Uint8*>( SDL_GetKeyboardState(nullptr) ); 

	// Decrement all cooldowns
	for (int& cooldown : s_cooldowns)
		if (cooldown > 0) cooldown--;
}

bool KeyTools::CheckKeyWithCooldown(Uint8 keyIndex, int newCooldown)
{
	int& cooldown = s_cooldowns[keyIndex]; // The corresponding cooldown value for the key at this index
	bool keyIsDown = s_keyStates[keyIndex];

	if (cooldown <= 0)
	{
		if (keyIsDown)
		{
			// Set a new cooldown when pressed
			cooldown = newCooldown;
		}

		// Return the state of the key
		return keyIsDown;
	}
	else return false;
}