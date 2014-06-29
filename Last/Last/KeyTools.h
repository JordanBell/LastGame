#pragma once
#include "SDL.h"

class KeyTools
{
public:
	// Normal key state checking, including a per-key cooldown period after being pressed.
	static bool CheckKeyWithCooldown(Uint8 keyIndex) { return CheckKeyWithCooldown(keyIndex, s_defaultCooldown); }
	static bool CheckKeyWithCooldown(Uint8 keyIndex, int cooldown);

	// Update the static keystate values
	static void UpdateStates(void);

private:
	// Remove the possibility of instantiating an object
	KeyTools(void) {}
	~KeyTools(void) {}

	// Make an array of corresponding cooldowns for each key
	static const int s_defaultCooldown = 10;
	//static int s_cooldowns[sizeof( SDL_GetKeyboardState(nullptr) )];
	static int s_cooldowns[];
	static Uint8* s_keyStates;
};

