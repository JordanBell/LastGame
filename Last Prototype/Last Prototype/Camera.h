#pragma once
#include "EntityContainer.h"
#include "Environment.h"

// Contains all of the entities, via the Player and Environment Entities
class Camera : public EntityContainer
{
	// Try to center the camera on the player, if doing so would not reveal the edges of the environment
	void CenterOnPlayer(void);

	// Return, for each direction, whether or not this position exposes the unrendered edge of the world
	Directions<bool> GetEdgeBools() const { return GetEdgeBools(g_environment->getBlittingPos()); }

	// Return, for each direction, whether or not a given position will expose the unrendered edge of the world
	Directions<bool> GetEdgeBools(XY _pos) const;

	// Zoom the camera in
	void ZoomToWidth(const int width);

public:
	Camera(void);
	~Camera(void);

	// Change the x and y, so that the player is in the center of the screen.
	void update(const int delta);
	void render(void);
};

extern Camera* g_camera;