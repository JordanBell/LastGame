#pragma once
#include "Environment.h"
#include "EntityContainer.h"

// Contains all of the Environment, and controls the uniform position on the screen
class Camera : public EntityContainer
{
public:
	Camera(void) 
		: EntityContainer(WORLD_DIMENSIONS * TILE_SIZE), defaultZoom( g_renderer->GetScale() ) { m_zoom = defaultZoom; }

	void InitChildren(void);

	//// Return the portion of this image that is visible on the window.
	//SDL_Rect GetViewingRect(void) const { return RectFromXY(pos*-1, LOGICAL_SIZE); }

	// Set a level of zoom, that fits the given width, in terms of tiles. Returns whether or not this was successful.
	bool ZoomToWidth(const int width);

protected:
	// Change the x and y, so that the player is in the center of the screen.
	void E_Update(const int delta);

	void E_Render(void);

private:
	// The zoom ratio set to the renderer while rendering the camera.
	float m_zoom;
	float defaultZoom;

	// Try to center the camera on the player, if doing so would not reveal the edges of the environment
	void CenterOnPlayer(void);
	
	// Return, for each direction, whether or not this position exposes the unrendered edge of the world
	Directions<bool> GetEdgeBools() const { return GetEdgeBools(g_environment->GetAbsolutePos()); }

	// Return, for each direction, whether or not a given position will expose the unrendered edge of the world
	Directions<bool> GetEdgeBools(Coordinates _pos) const;
};

extern Camera* g_camera;