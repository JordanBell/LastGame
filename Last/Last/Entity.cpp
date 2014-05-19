#include "Entity.h"
#include "Player.h" // For recognizing self as g_player

Entity::Entity(const XY& _pos,
		   const XY& blitOffset,
		   int spriteSheetID,
		   EntityFormat format,	
		   SDL_Rect* clip,
		   AnimationModule* personalisedAnimationModule) 
		   : m_format(format), m_clip(clip), a_module(personalisedAnimationModule), parent(NULL)
{
	// If GridDependent, take _pos as a grid position
	pos = (m_format[GRID_INDEPENDENT]) ? _pos : _pos*TILE_SIZE;

	/** Check format dependancies **/
	// ANIMATION
	if (format[ANIMATED] && !a_module) throw ModuleMisuseException("Animated Entities must be initialised with an Animation Module.");
	if (!format[ANIMATED] && a_module) throw ModuleMisuseException("You cannot pass an Animation Module to a non-animated Entity.");

	InitSpriteSheet(spriteSheetID);
	InitImageTexture(); 
}	

Entity::~Entity(void)
{
	SDL_FreeSurface(m_spriteSheet);
	SDL_DestroyTexture(m_image);
	delete a_module;
}

void Entity::InitSpriteSheet(int ssid)
{
	// Set the sprite sheet from the SpriteSheetID
	switch (ssid)
	{
	case SSID_ENVIRONMENT:
		m_spriteSheet = Resources::GetEnvironmentImage();
		break;
	case SSID_PLAYER:
		m_spriteSheet = Resources::GetPlayerImage();
		break;
	case SSID_DOOR:
		m_spriteSheet = Resources::GetDoorImage();
		break;
	default:
		throw ModuleMisuseException("SSID not recognised during Entity construction.");
	}
}

void Entity::InitImageTexture(void)
{
	if (m_format[ANIMATED])
	{
		// Just create the texture from the surface
		m_image = SDL_CreateTextureFromSurface(g_renderer, m_spriteSheet);
	}
	else // If this is not animated, it will save time to just take the clipping now, and set the clip to null to prevent clipping every frame
	{
		// Create a surface to hold the clipped image
		SDL_Surface* clippedImage = SDL_CreateRGBSurface(SDL_SWSURFACE, m_clip->w, m_clip->h, 0, 0, 0, 0, 0);
		// Clip the image onto the surface
		SurfaceToSurface(XY(0, 0), m_spriteSheet, clippedImage, m_clip);

		// Create the image from the clipped surface
		m_image = SDL_CreateTextureFromSurface(g_renderer, clippedImage);

		// Free the surface
		SDL_FreeSurface(clippedImage);
		// Set the clip to NULL, to prevent clipping every frame.
		m_clip = NULL;
	}
}

void Entity::Blit()
{
	XY blitPos = GetBlittingPos();
	RenderTexture(blitPos, m_image, m_clip);
}

XY Entity::GetAbsolutePos(void) const
{
	if (parent == NULL) return pos;
	else
	{
		// Add the parent's blitting x to this one
		return pos + parent->GetAbsolutePos();
	}
}

XY Entity::GetGridPosition(const XY& _pos)
{
	XY r_gridPosition = _pos;

	// Round to the nearest multiple of TILE_SIZE
	r_gridPosition /= (float)TILE_SIZE;
	r_gridPosition.RoundToNearest();

	return r_gridPosition;
}

bool Entity::IsInSight(void) const
{
	if (this != g_player)
	{
		if (g_player != NULL)
		{
			XY distsFromPlayer = g_player->pos - GetBlittingPos();
			int manDist = distsFromPlayer.manhatten() / TILE_SIZE;

			// Return whether this is within sight distance of the player
			return (manDist <= SIGHT_DISTANCE);
		}
	}
	
	return true;
}

bool Entity::IsOnScreen(void) const
{
	const XY blittingPos = GetBlittingPos();
	const XY dimensions = (m_clip) ?
						  XY(m_clip->h, m_clip->w) :
						  XY(m_spriteSheet->h, m_spriteSheet->w);

	const Directions<float>entityEdges(blittingPos.y,
									   blittingPos.y + dimensions.x,
									   blittingPos.x,
									   blittingPos.x + dimensions.y);

	// Return whether or not any of the edges peek over the screen
	return ((entityEdges.top	< g_windowSurface->h) &&
			(entityEdges.left	< g_windowSurface->w) &&
			(entityEdges.bottom > 0)		 &&
			(entityEdges.right	> 0));
}

bool Entity::ShouldRenderImage(void) const
{
	if (IsOnScreen()) 
	{
		if (LIMIT_RENDER_BY_SIGHT) { 
			if (IsInSight()) return true; 
		}
		else return true;
	}

	return false;
}

/**** CHECKED DELEGATION FUNCTIONS ****/

void Entity::Update(const int delta)
{ 
	if (m_format[UPDATES]) 
		E_Update(delta);
}

void Entity::Render(void)
{ 
	// Update animation information prior to rendering.
	if (m_format[ANIMATED])
	{
		if (a_module) 
		{ 
			a_module->UpdateModule(); 
			m_clip = a_module->GetClip();
		}
	}

	// Make visible if deemed necessary
	if (ShouldRenderImage()) Render();
}

void Entity::OnInteract(void)
{
	if (m_format[INTERACTABLE]) 
		E_OnInteract();
}

bool Entity::CanMoveThrough(void)
{
	if (m_format[TANGIBLE])
		return E_CanMoveThrough(); // Let the implementation decide
	else
		return true;
}