#pragma once
#include "Entity.h"
#include <list>
#include <memory>
#include "SoundSource.h" // Include this now, as unique_ptr cannot be applied to an incomplete type

class Traveller : public Entity
{
public:
	Traveller(const Coordinates& _pos);
	~Traveller(void) {};

	// Turn to face a direction (Set Direction)
	void TurnToFace(const E_Direction& direction);

	// Move one TILE_SIZE in the specified direction
	virtual void Walk(const E_Direction& direction);

	// Say something. Creates a speech bubble above the player's head.
	void Say(const string phrase, const bool priorityOverride = false, const int timeout = -1);

	// Return the traveller's direction
	E_Direction& GetDirection(void) { return direction; }

protected:
	int m_stillBuffer; // A number of frames after which the traveller stops animating, if still - prevents animation from snapping to "still" after each TILE_SIZE of movement
	float m_speed;
	bool m_moving;
	bool m_talking; // Is the traveller currently talking?
	unique_ptr<SoundSource> m_soundSource;
	E_Direction direction;	// The direction being faced by the traveller.

	// Update movement data
	virtual void E_Update(const int delta);

	// Render the soundSource and this
	virtual void E_Render(void);

	// Get the Entities in front of the traveller's position
	std::list<Entity*>& GetFrontEntities(Layer layer = BOTTOM_LAYER) const;

	// Get the Entities in front of the traveller's position
	std::list<Entity*>* GetAllFrontEntities(void) const;

	// Update the clip via the assigned animation module
	virtual void UpdateClipFromAnimation(void) { GetImage().SetClip( a_module->GetClip(direction) ); }

private:
	int misalignment; // The tracked difference between the traveller and their last tile-aligned position.

	// Start moving, turn on animation
	void StartMoving(void);

	// Stop moving, turn off animation
	void StopMoving(void);

	// Snap the traveller to the grid, or the grid to a TILE_SIZE multiple coordinate.
	void SnapPosition(void);
	
	// Return whether or not the traveller can move forward
	bool CanMoveForward(void) const;
};

