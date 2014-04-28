#pragma once
#include "EntityContainer.h"
#include "Environment.h"

// Contains all of the entities, via the Player and Environment Entities
class AllContainer : public EntityContainer
{
	// Try to center the camera on the player, if doing so would not reveal the edges of the environment
	void CenterOnPlayer(void);

	// Return, for each direction, whether or not this position exposes the unrendered edge of the world
	Directions<bool> GetEdgeBools() { return GetEdgeBools(g_environment->getBlittingPos()); }

	// Return, for each direction, whether or not a given position will expose the unrendered edge of the world
	Directions<bool> GetEdgeBools(XY _pos);

	bool MovingIntoEdges(void);

public:
	AllContainer(void);
	~AllContainer(void);

	// Change the x and y, so that the player is in the center of the screen.
	void update(int delta);
};

extern AllContainer* g_all;