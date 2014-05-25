#pragma once
#include "Entity.h"
#include <list>

class Traveller : public Entity
{
public:
	Traveller(const Coordinates& _pos);
	~Traveller(void) {};

	// Turn to face a direction
	void TurnToFace(const E_Direction& direction);

	// Move one TILE_SIZE in the specified direction
	virtual void Walk(const E_Direction& direction);

	// Return the traveller's direction
	E_Direction& GetDirection(void) { return direction; }

protected:
	float m_speed;
	bool m_moving;
	E_Direction direction;	// The direction being faced by the traveller.

	// Update movement data
	virtual void E_Update(const int delta);

	// Get the Entities in front of the traveller's position
	std::list<Entity*>& GetFrontEntities(Layer layer = BOTTOM_LAYER) const;

	// Get the Entities in front of the traveller's position
	std::list<Entity*>* GetAllFrontEntities(void) const;

private:
	int misalignment; // The tracked difference between the traveller and their last tile-aligned position.

	// Snap the traveller to the grid, or the grid to a TILE_SIZE multiple coordinate.
	void SnapPosition(void);
	
	// Return whether or not the traveller can move forward
	bool CanMoveForward(void) const;
};

