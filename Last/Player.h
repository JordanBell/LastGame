#ifndef player_h
#define player_h

#include "Traveller.h"
#include "Config.h"
#include <list>

using namespace std;

class Player : public Traveller {
public:	
	Player(Coordinates _pos) : Traveller(_pos), inputBuffer(0) { m_speed = PLAYER_SPEED; OverrideFormat(PLAYER_FRMT); }
	
	// Update the player's data
	void E_Update(const int delta);
	
	// Interact with the object in front of the player
	void Interact(void) const;

	virtual void Walk(const E_Direction& direction);

private:
	int inputBuffer; // Frames until input is reenabled. Input is enabled when inputBuffer == 0.
};

// A global player object
extern Player* g_player;

#endif