#ifndef player_h
#define player_h

#include "Traveller.h"
#include "Config.h"
#include <list>

using namespace std;

class Player : public Traveller {
public:	
	Player(Coordinates _pos) 
		: Traveller(_pos), inputBuffer(0), m_newPosRecently(false), m_frontInteractable(false)
	{ m_speed = PLAYER_SPEED; SetFormat(EntityFormat(PLAYER_FRMT)); }
	
	// Update the player's data
	void E_Update(const int delta) override final;
	
	// Interact with the object in front of the player
	void Interact(void) const;

	// Attempt to walk in a direction
	void Walk(const E_Direction& direction) override final;

private:
	int inputBuffer; // Frames until input is reenabled. Input is enabled when inputBuffer == 0.
	bool m_newPosRecently; // Has the position recently been changed?
	bool m_frontInteractable; // Is there an interactable object in front of the player?

	// Compute and set m_frontInteractable, which indicates whether or not an object in front of the player is interactable.
	void Compute_FrontInteractable(void);
};

extern Player* g_player;

#endif