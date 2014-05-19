#pragma once
#include "Entity.h"
#include <list>
#include "GridTiles.h"

class Traveller : public Entity
{
public:
	Traveller(const XY& _pos);
	~Traveller(void);

	// Turn to face a direction
	void TurnToFace(const E_Direction& direction);

	// Move one TILE_SIZE in the specified direction
	void Walk(const E_Direction& direction);

	// Return the traveller's direction
	E_Direction& GetDirection(void) { return direction; }

protected:
	float m_speed;
	bool m_moving;
	E_Direction direction;	// The direction being faced by the traveller.

	// Update movement data
	void E_Update(const int delta);

	// Get the GridTile object in front of the traveller's position
	std::list<TileEntity*>& GetFrontTiles(bool top = false) const;

private:
	int misalignment; // The tracked difference between the traveller and their last tile-aligned position.

	// Snap the traveller to the grid, or the grid to a TILE_SIZE multiple coordinate.
	void SnapPosition(void);
	
	// Return whether or not the traveller can move forward
	bool CanMoveForward(void) const;
};

