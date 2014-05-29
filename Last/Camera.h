#pragma once
#include "Environment.h"
#include "EntityContainer.h"

// Contains all of the entities, via the Player and Environment Entities
class Camera : public EntityContainer
{
public:
	Camera(void);
	~Camera(void);

	void InitChildren(void);

	// Zoom to a level that fits the given width, in terms of tiles
	void ZoomToWidth(const int width);

protected:
	// Change the x and y, so that the player is in the center of the screen.
	void E_Update(const int delta);
	void E_Render(void);

private:
	// Try to center the camera on the player, if doing so would not reveal the edges of the environment
	void CenterOnPlayer(void);
	
	// Return, for each direction, whether or not this position exposes the unrendered edge of the world
	Directions<bool> GetEdgeBools() const { return GetEdgeBools(g_environment->GetAbsolutePos()); }

	// Return, for each direction, whether or not a given position will expose the unrendered edge of the world
	Directions<bool> GetEdgeBools(Coordinates _pos) const;
};

extern Camera* g_camera;