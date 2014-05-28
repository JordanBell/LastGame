#pragma once

/*
A status is a value that the player must manage throughout the game. ie
	* Loneliness
	* Fear
	* Insanity
	* Fatigue
This class handles all components relating to this.
*/
class Status
{
public:
	Status(void) : value(100) {}
	~Status(void);
	
	Status operator+=(int val) { value += val; return *this; }
	Status operator-=(int val) { value -= val; return *this; }

	int GetValue(void) { return value; }

private:
	int value;
};

extern Status* g_fatigue;
extern Status* g_loneliness;
extern Status* g_insanity;
extern Status* g_fear;